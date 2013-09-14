#include <regression/test_header.hpp>

using namespace corebluron::test;

#define TYPE typename T::value_type
#define SIZE T::size
#define N T::n
#define MAX 1000 
//MAKE SIMD test is not easy do I do : memory -> simd register (perform something) -> memory where I finally test
//not the SIMD type is presently given bu the getsimd() function hardcoded into /memory/detail/simd.h
BOOST_AUTO_TEST_CASE_TEMPLATE(vec_init_default_constructor, T, floating_point_test_types) {
    int n = memory::getsimd()/sizeof(TYPE);
    numeric::vec<TYPE,memory::getsimd()> a;
    TYPE test[n],res[n]; 
    memset((void*)test,0,n*sizeof(TYPE)); 
    a.store(res);
    int b = memcmp((void*)test,(void*)res,n*sizeof(TYPE)); 
    BOOST_CHECK_EQUAL(0,b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vec_init_constant_constructor, T, floating_point_test_types) {
    int n = memory::getsimd()/sizeof(TYPE);
    TYPE Random = GetRandom<TYPE>();
    numeric::vec<TYPE,memory::getsimd()> a(Random);
    TYPE test[n],res[n]; 
   for(int i=0; i<n; ++i)
       test[i]=Random;
    a.store(res);
    int b = memcmp((void*)test,(void*)res,n*sizeof(TYPE)); 
    BOOST_CHECK_EQUAL(0,b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vec_init_pointer_constructor, T, floating_point_test_types) {
    int n = memory::getsimd()/sizeof(TYPE);
    TYPE test[n],res[n]; 
    for(int i=0; i<n; ++i){
       test[i] = GetRandom<TYPE>();
    }
    numeric::vec<TYPE,memory::getsimd()> a(test);
    a.store(res);
    int b = memcmp((void*)test,(void*)res,n*sizeof(TYPE)); 
    BOOST_CHECK_EQUAL(0,b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vec_add_operations, T, floating_point_test_types) {

    int n = memory::getsimd()/sizeof(TYPE);
    TYPE a[n],b[n],res[n]; 

    for(int i=0; i<n; ++i){
       a[i] = GetRandom<TYPE>();
       b[i] = GetRandom<TYPE>();
    }

    numeric::vec<TYPE,memory::getsimd()> va(a);
    numeric::vec<TYPE,memory::getsimd()> vb(b);

    for(int i=0; i<n; ++i)
        a[i] += b[i];

    va += vb;
    va.store(res);

    int b_bool = memcmp((void*)res,(void*)a,n*sizeof(TYPE)); 
    BOOST_CHECK_EQUAL(0,b_bool);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vec_mul_operations, T, floating_point_test_types) {

    int n = memory::getsimd()/sizeof(TYPE);
    TYPE a[n],b[n],res[n]; 

    for(int i=0; i<n; ++i){
       a[i] = GetRandom<TYPE>();
       b[i] = GetRandom<TYPE>();
    }

    numeric::vec<TYPE,memory::getsimd()> va(a);
    numeric::vec<TYPE,memory::getsimd()> vb(b);

    for(int i=0; i<n; ++i)
        a[i] *= b[i];

    va *= vb;
    va.store(res);

    int b_bool = memcmp((void*)res,(void*)a,n*sizeof(TYPE)); 
    BOOST_CHECK_EQUAL(0,b_bool);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vec_div_operations, T, floating_point_test_types) {

    int n = memory::getsimd()/sizeof(TYPE);
    TYPE a[n],b[n],res[n]; 

    for(int i=0; i<n; ++i){
       a[i] = GetRandom<TYPE>();
       b[i] = GetRandom<TYPE>();
    }

    numeric::vec<TYPE,memory::getsimd()> va(a);
    numeric::vec<TYPE,memory::getsimd()> vb(b);

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
