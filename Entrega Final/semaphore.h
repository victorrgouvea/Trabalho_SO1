#ifndef semaphore_h
#define semaphore_h

#include "cpu.h"
#include "thread.h"
#include "traits.h"
#include "debug.h"

__BEGIN_API

class Semaphore
{
public:
    typedef Ordered_List<Thread> Waiting_Queue;
    
    Semaphore(int v = 1) {
        valor = v;
        new (&_waiting) Waiting_Queue();
    }
    ~Semaphore(){
        wakeup_all();
    };

    void p();
    void v();
private:
    // Atomic operations
    int finc(volatile int & number);
    int fdec(volatile int & number);

    // Thread operations
    void sleep();
    void wakeup();
    void wakeup_all();

private:
    Waiting_Queue _waiting;
    int valor;
};

__END_API

#endif

