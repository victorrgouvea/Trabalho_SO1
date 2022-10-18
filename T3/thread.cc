#include "thread.h"
#include "list.h"
#include <iostream>


__BEGIN_API

// Inicializando o atributos estáticos da classe Thread
int Thread::total_threads = 0;
Thread * Thread::_running = nullptr;
Thread Thread::_main;
CPU::Context Thread::_main_context;
Thread Thread::_dispatcher;
Ordered_List<Thread> Thread::_ready;

int Thread::switch_context(Thread * prev, Thread * next)
{
    if (prev->id() != next->id()) {
        db<Thread>(INF) << "Contexto trocado entre: " << prev->id() << " e " << next->id() << "\n";
        return CPU::switch_context(prev->context(), next->context());
    }

    return 0;
}

void Thread::thread_exit (int exit_code)
{
    db<Thread>(INF) << "Thread " << this->id() << " exit chamado\n";
    _state = FINISHING;
    total_threads--;
    Thread::yield();
} 

Thread::~Thread() {

    if (_context) {
        delete _context;
        db<Thread>(INF) << "thread " << this->id() << " e seu contexto deletados com sucesso\n";
    } else {
        db<Thread>(ERR) << "o contexto da thread " << this->id() << "já foi deletado\n";
    }
}

void Thread::init(void (*main)(void *))
{
    new (&_main) Thread(main, (void *)("main"));
    db<Thread>(INF) << "Id da thread main = " << _main.id() << "\n";
    new (&_main_context) CPU::Context();
    new (&_dispatcher) Thread(dispatcher);
    db<Thread>(INF) << "Id da thread dispatcher = " << _dispatcher.id() << "\n";
    _running = &_main;
    _main._state = RUNNING;
    CPU::switch_context(&_main_context, _main.context());
}

void Thread::dispatcher() {  
    //enquanto existir thread do usuário
    while (total_threads > 2) {
        db<Thread>(TRC) << "ID do head: " << Thread::_ready.head()->object()->_id << "\n";
        // Remove o próximo element a ser executada da lista de prontos
        Ordered_List<Thread>::Element * next_element = _ready.remove();

        //atualiza o status da própria thread dispatacher para READY e reinsire a mesma em _ready
        Thread::_dispatcher._state = READY;
        Thread::_ready.insert(&(_dispatcher._link));

        //atualiza o ponteiro _running para apontar para a próxima thread a ser executada
        Thread::_running = next_element->object();

        //atualiza o estado da próxima thread a ser executada
        next_element->object()->_state = RUNNING;

        //troca o contexto entre as duas threads
        Thread::switch_context(&_dispatcher, next_element->object());

        //testa se o estado da próxima thread é FINISHNING e caso afirmativo a remova de _ready
        if (next_element->object()->_state == FINISHING) {
            Thread::_ready.remove(next_element->object());
        }
    }
    //muda o estado da thread dispatcher para FINISHING
    Thread::_dispatcher._state = FINISHING;

    //remova a thread dispatcher da fila de prontos
    Thread::_ready.remove(_dispatcher._link.object());

    //troque o contexto da thread dispatcher para main
    Thread::switch_context(&_dispatcher, &_main);
}

void Thread::yield() {
    // Salva a thread que chamou o yield
    Thread * prev_running = _running;

    // Prepara para passar o controle ao dispatcher
    _ready.remove(_dispatcher._link.object());
    _running = &_dispatcher;
    _running->_state = RUNNING;

    db<Thread>(TRC) << "Método yield chamado por "<< prev_running->id() << "\n";
    //Caso seja o main ou uma thread que terminou, não insere na lista de prontos nem atualiza a prioridade
    if (prev_running->_state != FINISHING && prev_running != &_main) {
        int now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        prev_running->_link.rank(now);
        prev_running->_state = READY;
        _ready.insert(&(prev_running->_link));
    } 

    db<Thread>(TRC) << "Método yield finalizado, retornando contexto para o dispatcher\n";
    switch_context(prev_running, _running);
}

__END_API