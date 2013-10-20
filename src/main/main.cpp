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

#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>

using namespace boost::accumulators;

typedef memory::block<float,8,1024, memory::AoS> block_f_aos;
typedef memory::block<float,8,1024, memory::AoSoA> block_f_aosoa;
typedef memory::block<double,8,1024, memory::AoS> block_d_aos;
typedef memory::block<double,8,1024, memory::AoSoA> block_d_aosoa;

typedef boost::mpl::vector< block_f_aos, block_f_aosoa, block_d_aos, block_d_aosoa > block_list;

template<class Ba> // m and n are differents into the block that why I passe like argument
void init(Ba& block_a){
    for(int i=0; i<block_a.number_block(); ++i)
        for(int j=0; j<block_a.size_block(); ++j){
            typename Ba::value_type random = 10*drand48();
            block_a(i,j) = random;
        }
}

void print( boost::accumulators::accumulator_set<double, stats<tag::variance, tag::mean> >const& acc, std::string name){
    std::cout << "bench: " << name <<" " << extract_result< tag::mean >(acc) << " [s], variance " << extract_result< tag::variance >(acc)  << std::endl;
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
        std::vector<double> time_res(100);
        
        boost::chrono::system_clock::time_point start;
        boost::chrono::nanoseconds sec;
        
        for(int i=0 ; i < 100; ++i){
            start = boost::chrono::system_clock::now();
            for(int j=0 ; j < 100; ++j)
                 Bench::template bench<block>(b);
            sec = boost::chrono::system_clock::now() - start;
            time_res.push_back(sec.count()/(1e9));
        }
    
        boost::accumulators::accumulator_set<double, stats<tag::variance, tag::mean> > acc;
        acc = std::for_each(time_res.begin(), time_res.end(), acc );
        print(acc,"to do");
    }
};

int main(int argc, char* argv[]){
    boost::mpl::for_each<block_list>(test_case<benchmark_one>());
    boost::mpl::for_each<block_list>(test_case<benchmark_two>());
//    boost::mpl::for_each<block_list>(test_case<benchmark_tree>());
//    boost::mpl::for_each<block_list>(test_case<benchmark_four>());
}
