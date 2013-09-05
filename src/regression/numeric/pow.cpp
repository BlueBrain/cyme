#include <regression/test_header.hpp>

using namespace corebluron::test;

#define TYPE typename T::value_type
#define SIZE T::size
#define N T::n
#define MAX 1000 

BOOST_AUTO_TEST_CASE_TEMPLATE(pow_zero, T, full_test_types) {
    T a = 1;
    T b = numeric::pow<T,0>(1);
   
    BOOST_CHECK_EQUAL(a,b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(one_to_the_power_3, T, full_test_types) {
    T a = 1;
    T b = numeric::pow<T,3>(1);
    BOOST_CHECK_EQUAL(a,b);
}


BOOST_AUTO_TEST_CASE_TEMPLATE(std_pow_comparison, T, floating_point_test_types) {
    TYPE b = TYPE(); // 0
    TYPE b_std = TYPE(); // 0
   
    for(int i=0; i<MAX; ++i){
        TYPE a = GetRandom<TYPE>();
        b = numeric::pow<TYPE,N>(a);
        b_std = pow(a,N);
        BOOST_CHECK_CLOSE( b, b_std, 0.0001); 
    }
}


BOOST_AUTO_TEST_CASE_TEMPLATE(std_vec_pow_comparison, T, floating_point_test_types) {
    TYPE a[SIZE];
    TYPE b[SIZE];
    TYPE c[SIZE];
    // To change to something more generic
    for(int i=0; i<MAX; ++i){
        for(int j=0; j<SIZE; ++j)
            b[j] = GetRandom<TYPE>();
       
        numeric::pow<TYPE,3>(&a[0],&b[0]); //vectorial version
       
        for(int j=0; j<SIZE; ++j)
            numeric::pow<TYPE,3>(c[j],b[j]); //serial
       
        for(int j=0; j<SIZE; ++j)
            BOOST_CHECK_CLOSE( a[j], c[j], 0.0001); 
    }
}

#undef SIZE
#undef TYPE
#undef N
#undef MAX
