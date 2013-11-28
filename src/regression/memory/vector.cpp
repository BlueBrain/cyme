#include <regression/test_header.hpp>

using namespace cyme::test;

#define TYPE typename T::value_type
#define N T::n
#define ORDER T::order 

    template<class T, int M>
    struct synapse{
       typedef T value_type;
       static const int value_size = M;
    };

BOOST_AUTO_TEST_CASE_TEMPLATE(vector_init_default_constructor, T, floating_point_block_types) {
     cyme::vector<synapse<TYPE,N>,ORDER> a;
     BOOST_CHECK_EQUAL(a(0,0),0); 
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vector_init_default_size_constructor, T, floating_point_block_types) {
     cyme::vector<synapse<TYPE,N>,ORDER> a(10);
     TYPE test[N*10];

     for(std::size_t i=0; i < N*10; ++i)
        test[i] = 0;

     int b = memcmp((void*)test, (void*)&a(0,0), N*10*sizeof(TYPE));
     BOOST_CHECK_EQUAL(b,0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vector_init_value_size_constructor, T, floating_point_block_types) {
     cyme::vector<synapse<TYPE,N>,ORDER> a(10,3);
     TYPE test[N*10];

     for(std::size_t i=0; i < N*10; ++i)
        test[i] = 3;

     int b = memcmp((void*)test, (void*)&a(0,0), N*10*sizeof(TYPE));
     BOOST_CHECK_EQUAL(b,0); 
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vector_init_operator_bracket, T, floating_point_block_types) {
    cyme::vector<synapse<TYPE,N>,memory::AoS> vector_a(1024);
    cyme::vector<synapse<TYPE,N>,memory::AoSoA> vector_b(1024);

    init(vector_a, vector_b);

    check(vector_a, vector_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vector_copy_constructor, T, floating_point_block_types) {
    cyme::vector<synapse<TYPE,N>,memory::AoS> vector_a(1024);
    cyme::vector<synapse<TYPE,N>,memory::AoSoA> vector_b(1024);

    init(vector_a, vector_b);

    cyme::vector<synapse<TYPE,N>,memory::AoS> vector_a_cpy(vector_a);
    cyme::vector<synapse<TYPE,N>,memory::AoSoA> vector_b_cpy(vector_b);

    check(vector_a, vector_b);
    check(vector_a_cpy, vector_b_cpy);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vector_resize_operator_bracket, T, floating_point_block_types) {
    cyme::vector<synapse<TYPE,N>,memory::AoS> vector_a(1024);
    cyme::vector<synapse<TYPE,N>,memory::AoSoA> vector_b(1024);

    init(vector_a, vector_b);
    check(vector_a, vector_b);

    vector_a.resize(999); 
    vector_b.resize(999); 

    check(vector_a, vector_b);

    vector_a.resize(777); 
    vector_b.resize(777); 

    check(vector_a, vector_b);

    vector_a.resize(7); 
    vector_b.resize(7); 

    check(vector_a, vector_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vector_operator_equal, T, floating_point_block_types) {
    cyme::vector<synapse<TYPE,N>,memory::AoS> vector_a(1024);
    cyme::vector<synapse<TYPE,N>,memory::AoSoA> vector_b(1024);

    init(vector_a, vector_b);

    typename cyme::vector<synapse<TYPE,N>,memory::AoS>::iterator it_AoS = vector_a.begin();
    for(; it_AoS != vector_a.end(); ++it_AoS)
        (*it_AoS)[0] = (*it_AoS)[1];

    typename cyme::vector<synapse<TYPE,N>,memory::AoSoA>::iterator it_AoSoA = vector_b.begin();
    for(; it_AoSoA != vector_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] = (*it_AoSoA)[1];

    check(vector_a, vector_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vector_operator_equal_multiple, T, floating_point_block_types) {
    cyme::vector<synapse<TYPE,N>,memory::AoS> vector_a(1024);
    cyme::vector<synapse<TYPE,N>,memory::AoSoA> vector_b(1024);

    init(vector_a, vector_b);

    typename cyme::vector<synapse<TYPE,N>,memory::AoS>::iterator it_AoS = vector_a.begin();
    for(; it_AoS != vector_a.end(); ++it_AoS){
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

    typename cyme::vector<synapse<TYPE,N>,memory::AoSoA>::iterator it_AoSoA = vector_b.begin();
    for(; it_AoSoA != vector_b.end(); ++it_AoSoA){
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
    
    check(vector_a, vector_b);
}



BOOST_AUTO_TEST_CASE_TEMPLATE(vector_operator_plusequal, T, floating_point_torture_list) {
    cyme::vector<synapse<TYPE,N>,memory::AoS> vector_a(1024);
    cyme::vector<synapse<TYPE,N>,memory::AoSoA> vector_b(1024);

    init(vector_a, vector_b);

    typename cyme::vector<synapse<TYPE,N>,memory::AoS>::iterator it_AoS = vector_a.begin();
    for(; it_AoS != vector_a.end(); ++it_AoS)
        (*it_AoS)[0] += (*it_AoS)[0];

    typename cyme::vector<synapse<TYPE,N>,memory::AoSoA>::iterator it_AoSoA = vector_b.begin();
    for(; it_AoSoA != vector_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] += (*it_AoSoA)[0];

    check(vector_a, vector_b);

    it_AoS = vector_a.begin();
    for(; it_AoS != vector_a.end(); ++it_AoS)
        (*it_AoS)[0] += (*it_AoS)[1];

    it_AoSoA = vector_b.begin();
    for(; it_AoSoA != vector_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] += (*it_AoSoA)[1];

    check(vector_a, vector_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vector_operator_minusequal, T, floating_point_torture_list) {
    cyme::vector<synapse<TYPE,N>,memory::AoS> vector_a(1024);
    cyme::vector<synapse<TYPE,N>,memory::AoSoA> vector_b(1024);

    init(vector_a, vector_b);

    typename cyme::vector<synapse<TYPE,N>,memory::AoS>::iterator it_AoS = vector_a.begin();
    for(; it_AoS != vector_a.end(); ++it_AoS)
        (*it_AoS)[0] -= (*it_AoS)[0];

    typename cyme::vector<synapse<TYPE,N>,memory::AoSoA>::iterator it_AoSoA = vector_b.begin();
    for(; it_AoSoA != vector_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] -= (*it_AoSoA)[0];

    check(vector_a, vector_b);

    it_AoS = vector_a.begin();
    for(; it_AoS != vector_a.end(); ++it_AoS)
        (*it_AoS)[0] -= (*it_AoS)[1];

    it_AoSoA = vector_b.begin();
    for(; it_AoSoA != vector_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] -= (*it_AoSoA)[1];

    check(vector_a, vector_b);
}


BOOST_AUTO_TEST_CASE_TEMPLATE(vector_operator_multiplyequal, T, floating_point_torture_list) {
    cyme::vector<synapse<TYPE,N>,memory::AoS> vector_a(1024);
    cyme::vector<synapse<TYPE,N>,memory::AoSoA> vector_b(1024);

    init(vector_a, vector_b);

    typename cyme::vector<synapse<TYPE,N>,memory::AoS>::iterator it_AoS = vector_a.begin();
    for(; it_AoS != vector_a.end(); ++it_AoS)
        (*it_AoS)[0] *= (*it_AoS)[0];

    typename cyme::vector<synapse<TYPE,N>,memory::AoSoA>::iterator it_AoSoA = vector_b.begin();
    for(; it_AoSoA != vector_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] *= (*it_AoSoA)[0];

    check(vector_a, vector_b);

    it_AoS = vector_a.begin();
    for(; it_AoS != vector_a.end(); ++it_AoS)
        (*it_AoS)[0] *= (*it_AoS)[1];

    it_AoSoA = vector_b.begin();
    for(; it_AoSoA != vector_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] *= (*it_AoSoA)[1];

    check(vector_a, vector_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vector_operator_divideequal, T, floating_point_torture_list) {
    cyme::vector<synapse<TYPE,N>,memory::AoS> vector_a(1024);
    cyme::vector<synapse<TYPE,N>,memory::AoSoA> vector_b(1024);

    init(vector_a, vector_b);

    typename cyme::vector<synapse<TYPE,N>,memory::AoS>::iterator it_AoS = vector_a.begin();
    for(; it_AoS != vector_a.end(); ++it_AoS)
        (*it_AoS)[0] /= (*it_AoS)[0];

    typename cyme::vector<synapse<TYPE,N>,memory::AoSoA>::iterator it_AoSoA = vector_b.begin();
    for(; it_AoSoA != vector_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] /= (*it_AoSoA)[0];

    check(vector_a, vector_b);

    it_AoS = vector_a.begin();
    for(; it_AoS != vector_a.end(); ++it_AoS)
        (*it_AoS)[0] /= (*it_AoS)[1];

    it_AoSoA = vector_b.begin();
    for(; it_AoSoA != vector_b.end(); ++it_AoSoA)
        (*it_AoSoA)[0] /= (*it_AoSoA)[1];

    check(vector_a, vector_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vector_push_back, T, floating_point_torture_list) {
    cyme::vector<synapse<TYPE,N>,memory::AoS> vector_a;
    cyme::vector<synapse<TYPE,N>,memory::AoSoA> vector_b;

    for(int i=0; i<10; ++i){
        vector_a.push_back(i);
        vector_b.push_back(i);
    }

    check(vector_a, vector_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vector_push_front, T, floating_point_torture_list) {
    cyme::vector<synapse<TYPE,N>,memory::AoS> vector_a;
    cyme::vector<synapse<TYPE,N>,memory::AoSoA> vector_b;

    for(int i=0; i<10; ++i){
        vector_a.push_front(i);
        vector_b.push_front(i);
    }

    check(vector_a, vector_b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vector_push_back_front, T, floating_point_torture_list) {
    cyme::vector<synapse<TYPE,N>,memory::AoS> vector_a;
    cyme::vector<synapse<TYPE,N>,memory::AoSoA> vector_b;

    for(int i=0; i<10; ++i){
        vector_a.push_front(i);
        vector_b.push_front(i);
    }

    for(int i=0; i<3; ++i){
        vector_a.push_back(i);
        vector_b.push_back(i);
    }

    for(int i=0; i<3; ++i){
        vector_a.push_front(i);
        vector_b.push_front(i);
    }


    check(vector_a, vector_b);
}

#undef TYPE
#undef N
#undef ORRDER
