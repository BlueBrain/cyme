#include <test/unit/test_header.hpp>

using namespace cyme::test;

#define TYPE typename T::value_type
#define N T::n
#define ORDER T::order
#define MAX 1000

    template<class T, size_t M>
    struct synapse{
       typedef T value_type;
       static const size_t value_size = M;
    };


BOOST_AUTO_TEST_CASE_TEMPLATE(core_operator_add_scalar, T, floating_point_block_types) {
    cyme::vector<synapse<TYPE,N>,memory::AoS> block_a(1024);
    cyme::vector<synapse<TYPE,N>,memory::AoSoA> block_b(1024);

    init(block_a, block_b);

    typename cyme::vector<synapse<TYPE,N>,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1] + 3.141592;

    typename cyme::vector<synapse<TYPE,N>,memory::AoSoA>::iterator it_AoSoA_w = block_b.begin();
    typename cyme::vector<synapse<TYPE,N>,memory::AoSoA>::const_iterator it_AoSoA_r = block_b.begin();
    for(; it_AoSoA_r != block_b.end(); ++it_AoSoA_w,++it_AoSoA_r)
        (*it_AoSoA_w)[0] = (*it_AoSoA_r)[1] + 3.141592;

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1] + 3;

    it_AoSoA_w = block_b.begin();
    it_AoSoA_r = block_b.begin();
    for(; it_AoSoA_r != block_b.end(); ++it_AoSoA_w,++it_AoSoA_r)
        (*it_AoSoA_w)[0] = (*it_AoSoA_r)[1] + 3;

    check(block_a, block_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(core_operator_sub_scalar, T, floating_point_block_types) {
    cyme::vector<synapse<TYPE,N>,memory::AoS> block_a(1024);
    cyme::vector<synapse<TYPE,N>,memory::AoSoA> block_b(1024);

    init(block_a, block_b);

    typename cyme::vector<synapse<TYPE,N>,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1] - 3.141592;

    typename cyme::vector<synapse<TYPE,N>,memory::AoSoA>::iterator it_AoSoA_w = block_b.begin();
    typename cyme::vector<synapse<TYPE,N>,memory::AoSoA>::const_iterator it_AoSoA_r = block_b.begin();
    for(; it_AoSoA_r != block_b.end(); ++it_AoSoA_w,++it_AoSoA_r)
        (*it_AoSoA_w)[0] = (*it_AoSoA_r)[1] - 3.141592;

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1] - 3;

    it_AoSoA_w = block_b.begin();
    it_AoSoA_r = block_b.begin();
    for(; it_AoSoA_r != block_b.end(); ++it_AoSoA_w,++it_AoSoA_r)
        (*it_AoSoA_w)[0] = (*it_AoSoA_r)[1] - 3;

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = 3.141592 - (*it_AoS)[1];

    it_AoSoA_w = block_b.begin();
    it_AoSoA_r = block_b.begin();
    for(; it_AoSoA_r != block_b.end(); ++it_AoSoA_w,++it_AoSoA_r)
        (*it_AoSoA_w)[0] = 3.1415912 - (*it_AoSoA_r)[1];

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = 3 - (*it_AoS)[1];

    it_AoSoA_w = block_b.begin();
    it_AoSoA_r = block_b.begin();
    for(; it_AoSoA_r != block_b.end(); ++it_AoSoA_w,++it_AoSoA_r)
        (*it_AoSoA_w)[0] = 3 - (*it_AoSoA_r)[1];

    check(block_a, block_b);
}


BOOST_AUTO_TEST_CASE_TEMPLATE(core_operator_mul_scalar, T, floating_point_block_types) {
    cyme::vector<synapse<TYPE,N>,memory::AoS> block_a(1024);
    cyme::vector<synapse<TYPE,N>,memory::AoSoA> block_b(1024);

    init(block_a, block_b);

    typename cyme::vector<synapse<TYPE,N>,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1] * 3.141592;

    typename cyme::vector<synapse<TYPE,N>,memory::AoSoA>::iterator it_AoSoA_w = block_b.begin();
    typename cyme::vector<synapse<TYPE,N>,memory::AoSoA>::const_iterator it_AoSoA_r = block_b.begin();
    for(; it_AoSoA_r != block_b.end(); ++it_AoSoA_w,++it_AoSoA_r)
        (*it_AoSoA_w)[0] = (*it_AoSoA_r)[1] * 3.141592;

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1] * 3;

    it_AoSoA_w = block_b.begin();
    it_AoSoA_r = block_b.begin();
    for(; it_AoSoA_r != block_b.end(); ++it_AoSoA_w,++it_AoSoA_r)
        (*it_AoSoA_w)[0] = (*it_AoSoA_r)[1] * 3;

    check(block_a, block_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(core_operator_div_scalar, T, floating_point_block_types) {
    cyme::vector<synapse<TYPE,N>,memory::AoS> block_a(1024);
    cyme::vector<synapse<TYPE,N>,memory::AoSoA> block_b(1024);

    init(block_a, block_b);

    typename cyme::vector<synapse<TYPE,N>,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1] / 3.141592;

    typename cyme::vector<synapse<TYPE,N>,memory::AoSoA>::iterator it_AoSoA_w = block_b.begin();
    typename cyme::vector<synapse<TYPE,N>,memory::AoSoA>::const_iterator it_AoSoA_r = block_b.begin();
    for(; it_AoSoA_r != block_b.end(); ++it_AoSoA_w,++it_AoSoA_r)
        (*it_AoSoA_w)[0] = (*it_AoSoA_r)[1] / 3.141592;

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1] / 3;

    it_AoSoA_w = block_b.begin();
    it_AoSoA_r = block_b.begin();
    for(; it_AoSoA_r != block_b.end(); ++it_AoSoA_w,++it_AoSoA_r)
        (*it_AoSoA_w)[0] = (*it_AoSoA_r)[1] / 3;

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = 3.141592 / (*it_AoS)[1];

    it_AoSoA_w = block_b.begin();
    it_AoSoA_r = block_b.begin();
    for(; it_AoSoA_r != block_b.end(); ++it_AoSoA_w,++it_AoSoA_r)
        (*it_AoSoA_w)[0] = 3.141592 / (*it_AoSoA_r)[1];

    check(block_a, block_b);

    it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
        (*it_AoS)[0] = 3 / (*it_AoS)[1];

    it_AoSoA_w = block_b.begin();
    it_AoSoA_r = block_b.begin();
    for(; it_AoSoA_r != block_b.end(); ++it_AoSoA_w,++it_AoSoA_r)
        (*it_AoSoA_w)[0] = 3 /  (*it_AoSoA_r)[1];

    check(block_a, block_b);
}



#undef TYPE
#undef N
#undef MAX
#undef SIZE
