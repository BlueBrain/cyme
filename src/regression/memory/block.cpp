#include <regression/test_header.hpp>

using namespace corebluron::test;

#define TYPE typename T::value_type
#define N T::n
#define M T::m
#define ORDER T::order 
#define MAX 1000 
//M*N is not really the size for AoSoA, as I may have additional padding to respect the structure
//TO DO: write better test
BOOST_AUTO_TEST_CASE_TEMPLATE(block_init_default_constructor, T, floating_point_block_types) {
     memory::block<TYPE,M,N,ORDER> block_a;
     TYPE test[M*N];
     memset((void*)test, 0, M*N*sizeof(TYPE));
     int b = memcmp((void*)test, (void*)&block_a(0,0), M*N*sizeof(TYPE));
     BOOST_CHECK_EQUAL( b,0); 
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_init_value_constructor, T, floating_point_block_types) {
     TYPE random = GetRandom<TYPE>(); 
     memory::block<TYPE,M,N,ORDER> block_a(random);
     TYPE test[M*N];
     for(int i=0; i < M*N; ++i)
         test[i]=random;
     int b = memcmp((void*)test, (void*)&block_a(0,0), M*N*sizeof(TYPE));
     BOOST_CHECK_EQUAL(b,0); 
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_init_operator_bracket, T, floating_point_block_types) {
     TYPE random;
     memory::block<TYPE,M,N,memory::AoS> block_a;
     memory::block<TYPE,M,N,memory::AoSoA> block_b;

     TYPE res_a[M][N];
     TYPE res_b[M][N];

     for(int i=0; i<M; ++i)
         for(int j=0; j<N; ++j){
            random = GetRandom<TYPE>(); 
            block_a(i,j) = random; 
            block_b(i,j) = random; 
            res_a[i][j] = block_a(i,j);
            res_b[i][j] = block_b(i,j);
         }

     int b_bool = memcmp((void*)res_a, (void*)res_b, M*N*sizeof(TYPE));
     std::cout << b_bool << std::endl;
     BOOST_CHECK_EQUAL(b_bool,0); 
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_add, T, floating_point_block_types) {
     TYPE random;
     memory::block<TYPE,M,N,memory::AoS> block_a;
     memory::block<TYPE,M,N,memory::AoSoA> block_b;

     TYPE test_a[M][N], res_a[M][N];
     TYPE test_b[M][N], res_b[M][N];

     for(int i=0; i<M; ++i)
         for(int j=0; j<N; ++j){
            random = GetRandom<TYPE>(); 
            block_a(i,j) = random; 
            block_b(i,j) = random; 
            test_a[i][j] = random;
            test_b[i][j] = random;
         }
    std::cout << " hello " << std::endl;

    typename memory::block<TYPE,M,N,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
         numeric::add<TYPE>((*it_AoS)[0],(*it_AoS)[1]);
 
    typename memory::block<TYPE,M,N,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
         numeric::add<TYPE>((*it_AoSoA)[0],(*it_AoSoA)[1]);
    
    for(int i=0; i<M; ++i)
        for(int j=0; j<N; ++j){
           test_a[0][j] += test_b[1][j];
           res_a[i][j] = block_a(i,j);
           res_b[i][j] = block_b(i,j);
        }
    
    int block_b_bool = memcmp((void*)res_a, (void*)res_b, M*N*sizeof(TYPE));
    int block_a_bool = memcmp((void*)res_b, (void*)test_a, M*N*sizeof(TYPE));

    std::cout << block_b_bool << " " << block_a_bool << std::endl;

}

#undef TYPE
#undef N
#undef MAX
#undef SIZE
