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

#define SIZE 16384
#define M 16

struct test_case{
    //redefine the operator() for boost mpl
    template<typename Solver>
    void operator()(Solver const&){

        memory::block<typename Solver::value_type,M,SIZE, Solver::O> block;
          
        typename Solver::value_type random;

        for(int i=0; i <SIZE; ++i)
            for(int j=0; j <M; ++j){
                random  = GetRandom<typename Solver::value_type>();
                block(i,j) = random;
      
        }

       typename memory::block<typename Solver::value_type,M,SIZE, Solver::O>::iterator it = block.begin();

       timer t;
       t.start();

            for(it = block.begin(); it != block.end(); ++it){
                Solver::op((*it)[15],(*it)[0]);
                Solver::op((*it)[14],(*it)[1]);
                Solver::op((*it)[13],(*it)[2]);
                Solver::op((*it)[12],(*it)[3]);
                Solver::op((*it)[11],(*it)[4]);
                Solver::op((*it)[10],(*it)[5]);
                Solver::op((*it)[9],(*it)[6]);
                Solver::op((*it)[8],(*it)[7]);
                Solver::op((*it)[7],(*it)[8]);
                Solver::op((*it)[6],(*it)[9]);
                Solver::op((*it)[5],(*it)[10]);
                Solver::op((*it)[4],(*it)[11]);
                Solver::op((*it)[3],(*it)[12]);
                Solver::op((*it)[2],(*it)[13]);
                Solver::op((*it)[1],(*it)[14]);
                Solver::op((*it)[0],(*it)[15]);
            }   

       t.stop();
       std::cout << Solver::name() << ", " << t.get() << " [s] " <<  std::endl;
    }
};

int main(int argc, char * argv[]){
    boost::mpl::for_each<Solver_op_list>(test_case());
    return 0;
}
