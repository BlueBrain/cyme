/*
 * Cyme - simd_pow.ipp, Copyright (c), 2014,
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
 * @file cyme/core/simd_vector/math/simd_pow.ipp
 * Implements exp for vec_simd class
 */

#ifndef CYME_SIMD_POW_IPP
#define CYME_SIMD_POW_IPP

namespace cyme {
/** Specialization of pow for even number

   Tthe template parameter K (default value exponent%2 true) make the selection
    if it is a multiple of 2
*/
template <class T, cyme::simd O, int N, int M, int K = M % 2>
struct pow_helper {
    static forceinline vec_simd<T, O, N> pow(const vec_simd<T, O, N> &lhs) {
        return pow_helper<T, O, N, M / 2>::pow(lhs) * pow_helper<T, O, N, M / 2>::pow(lhs);
    }
};

/** Specialization of pow for odd number

    \remarks with integer M/2 is equivalent to (M-1)/2 e.g. 7/2 = 3.5 rounds to 3
*/
template <class T, cyme::simd O, int N, int M>
struct pow_helper<T, O, N, M, 1> {
    static forceinline vec_simd<T, O, N> pow(const vec_simd<T, O, N> &lhs) {
        return lhs * pow_helper<T, O, N, M / 2>::pow(lhs) * pow_helper<T, O, N, M / 2>::pow(lhs);
    }
};

/** Final specialiasation of the pow function */
template <class T, cyme::simd O, int N>
struct pow_helper<T, O, N, 1, 1> {
    static forceinline vec_simd<T, O, N> pow(const vec_simd<T, O, N> &lhs) { return lhs; }
};

/** Final specialiasation of the pow function, x**0 = 1 */
template <class T, cyme::simd O, int N>
struct pow_helper<T, O, N, 0, 0> {
    static forceinline vec_simd<T, O, N> pow(const vec_simd<T, O, N> &) {
        std::cout << " PLEASE TUNE YOUR CODE, adjust your partialization " << std::endl;
        return vec_simd<T, O, N>(1.);
    }
};

/** Implementation of Pow(a,n) m integer

  The algo calculates the power of n (uint given)
     is the followingr:
     \code{.cpp}
          x^n is decomposed following n
          x^n = (x^n/2)^2 n even
          x^n = n(x^n/2)^2 n odd
     \endcode
*/
template <class T, cyme::simd O, int N, int M>
forceinline vec_simd<T, O, N> pow(const vec_simd<T, O, N> &lhs) {
    return pow_helper<T, O, N, M>::pow(lhs);
}

/** Function object for the vendor pow algorithm */
template <class T, cyme::simd O, int N>
struct Vendor_pow {
    static forceinline vec_simd<T, O, N> pow(vec_simd<T, O, N> const &x, vec_simd<T, O, N> const &y) {
        return vec_simd<T, O, N>(_mm_pow<T, O, N>(x.xmm, y.xmm)); // vendor call
    }
};

/** Function object for the cyme pow algorithm, very poor performance and no boundary check be carefull*/
template <class T, cyme::simd O, int N>
struct Cyme_pow {
    static forceinline vec_simd<T, O, N> pow(vec_simd<T, O, N> const &x, vec_simd<T, O, N> const &y) {
        // Tim math is not allowed ^_^
        //            vec_simd<T, O, N> sign_y(-0.); // mask bit sign set up
        //            sign_y &= x;                   // catch the sign of x
        //            sign_y |= y;                   // apply it to y
        return exp(y * log(fabs(x)));
    }
};

/** Selector for the pow algorithm (vendor or cyme implementation) */
template <class T, cyme::simd O, int N, class Solver = Cyme_pow<T, O, N>> // cyme_pow ou vendor
struct Selector_pow {
    static forceinline vec_simd<T, O, N> pow(vec_simd<T, O, N> x, const vec_simd<T, O, N> &y) {
        x = Solver::pow(x, y);
        return x;
    }
};

/** Implementation of Pow(x,y) x, y are floating point vector

 The algo computes x^y using exp(x*log*y))
 */
template <class T, cyme::simd O, int N>
forceinline vec_simd<T, O, N> pow(const vec_simd<T, O, N> &x, const vec_simd<T, O, N> &y) {
    return Selector_pow<T, O, N>::pow(x, y);
}
}
#endif
