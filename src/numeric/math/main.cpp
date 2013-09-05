#include <iostream>

#include <xmmintrin.h>
#include <emmintrin.h>

#include "trait.hpp"
#include "simd_wrapper.hpp"
#include "simd_vec.hpp"
#include "pow.hpp"
#include "fac.hpp"
#include "exp.hpp"


using namespace numeric;

int main(int argc, char* argv[]){
    double a1[2];
    double a2[2];
    double a3[2];
    a2[0] = atof(argv[1]);
    a2[1] = atof(argv[2]);

  //  exp<double,20>(&a1[0],&a2[0]);

    exp<double,20>(a3[0],a2[0]);
    exp<double,20>(a3[1],a2[1]);

    std::cout << a1[0] << " " << a1[1] << std::endl;
    std::cout << a3[0] << " " << a3[1] << std::endl;
}
