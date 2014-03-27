#include <regression/test_header.hpp>

using namespace cyme::test;

#define TYPE typename T::value_type
#define SIZE T::size
#define MAX 1000 


BOOST_AUTO_TEST_CASE_TEMPLATE(std_exp_comparison, T, floating_point_test_types) {
    int n = memory::unroll_factor::N*memory::__GETSIMD__()/sizeof(TYPE);
    TYPE a[n] __attribute__((aligned(64)));
    TYPE b[n] __attribute__((aligned(64)));
    TYPE res[n] __attribute__((aligned(64)));
    for(int k=0; k<100; ++k){
        for(int i=0; i<n; ++i){
            a[i] = GetRandom<TYPE>();
            b[i] = GetRandom<TYPE>();
        }
        
        numeric::vec_simd<TYPE,memory::__GETSIMD__(),memory::unroll_factor::N> va(a);
        numeric::vec_simd<TYPE,memory::__GETSIMD__(),memory::unroll_factor::N> vb(b);
        
        for(int i=0; i<n; ++i)
            a[i] = exp(b[i]);
        
        va = exp(vb);
        va.store(res);
        
        for(int i=0; i<n; ++i)
          BOOST_REQUIRE_CLOSE( a[i], res[i], 0.001);
    }
}

#undef TYPE
#undef MAX
#undef SIZE
