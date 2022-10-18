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
        _running = next;
        return CPU::switch_context(prev->context(), next->context());
    }

    return 0;
}

void Thread::thread_exit (int exit_code)
{
    this->_state = FINISHING;
    switch_context(this, &_main);
    db<Thread>(INF) << "thread " << this->id() << " exit com sucesso\n";
} 

Thread::~Thread() {

    if (_context) {
        delete _context;
        total_threads--;
        db<Thread>(INF) << "thread " << this->id() << " e seu contexto deletados com sucesso\n";
    } else {
        db<Thread>(ERR) << "o contexto da thread " << this->id() << "já foi deletado\n";
    }
}

void Thread::init(void (*main)(void *))
{
    _main = * (new Thread(main, (void *)("main")));
    _main_context = CPU::Context();
    _dispatcher = * (new Thread(dispatcher));
    _running = &_main;
    _main._state = RUNNING;
    CPU::switch_context(&_main_context, _main.context());
}

void Thread::dispatcher() {
    //imprima informação usando o debug em nível TRC
    db<Thread>(TRC) << "Thread dispatcher " << _dispatcher._id << " criada\n";
    Ordered_List<Thread>::Element * main_element = Thread::_ready.head();

    int user_threads = total_threads - 1;
    //enquanto existir thread do usuário
    while (user_threads > 0) {
        db<Thread>(TRC) << "ID do head: " << Thread::_ready.head()->object()->_id << "\n";
        db<Thread>(TRC) << "ID do next: " << Thread::_ready.head()->next()->object()->_id << "\n";
        db<Thread>(TRC) << "Tamanho da lista: " << Thread::_ready.size() << "\n";
        // Como o main é o primeiro elemento sempre, e o dispatcher não está na fila ainda
        // Então o segundo elemento é sempre a thread de usuário de maior prioridade

        Ordered_List<Thread>::Element * next_element = main_element->next();
        if (next_element->object()->_id == _main._id){
            next_element = next_element->next();
        }
        Thread::_ready.remove(next_element);
        db<Thread>(TRC) << "ID do next_element: " << next_element->object()->_id << "\n";
        //atualiza o status da própria thread dispatacher para READY e reinsire a mesma em _ready
        Thread::_dispatcher._state = READY;
        Thread::_ready.insert_tail(&(_dispatcher._link));
        //atualiza o ponteiro _running para apontar para a próxima thread a ser executada
        Thread::_running = next_element->object();
        //atualiza o estado da próxima thread a ser executada
        next_element->object()->_state = RUNNING;
        //troca o contexto entre as duas threads
        Thread::switch_context(&_dispatcher, next_element->object());
        //testa se o estado da próxima thread é FINISHNING e caso afirmativo a remova de _ready
        if (next_element->object()->_state == FINISHING) {
            Thread::_ready.remove(next_element);
            user_threads--;
        }
    }
    //muda o estado da thread dispatcher para FINISHING
    Thread::_dispatcher._state = FINISHING;

    //remova a thread dispatcher da fila de prontos
    Thread::_ready.remove(&(_dispatcher._link));

    //troque o contexto da thread dispatcher para main
    Thread::switch_context(&_dispatcher, &_main);
}

void Thread::yield() {
    db<Thread>(TRC) << "Método yield chamado\n";
    
    //Ordered_List<Thread>::Element * next_element = Thread::_ready.remove();
    
    if (_running->_state != FINISHING && _running != &_main) {
        int now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        _running->_link.rank(now);
        _running->_state = READY;
        _ready.insert(&(_running->_link));
    } 

    Thread * prev_running = _running;

    _running = &_dispatcher;

    _running->_state = RUNNING;
    _ready.remove(&(_running->_link));

    db<Thread>(TRC) << "Método yield finalizado\n";
    switch_context(prev_running, _running);
}

__END_API