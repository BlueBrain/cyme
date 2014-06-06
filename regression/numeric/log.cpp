#include <regression/test_header.hpp>

using namespace cyme::test;

#define TYPE typename T::value_type
#define SIZE T::size
#define MAX 1000


BOOST_AUTO_TEST_CASE_TEMPLATE(std_log_comparison, T, floating_point_test_types) {
    size_t n = memory::unroll_factor::N*memory::__GETSIMD__()/sizeof(TYPE);
    TYPE a[n] __attribute__((aligned(64)));
    TYPE b[n] __attribute__((aligned(64)));
    TYPE res[n] __attribute__((aligned(64)));
    for(size_t k=0; k<100; ++k){
        for(size_t i=0; i<n; ++i){
            b[i] = fabs(GetRandom<TYPE>());
        }

        numeric::vec_simd<TYPE,memory::__GETSIMD__(),memory::unroll_factor::N> va;
        numeric::vec_simd<TYPE,memory::__GETSIMD__(),memory::unroll_factor::N> vb(b);

        for(size_t i=0; i<n; ++i)
            a[i] = log(b[i]);

        va = log(vb);
        va.store(res);

        for(size_t i=0; i<n; ++i)
          BOOST_REQUIRE_CLOSE( a[i], res[i], 0.001);
    }
}

#undef TYPE
#undef MAX
#undef SIZE
