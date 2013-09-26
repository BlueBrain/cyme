#include <regression/test_header.hpp>

using namespace corebluron::test;

#define TYPE typename T::value_type
#define N T::n
#define M T::m
#define ORDER T::order 
#define MAX 1000 

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
    memory::block<TYPE,M,N,memory::AoS> block_a;
    memory::block<TYPE,M,N,memory::AoSoA> block_b;

    init(block_a, block_b);

    check(block_a, block_b);
}


BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_equal, T, floating_point_torture_list) {
    memory::block<TYPE,M,N,memory::AoS> block_a;
    memory::block<TYPE,M,N,memory::AoSoA> block_b;

    init(block_a, block_b);

    typename memory::block<TYPE,M,N,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1];

    typename memory::block<TYPE,M,N,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = (*it_AoSoA)[1];

    check(block_a, block_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_equal_multiple, T, floating_point_block_types) {
    memory::block<TYPE,4,N,memory::AoS> block_a;
    memory::block<TYPE,4,N,memory::AoSoA> block_b;

    init(block_a, block_b);

    typename memory::block<TYPE,4,N,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS){
        (*it_AoS)[0] = (*it_AoS)[0];
        (*it_AoS)[0] = (*it_AoS)[1];
        (*it_AoS)[0] = (*it_AoS)[2];
        (*it_AoS)[0] = (*it_AoS)[3];

        (*it_AoS)[1] = (*it_AoS)[0];
        (*it_AoS)[1] = (*it_AoS)[1];
        (*it_AoS)[1] = (*it_AoS)[2];
        (*it_AoS)[1] = (*it_AoS)[3];

        (*it_AoS)[2] = (*it_AoS)[0];
        (*it_AoS)[2] = (*it_AoS)[1];
        (*it_AoS)[2] = (*it_AoS)[2];
        (*it_AoS)[2] = (*it_AoS)[3];

        (*it_AoS)[3] = (*it_AoS)[0];
        (*it_AoS)[3] = (*it_AoS)[1];
        (*it_AoS)[3] = (*it_AoS)[2];
        (*it_AoS)[3] = (*it_AoS)[3];
    }


    typename memory::block<TYPE,4,N,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA){
        (*it_AoSoA)[0] = (*it_AoSoA)[0];
        (*it_AoSoA)[0] = (*it_AoSoA)[1];
        (*it_AoSoA)[0] = (*it_AoSoA)[2];
        (*it_AoSoA)[0] = (*it_AoSoA)[3];

        (*it_AoSoA)[1] = (*it_AoSoA)[0];
        (*it_AoSoA)[1] = (*it_AoSoA)[1];
        (*it_AoSoA)[1] = (*it_AoSoA)[2];
        (*it_AoSoA)[1] = (*it_AoSoA)[3];

        (*it_AoSoA)[2] = (*it_AoSoA)[0];
        (*it_AoSoA)[2] = (*it_AoSoA)[1];
        (*it_AoSoA)[2] = (*it_AoSoA)[2];
        (*it_AoSoA)[2] = (*it_AoSoA)[3];

        (*it_AoSoA)[3] = (*it_AoSoA)[0];
        (*it_AoSoA)[3] = (*it_AoSoA)[1];
        (*it_AoSoA)[3] = (*it_AoSoA)[2];
        (*it_AoSoA)[3] = (*it_AoSoA)[3];
    }
    
    check(block_a, block_b);
}



BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_plusequal, T, floating_point_torture_list) {
    memory::block<TYPE,M,N,memory::AoS> block_a;
    memory::block<TYPE,M,N,memory::AoSoA> block_b;

    init(block_a, block_b);

    typename memory::block<TYPE,M,N,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] += (*it_AoS)[0];

    typename memory::block<TYPE,M,N,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] += (*it_AoSoA)[0];

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] += (*it_AoS)[1];

    it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] += (*it_AoSoA)[1];

    check(block_a, block_b);
    
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_minusequal, T, floating_point_torture_list) {
    memory::block<TYPE,M,N,memory::AoS> block_a;
    memory::block<TYPE,M,N,memory::AoSoA> block_b;

    init(block_a, block_b);

    typename memory::block<TYPE,M,N,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] -= (*it_AoS)[0];

    typename memory::block<TYPE,M,N,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] -= (*it_AoSoA)[0];

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] -= (*it_AoS)[1];

    it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] -= (*it_AoSoA)[1];

    check(block_a, block_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_multiplyequal, T, floating_point_torture_list) {
    memory::block<TYPE,M,N,memory::AoS> block_a;
    memory::block<TYPE,M,N,memory::AoSoA> block_b;

    init(block_a, block_b);

    typename memory::block<TYPE,M,N,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] *= (*it_AoS)[0];

    typename memory::block<TYPE,M,N,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] *= (*it_AoSoA)[0];

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] *= (*it_AoS)[1];

    it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] *= (*it_AoSoA)[1];

    check(block_a, block_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_divideequal, T, floating_point_torture_list) {
    memory::block<TYPE,M,N,memory::AoS> block_a;
    memory::block<TYPE,M,N,memory::AoSoA> block_b;

    init(block_a, block_b);

    typename memory::block<TYPE,M,N,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] /= (*it_AoS)[0];

    typename memory::block<TYPE,M,N,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] /= (*it_AoSoA)[0];

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] /= (*it_AoS)[1];

    it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] /= (*it_AoSoA)[1];

    check(block_a, block_b);
}


#undef TYPE
#undef N
#undef MAX
#undef SIZE
