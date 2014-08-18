#include <test/unit/test_header.hpp>

using namespace cyme::test;

#define TYPE typename T::value_type
#define SIZE T::size
#define MAX 1000

#define NN memory::unroll_factor::N*memory::trait_register<TYPE,memory::__GETSIMD__()>::size/sizeof(TYPE)

template<class T>
T precision_log();

template<>
double precision_log(){
    return 0.005;
}

template<>
float precision_log(){
    return 5.0;
}

BOOST_AUTO_TEST_CASE_TEMPLATE(std_log_comparison, T, floating_point_test_types) {
    TYPE a[NN] __attribute__((aligned(64)));
    TYPE b[NN] __attribute__((aligned(64)));
    TYPE res[NN] __attribute__((aligned(64)));
    for(size_t k=0; k<100; ++k){
        for(size_t i=0; i<NN; ++i){
            b[i] = drand48();//fabs(GetRandom<TYPE>());
        }

        numeric::vec_simd<TYPE,memory::__GETSIMD__(),memory::unroll_factor::N> va;
        numeric::vec_simd<TYPE,memory::__GETSIMD__(),memory::unroll_factor::N> vb(b);

        for(size_t i=0; i<NN; ++i)
            a[i] = log(b[i]);

        va = log(vb);
        va.store(res);

        for(size_t i=0; i<NN; ++i)
          BOOST_REQUIRE_CLOSE( a[i], res[i], precision_log<TYPE>()); // precision soso on x86 try to understand why for float 0<x<=1 
                                                                     // {system : -0.00051404332} and me: -0.000523375755
    }
}

#undef NN
#undef TYPE
#undef MAX
#undef SIZE
