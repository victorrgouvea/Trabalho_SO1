#include "system.h"
#include <iostream>
#include "debug.h"

__BEGIN_API

void System::init(void (*main)(void *)) {
    setvbuf(stdout, 0,_IONBF, 0);
    db<System>(TRC) << "System::init() chamado\n";
    Thread::init(main);
}

__END_API