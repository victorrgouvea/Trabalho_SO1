#ifndef traits_h
#define traits_h

//Não alterar as 3 declarações abaixo

#define __BEGIN_API             namespace SOLUTION {
#define __END_API               }
#define __USING_API            using namespace SOLUTION;

__BEGIN_API

class CPU; //declaração das classes criadas nos trabalhos devem ser colocadas aqui

//declaração da classe Traits
template<typename T>
struct Traits {
};

template<> struct Traits<CPU>
{
    static const unsigned int STACK_SIZE = 64000;
};

__END_API

#endif
