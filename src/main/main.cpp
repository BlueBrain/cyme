#include <iostream>
#include <fstream>
#include <iomanip>  
#include <limits>  

#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/chrono/chrono.hpp>
#include <boost/type_traits.hpp>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/uniform_real_distribution.hpp>


//my files
#include "numeric/math/math.hpp"

#define SIZE 128*128

//random generator
static boost::random::uniform_real_distribution<float>    RandomDouble = boost::random::uniform_real_distribution<float>(-5,5);
static boost::random::uniform_real_distribution<double>   Randomfloat  = boost::random::uniform_real_distribution<double>(-5,5);
static boost::random::mt19937    rng;

template<class T>
T GetRandom();

template<>
float GetRandom<float>(){
    return Randomfloat(rng);
}

template<>
double GetRandom<double>(){
    return RandomDouble(rng);
}

//encapsulate the solver_exp for boost::mpl
template<class T, std::size_t n>
struct solver_exp{
   typedef T value_type;
   static const std::size_t n_ = n; // keep trace of n for the evaluation
};

//define different solver_exp for the boost::mpl::vector
typedef solver_exp<float, 14>  exp_f14;
typedef solver_exp<double, 14> exp_d14;

typedef boost::mpl::vector<exp_f14, exp_d14 > solver_exp_list;

template<class T>
struct block{
    T data[SIZE];
};

struct test_case{
    //redefine the operator() for boost mpl
    template<typename Solver>
    void operator()(Solver const&){
        int size_vector = 1024;

        std::vector<block<typename Solver::value_type> > vec_input(size_vector);
        std::vector<block<typename Solver::value_type> > vec_output_serial(size_vector);
        std::vector<block<typename Solver::value_type> > vec_output_serial_std(size_vector);
        std::vector<block<typename Solver::value_type> > vec_output_vec(size_vector);

        for(long long int i(0); i < size_vector; ++i)
            for(int j=0; j < SIZE; j++)
                vec_input[i].data[j] = GetRandom<typename Solver::value_type>(); 


//        boost::chrono::high_resolution_clock::time_point start1 = boost::chrono::high_resolution_clock::now();
        for(long long int i(0); i < size_vector; ++i)
            for(int j=0; j < SIZE; j++)
              vec_output_serial_std[i].data[j] = std::exp(vec_input[i].data[j]);
//        boost::chrono::nanoseconds ns1 = boost::chrono::high_resolution_clock::now() - start1;

//        boost::chrono::high_resolution_clock::time_point start3 = boost::chrono::high_resolution_clock::now();
        for(long long int i(0); i < size_vector; ++i)
            for(int j=0; j < SIZE; j+=(memory::getsimd()/sizeof(typename Solver::value_type)))
                numeric::exp<typename Solver::value_type, Solver::n_>(&vec_output_vec[i].data[j], &vec_input[i].data[j]);
//        boost::chrono::nanoseconds ns3 = boost::chrono::high_resolution_clock::now() - start3;

//        boost::chrono::high_resolution_clock::time_point start2 = boost::chrono::high_resolution_clock::now();
        for(long long int i(0); i < size_vector; ++i)
            for(int j=0; j < SIZE; j++)
              numeric::exp<typename Solver::value_type, Solver::n_>(vec_output_serial[i].data[j], vec_input[i].data[j]);
//        boost::chrono::nanoseconds ns2 = boost::chrono::high_resolution_clock::now() - start2;

//        std::cout << " numeric::exp<sizeof(T)"<<sizeof(typename Solver::value_type)<<", "<< Solver::n_ <<  ">  vec_exp " << ns3.count()  << " [s], serial_exp "  << ns2.count() << " [s], std::exp "  << ns1.count() << " [s] " << std::endl;

    }
};

    int main(int argc, char * argv[]){
        //generate all variants, we call the operator() defined previously
        boost::mpl::for_each<solver_exp_list>(test_case());
        return 0;
    }
