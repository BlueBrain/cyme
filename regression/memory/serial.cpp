#include <regression/test_header.hpp>

using namespace cyme::test;

#define TYPE typename T::value_type
#define N T::n
#define M T::m
#define ORDER T::order 
#define MAX 1000 

template<class T, size_t size>
struct synapse{
   typedef T value_type;
   static const size_t value_size = size;
};

BOOST_AUTO_TEST_CASE_TEMPLATE(block_init_default_constructor, T, floating_point_block_types) {
     cyme::serial<TYPE,ORDER> a;
     cyme::vector<synapse<TYPE,1>,ORDER> v(memory::stride<TYPE,ORDER>::helper_stride(),0);
     for(size_t i = 0;  i< memory::stride<TYPE,ORDER>::helper_stride();++i)
          BOOST_CHECK_CLOSE(v(i*ORDER,0),0,relative_error<TYPE>()); 
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_init_default_constructor_value, T, floating_point_block_types) {
     cyme::serial<TYPE,ORDER> a(1);
     cyme::vector<synapse<TYPE,1>,ORDER> v(memory::stride<TYPE,ORDER>::helper_stride(),1);
     for(size_t i = 0;  i< memory::stride<TYPE,ORDER>::helper_stride();++i)
          BOOST_CHECK_CLOSE(v(i*ORDER,0),1,relative_error<TYPE>()); 
}

BOOST_AUTO_TEST_CASE_TEMPLATE(serial_doest_not_store, T, floating_point_block_types) {
     cyme::vector<synapse<TYPE,1>,ORDER> v(memory::stride<TYPE,ORDER>::helper_stride(),2);
     typename cyme::vector<synapse<TYPE,1>,ORDER>::const_iterator it_AoSoA = v.begin();
     cyme::serial<TYPE,ORDER> a = (*it_AoSoA)[0];
     v[0][0] = a();
     for(size_t i = 0;  i< memory::stride<TYPE,ORDER>::helper_stride();++i)
         BOOST_CHECK_CLOSE(v(i*ORDER,0),2,relative_error<TYPE>()); 
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_ops_value, T, floating_point_block_types) {
     cyme::serial<TYPE,ORDER> a(2);
     cyme::vector<synapse<TYPE,1>,ORDER> v(memory::stride<TYPE,ORDER>::helper_stride(),2);
     v[0][0] += a();
     for(size_t i = 0;  i< memory::stride<TYPE,ORDER>::helper_stride();++i)
          BOOST_CHECK_CLOSE(v(i*ORDER,0),4,relative_error<TYPE>()); 

     v[0][0] *= a();
     for(size_t i = 0;  i< memory::stride<TYPE,ORDER>::helper_stride();++i)
          BOOST_CHECK_CLOSE(v(i*ORDER,0),8,relative_error<TYPE>()); 

     v[0][0] -= a();
     for(size_t i = 0;  i< memory::stride<TYPE,ORDER>::helper_stride();++i)
          BOOST_CHECK_CLOSE(v(i*ORDER,0),6,relative_error<TYPE>()); 

     v[0][0] /= a();
     for(size_t i = 0;  i< memory::stride<TYPE,ORDER>::helper_stride();++i)
          BOOST_CHECK_CLOSE(v(i*ORDER,0),3,relative_error<TYPE>()); 
}
/*
BOOST_AUTO_TEST_CASE_TEMPLATE(block_ops_value_second, T, floating_point_block_types) {
     cyme::serial<TYPE,ORDER> a(2);
     cyme::vector<synapse<TYPE,1>,ORDER> v(memory::stride<TYPE,ORDER>::helper_stride(),2);
     v[0][0] = v[0][0] + a();
     for(size_t i = 0;  i< memory::stride<TYPE,ORDER>::helper_stride();++i)
          BOOST_CHECK_CLOSE(v(i*ORDER,0),4,relative_error<TYPE>()); 

     v[0][0] = v[0][0] * a();
     for(size_t i = 0;  i< memory::stride<TYPE,ORDER>::helper_stride();++i)
          BOOST_CHECK_CLOSE(v(i*ORDER,0),8,relative_error<TYPE>()); 

     v[0][0] = v[0][0] - a();
     for(size_t i = 0;  i< memory::stride<TYPE,ORDER>::helper_stride();++i)
          BOOST_CHECK_CLOSE(v(i*ORDER,0),6,relative_error<TYPE>()); 

     v[0][0] = v[0][0]/ a();
     for(size_t i = 0;  i< memory::stride<TYPE,ORDER>::helper_stride();++i)
          BOOST_CHECK_CLOSE(v(i*ORDER,0),3,relative_error<TYPE>()); 
}*/
