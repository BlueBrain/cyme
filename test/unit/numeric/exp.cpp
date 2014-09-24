#include <test/unit/test_header.hpp>

using namespace cyme::test;

#define TYPE typename T::value_type
#define SIZE T::size
#define MAX 1000

#define NN memory::unroll_factor::N*memory::trait_register<TYPE,memory::__GETSIMD__()>::size/sizeof(TYPE)

BOOST_AUTO_TEST_CASE_TEMPLATE(std_exp_comparison, T, floating_point_test_types) {
    TYPE a[NN] __attribute__((aligned(64)));
    TYPE b[NN] __attribute__((aligned(64)));
    TYPE res[NN] __attribute__((aligned(64)));
    for(size_t k=0; k<100; ++k){
        for(size_t i=0; i<NN; ++i){
            a[i] = GetRandom<TYPE>();
            b[i] = GetRandom<TYPE>();
        }

        numeric::vec_simd<TYPE,memory::__GETSIMD__(),memory::unroll_factor::N> va(a);
        numeric::vec_simd<TYPE,memory::__GETSIMD__(),memory::unroll_factor::N> vb(b);

        for(size_t i=0; i<NN; ++i)
            a[i] = exp(b[i]);

        va = exp(vb);
        va.store(res);

        for(size_t i=0; i<NN; ++i)
          BOOST_REQUIRE_CLOSE( a[i], res[i], 0.001);
    }
}

#undef NN
#undef TYPE
#undef MAX
#undef SIZE