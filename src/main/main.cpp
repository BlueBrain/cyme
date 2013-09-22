//#include <vector>
//#include <cassert>
#include <iostream>

#include "numeric/math/math.hpp"
#include "memory/block.hpp"
#include "utils/timer.h"

#define TYPE double
#define SIZE 1
#define M 16
#define ORDER AoS

#define P_aos (*it_aos)
#define P_aosoa (*it_aosoa)

int main(int argc, char* argv[]){

    srand(-1);

    memory::block<TYPE,M,SIZE, memory::AoS> block_aos;
    memory::block<TYPE,M,SIZE, memory::AoSoA> block_aosoa;

    for(int i=0; i <SIZE; ++i)
        for(int j=0; j <M; ++j){
            block_aos(i,j) = drand48();
            block_aosoa(i,j) = drand48();
        }

    memory::block<TYPE,M,SIZE, memory::AoS>::iterator it_aos = block_aos.begin();
    memory::block<TYPE,M,SIZE, memory::AoSoA>::iterator it_aosoa = block_aosoa.begin();

    long long int t1 = rdtsc();

    for(it_aos = block_aos.begin(); it_aos != block_aos.end(); ++it_aos)
            P_aos[0] = (2.1*P_aos[15]*(P_aos[2]*(P_aos[1]+P_aos[3]) + P_aos[12]*(P_aos[9]+P_aos[6])) + 8)/P_aos[12];

    long long int t2 = rdtsc();
    std::cout << " cycle aos " << t2 - t1 << std::endl;


    t1 = rdtsc();
    for(it_aosoa = block_aosoa.begin(); it_aosoa != block_aosoa.end(); ++it_aosoa)
            P_aosoa[0] = (2.1*P_aosoa[15]*(P_aosoa[2]*(P_aosoa[1]+P_aosoa[3]) + P_aosoa[12]*(P_aosoa[9]+P_aosoa[6])) + 8)/P_aosoa[12];

    
    t2 = rdtsc();
    std::cout << " cycle aosoa " << t2 - t1 << std::endl;













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
