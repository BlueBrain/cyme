//#include <vector>
//#include <cassert>
#include <iostream>
#include <vector>

#include "cyme/cyme.hpp"

#include "utils/timer.h"
#include <boost/chrono.hpp>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>

#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>

using namespace boost::accumulators;

template<class T>
struct synapse{
    typedef T value_type;
    static const int value_size = 8;
};

typedef cyme::array<synapse<float>,1024, memory::AoS> block_f_aos;
typedef cyme::array<synapse<float>,1024, memory::AoSoA> block_f_aosoa;
typedef cyme::array<synapse<double>,1024, memory::AoS> block_d_aos;
typedef cyme::array<synapse<double>,1024, memory::AoSoA> block_d_aosoa;


typedef cyme::vector<synapse<float>, memory::AoS> vector_f_aos;
typedef cyme::vector<synapse<float>, memory::AoSoA> vector_f_aosoa;
typedef cyme::vector<synapse<double>, memory::AoS> vector_d_aos;
typedef cyme::vector<synapse<double>, memory::AoSoA> vector_d_aosoa;


typedef boost::mpl::vector< block_f_aos, block_f_aosoa, block_d_aos, block_d_aosoa > array_list;
//typedef boost::mpl::vector< vector_f_aos, vector_f_aosoa, vector_d_aos, vector_d_aosoa > vector_list;
typedef boost::mpl::vector<vector_f_aos, vector_f_aosoa > vector_list;



template<class Ba>
void init(Ba& block_a){
    block_a.resize(16384);
    for(int i=0; i<block_a.size(); ++i)
        for(int j=0; j<block_a.size_block(); ++j){
            typename Ba::value_type random = 10*drand48();
            block_a(i,j) = random;
        }
}

template<class Ba, class Bb>
void init(Ba& block_a, Bb& block_b){
    for(int i=0; i<block_a.size(); ++i)
        for(int j=0; j<block_a.size_block(); ++j){
            typename Ba::value_type random = 10*drand48();
            block_a(i,j) = random;
            block_b(i,j) = random;
        }
}

template<class Ba, class Bb>
void check(Ba const & block_a, Bb const & block_b){
    std::cout.precision(2*sizeof(typename Ba::value_type));

    for(int i=0; i<block_a.size(); ++i)
        for(int j=0; j<block_a.size_block(); ++j)
            std::cout << block_a(i,j)  << " " << block_b(i,j) << " " << block_a(i,j) - block_b(i,j) << std::endl;
}

void print( boost::accumulators::accumulator_set<double, stats<tag::mean, tag::variance> >const& acc, std::string name){
    std::cout.precision(2);
    std::cout.setf(std::ios::scientific, std::ios::floatfield);
    std::cout << "bench: " << name <<" " << extract_result< tag::mean >(acc)
                           << " [s], variance " << extract_result< tag::variance >(acc)
                           << ", standard deviation " << sqrt(extract_result< tag::variance >(acc)) << std::endl;
}

struct benchmark_one{
    template<class Ba>
    static void bench(Ba& a){
        for(typename Ba::iterator it = a.begin(); it != a.end(); ++it)
            (*it)[0] = (*it)[3]*(*it)[4]+(*it)[1]*numeric::e((*it)[2]);
        }
};

struct benchmark_two{
    template<class Ba>
    static void bench(Ba& a){
        std::cout << "The distance is: " << std::distance(a.begin(),a.end()) << std::endl;
        for(typename Ba::iterator it = a.begin(); it != a.end(); ++it)
            (*it)[0] = (*it)[5]/((*it)[1]*(*it)[2]+(*it)[3]-(*it)[4]);
    }
};

struct benchmark_tree{
    template<class Ba>
    static void bench(Ba& a){

        for(typename Ba::iterator it = a.begin(); it != a.end(); ++it){
            (*it)[0] = (*it)[1]*(*it)[2]+(*it)[6] + 3.14;
            (*it)[1] = (*it)[2]*(*it)[3]+(*it)[6] + 2.18;
            (*it)[2] = (*it)[3]*(*it)[4]+(*it)[6] + 4.26;
            (*it)[3] = (*it)[4]*(*it)[5]+(*it)[6] + 3;
        }
    }
};

struct benchmark_four{
    template<class Ba>
    static void bench(Ba& a){
        for(typename Ba::iterator it = a.begin(); it != a.end(); ++it){
            (*it)[0] = numeric::e((*it)[4]);
            (*it)[1] = numeric::e((*it)[5]);
            (*it)[2] = numeric::e((*it)[6]);
            (*it)[3] = numeric::e((*it)[7]);
        }
    }
};

template<class Bench>
struct test_case{
    template <typename block>
    void operator()(block const&){
        block b;
        init(b);
        std::vector<double> time_res;
        boost::chrono::system_clock::time_point start;
        boost::chrono::duration<double> sec;

   //     for(std::size_t i=0 ; i < 100; ++i){
            start = boost::chrono::system_clock::now();
 //            for(std::size_t j=0 ; j < 100; ++j)
                 Bench::template bench<block>(b);
            sec = boost::chrono::system_clock::now() - start;
            time_res.push_back(sec.count());
   //     }
    
        boost::accumulators::accumulator_set<double, stats<tag::mean, tag::variance> > acc;
        acc = std::for_each(time_res.begin(), time_res.end(), acc );
        print(acc,"to do");
    }
};

int main(int argc, char* argv[]){
    boost::mpl::for_each<vector_list>(test_case<benchmark_two>());
/*
    boost::mpl::for_each<array_list>(test_case<benchmark_one>());
    std::cout << " --------- " << std::endl;
    boost::mpl::for_each<array_list>(test_case<benchmark_two>());
    std::cout << " --------- " << std::endl;
    boost::mpl::for_each<array_list>(test_case<benchmark_tree>());
    std::cout << " --------- " << std::endl;
    boost::mpl::for_each<array_list>(test_case<benchmark_four>());
*/
}
