
//#include <vector>
//#include <cassert>
#include <iostream>
#include <vector>

#include "cyme/cyme.hpp"

//#include "utils/timer.h"

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
    static const int value_size = 18;
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


typedef boost::mpl::vector< block_f_aos, block_f_aosoa, block_d_aos, block_d_aosoa > array_list;
//typedef boost::mpl::vector< vector_f_aos, vector_f_aosoa, vector_d_aos, vector_d_aosoa > vector_list;
typedef boost::mpl::vector<vector_d_aosoa> vector_list;


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
            typename Ba::value_type random = 5.8;//10*drand48();
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


static double dt = 0.01;



struct Na{
    typedef double  value_type;

    template<class iterator, memory::order O>
    static inline void cnrn_functions(iterator it){
        (*it)[0] = exp((*it)[1]);

        double t = 123;

    //    cnrn_initmodel(it);
   //     cnrn_cur<iterator,O>(it);
    //    cnrn_state(it);
    }

    template<class iterator>
    static inline void cnrn_rates(iterator it){
        (*it)[8]  = (0.182*((*it)[16]+35.0)) / (1.0 - (exp((-(*it)[16]-35.0)/9.0)));
        (*it)[9]  = (-0.124*((*it)[16]+35.0))/ (1.0 - (exp(((*it)[16]+35.0)/9.0)));
        (*it)[6]  = (*it)[8]/((*it)[8]+(*it)[9]);
        (*it)[7]  = 1.0/((*it)[8]+(*it)[9]);
        (*it)[12] = (0.024*((*it)[16]+50.0))  /(1.0-(exp((-(*it)[16]-50.0)/5.0)));
        (*it)[13] = (-0.0091*((*it)[16]+75.0))/(1.0-(exp(((*it)[16]+75.0)/5.0)));
        (*it)[10] = 1.0/(1.0+exp(((*it)[16]+65.0)/6.2));
        (*it)[11] = 1.0/((*it)[12]+(*it)[13]);
    };

    template<class iterator>
    static inline void cnrn_states(iterator it){
        cnrn_rates(it);
        (*it)[3] += (1.-exp(dt*(-1.0/(*it)[7] )))*(-((*it)[6] /(*it)[7]) /(-1.0/(*it)[7]) -(*it)[3]);
        (*it)[4] += (1.-exp(dt*(-1.0/(*it)[11])))*(-((*it)[10]/(*it)[11])/(-1.0/(*it)[11])-(*it)[4]);
    }

    template<class iterator, memory::order O>
    static inline  cyme::serial<value_type,O> cnrn_current(iterator it, value_type t = value_type()){
        (*it)[16] = t;
        (*it)[2] = (*it)[0] * (*it)[3] * (*it)[3] * (*it)[3] * (*it)[4];
        (*it)[1] = (*it)[2] * ((*it)[16] - (*it)[5]);
        return cyme::serial<value_type,O> ((*it)[1]);
    }

    template<class iterator>
    static inline void cnrn_initmodel(iterator it){
        (*it)[4] = 0. ; // TO DO, (*it)[4] ^= (*it)[4] XOR, or basic set up to 0 <--------------------------------- TIM
        (*it)[3] = 0. ;
        cnrn_rates(it);
        (*it)[3] = (*it)[6]; 
        (*it)[4] = (*it)[10]; 
    }

    template<class iterator, memory::order O>
    static inline void cnrn_cur(iterator it){
        double _v=-33.33; // _v voltage fron a node random number
        cyme::serial<value_type,O> tmp  = cnrn_current<iterator, O>(it, _v + 0.001);
        cyme::serial<value_type,O> tmp2 = cnrn_current<iterator, O>(it, _v);
        tmp -= tmp2;
        (*it)[17] = tmp;
        (*it)[17] = (*it)[17]/0.001;
    }
    
    template<class iterator>
    static inline void cnrn_state(iterator it){
        cnrn_states(it);
    }

    const static int value_size = 18;
};


template<class mechanism, class container = cyme::vector<mechanism, memory::AoSoA> > // should use cyme container there
class pack{
public:
    typedef typename mechanism::value_type value_type;

    explicit pack(int size, int value):cont(size,value){ // vector constructor
    }

    explicit pack():cont(){ // array constructor
    }

    void execution(){
        for(typename container::iterator it = cont.begin(); it < cont.end(); ++it)
            m.template cnrn_functions<typename container::iterator, container::order_value>(it);
    }

    value_type& operator()(size_t i, size_t j){
        return this->cont(i,j);
    }

    std::size_t size(){
        return this->cont.size();
    }

    std::size_t size_block(){
        return this->cont.size_block();
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
        for(std::vector<base_type>::iterator it = s.begin(); it < s.end(); ++it)
            (*it)(); // execute cnrn_functions
    }
private:
    std::vector<base_type> s;
};


int main(int argc, char* argv[]){


    stack s;
    pack<Na> a(16384,0); // pack 16384 synapse, AoSoA

    init(a);


    s.push_back(boost::bind(&pack<Na>::execution,&a)); // fill up the stack
 //   s.push_back(boost::bind(&pack<ProbAMPA>::execution,&b)); // again
 //   s.push_back(boost::bind(&pack<Na, cyme::array<Na, 16, memory::AoSoA> >::execution,&c)); // again

    boost::chrono::system_clock::time_point start =  boost::chrono::system_clock::now();
    s.flush(); // execute the stack
    boost::chrono::duration<double>  sec = boost::chrono::system_clock::now() - start;
    std::cout << " sec " << sec.count() << std::endl;


//    boost::mpl::for_each<vector_list>(test_case<benchmark_two>());
/*
    boost::mpl::for_each<vector_list>(test_case<benchmark_one>());
    std::cout << " --------- " << std::endl;

    boost::mpl::for_each<vector_list>(test_case<benchmark_two>());
    std::cout << " --------- " << std::endl;
    boost::mpl::for_each<vector_list>(test_case<benchmark_tree>());
    std::cout << " --------- " << std::endl;
    boost::mpl::for_each<vector_list>(test_case<benchmark_four>());

    boost::mpl::for_each<array_list>(test_case<benchmark_one>());
    std::cout << " --------- " << std::endl;
    boost::mpl::for_each<array_list>(test_case<benchmark_two>());
    std::cout << " --------- " << std::endl;
    boost::mpl::for_each<array_list>(test_case<benchmark_tree>());
    std::cout << " --------- " << std::endl;
    boost::mpl::for_each<array_list>(test_case<benchmark_four>());
*/
}
