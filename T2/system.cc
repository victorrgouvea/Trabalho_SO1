#include "system.h"
#include <iostream>
#include "debug.h"

__BEGIN_API

void System::init() {
    setvbuf(stdout, 0,_IONBF, 0);
    db<System>(TRC) << "System::init() chamado\n";
}

__END_API