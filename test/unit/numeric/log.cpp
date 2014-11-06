/*
 * Cyme - log.cpp, Copyright (c), 2014,
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

#include <test/unit/test_header.hpp>

using namespace cyme::test;

#define TYPE typename T::value_type
#define SIZE T::size
#define MAX 1000

#define NN memory::unroll_factor::N*memory::trait_register<TYPE,memory::__GETSIMD__()>::size/sizeof(TYPE)

template<class T>
T precision_log();

template<>
double precision_log(){
    return 0.005;
}

template<>
float precision_log(){
    return 5.0;
}

BOOST_AUTO_TEST_CASE_TEMPLATE(std_log_comparison, T, floating_point_test_types) {
    TYPE a[NN] __attribute__((aligned(64)));
    TYPE b[NN] __attribute__((aligned(64)));
    TYPE res[NN] __attribute__((aligned(64)));
    for(size_t k=0; k<100; ++k){
        for(size_t i=0; i<NN; ++i){
            b[i] = fabs(GetRandom<TYPE>());
        }

        numeric::vec_simd<TYPE,memory::__GETSIMD__(),memory::unroll_factor::N> va;
        numeric::vec_simd<TYPE,memory::__GETSIMD__(),memory::unroll_factor::N> vb(b);

        for(size_t i=0; i<NN; ++i)
            a[i] = log(b[i]);

        va = log(vb);
        va.store(res);

        for(size_t i=0; i<NN; ++i)
          BOOST_REQUIRE_CLOSE( a[i], res[i], precision_log<TYPE>()); // precision soso on x86 try to understand why for float 0<x<=1 
                                                                     // {system : -0.00051404332} and me: -0.000523375755
    }
}

BOOST_AUTO_TEST_CASE_TEMPLATE(std_log_comparisoni_serial, T, floating_point_test_types) {
    TYPE a[NN] __attribute__((aligned(64)));
    TYPE b[NN] __attribute__((aligned(64)));

    TYPE sa[NN] __attribute__((aligned(64)));
    TYPE sb[NN] __attribute__((aligned(64)));


    TYPE res[NN] __attribute__((aligned(64)));
    for(size_t k=0; k<100; ++k){
        for(size_t i=0; i<NN; ++i){
            sa[i] = a[i] = fabs(GetRandom<TYPE>());
            sb[i] = b[i] = fabs(GetRandom<TYPE>());
        }


        for(size_t i=0; i<NN; ++i){
            a[i] = log(b[i]);
            sa[i] = slog(sb[i]);
        }

        for(size_t i=0; i<NN; ++i)
          BOOST_REQUIRE_CLOSE( a[i], sa[i], precision_log<TYPE>());
    }
}
#undef NN
#undef TYPE
#undef MAX
#undef SIZE
