/**
 * @file main.cc
 * @brief
 * 
 */


#include "Engine.h"
#include "system.h"
#include "thread.h"

__USING_API

int main(void)
{
   System::init(&MainThread::run);
}


