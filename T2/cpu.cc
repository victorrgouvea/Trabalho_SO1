#include "cpu.h"
#include <iostream>

__BEGIN_API

void CPU::Context::save()
{
    getcontext(&_context);
}

void CPU::Context::load()
{
    setcontext(&_context);
}

CPU::Context::~Context()
{
    if (_stack) {
        delete[] _stack;
    } else {
        db<CPU>(WRN) << "Não há um contexto para deletar\n";
    }
}

void CPU::switch_context(Context *from, Context *to)
{
    swapcontext(&(from->_context), &(to->_context));
}

__END_API
