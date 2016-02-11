/*
 * Cyme - bitwise.cpp, Copyright (c), 2014,
 * Timothee Ewart - Swiss Federal Institute of technology in Lausanne,
 * timothee.ewart@epfl.ch,
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3.0 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.
 */

#include <tests/unit/test_header.hpp>
#include <limits>

using namespace cyme::test;

#define TYPE typename T::value_type
#define SIZE T::size
#define MAX 1000

#pragma GCC diagnostic ignored "-Wvla" // compiler complains about line 13 which is not dynamic at all but determine during compile time
//MAKE SIMD test is not easy do I do : cyme -> simd register (perform something) -> cyme where I finally test
//not the SIMD type is presently given bu the __GETSIMD__() function hardcoded into /cyme/detail/simd.h
#ifdef __x86_64__

BOOST_AUTO_TEST_CASE_TEMPLATE(vec_simd_lt_operations, T, generic_test_types) {
    union helper { TYPE d; typename trait_integer<TYPE>::value_type n;};
    helper u;
    // for the test only
    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> va(3);
    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> vb(2);
    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> vr1;
    int n = cyme::unroll_factor::N*cyme::trait_register<TYPE,cyme::__GETSIMD__()>::size/sizeof(TYPE);
    TYPE r0[n] __attribute__((aligned(64)));


    vr1 = va < vb;
    vr1.store(r0);

    for(int i=0; i < n ; ++i)
        BOOST_CHECK(r0[i] == 0);

    vr1 = va > vb;
    vr1.store(r0);

    for(int i=0; i < n ; ++i){
        u.d = r0[i];
        BOOST_CHECK(u.n == -1);
    }

    vr1 = va == vb;
    vr1.store(r0);

    for(int i=0; i < n ; ++i)
        BOOST_CHECK(r0[i] == 0);


    vr1 = va == va;
    vr1.store(r0);

    for(int i=0; i < n ; ++i){
        u.d = r0[i];
        BOOST_CHECK(u.n == -1);
    }

}


BOOST_AUTO_TEST_CASE_TEMPLATE(vec_simd_and_operations, T, generic_test_types) {
    union helper { TYPE d; typename trait_integer<TYPE>::value_type n;};
    helper u,utest;
    u.n=-1;
    // for the test only

    double tmp = rand();
    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> va(tmp);
    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> mask_1(u.d);
    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> mask_0(0.);
    int n = cyme::unroll_factor::N*cyme::trait_register<TYPE,cyme::__GETSIMD__()>::size/sizeof(TYPE);
    TYPE r[n] __attribute__((aligned(64)));

    va = va & mask_1;
    va.store(r);

    for(int i=0; i < n ; ++i)
        BOOST_CHECK(r[i] == tmp);

    va &= mask_1;
    va.store(r);

    for(int i=0; i < n ; ++i)
        BOOST_CHECK(r[i] == tmp);

    va = va & mask_0;
    va.store(r);

    for(int i=0; i < n ; ++i)
        BOOST_CHECK(r[i] == 0);

    va &= mask_0;
    va.store(r);

    for(int i=0; i < n ; ++i)
        BOOST_CHECK(r[i] == 0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vec_simd_or_operations, T, generic_test_types) {
    union helper { TYPE d; typename trait_integer<TYPE>::value_type n;};
    helper u,utest;
    u.n=-1;
    // for the test only

    double tmp = drand48();
    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> va(tmp);
    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> vb(0.);
    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> mask_1(u.d);
    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> mask_0(0.);
    int n = cyme::unroll_factor::N*cyme::trait_register<TYPE,cyme::__GETSIMD__()>::size/sizeof(TYPE);
    TYPE r[n] __attribute__((aligned(64)));

    va = va | mask_1;
    va.store(r);

    for(int i=0; i < n ; ++i){
        utest.d = r[i];
        BOOST_CHECK(utest.n == -1);
    }

    va |= mask_1;
    va.store(r);

    for(int i=0; i < n ; ++i){
        utest.d = r[i];
        BOOST_CHECK(utest.n == -1);
    }

    vb = vb | mask_0;
    vb.store(r);

    for(int i=0; i < n ; ++i)
        BOOST_CHECK(r[i] == 0);

    vb |= mask_0;
    vb.store(r);

    for(int i=0; i < n ; ++i)
        BOOST_CHECK(r[i] == 0);
}
//
//BOOST_AUTO_TEST_CASE_TEMPLATE(vec_simd_andnot_operations, T, generic_test_types) {
//    union helper { TYPE d; typename trait_integer<TYPE>::value_type n;};
//    helper u,utest;
//    u.n=-1;
//    // for the test only
//
//    double tmp = drand48();
//    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> va(tmp);
//    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> vb(0.);
//    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> mask_1(u.d);
//    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> mask_0(0.);
//    int n = cyme::unroll_factor::N*cyme::trait_register<TYPE,cyme::__GETSIMD__()>::size/sizeof(TYPE);
//    TYPE r[n] __attribute__((aligned(64)));
//
//    va = va.andnot(mask_1);
//    va.store(r);
//
//    for(int i=0; i < n ; ++i){
//        utest.d = r[i];
//        BOOST_CHECK(utest.n == -1);
//    }
//
//    va |= mask_1;
//    va.store(r);
//
//    for(int i=0; i < n ; ++i){
//        utest.d = r[i];
//        BOOST_CHECK(utest.n == -1);
//    }
//
//    vb = vb | mask_0;
//    vb.store(r);
//
//    for(int i=0; i < n ; ++i)
//        BOOST_CHECK(r[i] == 0);
//
//    vb |= mask_0;
//    vb.store(r);
//
//    for(int i=0; i < n ; ++i)
//        BOOST_CHECK(r[i] == 0);
//}



#endif

#undef SIZE
#undef TYPE
#undef MAX
