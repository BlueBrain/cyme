#include <regression/test_header.hpp>

using namespace cyme::test;

#define TYPE typename T::value_type
#define N T::n
#define M T::m
#define ORDER T::order 
#define MAX 1000 

    template<class S, int m>
    struct synapse{
       typedef S value_type;
       static const int value_size = m;
    };

BOOST_AUTO_TEST_CASE_TEMPLATE(block_init_default_constructor, T, floating_point_block_types) {
     cyme::array<synapse<TYPE,M>,N,ORDER> block_a;
     TYPE test[M*N];
     memset((void*)test, 0, M*N*sizeof(TYPE));
     int b = memcmp((void*)test, (void*)&block_a(0,0), M*N*sizeof(TYPE));
     BOOST_CHECK_EQUAL( b,0); 
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_init_value_constructor, T, floating_point_block_types) {
     TYPE random = GetRandom<TYPE>(); 
     cyme::array<synapse<TYPE,M>,N,ORDER> block_a(random);
     TYPE test[M*N];
     for(std::size_t i=0; i < M*N; ++i)
         test[i]=random;
     int b = memcmp((void*)test, (void*)&block_a(0,0), M*N*sizeof(TYPE));
     BOOST_CHECK_EQUAL(b,0); 
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_init_operator_bracket, T, floating_point_block_types) {
     cyme::array<synapse<TYPE,M>,N,ORDER> block_a;
     cyme::array<synapse<TYPE,M>,N,ORDER> block_b;

    init(block_a, block_b);

    check(block_a, block_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_copy_constructor, T, floating_point_block_types) {
     cyme::array<synapse<TYPE,M>,N,ORDER> block_a;
     cyme::array<synapse<TYPE,M>,N,ORDER> block_b;

    init(block_a, block_b);

    cyme::array<synapse<TYPE,M>,N,ORDER> block_a_cpy(block_a);
    cyme::array<synapse<TYPE,M>,N,ORDER> block_b_cpy(block_b);

    check(block_a, block_b);
    check(block_a_cpy, block_b_cpy);
}


BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_equal, T, floating_point_torture_list) {
    cyme::array<synapse<TYPE,M>,N,memory::AoS> block_a;
    cyme::array<synapse<TYPE,M>,N,memory::AoSoA> block_b;

    init(block_a, block_b);

    typename cyme::array<synapse<TYPE,M>,N,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1];

    typename cyme::array<synapse<TYPE,M>,N,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = (*it_AoSoA)[1];

    check(block_a, block_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_negate, T, floating_point_torture_list) {
    cyme::array<synapse<TYPE,M>,N,memory::AoS> block_a;
    cyme::array<synapse<TYPE,M>,N,memory::AoSoA> block_b;

    init(block_a, block_b);

    typename cyme::array<synapse<TYPE,M>,N,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = -(*it_AoS)[1];

    typename cyme::array<synapse<TYPE,M>,N,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = -(*it_AoSoA)[1];

    check(block_a, block_b);

    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = -(-(*it_AoS)[1]);

    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = -(-(*it_AoSoA)[1]);

    check(block_a, block_b);

    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = -(-(*it_AoS)[1] -  -(*it_AoS)[2]);

    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = -(-(*it_AoSoA)[1] -  -(*it_AoS)[2] );

    check(block_a, block_b);

    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = -(-(*it_AoS)[1] - - - - - -(*it_AoS)[2]);

    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = -(-(*it_AoSoA)[1] - - - - - -(*it_AoS)[2] );

    check(block_a, block_b);
}


BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_equal_multiple, T, floating_point_block_types) {
    cyme::array<synapse<TYPE,4>,N,memory::AoS> block_a;
    cyme::array<synapse<TYPE,4>,N,memory::AoSoA> block_b;

    init(block_a, block_b);

    typename cyme::array<synapse<TYPE,4>,N,memory::AoS>::iterator it_AoS = block_a.begin();
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


    typename cyme::array<synapse<TYPE,4>,N,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
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
    cyme::array<synapse<TYPE,M>,N,memory::AoS> block_a;
    cyme::array<synapse<TYPE,M>,N,memory::AoSoA> block_b;

    init(block_a, block_b);

    typename cyme::array<synapse<TYPE,M>,N,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] += (*it_AoS)[0];

    typename cyme::array<synapse<TYPE,M>,N,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
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
    cyme::array<synapse<TYPE,M>,N,memory::AoS> block_a;
    cyme::array<synapse<TYPE,M>,N,memory::AoSoA> block_b;

    init(block_a, block_b);

    typename cyme::array<synapse<TYPE,M>,N,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] -= (*it_AoS)[0];

    typename cyme::array<synapse<TYPE,M>,N,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
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

BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_minus_basic_type, T, floating_point_torture_list) {
    cyme::array<synapse<TYPE,M>,N,memory::AoS> block_a;
    cyme::array<synapse<TYPE,M>,N,memory::AoSoA> block_b;

    init(block_a, block_b);

    TYPE one(1);

    typename cyme::array<synapse<TYPE,M>,N,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[0] - one;

    typename cyme::array<synapse<TYPE,M>,N,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = (*it_AoSoA)[0] - one;

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = one - (*it_AoS)[0];

    it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = one - (*it_AoSoA)[0];

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] =  -one - (*it_AoS)[0];

    it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = -one - (*it_AoSoA)[0];

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = -(*it_AoS)[0] - one;

    it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = -(*it_AoSoA)[0] -one;

    check(block_a, block_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_multiplyequal, T, floating_point_torture_list) {
    cyme::array<synapse<TYPE,M>,N,memory::AoS> block_a;
    cyme::array<synapse<TYPE,M>,N,memory::AoSoA> block_b;

    init(block_a, block_b);

    typename cyme::array<synapse<TYPE,M>,N,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] *= (*it_AoS)[0];

    typename cyme::array<synapse<TYPE,M>,N,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
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
    cyme::array<synapse<TYPE,M>,N,memory::AoS> block_a;
    cyme::array<synapse<TYPE,M>,N,memory::AoSoA> block_b;

    init(block_a, block_b);

    typename cyme::array<synapse<TYPE,M>,N,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] /= (*it_AoS)[0];

    typename cyme::array<synapse<TYPE,M>,N,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
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
