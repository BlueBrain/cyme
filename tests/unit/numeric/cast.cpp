/*
 * Cyme - cast.cpp, Copyright (c), 2017,
 * Timothée Ewart,
 * timothee.ewart@gmail.com,
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
#include "cyme/math/math.h"

using namespace cyme::test;

template <class T>
union helper {
    uint32_t n;
    T f;
};

BOOST_AUTO_TEST_CASE_TEMPLATE(cast_from_mask_single_inequality, T, full_test_types) {
    int n = cyme::unroll_factor::N * cyme::trait_register<T, cyme::__GETSIMD__()>::size / sizeof(T);
    T b[n] __attribute__((aligned(64)));

    cyme::vec<int, cyme::__GETSIMD__(), cyme::unroll_factor::N> zero;
    cyme::vec<int, cyme::__GETSIMD__(), cyme::unroll_factor::N> one(1);
    cyme::vec<int, cyme::__GETSIMD__(), cyme::unroll_factor::N> mask;
    cyme::vec<T, cyme::__GETSIMD__(), cyme::unroll_factor::N> res(b);

    mask = zero > one;

    res = cyme::cyme_cast<T>(mask);

    for (int i = 0; i < n; ++i)
        BOOST_CHECK(b[i] == 0);

    mask = zero < one;

    res = cyme::cyme_cast<T>(mask);

    helper<T> h;
    for (int i = 0; i < n; ++i) {
        h.f = b[i];
        BOOST_CHECK(h.n == 0xffffffff);
    }
}
