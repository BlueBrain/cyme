#include <iostream>
#include <fstream>
#include <iomanip>  
#include <limits>  

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
#include "utils/timer.h"
#include "helper.h"

#define SIZE 512*16384

struct test_case{
    //redefine the operator() for boost mpl
    template<typename Solver>
    void operator()(Solver const&){
        int size_vector = SIZE;

       std::vector<typename Solver::value_type > vec_input(size_vector);
       std::vector<typename Solver::value_type > vec_output_serial(size_vector);
       std::vector<typename Solver::value_type > vec_output_vec(size_vector);

       for(long long int i(0); i < size_vector; ++i)
                vec_input[i] = GetRandom<typename Solver::value_type>(); 

       timer t;
       t.start();

       for(long long int i(0); i < size_vector; i += memory::stride<typename Solver::value_type, Solver::O>::helper_stride())
          Solver::op(    helper_pointer<typename Solver::value_type, Solver::O>::get(vec_output_serial[i]),
                         helper_pointer<typename Solver::value_type, Solver::O>::get(vec_input[i]);

       t.stop();
       std::cout << Solver::name() << ", " << t.get() << " [s] " <<  std::endl;
    }
};

    int main(int argc, char * argv[]){
        //generate all variants, we call the operator() defined previously
        boost::mpl::for_each<Solver_op_list_2>(test_case());
        return 0;
    }
