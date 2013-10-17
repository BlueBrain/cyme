//#include <vector>
//#include <cassert>
#include <iostream>

#include "math/math.hpp"
#include "memory/block.hpp"
#include "utils/timer.h"

template<class Ba, class Bb> // m and n are differents into the block that why I passe like argument
void init(Ba& block_a, Bb& block_b){
    for(int i=0; i<block_a.number_block(); ++i)
        for(int j=0; j<block_a.size_block(); ++j){
            typename Ba::value_type random = 10*drand48();
            block_a(i,j) = random;
            block_b(i,j) = random;
        }
}

template<class Ba, class Bb>
void check(Ba const & block_a, Bb const & block_b){
    for(int i=0; i<block_a.number_block(); ++i)
        for(int j=0; j<block_a.size_block(); ++j)
            std::cout << block_a(i,j)  << " " << block_b(i,j) << " " << block_a(i,j) - block_b(i,j) << std::endl;
}

template<class T, std::size_t M, std::size_t N, memory::order O>
void bench1(memory::block<T,M,N,O>& a){

    typename memory::block<T,M,N,O>::iterator it;
    for(it = a.begin(); it != a.end(); ++it){
        (*it)[0] = (*it)[1]*(*it)[2]+(*it)[4]*((*it)[5]+(*it)[6]);
   //       auto d = (*it)[1]*(*it)[2]+(*it)[4]*((*it)[5]+(*it)[6]);
   //      boost::simd::aligned_store(d,(*it).store(0));
    }

}

template<class T, std::size_t M, std::size_t N, memory::order O>
void bench2(memory::block<T,M,N,O>& a){

    typename memory::block<T,M,N,O>::iterator it;

    for(it = a.begin(); it != a.end(); ++it)
        (*it)[0] = (*it)[5]/((*it)[1]*(*it)[2]+(*it)[3]-(*it)[4]);
}

template<class T, std::size_t M, std::size_t N, memory::order O>
void bench3(memory::block<T,M,N,O>& a){

    typename memory::block<T,M,N,O>::iterator it;

    for(it = a.begin(); it != a.end(); ++it){
        (*it)[0] = (*it)[1]*(*it)[2]+(*it)[6] + 3.14;
        (*it)[1] = (*it)[2]*(*it)[3]+(*it)[6] + 2.18;
        (*it)[2] = (*it)[3]*(*it)[4]+(*it)[6] + 4.26;
        (*it)[3] = (*it)[4]*(*it)[5]+(*it)[6] + 3;
    }
}

template<class T, std::size_t M, std::size_t N, memory::order O>
void bench4(memory::block<T,M,N,O>& a){

    typename memory::block<T,M,N,O>::iterator it;

    for(it = a.begin(); it != a.end(); ++it){
        (*it)[0] = numeric::e((*it)[4]);
        (*it)[1] = numeric::e((*it)[5]);
        (*it)[2] = numeric::e((*it)[6]);
        (*it)[3] = numeric::e((*it)[7]);
    }
}

void print(long t1, long t2, std::string name){
    std::cout << "bench: " << name <<", time [cycle] " << t2-t1 << std::endl;
}

#define TYPE double

// no mpl it will not compile on bgq
int main(int argc, char* argv[]){

    memory::block<TYPE,8,1024, memory::AoS> block_aos;
    memory::block<TYPE,8,1024, memory::AoSoA> block_aosoa;

    srand(-1);

    long long int t1,t2;//;

    init(block_aos, block_aosoa);

    t1 = rdtsc();
        bench1(block_aos);
    t2 = rdtsc();

    print(t1,t2,"exp aos");

    t1 = rdtsc();
        bench1(block_aosoa);
    t2 = rdtsc();

    print(t1,t2,"exp aosos");

    t1 = rdtsc();
        bench2(block_aos);
    t2 = rdtsc();

    print(t1,t2,"multi aos");

    t1 = rdtsc();
        bench2(block_aosoa);
    t2 = rdtsc();

    print(t1,t2,"multi aosoa");

    t1 = rdtsc();
        bench3(block_aos);
    t2 = rdtsc();

    print(t1,t2,"unroll aos");

    t1 = rdtsc();
        bench3(block_aosoa);
    t2 = rdtsc();

    print(t1,t2,"unroll aosoa");

    t1 = rdtsc();
        bench4(block_aos);
    t2 = rdtsc();

    print(t1,t2,"exp aos");

    t1 = rdtsc();
        bench4(block_aosoa);
    t2 = rdtsc();

    print(t1,t2,"exp aosoa");

 //   check(block_aos,block_aosoa);
}
