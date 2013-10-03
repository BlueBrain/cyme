//#include <vector>
//#include <cassert>
#include <iostream>

#include "numeric/math/math.hpp"
#include "memory/block.hpp"
#include "utils/timer.h"

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

template<class T, std::size_t M, std::size_t N, memory::order O>
void bench1(memory::block<T,M,N,O>& a){

    typename memory::block<T,M,N,O>::iterator it;

    for(it = a.begin(); it != a.end(); ++it)
        (*it)[0] = (*it)[4]*(*it)[5]+(*it)[1]*numeric::e((*it)[2]);
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

void print(long t1, long t2, std::string name){
    std::cout << "bench: " << name <<", time [cycle] " << t2-t1 << std::endl;
}
// no mpl it will not compile on bgq
int main(int argc, char* argv[]){

    memory::block<float,8,1024, memory::AoS> block_aos;
    memory::block<float,8,1024, memory::AoSoA> block_aosoa;

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
<<<<<<< HEAD
    for(it_aos = block_aos.begin(); it_aos != block_aos.end(); ++it_aos)
        P_aos[0] = ((P_aos[4]*(P_aos[5]*P_aos[1]*exp(P_aos[2])+ P_aos[3])+P_aos[6]) + P_aos[2]*exp(P_aos[3]))/P_aos[6];
=======
        bench2(block_aos);
    t2 = rdtsc();

    print(t1,t2,"multi aos");
>>>>>>> 17f57b8c1f930894ecf8c212f847854d4a646854

    t1 = rdtsc();
        bench2(block_aosoa);
    t2 = rdtsc();

    print(t1,t2,"multi aosoa");

    t1 = rdtsc();
<<<<<<< HEAD
    for(it_aosoa = block_aosoa.begin(); it_aosoa != block_aosoa.end(); ++it_aosoa)
        P_aosoa[0] = ((P_aosoa[4]*(P_aosoa[5]*P_aosoa[1]*numeric::exp(P_aosoa[2])+ P_aosoa[3])+P_aosoa[6]) + P_aosoa[2]*numeric::exp(P_aosoa[3]))/P_aosoa[6];
=======
        bench3(block_aos);
    t2 = rdtsc();

    print(t1,t2,"unroll aos");
>>>>>>> 17f57b8c1f930894ecf8c212f847854d4a646854

    t1 = rdtsc();
        bench3(block_aosoa);
    t2 = rdtsc();

    print(t1,t2,"unroll aosoa");

//    check(block_aos,block_aosoa);
}
