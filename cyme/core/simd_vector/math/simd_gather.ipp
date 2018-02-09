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
 * @file cyme/core/simd_vector/math/simd_gather.ipp
 * Implements gather for vec_simd class
 */

#ifndef CYME_SIMD_GATHER_IPP
#define CYME_SIMD_GATHER_IPP

#include <boost/assert.hpp>

namespace cyme {
template <class T, cyme::simd O, int N>
struct generic_gather {
    static forceinline vec_simd<T, O, N> gather(const T *src, const int *ind, const int range) {
        const int size = elems_helper<T, N>::size;
        BOOST_ASSERT_MSG(range <= size, "range larger than size");
        T elems[size]
            __attribute__((aligned(static_cast<std::size_t>(cyme::trait_register<T, cyme::__GETSIMD__()>::size))));

        for (int i = 0; i < range; i++)
            elems[i] = src[ind[i]];

        vec_simd<T, O, N> nrv(_mm_load<typename simd_trait<T, O, N>::value_type, O, N>(elems));
        return nrv;
    }
};

/** Free function for call the vendor gather */
template <class T, cyme::simd O, int N>
forceinline vec_simd<T, O, N> gather_v(const T *src, const int *ind, const int range) {
    vec_simd<T, O, N> nrv(_mm_gather<T, O, N>(src, ind, range));
    return nrv;
}

/** Function object for the vendor gather algorithm */
template <class T, cyme::simd O, int N>
struct simd_gather {
    static forceinline vec_simd<T, O, N> gather(const T *src, const int *ind, const int range) {
        return gather_v<T, O, N>(src, ind, range); /* call vendor wrapper */
    }
};

/** Selector for the gather algorithm (vendor (simd_gather) or generic implementation (generic_gather)) */
template <class T, cyme::simd O, int N, class Solver = generic_gather<T, O, N>>
struct Selector_gather {
    static forceinline vec_simd<T, O, N> gather(const T *src, const int *ind, const int range) {
        return Solver::gather(src, ind, range);
    }
};

/** free function for gather */
template <class T, cyme::simd O, int N>
forceinline vec_simd<T, O, N> help_gather(const T *src, const int *ind, const int range) {
    return Selector_gather<T, O, N>::gather(src, ind, range); // range is useless
}
} // namespace cyme

#endif
