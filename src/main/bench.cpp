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
#include "memory/block.hpp"

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

template<class T, memory::order O>
struct Solver_add;

template<class T>
struct Solver_add<T, memory::AoS>{
   typedef T value_type;
   static inline void add(T a,T b){
       std::cout << " je suis la " << std::endl;
       numeric::add(a,b);
   };   
};

typedef Solver_add<float,memory::AoS>  add_s;

typedef boost::mpl::vector<add_s> Solver_op_list;

struct test_case{
    //redefine the operator() for boost mpl
    template<typename Solver>
    void operator()(Solver const&){

        memory::block<typename Solver::value_type,16,1024,memory::AoS> block;
          
        typename Solver::value_type random;

        for(int i=0; i <1024; ++i)
            for(int j=0; j <16; ++j){
                random  = GetRandom<typename Solver::value_type>();
                block(i,j) = random;
      
        }

        typename memory::block<typename Solver::value_type,16,1024,memory::AoS>::iterator it = block.begin();

        boost::chrono::high_resolution_clock::time_point start1 = boost::chrono::high_resolution_clock::now();
            for(it = block.begin(); it != block.end(); ++it){
                //Solver::add<typename Solver::value_type, memory::AoS>((*it)[15],(*it)[0]);
                Solver::add((*it)[15],(*it)[0]);
/*
                Solver::add((*it)[14],(*it)[1]);
                Solver::add((*it)[13],(*it)[2]);
                Solver::add((*it)[12],(*it)[3]);
                Solver::add((*it)[11],(*it)[4]);
                Solver::add((*it)[10],(*it)[5]);
                Solver::add((*it)[9],(*it)[6]);
                Solver::add((*it)[8],(*it)[7]);
                Solver::add((*it)[7],(*it)[8]);
                Solver::add((*it)[6],(*it)[9]);
                Solver::add((*it)[5],(*it)[10]);
                Solver::add((*it)[4],(*it)[11]);
                Solver::add((*it)[3],(*it)[12]);
                Solver::add((*it)[2],(*it)[13]);
                Solver::add((*it)[1],(*it)[14]);
                Solver::add((*it)[0],(*it)[15]);
*/
            }   
        boost::chrono::nanoseconds ns1 = boost::chrono::high_resolution_clock::now() - start1;


        std::cout << ns1.count() << " [s] " << std::endl;

    }
};

    int main(int argc, char * argv[]){
        //generate all variants, we call the operator() defined previously
        boost::mpl::for_each<Solver_op_list>(test_case());
        return 0;
    }
