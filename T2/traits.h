#ifndef traits_h
#define traits_h

//Não alterar as 3 declarações abaixo

#define __BEGIN_API             namespace SOLUTION {
#define __END_API               }
#define __USING_API            using namespace SOLUTION;

__BEGIN_API

class CPU; //declaração das classes criadas nos trabalhos devem ser colocadas aqui
class Thread;
class System;
class Debug;

//declaração da classe Traits
template<typename T>
struct Traits {
    static const bool debugged = false;
};

template<> struct Traits<CPU> : public Traits<void>
{
    static const unsigned int STACK_SIZE = 64000;
    static const bool debugged = true;
};

template<> struct Traits<Debug>: public Traits<void>
{
 static const bool error = true;
 static const bool warning = true;
 static const bool info = true;
 static const bool trace = true;
};

template<> struct Traits<System> : public Traits<void>
{
static const bool debugged = true;
};
template<> struct Traits<Thread> : public Traits<void>
{
static const bool debugged = true;
};


__END_API

#endif
