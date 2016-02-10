/*
 * Cyme - gather_scatter.cpp, Copyright (c), 2014,
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

using namespace cyme::test;
#define TYPE typename T::value_type

#define NN cyme::unroll_factor::N*cyme::trait_register<TYPE,cyme::__GETSIMD__()>::size/sizeof(TYPE)

BOOST_AUTO_TEST_CASE_TEMPLATE(interface_gather_scatter_comparison_reverse, T, floating_point_test_types) {
      TYPE a[NN] __attribute__((aligned(64)));
      TYPE b[NN] __attribute__((aligned(64)));
      int ind[NN];

      for(size_t i=0; i<NN; ++i){
          a[i] = GetRandomExp10<TYPE>();
          b[i] = 0;
          ind[i] = i;
      }
      cyme::vec<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> v = cyme::gather<TYPE,cyme::__GETSIMD__(),
                                                                                  cyme::unroll_factor::N>(a,ind,NN);
      cyme::scatter<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N,cyme::eq>(v,b,ind,NN);

      for(size_t i=0; i<NN; ++i)
        BOOST_REQUIRE_CLOSE( a[i], b[i], 0.001);
}


BOOST_AUTO_TEST_CASE_TEMPLATE(simd_gather_scatter_comparison_reverse_add, T, floating_point_test_types) {
      TYPE a[NN] __attribute__((aligned(64)));
      TYPE b[NN] __attribute__((aligned(64)));
      TYPE c[NN] __attribute__((aligned(64)));

      int ind[NN];

      for(size_t i=0; i<NN; ++i){
          a[i] = GetRandomExp10<TYPE>();
          b[i] = GetRandomExp10<TYPE>();
          c[i] = a[i] + b[i];
          ind[i] = i;

      }
      cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> v = cyme::help_gather<TYPE,cyme::__GETSIMD__(),
                                                                                       cyme::unroll_factor::N>(a,ind,NN);
      cyme::help_scatter<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N,cyme::add>(v,b,ind,NN);

      for(size_t i=0; i<NN; ++i)
        BOOST_REQUIRE_CLOSE( c[i], b[i], 0.001);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(simd_gather_scatter_comparison_reverse_sub, T, floating_point_test_types) {
    TYPE a[NN] __attribute__((aligned(64)));
    TYPE b[NN] __attribute__((aligned(64)));
    TYPE c[NN] __attribute__((aligned(64)));

    int ind[NN];

    for(size_t i=0; i<NN; ++i){
        a[i] = GetRandomExp10<TYPE>();
        b[i] = GetRandomExp10<TYPE>();
        c[i] = b[i] - a[i]; // b -a != a-b
        ind[i] = i;

    }
    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> v = cyme::help_gather<TYPE,cyme::__GETSIMD__(),
    cyme::unroll_factor::N>(a,ind,NN);
    cyme::help_scatter<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N,cyme::sub>(v,b,ind,NN);

    for(size_t i=0; i<NN; ++i)
        BOOST_REQUIRE_CLOSE( c[i], b[i], 0.001);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(simd_gather_scatter_comparison_reverse_mul, T, floating_point_test_types) {
    TYPE a[NN] __attribute__((aligned(64)));
    TYPE b[NN] __attribute__((aligned(64)));
    TYPE c[NN] __attribute__((aligned(64)));

    int ind[NN];

    for(size_t i=0; i<NN; ++i){
        a[i] = GetRandomExp10<TYPE>();
        b[i] = GetRandomExp10<TYPE>();
        c[i] = a[i] * b[i];
        ind[i] = i;

    }
    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> v = cyme::help_gather<TYPE,cyme::__GETSIMD__(),
    cyme::unroll_factor::N>(a,ind,NN);
    cyme::help_scatter<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N,cyme::mul>(v,b,ind,NN);

    for(size_t i=0; i<NN; ++i)
        BOOST_REQUIRE_CLOSE( c[i], b[i], 0.001);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(simd_gather_scatter_comparison_reverse_div, T, floating_point_test_types) {
    TYPE a[NN] __attribute__((aligned(64)));
    TYPE b[NN] __attribute__((aligned(64)));
    TYPE c[NN] __attribute__((aligned(64)));

    int ind[NN];

    for(size_t i=0; i<NN; ++i){
        a[i] = GetRandomExp10<TYPE>();
        b[i] = GetRandomExp10<TYPE>();
        c[i] = b[i] / a[i]; // b/a != a/b
        ind[i] = i;

    }
    cyme::vec_simd<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N> v = cyme::help_gather<TYPE,cyme::__GETSIMD__(),
    cyme::unroll_factor::N>(a,ind,NN);
    cyme::help_scatter<TYPE,cyme::__GETSIMD__(),cyme::unroll_factor::N,cyme::div>(v,b,ind,NN);

    for(size_t i=0; i<NN; ++i)
        BOOST_REQUIRE_CLOSE( c[i], b[i], 0.001);
}
