
/*
 * Cyme - exp.cpp, Copyright (c), 2018,
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

#include <limits>
#include <tests/unit/test_header.hpp>

using namespace cyme::test;

BOOST_AUTO_TEST_CASE_TEMPLATE(vec_simd_lt, T, full_test_inequality_types) {
    union helper {
        T d;
        typename trait_integer<T>::value_type n;
    };
    helper u;

    cyme::vec_simd<T, cyme::__GETSIMD__(), cyme::unroll_factor::N> va(T(0));
    cyme::vec_simd<T, cyme::__GETSIMD__(), cyme::unroll_factor::N> vb(T(1));
    cyme::vec_simd<T, cyme::__GETSIMD__(), cyme::unroll_factor::N> vc;
    int n = cyme::unroll_factor::N * cyme::trait_register<T, cyme::__GETSIMD__()>::size / sizeof(T);
    T r[n] __attribute__((aligned(64)));
    vc = va < vb;
    vc.store(r);

    for (int i = 0; i < n; ++i) {
        u.d = r[i];
        BOOST_CHECK(u.n == -1);
    }
}

BOOST_AUTO_TEST_CASE_TEMPLATE(vec_simd_gt, T, full_test_inequality_types) {
    union helper {
        T d;
        typename trait_integer<T>::value_type n;
    };
    helper u;

    cyme::vec_simd<T, cyme::__GETSIMD__(), cyme::unroll_factor::N> va(T(1));
    cyme::vec_simd<T, cyme::__GETSIMD__(), cyme::unroll_factor::N> vb(T(0));
    cyme::vec_simd<T, cyme::__GETSIMD__(), cyme::unroll_factor::N> vc;
    int n = cyme::unroll_factor::N * cyme::trait_register<T, cyme::__GETSIMD__()>::size / sizeof(T);
    T r[n] __attribute__((aligned(64)));
    vc = va > vb;
    vc.store(r);

    for (int i = 0; i < n; ++i) {
        u.d = r[i];
        BOOST_CHECK(u.n == -1);
    }
}
