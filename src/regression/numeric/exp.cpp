#include <regression/test_header.hpp>

using namespace corebluron::test;

#define TYPE typename T::value_type
#define N T::n
#define SIZE T::size
#define MAX 1000 


BOOST_AUTO_TEST_CASE_TEMPLATE(std_exp_comparison, T, floating_point_test_types) {
    TYPE b = TYPE(); // 0
    TYPE b_std = TYPE(); // 0
   
    for(int i=0; i<MAX; ++i){
        TYPE a = GetRandom<TYPE>();
        b = numeric::exp<TYPE,14>(a);
        b_std = std::exp(a);
        BOOST_REQUIRE_CLOSE( b, b_std, 0.001); 
    }
}

BOOST_AUTO_TEST_CASE_TEMPLATE(std_vec_exp_comparison, T, floating_point_test_types) {
    TYPE a[SIZE];
    TYPE b[SIZE];
    TYPE c[SIZE];
    // To change to something more generic
    for(int i=0; i<MAX; ++i){
        for(int j=0; j<SIZE; ++j)
            b[j] = GetRandom<TYPE>();
       
        numeric::exp<TYPE,N>(&a[0],&b[0]); //vectorial version
       
        for(int j=0; j<SIZE; ++j)
            numeric::exp<TYPE,N>(c[j],b[j]); //serial
       
        for(int j=0; j<SIZE; ++j){
            BOOST_CHECK_CLOSE( a[j], c[j], 0.0001); 
        }
    }
}

#undef TYPE
#undef N
#undef MAX
#undef SIZE
