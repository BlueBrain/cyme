#include <regression/test_header.hpp>

using namespace corebluron::test;

#define TYPE typename T::value_type
#define N T::n
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

#undef TYPE
#undef N
#undef MAX
