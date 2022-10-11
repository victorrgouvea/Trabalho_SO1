#include "thread.h"
#include <iostream>


__BEGIN_API

// Inicializando o atributos estáticos da classe Thread
int Thread::total_threads = 0;
Thread * Thread::_running = nullptr;
Thread * Thread::_main_thread = nullptr;

int Thread::switch_context(Thread * prev, Thread * next)
{
    _running = next;
    return CPU::switch_context(prev->context(), next->context());
}

void Thread::thread_exit (int exit_code)
{
    if (_context) {
        if (this == _running) {
            _running = _main_thread;
        }
        delete _context;
        total_threads--;
        db<Thread>(INF) << "thread " << this->id() << " exit com sucesso\n";
    } else {
        db<Thread>(ERR) << "thread " << this->id() << " exit falhou\n";
    }
}

__END_API