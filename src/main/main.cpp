//#include <vector>
//#include <cassert>
#include <iostream>

#include "numeric/math/math.hpp"
#include "memory/block.hpp"
#include "utils/timer.h"

#define TYPE double
#define M 12
#define SIZE 13
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
    //   BOOST_CHECK_CLOSE(block_a(i,j), block_b(i,j), RELATIVE_ERROR);}
}


int main(int argc, char* argv[]){
    std::cout.precision(14);
    srand(-1);

    memory::block<TYPE,M,SIZE, memory::AoS> block_a;
    memory::block<TYPE,M,SIZE, memory::AoSoA> block_b;

    init(block_a, block_b);

    typename memory::block<TYPE,M,SIZE,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0]=(*it_AoS)[1];

    typename memory::block<TYPE,M,SIZE,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA){
        (*it_AoSoA)[0] = (*it_AoSoA)[1];
        std::cout <<  block_b.size() << std::endl;
    }

    check(block_a,block_b);
    std::cout << "finish" << std::endl;

    /*
    memory::block<TYPE,M,SIZE, memory::AoS>::iterator it_aos = block_aos.begin();
    memory::block<TYPE,M,SIZE, memory::AoSoA>::iterator it_aosoa = block_aosoa.begin();

    long long int t1,t2;//;

    t1 = rdtsc();
    for(int i=0; i <SIZE; i++)
      block_aos(i,0) = (2*block_aos(i,1)*(block_aos(i,2)*(block_aos(i,3)+block_aos(i,4)) + block_aos(i,5)*(block_aos(i,6)+block_aos(i,7))) +8.1 )/block_aos(i,7);
    t2 = rdtsc();
    std::cout << " classic " << t2 - t1 << std::endl;


    t1 = rdtsc();
    for(it_aos = block_aos.begin(); it_aos != block_aos.end(); ++it_aos)
        P_aos[0] += P_aos[1] + P_aos[2] ;

        //        P_aos[0] = ((P_aos[4]*(P_aos[5]*P_aos[1]*P_aos[2]+ P_aos[3])+P_aos[6]) + P_aos[2]*P_aos[3])/P_aos[6];

    t2 = rdtsc();
    std::cout << " cycle aos " << t2 - t1 << std::endl;

    t1 = rdtsc();
    for(it_aosoa = block_aosoa.begin(); it_aosoa != block_aosoa.end(); ++it_aosoa){
        P_aosoa[0] += P_aosoa[1] + P_aosoa[2] ;
//        P_aosoa[1] =  P_aosoa[2]*P_aosoa[5]- P_aosoa[3];

}
//        P_aosoa[0] = ((P_aosoa[4]*(P_aosoa[5]*P_aosoa[1]*P_aosoa[2]+ P_aosoa[3])+P_aosoa[6]) + P_aosoa[2]*P_aosoa[3])/P_aosoa[6];

    t2 = rdtsc();
    std::cout << " cycle aosoa " << t2 - t1 << std::endl;



    for(int i=0; i <SIZE; ++i)
        for(int j=0; j <M; ++j)
            std::cout <<  block_aos(i,j) << " " <<  block_aosoa(i,j) << " "  << block_aos(i,j) - block_aosoa(i,j) << std::endl;
*/

}
