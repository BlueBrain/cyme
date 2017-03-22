/*
 * Cyme - div.cpp, Copyright (c), 2014,
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
#include <boost/math/special_functions/next.hpp>
#include "cyme/math/math.h"

using namespace cyme::test;

#define TYPE typename T::value_type
#define SIZE T::size
#define MAX 1000

#define NN cyme::unroll_factor::N *cyme::trait_register<TYPE, cyme::__GETSIMD__()>::size / sizeof(TYPE)

BOOST_AUTO_TEST_CASE_TEMPLATE(std_div_comparison, T, generic_test_types) {
    TYPE a[NN] __attribute__((aligned(64)));
    TYPE b[NN] __attribute__((aligned(64)));
    TYPE c[NN] __attribute__((aligned(64)));
    TYPE res[NN] __attribute__((aligned(64)));
    double max(0.), ulp(0.);
    for (size_t k = 0; k < 1000; ++k) {
        for (size_t i = 0; i < NN; ++i) {
            a[i] = GetRandom<TYPE>();
            b[i] = GetRandom<TYPE>();
        }

        cyme::vec_simd<TYPE, cyme::__GETSIMD__(), cyme::unroll_factor::N> va(a);
        cyme::vec_simd<TYPE, cyme::__GETSIMD__(), cyme::unroll_factor::N> vb(b);
        cyme::vec_simd<TYPE, cyme::__GETSIMD__(), cyme::unroll_factor::N> vc;

        for (size_t i = 0; i < NN; ++i)
            c[i] = a[i] / b[i];

        vc = va / vb;
        vc.store(res);

        for (size_t i = 0; i < NN; ++i) {
            ulp = boost::math::float_distance(c[i], res[i]);
            // std::cout << ulp << " a / b " << a[i] << " " << b[i] << std::endl;
            std::cout << ulp << std::endl;
            //   max = std::max(ulp,max);
        }
    }
    std::cout << max << std::endl;
}

#undef NN
#undef TYPE
#undef MAX
#undef SIZE
