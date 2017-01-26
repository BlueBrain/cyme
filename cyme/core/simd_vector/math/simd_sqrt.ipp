/*
 * Cyme - simd_sqrt.ipp, Copyright (c), 2014,
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
 * @file cyme/core/simd_vector/math/simd_sqrt.ipp
 * Implements function sqrt for vec_simd class
 */

#ifndef CYME_SIMD_SQRT_IPP
#define CYME_SIMD_SQRT_IPP

namespace cyme {

/** Reccursive implementation of the Newton-Raphson algo for the sqrt */
template <class T, cyme::simd O, int N, std::size_t n>
struct helper_rsqrt {
    static forceinline vec_simd<T, O, N> rsqrt(vec_simd<T, O, N> const &rhs) {
#ifdef __FMA__
        // FMA negate operations are differents between INTEL-IBM
        return vec_simd<T, O, N>(0.5) * helper_rsqrt<T, O, N, n - 1>::rsqrt(rhs) *
               negatemuladd(rhs, helper_rsqrt<T, O, N, n - 1>::rsqrt(rhs) * helper_rsqrt<T, O, N, n - 1>::rsqrt(rhs),
                            vec_simd<T, O, N>(3.0));
#else
        return vec_simd<T, O, N>(0.5) * helper_rsqrt<T, O, N, n - 1>::rsqrt(rhs) *
               (vec_simd<T, O, N>(3.0) -
                rhs * helper_rsqrt<T, O, N, n - 1>::rsqrt(rhs) * helper_rsqrt<T, O, N, n - 1>::rsqrt(rhs));
#endif
    }
};

/** Final specialisation of cyme::helper_div and computation of an approximation of 1/sqrt(r) */
template <class T, cyme::simd O, int N>
struct helper_rsqrt<T, O, N, 0> {
    static forceinline vec_simd<T, O, N> rsqrt(vec_simd<T, O, N> const &rhs) { return recsqrt<T, O, N>(rhs); }
};

/** Function object calling Newton-Raphson algo <3, ^_^' */
template <class T, cyme::simd O, int N>
struct NewtonRaphson_sqrt {
    static forceinline vec_simd<T, O, N> sqrt(const vec_simd<T, O, N> &rhs) {                         // lhs/rhs
        vec_simd<T, O, N> nrv = rhs * helper_rsqrt<T, O, N, sqrt_recursion<T, O>::value>::rsqrt(rhs); // x * 1/sqrt(x)
        return nrv;
    }
};

/** Function object calling vendor algo */
template <class T, cyme::simd O, int N>
forceinline vec_simd<T, O, N> sqrt_v(const vec_simd<T, O, N> &rhs) {
    vec_simd<T, O, N> nrv(_mm_sqrt<T, O, N>(rhs.xmm));
    return nrv;
}

/** Vendor implementation of the sqrt (hardware) */
template <class T, cyme::simd O, int N>
struct Vendor_sqrt {
    static forceinline vec_simd<T, O, N> sqrt(vec_simd<T, O, N> const &a) {
        return sqrt_v(a); /* call vendor wrapper */
    }
};

/** Selector for the division algorithm (vendor or Newton-Raphson) */
template <class T, cyme::simd O, int N>
struct helper_Solver {
#ifdef __x86_64__
    typedef Vendor_sqrt<T, O, N> Solver_sqrt;
#elif defined(_ARCH_QP) || defined(__PPC64__) || (__aarch64__)
    typedef NewtonRaphson_sqrt<T, O, N> Solver_sqrt;
#endif
};

/** Selector for the sqrt algorithm (vendor or Newton-Raphson)

 \warning BG/Q does not support natively square root
*/
template <class T, cyme::simd O, int N, class Solver = typename helper_Solver<T, O, N>::Solver_sqrt>
struct Selector_sqrt {
    static forceinline vec_simd<T, O, N> sqrt(vec_simd<T, O, N> x) {
        x = Solver::sqrt(x);
        return x;
    }
};

/** Implements function sqrt for syme::vec_simd */
template <class T, cyme::simd O, int N>
forceinline vec_simd<T, O, N> sqrt(const vec_simd<T, O, N> &rhs) {
    return Selector_sqrt<T, O, N>::sqrt(rhs);
}
}
#endif
