//#include <vector>
//#include <cassert>
#include <iostream>

#include "numeric/math/math.hpp"
#include "memory/block.hpp"
#include "utils/timer.h"

#define TYPE float
#define M 8
#define SIZE 1024
#define ORDER AoS

#define P_aos (*it_aos)
#define P_aosoa (*it_aosoa)


template<class Ba, class Bb> // m and n are differents into the block that why I passe like argument
void init(Ba& block_a, Bb& block_b){
    for(int i=0; i<block_a.number_block(); ++i)
        for(int j=0; j<block_a.size_block(); ++j){
            typename Ba::value_type random = drand48();
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


int main(int argc, char* argv[]){

    memory::block<TYPE,M,SIZE, memory::AoS> block_aos;
    memory::block<TYPE,M,SIZE, memory::AoSoA> block_aosoa;

    srand(-1);
    init(block_aos, block_aosoa);

    memory::block<TYPE,M,SIZE, memory::AoS>::iterator it_aos = block_aos.begin();
    memory::block<TYPE,M,SIZE, memory::AoSoA>::iterator it_aosoa = block_aosoa.begin();

    long long int t1,t2;//;
/*
    t1 = rdtsc();
    for(int i=0; i <SIZE; i++)
      block_aos(i,0) = (block_aos(i,1)*(exp(block_aos(i,2))*(block_aos(i,3)+block_aos(i,4)) + block_aos(i,5)*(block_aos(i,6)+block_aos(i,7))) +8.1 )/block_aos(i,7);
    t2 = rdtsc();
    std::cout << " classic " << t2 - t1 << std::endl;
*/

    t1 = rdtsc();
    for(it_aos = block_aos.begin(); it_aos != block_aos.end(); ++it_aos)
        P_aos[0] = ((P_aos[4]*(P_aos[5]*P_aos[1]*exp(P_aos[2])+ P_aos[3])+P_aos[6]) + P_aos[2]*P_aos[3])/P_aos[6];

    t2 = rdtsc();
    std::cout << " cycle aos " << t2 - t1 << std::endl;

    t1 = rdtsc();
    for(it_aosoa = block_aosoa.begin(); it_aosoa != block_aosoa.end(); ++it_aosoa)
        P_aosoa[0] = ((P_aosoa[4]*(P_aosoa[5]*P_aosoa[1]*numeric::exp(P_aosoa[2])+ P_aosoa[3])+P_aosoa[6]) + P_aosoa[2]*P_aosoa[3])/P_aosoa[6];

    t2 = rdtsc();
    std::cout << " cycle aosoa " << t2 - t1 << std::endl;

  //  check(block_aos,block_aosoa);
}
