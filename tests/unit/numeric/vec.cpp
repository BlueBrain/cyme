/*
 * Cyme - vec.cpp, Copyright (c), 2014,
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

BOOST_AUTO_TEST_CASE_TEMPLATE(vec_simd_init_default_constructor, T, generic_test_types) {
    int n = cyme::unroll_factor::N*cyme::trait_register<TYPE,cyme::__GETSIMD__()>::size/sizeof(TYPE);
    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> a(0.0);
    TYPE test[n];
    TYPE res[n] __attribute__((aligned(64)));
    memset((void*)test,0,n*sizeof(TYPE));
    a.store(res);
    int b = memcmp((void*)test,(void*)res,n*sizeof(TYPE));
    BOOST_CHECK_EQUAL(0,b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vec_simd_init_constant_constructor, T, generic_test_types) {
    int n = cyme::unroll_factor::N*cyme::trait_register<TYPE,cyme::__GETSIMD__()>::size/sizeof(TYPE);
    TYPE Random = GetRandom<TYPE>();
    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> a(Random);
    TYPE test[n];
    TYPE res[n] __attribute__((aligned(64)));
   for(int i=0; i<n; ++i)
       test[i]=Random;
    a.store(res);

    int b = memcmp((void*)test,(void*)res,n*sizeof(TYPE));
    BOOST_CHECK_EQUAL(0,b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vec_simd_negate, T, floating_point_test_types) {
    int n = cyme::unroll_factor::N*cyme::trait_register<TYPE,cyme::__GETSIMD__()>::size/sizeof(TYPE);
    TYPE Random = GetRandom<TYPE>();
    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> a(Random);
    TYPE test[n];
    TYPE res[n] __attribute__((aligned(64)));
    for(int i=0; i<n; ++i)
        test[i]=-Random;

    a = a.neg();

    a.store(res);

    int b = memcmp((void*)test,(void*)res,n*sizeof(TYPE));
    BOOST_CHECK_EQUAL(0,b);
}


BOOST_AUTO_TEST_CASE_TEMPLATE(vec_simd_double_negate, T, floating_point_test_types) {
    int n = cyme::unroll_factor::N*cyme::trait_register<TYPE,cyme::__GETSIMD__()>::size/sizeof(TYPE);
    TYPE Random = GetRandom<TYPE>();
    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> a(Random);
    TYPE test[n];
    TYPE res[n] __attribute__((aligned(64)));
    for(int i=0; i<n; ++i)
        test[i]=Random;

    a = (a.neg().neg());

    a.store(res);

    int b = memcmp((void*)test,(void*)res,n*sizeof(TYPE));
    BOOST_CHECK_EQUAL(0,b);
}


BOOST_AUTO_TEST_CASE_TEMPLATE(vec_simd_init_pointer_constructor, T, generic_test_types) {
    int n = cyme::unroll_factor::N*cyme::trait_register<TYPE,cyme::__GETSIMD__()>::size/sizeof(TYPE);
    TYPE test[n]  __attribute__((aligned(64)));
    TYPE res[n] __attribute__((aligned(64)));
    for(int i=0; i<n; ++i){
       test[i] = GetRandom<TYPE>();
    }
    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> a(test);
    a.store(res);

    int b = memcmp((void*)test,(void*)res,n*sizeof(TYPE));
    BOOST_CHECK_EQUAL(0,b);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vec_simd_add_operations, T, floating_point_test_types) {
    int n = cyme::unroll_factor::N*cyme::trait_register<TYPE,cyme::__GETSIMD__()>::size/sizeof(TYPE);
    TYPE a[n] __attribute__((aligned(64)));
    TYPE b[n] __attribute__((aligned(64)));
    TYPE res[n] __attribute__((aligned(64)));

    for(int i=0; i<n; ++i){
       a[i] = GetRandom<TYPE>();
       b[i] = GetRandom<TYPE>();
    }

    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> va(a);
    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> vb(b);

    for(int i=0; i<n; ++i)
        a[i] += b[i];

    va += vb;
    va.store(res);

    for(int i=0; i<n; ++i)
        BOOST_REQUIRE_CLOSE( a[i], res[i], 0.001);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vec_simd_sub_operations, T, floating_point_test_types) {
    int n = cyme::unroll_factor::N*cyme::trait_register<TYPE,cyme::__GETSIMD__()>::size/sizeof(TYPE);
    TYPE a[n] __attribute__((aligned(64)));
    TYPE b[n] __attribute__((aligned(64)));
    TYPE res[n] __attribute__((aligned(64)));

    for(int i=0; i<n; ++i){
       a[i] = GetRandom<TYPE>();
       b[i] = GetRandom<TYPE>();
    }

    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> va(a);
    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> vb(b);

    for(int i=0; i<n; ++i)
        a[i] -= b[i];

    va -= vb;
    va.store(res);

    for(int i=0; i<n; ++i)
        BOOST_REQUIRE_CLOSE( a[i], res[i], 0.001);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vec_simd_mul_operations, T, floating_point_test_types) {
    int n = cyme::unroll_factor::N*cyme::trait_register<TYPE,cyme::__GETSIMD__()>::size/sizeof(TYPE);
    TYPE a[n] __attribute__((aligned(64)));
    TYPE b[n] __attribute__((aligned(64)));
    TYPE res[n] __attribute__((aligned(64)));

    for(int i=0; i<n; ++i){
       a[i] = GetRandom<TYPE>();
       b[i] = GetRandom<TYPE>();
    }

    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> va(a);
    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> vb(b);

    for(int i=0; i<n; ++i)
        a[i] *= b[i];

    va *= vb;
    va.store(res);

    for(int i=0; i<n; ++i)
        BOOST_REQUIRE_CLOSE( a[i], res[i], 0.001);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vec_simd_div_operations, T, floating_point_test_types) {
    int n = cyme::unroll_factor::N*cyme::trait_register<TYPE,cyme::__GETSIMD__()>::size/sizeof(TYPE);
    TYPE a[n] __attribute__((aligned(64)));
    TYPE b[n] __attribute__((aligned(64)));
    TYPE res[n] __attribute__((aligned(64)));

    for(int i=0; i<n; ++i){
       a[i] = GetRandom<TYPE>();
       b[i] = GetRandom<TYPE>();
    }

    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> va(a);
    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> vb(b);

    for(int i=0; i<n; ++i)
        a[i] /= b[i];

    va /= vb;
    va.store(res);

    for(int i=0; i<n; ++i)
        BOOST_REQUIRE_CLOSE( a[i], res[i], 0.001);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vec_simd_ZERO_add, T, generic_test_types) {

    int n = cyme::unroll_factor::N*cyme::trait_register<TYPE,cyme::__GETSIMD__()>::size/sizeof(TYPE);
    TYPE a[n] __attribute__((aligned(64)));
    TYPE b[n] __attribute__((aligned(64)));

    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> va(3);
    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> vb(va);

    va = vb + cyme::ZERO();

    va.store(a);
    vb.store(b);

    for(int i=0; i<n; ++i)
        BOOST_CHECK_EQUAL(a[i],b[i]);

    va = cyme::ZERO() + vb;

    va.store(a);
    vb.store(b);

    for(int i=0; i<n; ++i)
        BOOST_CHECK_EQUAL(a[i],b[i]);


}


BOOST_AUTO_TEST_CASE_TEMPLATE(vec_simd_ZERO_mul, T, generic_test_types) {

    int n = cyme::unroll_factor::N*cyme::trait_register<TYPE,cyme::__GETSIMD__()>::size/sizeof(TYPE);
    TYPE a[n] __attribute__((aligned(64)));
    TYPE b[n] __attribute__((aligned(64)));

    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> va(3);
    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> vb(va);

    va = vb * cyme::ZERO() + vb;

    va.store(a);
    vb.store(b);

    for(int i=0; i<n; ++i)
        BOOST_CHECK_EQUAL(a[i],b[i]);

    va = vb + cyme::ZERO() * vb;

    va.store(a);
    vb.store(b);

    for(int i=0; i<n; ++i)
        BOOST_CHECK_EQUAL(a[i],b[i]);


}

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

//BOOST_AUTO_TEST_CASE(vec_simd_and_operation) {
//    int n = cyme::unroll_factor::N*cyme::trait_register<int,cyme::__GETSIMD__()>::size/sizeof(int);
//    int a[n] __attribute__((aligned(16)));
//    int b[n] __attribute__((aligned(16)));
//    int c[n] __attribute__((aligned(16)));
//    int res[n] __attribute__((aligned(16)));
//
//    for(int i=0; i<n; ++i){
//       a[i] = GetRandom<int>();
//       b[i] = GetRandom<int>();
//    }
//
//    cyme::vec_simd<int,cyme::__GETSIMD__(),cyme::unroll_factor::N> va(a);
//    cyme::vec_simd<int,cyme::__GETSIMD__(),cyme::unroll_factor::N> vb(b);
//    cyme::vec_simd<int,cyme::__GETSIMD__(),cyme::unroll_factor::N> vc;
//
//    for(int i=0; i<n; ++i){
//        a[i] &= b[i];
//        c[i] =a[i] && b[i];
//    }
//
//    va &= vb;
//    vc = va && vb;
//    va.store(res);
//
//    for(int i=0; i<n; ++i)
//       BOOST_CHECK_EQUAL(a[i],res[i]);
//}

#endif

#undef SIZE
#undef TYPE
#undef MAX
