/*
 * Cyme - simd_add.ipp, Copyright (c), 2014,
 * Timothee Ewart - Swiss Federal Institute of technology in Lausanne,
 * timothee.ewart@epfl.ch,
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
 * @file cyme/core/simd_vector/math/simd_add.ipp
 * Implements operator+ for vec_simd class
 */

#ifndef CYME_SIMD_ADD_IPP
#define CYME_SIMD_ADD_IPP

namespace cyme {

/** Implements operator+ for cyme::vec_simd */
template <class T, cyme::simd O, int N>
forceinline vec_simd<T, O, N> operator+(const vec_simd<T, O, N> &lhs, const vec_simd<T, O, N> &rhs) {
    vec_simd<T, O, N> nrv(lhs);
    nrv += rhs;
    return nrv;
}

/** addition with 0, see vec_simd.hpp for explanation  */
template <class T, cyme::simd O, int N>
forceinline vec_simd<T, O, N> operator+(const vec_simd<T, O, N> &lhs, ZERO) {
    return lhs;
}

/** addition with 0, see vec_simd.hpp for explanation  */
template <class T, cyme::simd O, int N>
forceinline vec_simd<T, O, N> operator+(ZERO, const vec_simd<T, O, N> &rhs) {
    return rhs;
}

/** addition with 0+0, see vec_simd.hpp for explanation  */
forceinline ZERO operator+(ZERO, ZERO) { return ZERO(); }
} // namespace cyme
#endif
