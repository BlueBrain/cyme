#include <regression/test_header.hpp>

using namespace cyme::test;

BOOST_AUTO_TEST_CASE(factorial_zero){
   std::size_t a(1),b;
   b=numeric::factorial<0>(); 
    
   BOOST_CHECK_EQUAL(a,b);
}

BOOST_AUTO_TEST_CASE(factorial_10){
   std::size_t a(3628800),b;
   b=numeric::factorial<10>(); 
    
   BOOST_CHECK_EQUAL(a,b);
}

BOOST_AUTO_TEST_CASE(quotient_factorial_10_9){
   std::size_t a = numeric::helper_quotient_factorial<9,10>::quotient_factorial();
   std::size_t b(10);
   BOOST_CHECK_EQUAL(a,b);
}

BOOST_AUTO_TEST_CASE(quotient_factorial_10_4){
   std::size_t a = numeric::helper_quotient_factorial<4,10>::quotient_factorial();
   std::size_t b(151200);
   BOOST_CHECK_EQUAL(a,b);
}
