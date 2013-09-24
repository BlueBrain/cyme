//#include <vector>
//#include <cassert>
#include <iostream>

#include "numeric/math/math.hpp"
#include "memory/block.hpp"
#include "utils/timer.h"

#define TYPE double
#define SIZE 1024
#define M 8
#define ORDER AoS

#define P_aos (*it_aos)
#define P_aosoa (*it_aosoa)

int main(int argc, char* argv[]){

    srand(-1);

    memory::block<TYPE,M,SIZE, memory::AoS> block_aos;
    memory::block<TYPE,M,SIZE, memory::AoSoA> block_aosoa;

    for(int i=0; i <SIZE; ++i)
        for(int j=0; j <M; ++j){
            TYPE random = drand48();
            block_aos(i,j) = random;
            block_aosoa(i,j) = random;
        }

    memory::block<TYPE,M,SIZE, memory::AoS>::iterator it_aos = block_aos.begin();
    memory::block<TYPE,M,SIZE, memory::AoSoA>::iterator it_aosoa = block_aosoa.begin();

    long long int t1,t2;//;
/*
    t1 = rdtsc();
    for(int i=0; i <SIZE; i++)
      block_aos(i,0) = (2*block_aos(i,1)*(block_aos(i,2)*(block_aos(i,3)+block_aos(i,4)) + block_aos(i,5)*(block_aos(i,6)+block_aos(i,7))) +8.1 )/block_aos(i,7);
    t2 = rdtsc();
    std::cout << " classic " << t2 - t1 << std::endl;
    

    t1 = rdtsc();
    for(it_aos = block_aos.begin(); it_aos != block_aos.end(); ++it_aos)
        P_aos[0] = (2*P_aos[1]*(P_aos[2]*(P_aos[3]+P_aos[4]) + P_aos[5]*(P_aos[6]+P_aos[7])) +8.1 )/P_aos[7];

    t2 = rdtsc();
    std::cout << " cycle aos " << t2 - t1 << std::endl;
*/
    t1 = rdtsc();
    for(it_aosoa = block_aosoa.begin(); it_aosoa != block_aosoa.end(); ++it_aosoa){
        P_aosoa[0] = P_aosoa[1]*P_aosoa[2]+P_aosoa[3];
//      P_aosoa[0] = (2*P_aosoa[1]*(P_aosoa[2]*(P_aosoa[3]+P_aosoa[4]) + P_aosoa[5]*(P_aosoa[6]+P_aosoa[7])) +8.1 )/P_aosoa[7];

    }
    t2 = rdtsc();
    std::cout << " cycle aosoa " << t2 - t1 << std::endl;


}
