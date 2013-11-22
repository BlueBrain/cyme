#include <regression/test_header.hpp>

using namespace cyme::test;

#define TYPE typename T::value_type
#define N T::n
#define SIZE T::size
#define MAX 1000 


BOOST_AUTO_TEST_CASE_TEMPLATE(std_exp_comparison, T, floating_point_test_types) {
    int n = memory::__GETSIMD__()/sizeof(TYPE);
    TYPE a[n] __attribute__((aligned(64)));
    TYPE b[n] __attribute__((aligned(64)));
    TYPE res[n] __attribute__((aligned(64)));

    std::cout << n << std::endl;

    for(int i=0; i<n; ++i){
        a[i] = GetRandom<TYPE>();
        b[i] = GetRandom<TYPE>();
    }

    numeric::vec_simd<TYPE,memory::__GETSIMD__()> va(a);
    numeric::vec_simd<TYPE,memory::__GETSIMD__()> vb(b);

    for(int i=0; i<n; ++i)
        a[i] = exp(b[i]);

    va = exp(vb);
    va.store(res);

    for(int i=0; i<n; ++i)
        std::cout << b[i] << " " << a[i] << " " << res[i] << std::endl;
//        BOOST_REQUIRE_CLOSE( a[i], res[i], 0.001);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(std_vec_exp_comparison, T, floating_point_test_types) {

}

#undef TYPE
#undef N
#undef MAX
#undef SIZE
