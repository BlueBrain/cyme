#include <regression/test_header.hpp>

using namespace cyme::test;

#define TYPE typename T::value_type
#define N T::n
#define M T::m
#define ORDER T::order 
#define MAX 1000 

BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_plus, T, floating_point_block_types) {
    memory::block<TYPE,M,N,memory::AoS> block_a;
    memory::block<TYPE,M,N,memory::AoSoA> block_b;

    init(block_a, block_b);

    typename memory::block<TYPE,M,N,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1]+(*it_AoS)[1];

    typename memory::block<TYPE,M,N,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = (*it_AoSoA)[1]+(*it_AoSoA)[1];

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1]+(*it_AoS)[2];

    it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = (*it_AoSoA)[1]+(*it_AoSoA)[2];

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1]+(*it_AoS)[2]+(*it_AoS)[3];

    it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = (*it_AoSoA)[1]+(*it_AoSoA)[2]+(*it_AoSoA)[3];

    check(block_a, block_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_sub, T, floating_point_block_types) {
    memory::block<TYPE,M,N,memory::AoS> block_a;
    memory::block<TYPE,M,N,memory::AoSoA> block_b;

    init(block_a, block_b);

    typename memory::block<TYPE,M,N,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1]-(*it_AoS)[1];

    typename memory::block<TYPE,M,N,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = (*it_AoSoA)[1]-(*it_AoSoA)[1];

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1]-(*it_AoS)[2];

    it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = (*it_AoSoA)[1]-(*it_AoSoA)[2];

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1]-(*it_AoS)[2]+(*it_AoS)[3];

    it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = (*it_AoSoA)[1]-(*it_AoSoA)[2]+(*it_AoSoA)[3];
    
    check(block_a, block_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_mul, T, floating_point_block_types) {
    memory::block<TYPE,M,N,memory::AoS> block_a;
    memory::block<TYPE,M,N,memory::AoSoA> block_b;

    init(block_a, block_b);

    typename memory::block<TYPE,M,N,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1]*(*it_AoS)[1];

    typename memory::block<TYPE,M,N,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = (*it_AoSoA)[1]*(*it_AoSoA)[1];

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1]*(*it_AoS)[2];

    it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = (*it_AoSoA)[1]*(*it_AoSoA)[2];

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1]*(*it_AoS)[2]*(*it_AoS)[3];

    it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = (*it_AoSoA)[1]*(*it_AoSoA)[2]*(*it_AoSoA)[3];
    
    check(block_a, block_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_div, T, floating_point_block_types) {
    memory::block<TYPE,M,N,memory::AoS> block_a;
    memory::block<TYPE,M,N,memory::AoSoA> block_b;

    init(block_a, block_b);

    typename memory::block<TYPE,M,N,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1]/(*it_AoS)[1];

    typename memory::block<TYPE,M,N,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = (*it_AoSoA)[1]/(*it_AoSoA)[1];

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1]/(*it_AoS)[2];

    it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = (*it_AoSoA)[1]/(*it_AoSoA)[2];

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1]/(*it_AoS)[2]/(*it_AoS)[3];

    it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = (*it_AoSoA)[1]/(*it_AoSoA)[2]/(*it_AoSoA)[3];
    
    check(block_a, block_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_add_mul_min_div, T, floating_point_block_types) {
    memory::block<TYPE,M,N,memory::AoS> block_a;
    memory::block<TYPE,M,N,memory::AoSoA> block_b;

    init(block_a, block_b);

    typename memory::block<TYPE,M,N,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1]+(*it_AoS)[2]*(*it_AoS)[3]-(*it_AoS)[4]/(*it_AoS)[5];

    typename memory::block<TYPE,M,N,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = (*it_AoSoA)[1]+(*it_AoSoA)[2]*(*it_AoSoA)[3]-(*it_AoSoA)[4]/(*it_AoSoA)[5];

    check(block_a, block_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_add_mul_div_min, T, floating_point_block_types) {
    memory::block<TYPE,M,N,memory::AoS> block_a;
    memory::block<TYPE,M,N,memory::AoSoA> block_b;

    init(block_a, block_b);

    typename memory::block<TYPE,M,N,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1]+(*it_AoS)[2]*(*it_AoS)[3]/(*it_AoS)[4]-(*it_AoS)[5];

    typename memory::block<TYPE,M,N,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = (*it_AoSoA)[1]+(*it_AoSoA)[2]*(*it_AoSoA)[3]/(*it_AoSoA)[4]-(*it_AoSoA)[5];

    check(block_a, block_b);
}


BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_fma_a_mul_b_plus_c, T, floating_point_block_types) {
    memory::block<TYPE,M,N,memory::AoS> block_a;
    memory::block<TYPE,M,N,memory::AoSoA> block_b;

    init(block_a, block_b);

    typename memory::block<TYPE,M,N,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1]*(*it_AoS)[2]+(*it_AoS)[3];

    typename memory::block<TYPE,M,N,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = (*it_AoSoA)[1]*(*it_AoSoA)[2]+(*it_AoSoA)[3];

    check(block_a, block_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_fma_c_plus_a_mul_b, T, floating_point_block_types) {
    memory::block<TYPE,M,N,memory::AoS> block_a;
    memory::block<TYPE,M,N,memory::AoSoA> block_b;

    typename memory::block<TYPE,M,N,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1]+(*it_AoS)[2]*(*it_AoS)[3];

    typename memory::block<TYPE,M,N,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = (*it_AoSoA)[1]+(*it_AoSoA)[2]*(*it_AoSoA)[3];

    check(block_a, block_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_fma_a_mul_b_plus_c_mul_d, T, floating_point_block_types) {
    memory::block<TYPE,M,N,memory::AoS> block_a;
    memory::block<TYPE,M,N,memory::AoSoA> block_b;

    typename memory::block<TYPE,M,N,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1]*(*it_AoS)[4]+(*it_AoS)[2]*(*it_AoS)[3];

    typename memory::block<TYPE,M,N,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = (*it_AoSoA)[1]*(*it_AoSoA)[4]+(*it_AoSoA)[2]*(*it_AoSoA)[3];

    check(block_a, block_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_fms_a_mul_b_minus_c, T, floating_point_block_types) {
    memory::block<TYPE,M,N,memory::AoS> block_a;
    memory::block<TYPE,M,N,memory::AoSoA> block_b;

    init(block_a, block_b);

    typename memory::block<TYPE,M,N,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1]*(*it_AoS)[2]-(*it_AoS)[3];

    typename memory::block<TYPE,M,N,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = (*it_AoSoA)[1]*(*it_AoSoA)[2]-(*it_AoSoA)[3];

    check(block_a, block_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_fms_a_minus_b_mul_c, T, floating_point_block_types) {
    memory::block<TYPE,M,N,memory::AoS> block_a;
    memory::block<TYPE,M,N,memory::AoSoA> block_b;

    typename memory::block<TYPE,M,N,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1]-(*it_AoS)[2]*(*it_AoS)[3];

    typename memory::block<TYPE,M,N,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = (*it_AoSoA)[1]-(*it_AoSoA)[2]*(*it_AoSoA)[3];

    check(block_a, block_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_fms_a_mul_b_minus_c_mul_d, T, floating_point_block_types) {
    memory::block<TYPE,M,N,memory::AoS> block_a;
    memory::block<TYPE,M,N,memory::AoSoA> block_b;

    typename memory::block<TYPE,M,N,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[4]*(*it_AoS)[1]-(*it_AoS)[2]*(*it_AoS)[3];

    typename memory::block<TYPE,M,N,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = (*it_AoSoA)[4]*(*it_AoSoA)[1]-(*it_AoSoA)[2]*(*it_AoSoA)[3];

    check(block_a, block_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_operator_bracket_torture, T, floating_point_block_types) {
    memory::block<TYPE,M,N,memory::AoS> block_a;
    memory::block<TYPE,M,N,memory::AoSoA> block_b;

    init(block_a, block_b);

    typename memory::block<TYPE,M,N,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0]   = (((((*it_AoS)[1]+(*it_AoS)[2])+(*it_AoS)[3])+(*it_AoS)[4])+(*it_AoS)[5]);

    typename memory::block<TYPE,M,N,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = (((((*it_AoSoA)[1]+(*it_AoSoA)[2])+(*it_AoSoA)[3])+(*it_AoSoA)[4])+(*it_AoSoA)[5]);

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0]   = (((((*it_AoS)[1]-(*it_AoS)[2])-(*it_AoS)[3])-(*it_AoS)[4])-(*it_AoS)[5]);

    it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = (((((*it_AoSoA)[1]-(*it_AoSoA)[2])-(*it_AoSoA)[3])-(*it_AoSoA)[4])-(*it_AoSoA)[5]);

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0]   = (((((*it_AoS)[1]*(*it_AoS)[2])*(*it_AoS)[3])*(*it_AoS)[4])*(*it_AoS)[5]);

    it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = (((((*it_AoSoA)[1]*(*it_AoSoA)[2])*(*it_AoSoA)[3])*(*it_AoSoA)[4])*(*it_AoSoA)[5]);

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0]   = (((((*it_AoS)[1]  /(*it_AoS)[2])/(*it_AoS)[3])/(*it_AoS)[4])/(*it_AoS)[5]);

    it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = (((((*it_AoSoA)[1]/(*it_AoSoA)[2])/(*it_AoSoA)[3])/(*it_AoSoA)[4])/(*it_AoSoA)[5]);

    check(block_a, block_b);


    it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0]   = (((((*it_AoS)[1]  +(*it_AoS)[2])*(*it_AoS)[3])-(*it_AoS)[4])/(*it_AoS)[5]);

    it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = (((((*it_AoSoA)[1]+(*it_AoSoA)[2])*(*it_AoSoA)[3])-(*it_AoSoA)[4])/(*it_AoSoA)[5]);

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0]   = ((*it_AoS)[1]  +(*it_AoS)[2])*(*it_AoS)[3]-((*it_AoS)[4]/(*it_AoS)[5]);

    it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = ((*it_AoSoA)[1]+(*it_AoSoA)[2])*(*it_AoSoA)[3]-((*it_AoSoA)[4]/(*it_AoSoA)[5]);

    check(block_a, block_b);
}


#undef TYPE
#undef N
#undef MAX
#undef SIZE
