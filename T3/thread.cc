#include "thread.h"
#include <iostream>


__BEGIN_API

// Inicializando o atributos estáticos da classe Thread
int Thread::total_threads = 0;
Thread * Thread::_running = nullptr;

int Thread::switch_context(Thread * prev, Thread * next)
{
    return CPU::switch_context(prev->context(), next->context());
}

void Thread::thread_exit (int exit_code)
{
    if (_context) {
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
    Thread::_main_context = Thread::_main->_context;
    Thread::_dispatcher =  new Thread(Thread::dispatcher());
    Thread::_running = Thread::_main;
    Thread::_main->state = RUNNING;
    Thread::switch_context(this, Thread::_main);
}

void Thread::dispatcher() {
    //imprima informação usando o debug em nível TRC
    db<Thread>(TRC) << "Thread " << this->_id << " criada\n";
    main_element = Thread::_ready::head();

    //enquanto existir thread do usuário
    while (Thread::_ready::size() >= 2) {
        // Como o main é o primeiro elemento sempre, e o dispatcher não está na fila ainda
        // Então o segundo elemento é sempre a thread de usuário de maior prioridade
        next = Thread::_ready::remove(main_element->next());
        //atualiza o status da própria thread dispatacher para READY e reinsire a mesma em _ready
        this->_state = READY;
        Thread::_ready::insert(this->_link);
        //atualiza o ponteiro _running para apontar para a próxima thread a ser executada
        Thread::_running = next->_object;
        //atualiza o estado da próxima thread a ser executada
        next->_object->_state = RUNNING;
        //troca o contexto entre as duas threads
        Thread::switch_context(this, next->_object);
        //testa se o estado da próxima thread é FINISHNING e caso afirmativo a remova de _ready
        if (next->_object->_state == FINISHING) {
            Thread::_ready::remove(next);
        }
    }
    //muda o estado da thread dispatcher para FINISHING
    this->_state = FINISHING;

    //remova a thread dispatcher da fila de prontos
    Thread::_ready::remove(this->_link);

    //troque o contexto da thread dispatcher para main
    Thread::switch_context(this, Thread::_main);
}
__END_API