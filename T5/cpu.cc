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

int CPU::finc(volatile int & number){
    int val = 1;
    int r;

    asm(
       "lock\n\t"
       "xadd %1, %0":"+m"( number), "=r"(r):"1"( val ):"memory", "cc");

    return number;
}

int CPU::fdec(volatile int & number){
    int val = -1;
    int r;

    asm(
       "lock\n\t"
       "xadd %1, %0":
       "+m"( number), "=r"(r):
       "1"( val ):
       "memory", "cc");

    return number;
}

__END_API
