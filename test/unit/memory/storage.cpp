#include <test/unit/test_header.hpp>

using namespace cyme::test;

#define TYPE typename T::value_type
#define N T::n
#define SIZE T::size
#define ORDER T::order 
#define MAX 1000 

BOOST_AUTO_TEST_CASE_TEMPLATE(storage_init_default_constructor, T, floating_point_test_types) {
   memory::storage<TYPE, SIZE, ORDER> a; //should be set to 0
   TYPE test[SIZE];
   memset((void*)test, 0, SIZE*sizeof(TYPE));
   int b = memcmp((void*)test, (void*)&a(0), SIZE*sizeof(TYPE));
   BOOST_CHECK_EQUAL( b,0); 
}

BOOST_AUTO_TEST_CASE_TEMPLATE(storage_init_value_constructor, T, floating_point_test_types) {
   memory::storage<TYPE, SIZE, ORDER> a(1);
   TYPE test[SIZE];
   for(int i=0; i < SIZE; ++i)
       test[i]=1;
   int b = memcmp((void*)test, (void*)&a(0), SIZE*sizeof(TYPE));
   BOOST_CHECK_EQUAL(b,0); 
}

BOOST_AUTO_TEST_CASE_TEMPLATE(storage_init_operator, T, floating_point_test_types) {
   memory::storage<TYPE, SIZE, ORDER> a;
   TYPE test[SIZE];
   for(int i=0; i < SIZE; ++i){
       test[i]=i;
       a(i)=i;
   }
   int b = memcmp((void*)test, (void*)&a(0), SIZE*sizeof(TYPE));
   BOOST_CHECK_EQUAL(b,0); 
}

BOOST_AUTO_TEST_CASE_TEMPLATE(storage_operator, T, floating_point_test_types) {
   memory::storage<TYPE, SIZE, ORDER> a;
   TYPE test = GetRandom<TYPE>();
   a(SIZE-1) = test;
   TYPE res = a(SIZE-1);
   BOOST_CHECK_CLOSE( res, test, 0.0001);
}

#undef TYPE
#undef N
#undef MAX
#undef SIZE
