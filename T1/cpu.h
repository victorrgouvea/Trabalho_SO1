#ifndef cpu_h
#define cpu_h

#include <ucontext.h>
#include <iostream>
#include "traits.h"

__BEGIN_API

class CPU
{
    public:

        class Context
        {
        private:
            static const unsigned int STACK_SIZE = Traits<CPU>::STACK_SIZE;
        public:
            Context() { _stack = 0; }

            template<typename ... Tn>
            Context(void (* func)(Tn ...), Tn ... an);

            ~Context();

            void save();
            void load();

        private:            
            char *_stack;
        public:
            ucontext_t _context;
        };

    public:
        static void switch_context(Context *from, Context *to);

};

template<typename ... Tn>
CPU::Context::Context(void (* func)(Tn ...), Tn ... an)
{
    _stack = new char[STACK_SIZE];
    getcontext(&_context);
    
    if (_stack) {
        _context.uc_link=0;
        _context.uc_stack.ss_sp=(void *)(_stack);
        _context.uc_stack.ss_size=STACK_SIZE;
        _context.uc_stack.ss_flags=0;
    } else {
        std::cout << "Não foi possível criar a stack\n";
        exit(-1);
    }
    
    makecontext(&_context, (void (*)())(func), sizeof...(an), an...);  
}

__END_API

#endif

