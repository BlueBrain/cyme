/*
 * Cyme - simd_div.hpp, Copyright (c), 2014,
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
 * @file cyme/core/simd_vector/math/simd_div.ipp
 * Implements operator/ for vec_simd class
 */

#ifndef CYME_SIMD_DIV_IPP
#define CYME_SIMD_DIV_IPP

namespace cyme {

/** Reccursive implementation of the Newton-Raphson algo for the division */
template <class T, cyme::simd O, int N, std::size_t n>
struct helper_div {
    static forceinline vec_simd<T, O, N> div(vec_simd<T, O, N> const &rhs) {
#ifdef __FMA__
        /** FMA negate operations are differents between INTEL-IBM */
        return helper_div<T, O, N, n - 1>::div(rhs) *
               negatemuladd(rhs, helper_div<T, O, N, n - 1>::div(rhs), vec_simd<T, O, N>(2.0));
#else
        return helper_div<T, O, N, n - 1>::div(rhs) *
               (vec_simd<T, O, N>(2.0) - rhs * helper_div<T, O, N, n - 1>::div(rhs));
#endif
    }
};

/** Final specialisation of cyme::helper_div and computation of an approximation of 1/r */
template <class T, cyme::simd O, int N>
struct helper_div<T, O, N, 0> {
    static forceinline vec_simd<T, O, N> div(vec_simd<T, O, N> const &rhs) { return rec<T, O, N>(rhs); }
};

/** Function object calling Newton-Raphson algo <3, ^_^' */
template <class T, cyme::simd O, int N>
struct NewtonRaphson_div {
    static forceinline vec_simd<T, O, N> div(const vec_simd<T, O, N> &lhs, const vec_simd<T, O, N> &rhs) { // lhs/rhs
        vec_simd<T, O, N> nrv = lhs * helper_div<T, O, N, div_recursion<T, O>::value>::div(rhs);
        return nrv;
    }
};

/** Function object calling vendor algo */
template <class T, cyme::simd O, int N>
struct Vendor_div {
    static forceinline vec_simd<T, O, N> div(const vec_simd<T, O, N> &lhs, const vec_simd<T, O, N> &rhs) { // lhs/rhs
        vec_simd<T, O, N> nrv(lhs);
        nrv /= rhs;
        return nrv;
    }
};

/** Selector for the division algorithm (vendor or Newton-Raphson) */
template <class T, cyme::simd O, int N, class Solver = NewtonRaphson_div<T, O, N>>
struct Helper_div {
    static forceinline vec_simd<T, O, N> div(const vec_simd<T, O, N> &lhs, const vec_simd<T, O, N> &rhs) { // lhs/rhs
        return Solver::div(lhs, rhs);
    }
};

/** Implements operator/ for syme::vec_simd */
template <class T, cyme::simd O, int N>
forceinline vec_simd<T, O, N> operator/(const vec_simd<T, O, N> &lhs, const vec_simd<T, O, N> &rhs) {
    return Helper_div<T, O, N>::div(lhs, rhs);
}
} // end namespace
#endif
