#include <regression/test_header.hpp>

using namespace cyme::test;

#define TYPE typename T::value_type
#define N T::n
#define M T::m
#define ORDER T::order 
#define MAX 1000 



    template<class T, int size>
    struct synapse{
       typedef T value_type;
       static const int value_size = size;
    };

BOOST_AUTO_TEST_CASE_TEMPLATE(block_init_default_constructor, T, floating_point_block_types) {
     cyme::serial<TYPE,ORDER> a;
     cyme::vector<synapse<TYPE,1>,ORDER> v(memory::stride<TYPE,ORDER>::helper_stride(),0);
     for(size_t i = 0;  i< memory::stride<TYPE,ORDER>::helper_stride();++i)
          BOOST_CHECK_CLOSE(v(i*ORDER,0),0,RELATIVE_ERROR); 
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_init_default_constructor_value, T, floating_point_block_types) {
     cyme::serial<TYPE,ORDER> a(1);
     cyme::vector<synapse<TYPE,1>,ORDER> v(memory::stride<TYPE,ORDER>::helper_stride(),1);
     for(size_t i = 0;  i< memory::stride<TYPE,ORDER>::helper_stride();++i)
          BOOST_CHECK_CLOSE(v(i*ORDER,0),1,RELATIVE_ERROR); 
}

BOOST_AUTO_TEST_CASE_TEMPLATE(serial_doest_not_store, T, floating_point_block_types) {
     cyme::vector<synapse<TYPE,1>,ORDER> v(memory::stride<TYPE,ORDER>::helper_stride(),2);
     cyme::serial<TYPE,ORDER> a = v[0][0];
     v[0][0] = a();
     for(size_t i = 0;  i< memory::stride<TYPE,ORDER>::helper_stride();++i)
         BOOST_CHECK_CLOSE(v(i*ORDER,0),2,RELATIVE_ERROR); 
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_ops_value, T, floating_point_block_types) {
     cyme::serial<TYPE,ORDER> a(2);
     cyme::vector<synapse<TYPE,1>,ORDER> v(memory::stride<TYPE,ORDER>::helper_stride(),2);
     v[0][0] += a();
     for(size_t i = 0;  i< memory::stride<TYPE,ORDER>::helper_stride();++i)
          BOOST_CHECK_CLOSE(v(i*ORDER,0),4,RELATIVE_ERROR); 

     v[0][0] *= a();
     for(size_t i = 0;  i< memory::stride<TYPE,ORDER>::helper_stride();++i)
          BOOST_CHECK_CLOSE(v(i*ORDER,0),8,RELATIVE_ERROR); 

     v[0][0] -= a();
     for(size_t i = 0;  i< memory::stride<TYPE,ORDER>::helper_stride();++i)
          BOOST_CHECK_CLOSE(v(i*ORDER,0),6,RELATIVE_ERROR); 

     v[0][0] /= a();
     for(size_t i = 0;  i< memory::stride<TYPE,ORDER>::helper_stride();++i)
          BOOST_CHECK_CLOSE(v(i*ORDER,0),3,RELATIVE_ERROR); 
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_ops_value_second, T, floating_point_block_types) {
     cyme::serial<TYPE,ORDER> a(2);
     cyme::vector<synapse<TYPE,1>,ORDER> v(memory::stride<TYPE,ORDER>::helper_stride(),2);
     v[0][0] = v[0][0] + a();
     for(size_t i = 0;  i< memory::stride<TYPE,ORDER>::helper_stride();++i)
          BOOST_CHECK_CLOSE(v(i*ORDER,0),4,RELATIVE_ERROR); 

     v[0][0] = v[0][0] * a();
     for(size_t i = 0;  i< memory::stride<TYPE,ORDER>::helper_stride();++i)
          BOOST_CHECK_CLOSE(v(i*ORDER,0),8,RELATIVE_ERROR); 

     v[0][0] = v[0][0] - a();
     for(size_t i = 0;  i< memory::stride<TYPE,ORDER>::helper_stride();++i)
          BOOST_CHECK_CLOSE(v(i*ORDER,0),6,RELATIVE_ERROR); 

     v[0][0] = v[0][0]/ a();
     for(size_t i = 0;  i< memory::stride<TYPE,ORDER>::helper_stride();++i)
          BOOST_CHECK_CLOSE(v(i*ORDER,0),3,RELATIVE_ERROR); 
}
