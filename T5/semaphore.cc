#include "semaphore.h"
#include <iostream>


__BEGIN_API

void Semaphore::p() {
    if (fdec(valor) < 1) {
        sleep();
    }
}

void Semaphore::v() {
    if (finc(valor) > 0) {
        wakeup();
    }
}

int Semaphore::finc(volatile int & number) {
    return CPU::finc(number);
}

int Semaphore::fdec(volatile int & number) {
    return CPU::fdec(number);
}

void Semaphore::sleep() {
    _waiting.insert(Thread::running()->link());
    Thread::running()->sleep();
}

void Semaphore::wakeup() {
    Thread * running = (_waiting.remove())->object();
    running->wakeup();
}

void Semaphore::wakeup_all() {
    Thread * acordada;
    while (_waiting.size() > 0) {
        acordada = _waiting.remove()->object();
        acordada->wakeup_all();
    }
    acordada->yield();
}
__END_API