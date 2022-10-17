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
    return CPU::switch_context(prev->_context, next->_context);
}

void Thread::thread_exit (int exit_code)
{
    if (_context) {
        Thread::_ready.remove(&(this->_link));
        this->_state = FINISHING;
        delete _context;
        total_threads--;
        db<Thread>(INF) << "thread " << this->id() << " exit com sucesso\n";
    } else {
        db<Thread>(ERR) << "thread " << this->id() << " exit falhou\n";
    }
}

void Thread::init(void (*main)(void *))
{
    Thread::_main = new Thread(main);
    Thread::_main_context = Thread::_main._context;
    Thread::_dispatcher =  new Thread(Thread::dispatcher());
    Thread::_running = &_main;
    Thread::_main._state = RUNNING;
    Thread::switch_context(this, Thread::_main);
}

void Thread::dispatcher() {
    //imprima informação usando o debug em nível TRC
    db<Thread>(TRC) << "Thread " << _dispatcher._id << " criada\n";
    Ordered_List<Thread>::Element * main_element = Thread::_ready.head();

    //enquanto existir thread do usuário
    while (Thread::_ready.size() >= 2) {
        // Como o main é o primeiro elemento sempre, e o dispatcher não está na fila ainda
        // Então o segundo elemento é sempre a thread de usuário de maior prioridade
        Ordered_List<Thread>::Element * next_element = Thread::_ready.remove(main_element->next());
        //atualiza o status da própria thread dispatacher para READY e reinsire a mesma em _ready
        _dispatcher._state = READY;
        Thread::_ready.insert(&(_dispatcher._link));
        //atualiza o ponteiro _running para apontar para a próxima thread a ser executada
        Thread::_running = next_element->object();
        //atualiza o estado da próxima thread a ser executada
        next_element->object()->_state = RUNNING;
        //troca o contexto entre as duas threads
        Thread::switch_context(_dispatcher, next_element->object());
        //testa se o estado da próxima thread é FINISHNING e caso afirmativo a remova de _ready
        if (next_element->object()->_state == FINISHING) {
            Thread::_ready.remove(&next_element);
        }
    }
    //muda o estado da thread dispatcher para FINISHING
    _dispatcher._state = FINISHING;

    //remova a thread dispatcher da fila de prontos
    Thread::_ready.remove(_dispatcher._link);

    //troque o contexto da thread dispatcher para main
    Thread::switch_context(&_dispatcher, &_main);
}

void Thread::yield() {
    // Adicionar debug TRC
    
    if (_running->_state != FINISHING or _running != &_main) {
        int now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        _running->_link.rank(now);
    }

    _running->_state = READY;
    _ready.insert(&(_running->_link));

    Thread * prev_running;
    _running = &_dispatcher;

    _running->_state = RUNNING;
    _ready.remove(&(_running->_link));

    switch_context(prev_running, _running);
}

__END_API