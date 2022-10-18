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
        db<CPU>(WRN) << "O contexto não possui stack para deletar\n";
    }
}

int CPU::switch_context(Context *from, Context *to)
{
    if (from && to) {
        swapcontext(&(from->_context), &(to->_context));
        return 0;
    } else {
        db<CPU>(ERR) << "Troca de contexto entre threads falhou\n";
        return -1;
    }
}

__END_API
