/*
 * Cyme - simd_exp.hpp, Copyright (c), 2014,
 * Timothee Ewart - Swiss Federal Institute of technology in Lausanne,
 * timothee.ewart@epfl.ch,
 * Kai Langen,
 * kai.langen@usask.ca,
 * All rights reserved.
 * This file is part of Cyme <https://github.com/BlueBrain/cyme>
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

/**
 * @file cyme/core/simd_vector/math/simd_scatter.ipp
 * Implements scatter for vec_simd class
 */

#ifndef CYME_SIMD_SCATTER_IPP
#define CYME_SIMD_SCATTER_IPP

#include <boost/assert.hpp>

namespace cyme {

template <class T, cyme::scatter_op P>
struct scatter_op_selector_helper {};

template <class T>
struct scatter_op_selector_helper<T, cyme::add> {
    static void forceinline scatter_op_selector(T &a, T const &b) { a += b; }
};

template <class T>
struct scatter_op_selector_helper<T, cyme::sub> {
    static void forceinline scatter_op_selector(T &a, T const &b) { a -= b; }
};

template <class T>
struct scatter_op_selector_helper<T, cyme::mul> {
    static void forceinline scatter_op_selector(T &a, T const &b) { a *= b; }
};

template <class T>
struct scatter_op_selector_helper<T, cyme::div> {
    static void forceinline scatter_op_selector(T &a, T const &b) { a /= b; }
};

template <class T>
struct scatter_op_selector_helper<T, cyme::eq> {
    static void forceinline scatter_op_selector(T &a, T const &b) { a = b; }
};

/** Free function that associate a scatter operations with an operations
 * We are looking for scatter add
 * 1) store the "destination" data into array
 * 2) create tmp SIMD vector
 * 3) do the op.
 * 4) scatter the res
 */
template <class T, cyme::simd O, int N, cyme::scatter_op P>
struct scatter_ops_helper {
    static void forceinline scatter_ops(vec_simd<T, O, N> const &u, T *dst, const int *ind, const int range) {
        const int size = elems_helper<T, N>::size;
        BOOST_ASSERT_MSG(range <= size, "range larger than size");
        T elems[size]
            __attribute__((aligned(static_cast<std::size_t>(cyme::trait_register<T, cyme::__GETSIMD__()>::size))));

        _mm_store<T, O, N>(u.xmm, elems);

        for (int i = 0; i < range; i++)
            scatter_op_selector_helper<T, P>::scatter_op_selector(dst[ind[i]], elems[i]);
    }
};

/** Free function for scatter */
template <class T, cyme::simd O, int N, cyme::scatter_op P>
void forceinline help_scatter(cyme::vec_simd<T, O, N> const &u, T *dst, const int *ind, const int range) {
    scatter_ops_helper<T, O, N, P>::scatter_ops(u, dst, ind, range);
}
}
#endif
