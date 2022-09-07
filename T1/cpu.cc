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

template<typename ... Tn>
CPU::Context::Context(void (* func)(Tn ...), Tn ... an)
{
    this->_stack = new char [STACK_SIZE];
    getcontext(&_context);
    _context.uc_link=0;
    _context.uc_stack.ss_sp=(void *)(this->_stack);
    _context.uc_stack.ss_size=STACK_SIZE;
    _context.uc_stack.ss_flags=0;
    makecontext(&_context, (void (*)())(func), sizeof...(an), an...);
    
}

CPU::Context::~Context()
{
    delete this->_stack;
}

void CPU::switch_context(Context *from, Context *to)
{
    swapcontext(&(from->_context), &(to->_context));
}

__END_API
