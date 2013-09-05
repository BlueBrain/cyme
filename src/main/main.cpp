#include <iostream>
#include <fstream>
#include <iomanip>  
#include <limits>  
#include <math.h>
#include <array>
#include <vector>
#include <random>

#include <boost/lexical_cast.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/chrono/chrono.hpp>
#include <boost/type_traits.hpp>



//my files
#include "numeric/math/math.hpp"

//using namespace utils;

#define SIZE 0xffff

//encapsulate the solver_exp for boost::mpl
template<class T, std::size_t n>
struct solver_exp{
   typedef T value_type;
   static  T Series_exp( T const& a){ 
       return numeric::Series_exp<T,n>::exp(a);
   }   
   static  T Pade_exp( T const& a){ 
       return numeric::Pade_exp<T,n>::exp(a);
   }   
   static const std::size_t n_ = n; // keep trace of n for the evaluation
};

//define different solver_exp for the boost::mpl::vector
typedef solver_exp<double, 2> exp_d2;
typedef solver_exp<double, 4> exp_d4;
typedef solver_exp<double, 6> exp_d6;
typedef solver_exp<double, 8> exp_d8;
typedef solver_exp<double, 10> exp_d10;
typedef solver_exp<double, 12> exp_d12;
typedef solver_exp<double, 14> exp_d14;
typedef solver_exp<double, 16> exp_d16;
typedef solver_exp<double, 18> exp_d18;
typedef solver_exp<double, 20> exp_d20;
typedef solver_exp<double, 22> exp_d22;
typedef solver_exp<double, 24> exp_d24;
typedef solver_exp<double, 26> exp_d26;
typedef solver_exp<double, 28> exp_d28;
typedef solver_exp<double, 30> exp_d30;
typedef solver_exp<double, 32> exp_d32;

typedef boost::mpl::vector<
                              exp_d2,
                              exp_d4,
                              exp_d6,
                              exp_d8,
                              exp_d10,
                              exp_d12,
                              exp_d14,
                              exp_d16,
                              exp_d18,
                              exp_d20,
                              exp_d22,
                              exp_d24,
                              exp_d26,
                              exp_d28,  
                              exp_d30,
                              exp_d32 > solver_exp_list;

struct test_case{
    //redefine the operator() for boost mpl
    template<typename Solver>
    void operator()(Solver const&){
      //  srand();
        boost::chrono::high_resolution_clock::time_point start1 = boost::chrono::high_resolution_clock::now();
        for(long long int i(-SIZE); i < SIZE; ++i){
             typename Solver::value_type a = rand(); // (typename Solver::value_type)i*(typename Solver::value_type)1/SIZE*100;
             std::exp(a);
        }
        boost::chrono::nanoseconds ns1 = boost::chrono::high_resolution_clock::now() - start1;

        boost::chrono::high_resolution_clock::time_point start2 = boost::chrono::high_resolution_clock::now();
        for(long long int i(-SIZE); i < SIZE; ++i){
             typename Solver::value_type a = rand(); // (typename Solver::value_type)i*(typename Solver::value_type)1/SIZE*100;
             Solver::Series_exp(a);
        }
        boost::chrono::nanoseconds ns2 = boost::chrono::high_resolution_clock::now() - start2;

        boost::chrono::high_resolution_clock::time_point start3 = boost::chrono::high_resolution_clock::now();
        for(long long int i(-SIZE); i < SIZE; ++i){
             typename Solver::value_type a = rand();// (typename Solver::value_type)i*(typename Solver::value_type)1/SIZE*100;
             Solver::Pade_exp(a);
        }
        boost::chrono::nanoseconds ns3 = boost::chrono::high_resolution_clock::now() - start3;

        std::cout << " numeric::exp<double,"<< Solver::n_ <<  ">  pade_exp " << ns3.count()  << " [s], series_exp "  << ns2.count() << " [s], std::exp "  << ns1.count() << " [s] " << std::endl;
    }
};

    int main(int argc, char * argv[]){
        //generate all variants, we call the operator() defined previously
        boost::mpl::for_each<solver_exp_list>(test_case());
        return 0;
    }
