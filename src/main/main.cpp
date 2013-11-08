
//#include <vector>
//#include <cassert>
#include <iostream>
#include <vector>

#include "cyme/cyme.hpp"

#include "utils/timer.h"
#include <boost/chrono.hpp>

#include <boost/function.hpp>
#include <boost/bind.hpp>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>

#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/push_back.hpp>



#include <functional>

#include <algorithm>

template<class T>
struct synapse{
    typedef T value_type;
    static const int value_size = 5;
};

typedef cyme::array<synapse<float>,1024, memory::AoS> block_f_aos;
typedef cyme::array<synapse<float>,1024, memory::AoSoA> block_f_aosoa;
typedef cyme::array<synapse<double>,1024, memory::AoS> block_d_aos;
typedef cyme::array<synapse<double>,1024, memory::AoSoA> block_d_aosoa;


typedef cyme::vector<synapse<float>, memory::AoS> vector_f_aos;
typedef cyme::vector<synapse<float>, memory::AoSoA> vector_f_aosoa;
typedef cyme::vector<synapse<double>, memory::AoS> vector_d_aos;
typedef cyme::vector<synapse<double>, memory::AoSoA> vector_d_aosoa;

using namespace boost::accumulators;



typedef cyme::array<synapse<float>,1024, memory::AoS> block_f_aos;
typedef cyme::array<synapse<float>,1024, memory::AoSoA> block_f_aosoa;
typedef cyme::array<synapse<double>,1024, memory::AoS> block_d_aos;
typedef cyme::array<synapse<double>,1024, memory::AoSoA> block_d_aosoa;


typedef cyme::vector<synapse<float>, memory::AoS> vector_f_aos;
typedef cyme::vector<synapse<float>, memory::AoSoA> vector_f_aosoa;
typedef cyme::vector<synapse<double>, memory::AoS> vector_d_aos;
typedef cyme::vector<synapse<double>, memory::AoSoA> vector_d_aosoa;


typedef boost::mpl::vector< block_f_aos, block_f_aosoa, block_d_aos, block_d_aosoa > array_list;
typedef boost::mpl::vector< vector_f_aos, vector_f_aosoa, vector_d_aos, vector_d_aosoa > vector_list;



template<class Ba>
void init(Ba& block_a){
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
            (*it)[0] = (*it)[3]*(*it)[4]+(*it)[1]*exp((*it)[2]);
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
            (*it)[0] = (*it)[4]*(*it)[6]+(*it)[6] + 3.14;
            (*it)[1] = (*it)[5]*(*it)[5]+(*it)[6] + 2.18;
            (*it)[2] = (*it)[6]*(*it)[5]+(*it)[6] + 4.26;
            (*it)[3] = (*it)[7]*(*it)[4]+(*it)[6] + 3;
        }
    }
};

struct benchmark_four{
    template<class Ba>
    static void bench(Ba& a){
        for(typename Ba::iterator it = a.begin(); it != a.end(); ++it){
            (*it)[0] = exp((*it)[4]);
            (*it)[1] = exp((*it)[5]);
            (*it)[2] = exp((*it)[6]);
            (*it)[3] = exp((*it)[7]);
        }
    }
};

template<class Bench>
struct test_case{
    template <typename block>
    void operator()(block const&){
        block b;//(16384);
        init(b);
        std::vector<double> time_res;
        boost::chrono::system_clock::time_point start;
        boost::chrono::duration<double> sec;

        for(std::size_t i=0 ; i < 100; ++i){
            start = boost::chrono::system_clock::now();
            for(std::size_t j=0 ; j < 100; ++j)
                 Bench::template bench<block>(b); // C++ syntax, ~_~'
            sec = boost::chrono::system_clock::now() - start;
            time_res.push_back(sec.count());
        }
    
        boost::accumulators::accumulator_set<double, stats<tag::mean, tag::variance> > acc;
        acc = std::for_each(time_res.begin(), time_res.end(), acc );
        print(acc,"to do");
    }
};

struct ProbGABAA{
    typedef float value_type;

    template<class iterator>
    static inline void nrn_function(iterator const& it){
        (*it)[12] = (0.182*((*it)[16]+35.0))/ (1.0 - exp(-(-(*it)[14]-35.0))/9.0);

    };

    const static int value_size = 8;
};

struct ProbAMPA{
    typedef double value_type;

    template<class iterator>
    void nrn_function(iterator const& it){
        (*it)[1] = ((*it)[4] + (*it)[2] + (*it)[5]) / (*it)[2];
    };

    const static int value_size = 7;
};

struct Na{
    typedef double value_type;

    template<class iterator>
    void nrn_function(iterator const& it){
        (*it)[1] = (-(*it)[6] + (*it)[7] + (*it)[2]) / exp((*it)[2]/9.0);
    };

    const static int value_size = 6;
};

template<class mechanism, class container = cyme::vector<mechanism, memory::AoSoA> > // should use cyme container there
class pack{
public:
    explicit pack(int size, int value):cont(size*mechanism::value_size,value){ // vector constructor
    }

    explicit pack():cont(){ // array constructor
    }

    void execution(){
        for(typename container::iterator it = cont.begin(); it < cont.end(); ++it) // cilk should do that in parallel
            m.nrn_function(it);
    }
private:
    container cont;
    mechanism m;
};

class stack{
public:
    typedef boost::function<void(void)> base_type; // pointer to function
    stack(){

    }

    void push_back(base_type const& f){
        s.push_back(f); // fill up the stack
    }

    void flush(){
        #pragma omp parallel
        for(std::vector<base_type>::iterator it = s.begin(); it < s.end(); ++it)
            #pragma omp task
            (*it)(); // execute nrn_function
    }
private:
    std::vector<base_type> s;
};

int main(int argc, char* argv[]){
    stack s;

    pack<ProbGABAA > a(16384,1); // pack 16384 synapse, AoSoA
    pack<ProbAMPA> b(32415,2); // pack 32415 synapse, AoSoA
    pack<Na, cyme::array<Na, 16, memory::AoSoA> > c; // pack 16 channel small object array is better choice, AoSoA

    s.push_back(boost::bind(&pack<ProbGABAA>::execution,a)); // fill up the stack
    s.push_back(boost::bind(&pack<ProbAMPA>::execution,b)); // again
    s.push_back(boost::bind(&pack<Na, cyme::array<Na, 16, memory::AoSoA> >::execution,c)); // again
    std::cout << " stack execution " << std::endl;
    s.flush(); // execute the stack


    boost::mpl::for_each<vector_list>(test_case<benchmark_one>());
    std::cout << " --------- " << std::endl;
    boost::mpl::for_each<vector_list>(test_case<benchmark_two>());
    std::cout << " --------- " << std::endl;
    boost::mpl::for_each<vector_list>(test_case<benchmark_tree>());
    std::cout << " --------- " << std::endl;
    boost::mpl::for_each<vector_list>(test_case<benchmark_four>());
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
