#include <iostream>
#include <fstream>
#include <iomanip>  
#include <limits>  
#include <math.h>
#include <vector>
#include <random>

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

#define SIZE 65536

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

struct test_case{
    //redefine the operator() for boost mpl
    template<typename Solver>
    void operator()(Solver const&){

        typename Solver::value_type* input             = new typename Solver::value_type[SIZE]; 
        typename Solver::value_type* output_serial_std = new typename Solver::value_type[SIZE]; 
        typename Solver::value_type* output_serial     = new typename Solver::value_type[SIZE]; 
        typename Solver::value_type* output_vec        = new typename Solver::value_type[SIZE]; 
/*
        typename Solver::value_type input[SIZE]; 
        typename Solver::value_type output_serial_std[SIZE]; 
        typename Solver::value_type output_serial[SIZE]; 
        typename Solver::value_type output_vec[SIZE]; 
*/
        for(long long int i(0); i < SIZE; ++i){
            input[i] = GetRandom<typename Solver::value_type>(); 
        }
        
        boost::chrono::high_resolution_clock::time_point start1 = boost::chrono::high_resolution_clock::now();
        for(long long int i(0); i < SIZE; ++i)
              output_serial_std[i] = std::exp(input[i]);
        boost::chrono::nanoseconds ns1 = boost::chrono::high_resolution_clock::now() - start1;

        boost::chrono::high_resolution_clock::time_point start2 = boost::chrono::high_resolution_clock::now();
        for(long long int i(0); i < SIZE; ++i) 
              numeric::exp<typename Solver::value_type, Solver::n_>(output_serial[i], input[i]);
        boost::chrono::nanoseconds ns2 = boost::chrono::high_resolution_clock::now() - start2;

        boost::chrono::high_resolution_clock::time_point start3 = boost::chrono::high_resolution_clock::now();
        for(long long int i(0); i < SIZE; i=i+16/sizeof(typename Solver::value_type)){
              numeric::exp<typename Solver::value_type, Solver::n_>(&output_vec[i], &input[i]);
        }
        boost::chrono::nanoseconds ns3 = boost::chrono::high_resolution_clock::now() - start3;

        std::cout << " numeric::exp<sizeof(T)"<<sizeof(typename Solver::value_type)<<", "<< Solver::n_ <<  ">  vec_exp " << ns3.count()  << " [s], serial_exp "  << ns2.count() << " [s], std::exp "  << ns1.count() << " [s] " << std::endl;
         
        delete[] input;
        delete[] output_serial_std;
        delete[] output_serial;
        delete[] output_vec;

    }
};

    int main(int argc, char * argv[]){
        //generate all variants, we call the operator() defined previously
        boost::mpl::for_each<solver_exp_list>(test_case());
        return 0;
    }
