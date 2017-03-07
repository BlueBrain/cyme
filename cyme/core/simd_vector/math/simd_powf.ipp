/*
 * Cyme - simd_powf.ipp, Copyright (c), 2014,
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
 * @file cyme/core/simd_vector/math/simd_powf.ipp
 * Implements powf for vec_simd class
 */

#ifndef CYME_SIMD_POWF_IPP
#define CYME_SIMD_POWF_IPP

#include <limits>

namespace cyme {

/** Function object for the vendor powf algorithm */
template <class T, cyme::simd O, int N>
struct Vendor_pow {
    static forceinline vec_simd<T, O, N> powf(vec_simd<T, O, N> const &x, vec_simd<T, O, N> const &y) {
        return vec_simd<T, O, N>(_mm_pow<T, O, N>(x.xmm, y.xmm)); // vendor call
    }
};

/** Function object for the cyme powf algorithm, very poor performance */
template <class T, cyme::simd O, int N>
struct Cyme_pow {
    static forceinline vec_simd<T, O, N> powf(vec_simd<T, O, N> const &x, vec_simd<T, O, N> const &y) {
        vec_simd<T, O, N> sign_y(-0.); // mask bit sign set up
        sign_y &= x;                   // catch the sign of x
        sign_y |= y;                   // apply it to y
        return exp(sign_y * log(fabs(x)));
    }
};

/** Selector for the powf algorithm (vendor or cyme implementation) */
template <class T, cyme::simd O, int N, class Solver = Cyme_pow<T, O, N>> // cyme_powf ou vendor
struct Selector_powf {
    static forceinline vec_simd<T, O, N> powf(vec_simd<T, O, N> x, const vec_simd<T, O, N> &y) {
        x = Solver::powf(x, y);
        return x;
    }
};

/** free function for the powf */
template <class T, cyme::simd O, int N>
forceinline vec_simd<T, O, N> pow_f(const vec_simd<T, O, N> &x, const vec_simd<T, O, N> &y) {
    return Selector_powf<T, O, N>::powf(x, y);
}
}
#endif
