#include <test/unit/test_header.hpp>

using namespace cyme::test;

#define TYPE typename T::value_type
#define SIZE T::size
#define MAX 1000

#define NN memory::unroll_factor::N*memory::trait_register<TYPE,memory::__GETSIMD__()>::size/sizeof(TYPE)

BOOST_AUTO_TEST_CASE_TEMPLATE(std_pow_comparison, T, floating_point_test_types) {
    TYPE a[NN] __attribute__((aligned(64)));
    TYPE b[NN] __attribute__((aligned(64)));
    TYPE res[NN] __attribute__((aligned(64)));
        for(size_t i=0; i<NN; ++i){
            a[i] = GetRandom<TYPE>();
            b[i] = GetRandom<TYPE>();
        }

        numeric::vec_simd<TYPE,memory::__GETSIMD__(),memory::unroll_factor::N> va(a);
        numeric::vec_simd<TYPE,memory::__GETSIMD__(),memory::unroll_factor::N> vb(b);

        for(size_t i=0; i<NN; ++i)
            a[i] = std::pow(b[i],7);

        va = numeric::pow<TYPE,memory::__GETSIMD__(),memory::unroll_factor::N,7>(vb);
        va.store(res);

        for(size_t i=0; i<NN; ++i)
          BOOST_REQUIRE_CLOSE( a[i], res[i], 0.001);

        for(size_t i=0; i<NN; ++i)
            a[i] = std::pow(b[i],6);

        va = numeric::pow<TYPE,memory::__GETSIMD__(),memory::unroll_factor::N,6>(vb);

        va.store(res);

        for(size_t i=0; i<NN; ++i)
          BOOST_REQUIRE_CLOSE( a[i], res[i], 0.001);
}

#undef NN
#undef TYPE
#undef MAX
#undef SIZE
