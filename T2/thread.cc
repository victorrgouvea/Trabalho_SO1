#include "thread.h"
#include <iostream>


__BEGIN_API


int Thread::switch_context(Thread * prev, Thread * next)
{
    try {
        CPU::switch_context(prev->context(), next->context());
        return  0;
    } catch (...) {
        return -1;
    }
}

void Thread::thread_exit (int exit_code)
{
    if (_context)
        delete _context;
}

__END_API