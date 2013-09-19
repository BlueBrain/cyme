#include <iostream>
#include <fstream>
#include <iomanip>  
#include <limits>  
#include <string>  

#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/type_traits.hpp>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/uniform_real_distribution.hpp>


//my files
#include "numeric/math/math.hpp"
#include "memory/block.hpp"
#include "utils/timer.h"
#include "helper.h"

#define SIZE 1024
#define M 16

struct test_case{
    //redefine the operator() for boost mpl
    template<typename Solver>
    void operator()(Solver const&){
        srand(-1);

        memory::block<typename Solver::value_type,M,SIZE, Solver::O> block;

        for(int i=0; i <SIZE; ++i)
            for(int j=0; j <M; ++j){
                block(i,j) = GetRandom<typename Solver::value_type>();
        }

       typename memory::block<typename Solver::value_type,M,SIZE, Solver::O>::iterator it = block.begin();

       timer t;
       t.start();

        long long int t1 = rdtsc();

            for(it = block.begin(); it != block.end(); ++it){
                for(int i = 0; i<0xffff; ++i)
                Solver::ops((*it)[rand()%16],(*it)[rand()%16]);
            }

        long long int t2 = rdtsc();


       t.stop();
       std::cout << Solver::name() << ", " << t.get() << " [s] " << t2-t1 <<  std::endl;
    }
};

int main(int argc, char * argv[]){
    boost::mpl::for_each<Solver_op_list>(test_case());
    return 0;
}
