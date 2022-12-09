/**
 * @file main.cc
 * @brief
 * 
 */


#include "Engine.h"
#include "Threads/system.h"
#include "Threads/thread.h"

__USING_API

int main(void)
{
   System::init(&Engine::run);
}


