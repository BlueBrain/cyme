/*
 * Cyme - simd_wrapper.hpp, Copyright (c), 2014,
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
 * @file cyme/core/simd_vector/simd_wrapper.hpp
 * Defines corresponding SIMD wrappers for the vortexes of the DAG.
 */

#ifndef CYME_WRAPPER_HPP
#define CYME_WRAPPER_HPP

namespace cyme {
/**
  Free function (wrapper) to round integer up to the next even value.
*/
template <cyme::simd O, int N>
forceinline typename simd_trait<int, O, N>::register_type
_mm_round_up_even(typename simd_trait<int, O, N>::register_type xmm0);

/** Free function (wrapper) for loading basic type (double, int) into register */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::register_type _mm_load1(const typename simd_trait<T, O, N>::value_type &a);

/** Free function (wrapper) for loading data from cyme (pointer) into register
\warning The data must be aligned or else there will be a SEGFAULT
*/
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::register_type _mm_load(typename simd_trait<T, O, N>::const_pointer a);

/** Free function (wrapper) for storing the data in the cyme (pointer)
\warning The data must be aligned or else there will be a SEGFAULT
*/
template <class T, cyme::simd O, int N>
forceinline void _mm_store(typename simd_trait<T, O, N>::register_type xmm0, typename simd_trait<T, O, N>::pointer a);

/** Free function (wrapper) for multiplying two registers */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::register_type _mm_mul(typename simd_trait<T, O, N>::register_type xmm0,
                                                                typename simd_trait<T, O, N>::register_type xmm1);

/** Free function (wrapper) for dividing two registers */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::register_type _mm_div(typename simd_trait<T, O, N>::register_type xmm0,
                                                                typename simd_trait<T, O, N>::register_type xmm1);

/** Free function (wrapper) for adding two registers */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::register_type _mm_add(typename simd_trait<T, O, N>::register_type xmm0,
                                                                typename simd_trait<T, O, N>::register_type xmm1);

/** Free function (wrapper) for subtracting two registers */
template <class T, cyme::simd O, int N> // xmm0 - xmm1
forceinline typename simd_trait<T, O, N>::register_type _mm_sub(typename simd_trait<T, O, N>::register_type xmm0,
                                                                typename simd_trait<T, O, N>::register_type xmm1);

/** Free function (wrapper) for calculating the exp of a vector
\warning this function is only works if the wrapper Helper_exp is setup to Vendor_exp
*/
template <class T, cyme::simd O, int N> // Vendor (IBM/Intel) only
forceinline typename simd_trait<T, O, N>::register_type _mm_exp(typename simd_trait<T, O, N>::register_type xmm0);

/** Free function (wrapper) for calculating the log of a vector
\warning this function is only works if the wrapper Helper_log is setup to Vendor_log
*/
template <class T, cyme::simd O, int N> // Vendor (IBM/Intel) only
forceinline typename simd_trait<T, O, N>::register_type _mm_log(typename simd_trait<T, O, N>::register_type xmm0);

/** Free function (wrapper) for calculating sqrt of a vector
\warning this function is only works if the wrapper Helper_sqrt is setup to Vendor_sqrt
*/
template <class T, cyme::simd O, int N> // Vendor only - to check ?
forceinline typename simd_trait<T, O, N>::register_type _mm_sqrt(typename simd_trait<T, O, N>::register_type xmm0);

/** Free function (wrapper) for calculating a light version of the inverse (reciprocal) */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::register_type _mm_rec(typename simd_trait<T, O, N>::register_type xmm0);

/** Free function (wrapper) for calculating a light version of the inverse of sqrt */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::register_type _mm_rsqrt(typename simd_trait<T, O, N>::register_type xmm0);

/** Free function (wrapper) for calculating the negation of a number */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::register_type _mm_neg(typename simd_trait<T, O, N>::register_type xmm0);

/** Free function (wrapper) to check is the register is full of 0 */
template <class T, cyme::simd O, int N>
forceinline bool _mm_is_empty(typename simd_trait<T, O, N>::register_type xmm0);

/** Free function to cast in/to float for the exp */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::register_type _mm_cast(typename simd_trait<int, O, N>::register_type xmm0);

/** Free function (wrapper) for calculating the floor */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<int, O, N>::register_type _mm_floor(typename simd_trait<T, O, N>::register_type xmm0);

/** Free function to return the float vector 2^k */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::register_type _mm_twok(typename simd_trait<int, O, N>::register_type xmm0);

/** Free function to return the exponent of a float */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::register_type _mm_ge(typename simd_trait<T, O, N>::register_type xmm0);

/** Free function to return the fraction of a float */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::register_type _mm_gf(typename simd_trait<T, O, N>::register_type xmm0);

/** Free function to return the absolute value of a float */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::register_type _mm_fabs(typename simd_trait<T, O, N>::register_type xmm0);

/** Free function that change the type of register */
template <class T, cyme::simd O, int N, class T2>
forceinline typename simd_trait<T2, O, N>::register_type _mm_cast(typename simd_trait<T, O, N>::register_type xmm0);

/** Free function to return poly1 or poly2 depending on the value of sel */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::register_type
_mm_select_poly(typename simd_trait<int, O, N>::register_type sel, typename simd_trait<T, O, N>::register_type xmm0,
                typename simd_trait<T, O, N>::register_type xmm1);

/** Free function to select the sign (+/-) for sin function */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::register_type
_mm_select_sign_sin(typename simd_trait<int, O, N>::register_type swap,
                    typename simd_trait<T, O, N>::register_type xmm0, typename simd_trait<T, O, N>::register_type xmm1);

/** Free function to select the sign (+/-) for cos function */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::register_type
_mm_select_sign_cos(typename simd_trait<int, O, N>::register_type swap,
                    typename simd_trait<T, O, N>::register_type xmm0);

/** Free function to load a SIMD vector with a single value */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::register_type _mm_single_load(const typename simd_trait<T, O, N>::value_type);

/** Free function return a single value from a SIMD vector */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::value_type _mm_single_store(typename simd_trait<T, O, N>::register_type xmm0,
                                                                      const typename simd_trait<T, O, N>::pointer);
/** Free function (wrapper) to compare two register xmm0 less than xmm1 */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::register_type _mm_lt(typename simd_trait<T, O, N>::register_type xmm0,
                                                               typename simd_trait<T, O, N>::register_type xmm1);

/** Free function (wrapper) to compare two register xmm0 more than xmm1 */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::register_type _mm_gt(typename simd_trait<T, O, N>::register_type xmm0,
                                                               typename simd_trait<T, O, N>::register_type xmm1);

/** Free function (wrapper) to compare two register xmm0 equal to xmm1 */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::register_type _mm_eq(typename simd_trait<T, O, N>::register_type xmm0,
                                                               typename simd_trait<T, O, N>::register_type xmm1);

/** Free function (wrapper) to bitwise xmm0 & xmm1 */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::register_type _mm_and(typename simd_trait<T, O, N>::register_type xmm0,
                                                                typename simd_trait<T, O, N>::register_type xmm1);

/** Free function (wrapper) to bitwise xmm0 | xmm1 */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::register_type _mm_or(typename simd_trait<T, O, N>::register_type xmm0,
                                                               typename simd_trait<T, O, N>::register_type xmm1);

/** Free function (wrapper) to bitwise xmm0 &! xmm1 for negate only */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::register_type _mm_andnot(typename simd_trait<T, O, N>::register_type xmm0);

/** Free function (wrapper) of the minimum function */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::register_type _mm_min(typename simd_trait<T, O, N>::register_type xmm0,
                                                                typename simd_trait<T, O, N>::register_type xmm1);

#ifdef __FMA__ // This macro is a compiler one
/** Free function (wrapper) for FMA between three registers, a*b+c */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::register_type _mm_fma(typename simd_trait<T, O, N>::register_type xmm0,
                                                                typename simd_trait<T, O, N>::register_type xmm1,
                                                                typename simd_trait<T, O, N>::register_type xmm2);

/** Free function (wrapper) for FMS between three registers, a*b-c */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::register_type _mm_fms(typename simd_trait<T, O, N>::register_type xmm0,
                                                                typename simd_trait<T, O, N>::register_type xmm1,
                                                                typename simd_trait<T, O, N>::register_type xmm2);

/** Free function (wrapper) for negative FMA part between three registers */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::register_type _mm_nfma(typename simd_trait<T, O, N>::register_type xmm0,
                                                                 typename simd_trait<T, O, N>::register_type xmm1,
                                                                 typename simd_trait<T, O, N>::register_type xmm2);

/** Free function (wrapper) for negative FMS part between three registers */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::register_type _mm_nfms(typename simd_trait<T, O, N>::register_type xmm0,
                                                                 typename simd_trait<T, O, N>::register_type xmm1,
                                                                 typename simd_trait<T, O, N>::register_type xmm2);

#endif
/** Free function (wrapper) for loading data into registers using gather instructions */
template <class T, cyme::simd O, int N>
forceinline typename simd_trait<T, O, N>::register_type _mm_gather(const T *src, const int *ind, const int range);

/** Free function (wrapper) for storing data into a cyme (pointer) using scatter instructions */
template <class T, cyme::simd O, int N>
void _mm_scatter(typename simd_trait<T, O, N>::register_type xmm0, T *dst, const int *ind, const int range);

} // end namespace

#include "cyme/core/simd_vector/detail/x86/simd_svml.ipp" // mix GCC/clang and intel svml

#ifdef __SSE__
#include "cyme/core/simd_vector/detail/x86/simd_wrapper_sse.ipp"
#endif

#ifdef __AVX__
#include "cyme/core/simd_vector/detail/x86/simd_wrapper_avx.ipp"
#endif

#ifdef __aarch64__
#include "cyme/core/simd_vector/detail/arm/simd_wrapper_arm.ipp"
#endif

#ifdef _ARCH_QP
#include "cyme/core/simd_vector/detail/powerpc64/simd_wrapper_qpx.ipp"
#endif

#ifdef __MIC__
#include "cyme/core/simd_vector/detail/mic/simd_wrapper_mic.ipp"
#endif

#if !defined(_ARCH_QP) && defined(__PPC64__)
#include "cyme/core/simd_vector/detail/powerpc64/simd_wrapper_vmx.ipp"
#endif

#endif
