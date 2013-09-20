//#include <vector>
//#include <cassert>
#include <iostream>

#include "numeric/math/math.hpp"
#include "memory/block.hpp"
#include "utils/timer.h"

#define TYPE double
#define SIZE 1
#define M 16

#define P (*it)

int main(int argc, char* argv[]){

    srand(-1);

    memory::block<TYPE,M,SIZE, memory::AoSoA> block;

    for(int i=0; i <SIZE; ++i)
        for(int j=0; j <M; ++j){
            block(i,j) = drand48();
        }

    typename memory::block<TYPE,M,SIZE, memory::AoSoA>::iterator it = block.begin();

    timer t;
    t.start();

    long long int t1 = rdtsc();

    for(it = block.begin(); it != block.end(); ++it){
//        for(int i = 0; i<0xfff; ++i)
//            P[0] = 3.14*P[15]*(12.2*P[2]*(P[1]+P[3]) + 23.1*P[12]*(P[9]+P[6]));
        P[0] = P[1]*P[2];

    }
    std::cout << " dlsaubhludsghvab " << std::endl;
//    double a[2];
//    P[0].rep().store(a);


    long long int t2 = rdtsc();


    t.stop();















/*
    srand(-9861);

    double i_u[2],a[2];
    i_u[0] = drand48();
    i_u[1] = drand48();

    double i_v[2];
    i_v[0] = drand48();
    i_v[1] = drand48();

    double i_w[2];
    i_w[0] = drand48();
    i_w[1] = drand48();

    double i_y[2];
    i_y[0] = drand48();
    i_y[1] = drand48();


    numeric::Vec<double, memory::sse>u(i_u);
    numeric::Vec<double, memory::sse>v(i_v);
    numeric::Vec<double, memory::sse>w(i_w);
    numeric::Vec<double, memory::sse>y(i_y);


    u = 2.0*(w*(v*y)+y*(w+v));
//    u = 2.0*w;

    u.rep().store(a);
 
    std::cout << a[0] << " " << a[1] << std::endl;
 */
}







/*
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

#define SIZE 16384
struct test_case{
    //redefine the operator() for boost mpl
    template<typename Solver>
    void operator()(Solver const&){
        int size_vector = SIZE;

       std::vector<typename Solver::value_type > vec_input(size_vector);
       std::vector<typename Solver::value_type > vec_output_serial(size_vector);

        for(long long int i(0); i < size_vector; ++i){
                vec_input[i] = GetRandom<typename Solver::value_type>();
                vec_output_serial[i] = GetRandom<typename Solver::value_type>();
        }

       timer t;
       t.start();

        for(long long int i(0); i < size_vector; i += memory::stride<typename Solver::value_type, Solver::O>::helper_stride()){
          Solver::op( 
                        vec_output_serial[i],
                        vec_input[i]
                    );
        }
       t.stop();
       std::cout << Solver::name() << ", " << t.get() << " [s] " <<  std::endl;
    }
};

    int main(int argc, char * argv[]){
        //generate all variants, we call the operator() defined previously
        boost::mpl::for_each<Solver_op_list_2>(test_case());
        return 0;
    }
*/
