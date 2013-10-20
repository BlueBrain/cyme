//#include <vector>
//#include <cassert>
#include <iostream>
#include <vector>

#include "math/math.hpp"
#include "memory/block.hpp"
#include "utils/timer.h"
#include <boost/chrono.hpp>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>

using namespace boost::accumulators;

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
        (*it)[0] = (*it)[4]*(*it)[4]+(*it)[1]*numeric::e((*it)[2]);
   //      auto d = (*it)[1]*(*it)[2]+(*it)[4]*((*it)[5]+(*it)[6]);
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

#define TYPE float

void print( boost::accumulators::accumulator_set<TYPE, stats<tag::variance, tag::mean> >const& acc, std::string name){
    std::cout << "bench: " << name <<", time [nano s] " << extract_result< tag::mean >( acc ) << " variance " << extract_result< tag::variance >( acc )  << std::endl;
}


// no mpl it will not compile on bgq
int main(int argc, char* argv[]){

    memory::block<TYPE,8,1024, memory::AoS> block_aos;
    memory::block<TYPE,8,1024, memory::AoSoA> block_aosoa;

    srand(-1);

    long long int t1,t2;//;

    init(block_aos, block_aosoa);
    
    std::vector<TYPE> time_aos(100);
    std::vector<TYPE> time_aosoa(100);
    boost::chrono::system_clock::time_point start;
    boost::chrono::nanoseconds sec;
    
    for(int j=0 ; j < 100; ++j){
        start = boost::chrono::system_clock::now();
        for(int i=0; i< 10000; ++i)
            bench1(block_aos);
        sec = boost::chrono::system_clock::now() - start;
        time_aos.push_back(sec.count()/(1e9));
       
    }
    
    {
        boost::accumulators::accumulator_set<TYPE, stats<tag::variance, tag::mean> > acc;
        acc = std::for_each( time_aos.begin(), time_aos.end(), acc );
        print(acc,"exp aos");
    }
    
    for(int j=0 ; j < 100; ++j){
        start = boost::chrono::system_clock::now();
        for(int i=0; i< 10000; ++i)
            bench1(block_aosoa);
        sec = boost::chrono::system_clock::now() - start;
        time_aosoa.push_back(sec.count()/(1e9));
    }

    {
        boost::accumulators::accumulator_set<TYPE, stats<tag::variance, tag::mean> > acc;
        acc = std::for_each( time_aosoa.begin(), time_aosoa.end(), acc );
        print(acc,"exp aosoa");
    }

/*
    start = boost::chrono::system_clock::now();
    t1 = rdtsc();
    for(int i=0; i< 10000; ++i)
        bench2(block_aos);
    t2 = rdtsc();
    sec = boost::chrono::system_clock::now() - start;

    print(sec,"multi aos");

    start = boost::chrono::system_clock::now();
    t1 = rdtsc();
    for(int i=0; i< 10000; ++i)
        bench2(block_aosoa);
    t2 = rdtsc();
    sec = boost::chrono::system_clock::now() - start;

    print(sec,"multi aosoa");


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
*/
 //   check(block_aos,block_aosoa);
}
