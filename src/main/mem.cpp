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

  TYPE random;

  for(int i=0; i <1024; ++i)
      for(int j=0; j <16; ++j){
              random  = GetRandom<TYPE>();
              block_a(i,j) = random;
              block_b(i,j) = random;

      }

  typename memory::block<TYPE,16,1024,memory::AoS>::iterator it_AoS = block_a.begin();
  typename memory::block<TYPE,16,1024,memory::AoSoA>::iterator it_AoSoA = block_b.begin();

  unsigned long long a,b,c,d;


  a = rdtsc();
    for(it_AoS = block_a.begin(); it_AoS != block_a.end(); ++it_AoS){
           numeric::exp<TYPE,14>((*it_AoS)[15],(*it_AoS)[0]);
           numeric::exp<TYPE,14>((*it_AoS)[14],(*it_AoS)[1]);
           numeric::exp<TYPE,14>((*it_AoS)[13],(*it_AoS)[2]);
           numeric::exp<TYPE,14>((*it_AoS)[12],(*it_AoS)[3]);
           numeric::exp<TYPE,14>((*it_AoS)[11],(*it_AoS)[4]);
           numeric::exp<TYPE,14>((*it_AoS)[10],(*it_AoS)[5]);
           numeric::exp<TYPE,14>((*it_AoS)[9],(*it_AoS)[6]);
           numeric::exp<TYPE,14>((*it_AoS)[8],(*it_AoS)[7]);
           numeric::exp<TYPE,14>((*it_AoS)[7],(*it_AoS)[8]);
           numeric::exp<TYPE,14>((*it_AoS)[6],(*it_AoS)[9]);
           numeric::exp<TYPE,14>((*it_AoS)[5],(*it_AoS)[10]);
           numeric::exp<TYPE,14>((*it_AoS)[4],(*it_AoS)[11]);
           numeric::exp<TYPE,14>((*it_AoS)[3],(*it_AoS)[12]);
           numeric::exp<TYPE,14>((*it_AoS)[2],(*it_AoS)[13]);
           numeric::exp<TYPE,14>((*it_AoS)[1],(*it_AoS)[14]);
           numeric::exp<TYPE,14>((*it_AoS)[0],(*it_AoS)[15]);
    }   
  b = rdtsc();

 printf("%llu\n", b-a);

  c = rdtsc();
    for(it_AoSoA = block_b.begin(); it_AoSoA != block_b.end(); ++it_AoSoA){
           numeric::exp<TYPE,14>((*it_AoSoA)[15],(*it_AoSoA)[0]);
           numeric::exp<TYPE,14>((*it_AoSoA)[14],(*it_AoSoA)[1]);
           numeric::exp<TYPE,14>((*it_AoSoA)[13],(*it_AoSoA)[2]);
           numeric::exp<TYPE,14>((*it_AoSoA)[12],(*it_AoSoA)[3]);
           numeric::exp<TYPE,14>((*it_AoSoA)[11],(*it_AoSoA)[4]);
           numeric::exp<TYPE,14>((*it_AoSoA)[10],(*it_AoSoA)[5]);
           numeric::exp<TYPE,14>((*it_AoSoA)[9],(*it_AoSoA)[6]);
           numeric::exp<TYPE,14>((*it_AoSoA)[8],(*it_AoSoA)[7]);
           numeric::exp<TYPE,14>((*it_AoSoA)[7],(*it_AoSoA)[8]);
           numeric::exp<TYPE,14>((*it_AoSoA)[6],(*it_AoSoA)[9]);
           numeric::exp<TYPE,14>((*it_AoSoA)[5],(*it_AoSoA)[10]);
           numeric::exp<TYPE,14>((*it_AoSoA)[4],(*it_AoSoA)[11]);
           numeric::exp<TYPE,14>((*it_AoSoA)[3],(*it_AoSoA)[12]);
           numeric::exp<TYPE,14>((*it_AoSoA)[2],(*it_AoSoA)[13]);
           numeric::exp<TYPE,14>((*it_AoSoA)[1],(*it_AoSoA)[14]);
           numeric::exp<TYPE,14>((*it_AoSoA)[0],(*it_AoSoA)[15]);
    }   
  d = rdtsc();
/*
  for(int i=0; i <1024; ++i)
      for(int j=0; j <16; ++j)
          std::cout << block_a(i,j) << " " << block_b(i,j) << std::endl;
*/
 printf("%llu\n", d-c);


}
