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

namespace cyme{
    /** Specialization of pow for even number

       Tthe template parameter K (default value exponent%2 true) make the selection
        if it is a multiple of 2
    */
    template<class T,cyme::simd O, int N, int M, int K = M%2>
    struct pow_helper{
        static forceinline vec_simd<T,O,N> pow(const vec_simd<T,O,N>& lhs){
             return pow_helper<T,O,N,M/2>::pow(lhs)*pow_helper<T,O,N,M/2>::pow(lhs);
        }
    };

    /** Specialization of pow for odd number

        \remarks with integer M/2 is equivalent to (M-1)/2 e.g. 7/2 = 3.5 rounds to 3
    */
    template<class T,cyme::simd O, int N, int M>
    struct pow_helper<T,O,N,M,1>{
        static forceinline vec_simd<T,O,N> pow(const vec_simd<T,O,N>& lhs){
             return lhs*pow_helper<T,O,N,M/2>::pow(lhs)*pow_helper<T,O,N,M/2>::pow(lhs);
        }
    };

    /** Final specialirsation of the pow function */
    template<class T,cyme::simd O, int N>
    struct pow_helper<T,O,N,1,1>{
        static forceinline vec_simd<T,O,N> pow(const vec_simd<T,O,N>& lhs){
             return lhs;
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
    template<class T,cyme::simd O, int N, int M>
    forceinline vec_simd<T,O,N> pow(const vec_simd<T,O,N>& lhs){
        return pow_helper<T,O,N,M>::pow(lhs);
    }
}
#endif

