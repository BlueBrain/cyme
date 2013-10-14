#include <regression/test_header.hpp>

using namespace cyme::test;

#define TYPE typename T::value_type
#define SIZE T::size
#define N T::n
#define MAX 1000 
//MAKE SIMD test is not easy do I do : memory -> simd register (perform something) -> memory where I finally test
//not the SIMD type is presently given bu the __GETSIMD__() function hardcoded into /memory/detail/simd.h
BOOST_AUTO_TEST_CASE_TEMPLATE(vec_simd_init_default_constructor, T, floating_point_test_types) {
    int n = memory::__GETSIMD__()/sizeof(TYPE);
    numeric::vec_simd<TYPE,memory::__GETSIMD__()> a;
    TYPE test[n]; 
    TYPE res[n] __attribute__((aligned(64)));
    memset((void*)test,0,n*sizeof(TYPE)); 
    a.store(res);
    int b = memcmp((void*)test,(void*)res,n*sizeof(TYPE)); 
    BOOST_CHECK_EQUAL(0,b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vec_simd_init_constant_constructor, T, floating_point_test_types) {
    int n = memory::__GETSIMD__()/sizeof(TYPE);
    TYPE Random = GetRandom<TYPE>();
    numeric::vec_simd<TYPE,memory::__GETSIMD__()> a(Random);
    TYPE test[n]; 
    TYPE res[n] __attribute__((aligned(64)));
   for(int i=0; i<n; ++i)
       test[i]=Random;
    a.store(res);
    int b = memcmp((void*)test,(void*)res,n*sizeof(TYPE)); 
    BOOST_CHECK_EQUAL(0,b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vec_simd_init_pointer_constructor, T, floating_point_test_types) {
    int n = memory::__GETSIMD__()/sizeof(TYPE);
    TYPE test[n]  __attribute__((aligned(64)))  ; 
    TYPE res[n] __attribute__((aligned(64)));
    for(int i=0; i<n; ++i){
       test[i] = GetRandom<TYPE>();
    }
    numeric::vec_simd<TYPE,memory::__GETSIMD__()> a(test);
    a.store(res);
    int b = memcmp((void*)test,(void*)res,n*sizeof(TYPE)); 
    BOOST_CHECK_EQUAL(0,b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vec_simd_add_operations, T, floating_point_test_types) {

    int n = memory::__GETSIMD__()/sizeof(TYPE);
    TYPE a[n] __attribute__((aligned(64)));
    TYPE b[n] __attribute__((aligned(64)));
    TYPE res[n] __attribute__((aligned(64)));

    for(int i=0; i<n; ++i){
       a[i] = GetRandom<TYPE>();
       b[i] = GetRandom<TYPE>();
    }

    numeric::vec_simd<TYPE,memory::__GETSIMD__()> va(a);
    numeric::vec_simd<TYPE,memory::__GETSIMD__()> vb(b);

    for(int i=0; i<n; ++i)
        a[i] += b[i];

    va += vb;
    va.store(res);

    int b_bool = memcmp((void*)res,(void*)a,n*sizeof(TYPE)); 
    BOOST_CHECK_EQUAL(0,b_bool);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vec_simd_sub_operations, T, floating_point_test_types) {

    int n = memory::__GETSIMD__()/sizeof(TYPE);
    TYPE a[n] __attribute__((aligned(64)));
    TYPE b[n] __attribute__((aligned(64)));
    TYPE res[n] __attribute__((aligned(64)));

    for(int i=0; i<n; ++i){
       a[i] = GetRandom<TYPE>();
       b[i] = GetRandom<TYPE>();
    }

    numeric::vec_simd<TYPE,memory::__GETSIMD__()> va(a);
    numeric::vec_simd<TYPE,memory::__GETSIMD__()> vb(b);

    for(int i=0; i<n; ++i)
        a[i] -= b[i];

    va -= vb;
    va.store(res);

    int b_bool = memcmp((void*)res,(void*)a,n*sizeof(TYPE)); 
    BOOST_CHECK_EQUAL(0,b_bool);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vec_simd_mul_operations, T, floating_point_test_types) {

    int n = memory::__GETSIMD__()/sizeof(TYPE);
    TYPE a[n] __attribute__((aligned(64)));
    TYPE b[n] __attribute__((aligned(64)));
    TYPE res[n] __attribute__((aligned(64)));

    for(int i=0; i<n; ++i){
       a[i] = GetRandom<TYPE>();
       b[i] = GetRandom<TYPE>();
    }

    numeric::vec_simd<TYPE,memory::__GETSIMD__()> va(a);
    numeric::vec_simd<TYPE,memory::__GETSIMD__()> vb(b);

    for(int i=0; i<n; ++i)
        a[i] *= b[i];

    va *= vb;
    va.store(res);

    int b_bool = memcmp((void*)res,(void*)a,n*sizeof(TYPE)); 
    BOOST_CHECK_EQUAL(0,b_bool);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vec_simd_div_operations, T, floating_point_test_types) {

    int n = memory::__GETSIMD__()/sizeof(TYPE);
    TYPE a[n] __attribute__((aligned(64)));
    TYPE b[n] __attribute__((aligned(64)));
    TYPE res[n] __attribute__((aligned(64)));

    for(int i=0; i<n; ++i){
       a[i] = GetRandom<TYPE>();
       b[i] = GetRandom<TYPE>();
    }

    numeric::vec_simd<TYPE,memory::__GETSIMD__()> va(a);
    numeric::vec_simd<TYPE,memory::__GETSIMD__()> vb(b);

    for(int i=0; i<n; ++i)
        a[i] /= b[i];

    va /= vb;
    va.store(res);

    int b_bool = memcmp((void*)res,(void*)a,n*sizeof(TYPE)); 
    BOOST_CHECK_EQUAL(0,b_bool);
}

#undef SIZE
#undef TYPE
#undef N
#undef MAX
