#include <iostream>

#include "numeric/math/math.hpp"
#include "memory/block.hpp"

#include <stdlib.h>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/uniform_real_distribution.hpp>

static boost::random::uniform_real_distribution<float>    RandomDouble = boost::random::uniform_real_distribution<float>(-5,5);
static boost::random::uniform_real_distribution<double>   Randomfloat  = boost::random::uniform_real_distribution<double>(-5,5);
static boost::random::mt19937    rng;

template<class T>
T GetRandom();

template<>
float GetRandom<float>(){
    return Randomfloat(rng);
}

template<>
double GetRandom<double>(){
    return RandomDouble(rng);
}

#define TYPE float


static __inline__ unsigned long long rdtsc(void) {
  unsigned hi, lo;
  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
  return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}


int main(){
    
    
      
    memory::block<TYPE,16,1024,memory::AoS> block_a;
    memory::block<TYPE,16,1024,memory::AoSoA> block_b;

    typename memory::block<TYPE,16,1024,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS){
        for(int i=0  ; i<16 ; ++i)
            (*it_AoS)[0] = GetRandom<TYPE>();
    }

    typename memory::block<TYPE,16,1024,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA){
        for(int i=0  ; i<16 ; ++i)
            *(*it_AoSoA)[0] = GetRandom<TYPE>();
    }


  unsigned long long a,b,c,d;




  a = rdtsc();
    for(it_AoS = block_a.begin(); it_AoS != block_a.end(); ++it_AoS){
           numeric::add<TYPE>((*it_AoS)[0],(*it_AoS)[1]);
           numeric::mul<TYPE>((*it_AoS)[0],(*it_AoS)[2]);
           numeric::add<TYPE>((*it_AoS)[0],(*it_AoS)[3]);
           numeric::add<TYPE>((*it_AoS)[0],(*it_AoS)[4]);
           numeric::add<TYPE>((*it_AoS)[0],(*it_AoS)[5]);
           numeric::add<TYPE>((*it_AoS)[0],(*it_AoS)[6]);
           numeric::add<TYPE>((*it_AoS)[0],(*it_AoS)[7]);
           numeric::add<TYPE>((*it_AoS)[0],(*it_AoS)[8]);
           numeric::mul<TYPE>((*it_AoS)[0],(*it_AoS)[9]);
           numeric::mul<TYPE>((*it_AoS)[0],(*it_AoS)[11]);
           numeric::mul<TYPE>((*it_AoS)[0],(*it_AoS)[12]);
           numeric::mul<TYPE>((*it_AoS)[0],(*it_AoS)[13]);
           numeric::mul<TYPE>((*it_AoS)[0],(*it_AoS)[14]);
           numeric::mul<TYPE>((*it_AoS)[0],(*it_AoS)[15]);
    }
  b = rdtsc();

 printf("%llu\n", b-a);

  c = rdtsc();
    for(it_AoSoA = block_b.begin(); it_AoSoA != block_b.end(); ++it_AoSoA){
           numeric::add<TYPE>((*it_AoSoA)[0],(*it_AoSoA)[1]);
           numeric::mul<TYPE>((*it_AoSoA)[0],(*it_AoSoA)[2]);
           numeric::add<TYPE>((*it_AoSoA)[0],(*it_AoSoA)[3]);
           numeric::add<TYPE>((*it_AoSoA)[0],(*it_AoSoA)[4]);
           numeric::add<TYPE>((*it_AoSoA)[0],(*it_AoSoA)[5]);
           numeric::add<TYPE>((*it_AoSoA)[0],(*it_AoSoA)[6]);
           numeric::add<TYPE>((*it_AoSoA)[0],(*it_AoSoA)[7]);
           numeric::add<TYPE>((*it_AoSoA)[0],(*it_AoSoA)[8]);
           numeric::mul<TYPE>((*it_AoSoA)[0],(*it_AoSoA)[9]);
           numeric::mul<TYPE>((*it_AoSoA)[0],(*it_AoSoA)[11]);
           numeric::mul<TYPE>((*it_AoSoA)[0],(*it_AoSoA)[12]);
           numeric::mul<TYPE>((*it_AoSoA)[0],(*it_AoSoA)[13]);
           numeric::mul<TYPE>((*it_AoSoA)[0],(*it_AoSoA)[14]);
           numeric::mul<TYPE>((*it_AoSoA)[0],(*it_AoSoA)[15]);
    }
  d = rdtsc();

 printf("%llu\n", d-c);


}
