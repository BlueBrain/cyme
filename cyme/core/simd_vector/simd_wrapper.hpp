/*
 * Cyme - simd_wrapper.hpp, Copyright (c), 2014,
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

#ifndef CYME_WRAPPER_HPP
#define CYME_WRAPPER_HPP

namespace numeric{

    /**
    \brief Free function (wrapper) for loading basic type (double, int) into register
    */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_load1(const typename simd_trait<T,O,N>::value_type& a);

    /**
    \brief Free function (wrapper) for loading data from memory (pointer) into register
    \warning The data must be aligned or else there will be a SEGFAULT
    */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_load(typename simd_trait<T,O,N>::const_pointer a);

    /**
    \brief Free function (wrapper) for storing the data in the memory (pointer)
    \warning The data must be aligned or else there will be a SEGFAULT
    */
    template<class T, memory::simd O, int N>
    forceinline void _mm_store(typename simd_trait<T,O,N>::register_type xmm0, typename simd_trait<T,O,N>::pointer a);

    /**
    \brief Free function (wrapper) for multiplying two registers
    */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_mul(typename simd_trait<T,O,N>::register_type xmm0, typename simd_trait<T,O,N>::register_type xmm1);

    /**
    \brief Free function (wrapper) for dividing two registers
    */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_div(typename simd_trait<T,O,N>::register_type xmm0, typename simd_trait<T,O,N>::register_type xmm1);

    /**
    \brief Free function (wrapper) for adding two registers
    */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_add(typename simd_trait<T,O,N>::register_type xmm0, typename simd_trait<T,O,N>::register_type xmm1);

    /**
    \brief Free function (wrapper) for subtracting two registers
    */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_sub(typename simd_trait<T,O,N>::register_type xmm0, typename simd_trait<T,O,N>::register_type xmm1); //xmm0 - xmm1

    /**
    \brief Free function (wrapper) for calculating the exp of a vector
    \warning this function is only works if the wrapper Helper_exp is setup to Vendor_exp
    */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_exp(typename simd_trait<T,O,N>::register_type xmm0); // Vendor (IBM/Intel) only 

    /**
    \brief Free function (wrapper) for calculating the log of a vector
    \warning this function is only works if the wrapper Helper_log is setup to Vendor_log
    */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_log(typename simd_trait<T,O,N>::register_type xmm0); // Vendor (IBM/Intel) only 

    /**
    \brief Free function (wrapper) for calculating sqrt of a vector
    \warning this function is only works if the wrapper Helper_sqrt is setup to Vendor_sqrt
    */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_sqrt(typename simd_trait<T,O,N>::register_type xmm0); // Vendor only - to check ? 

    /**
     \brief Free function (wrapper) for calculating a light version of the inverse (reciprocal)
     */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_rec(typename simd_trait<T,O,N>::register_type xmm0);

    /**
     \brief Free function (wrapper) for calculating a light version of the inverse of sqrt
     */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_rsqrt(typename simd_trait<T,O,N>::register_type xmm0);

    /**
     \brief Free function (wrapper) for calculating the negation of a number
     */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_neg(typename simd_trait<T,O,N>::register_type xmm0);

    /**
     \brief Free function (wrapper) for calculating the floor
     */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<int,O,N>::register_type _mm_floor(typename simd_trait<T,O,N>::register_type xmm0);

    /**
     \brief Free function to cast in/to float for the exp
     */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_cast(typename simd_trait<int,O,N>::register_type xmm0);

    /**
     \brief Free function to return the float vector 2^k
     */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_twok(typename simd_trait<int,O,N>::register_type xmm0);

    /**
     \brief Free function to return the exponent of a float
     */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_ge(typename simd_trait<T,O,N>::register_type xmm0);

    /**
     \brief Free function to return the fraction of a float
     */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_gf(typename simd_trait<T,O,N>::register_type xmm0);

    /**
     \brief Free function to load a SIMD vector with a single value
     */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_single_load(const typename simd_trait<T,O,N>::value_type);

    /**
     \brief Free function return a single value from a SIMD vector
    */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::value_type _mm_single_store(typename simd_trait<T,O,N>::register_type xmm0,
                                                                        const typename simd_trait<T,O,N>::pointer);

#ifdef __FMA__ // This macro is a compiler one
    /**
    \brief Free function (wrapper) for FMA between three registers
    */
    template<class T, memory::simd O, int N> // a*b+c
    forceinline typename simd_trait<T,O,N>::register_type _mm_fma(typename simd_trait<T,O,N>::register_type xmm0, typename simd_trait<T,O,N>::register_type xmm1, typename simd_trait<T,O,N>::register_type xmm2);

    /**
    \brief Free function (wrapper) for FMS between three registers
    */
    template<class T, memory::simd O, int N> // a*b-c
    forceinline typename simd_trait<T,O,N>::register_type _mm_fms(typename simd_trait<T,O,N>::register_type xmm0, typename simd_trait<T,O,N>::register_type xmm1, typename simd_trait<T,O,N>::register_type xmm2);

    /**
     \brief Free function (wrapper) for negative FMA part between three registers
     */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_nfma(typename simd_trait<T,O,N>::register_type xmm0, typename simd_trait<T,O,N>::register_type xmm1, typename simd_trait<T,O,N>::register_type xmm2);

    /**
     \brief Free function (wrapper) for negative FMS part between three registers
     */
    template<class T, memory::simd O, int N>
    forceinline typename simd_trait<T,O,N>::register_type _mm_nfms(typename simd_trait<T,O,N>::register_type xmm0, typename simd_trait<T,O,N>::register_type xmm1, typename simd_trait<T,O,N>::register_type xmm2);

#endif
} //end namespace

    #include "cyme/core/simd_vector/detail/x86/simd_svml.ipp" // mix GCC/clang and intel svml

#ifdef __SSE__
    #include "cyme/core/simd_vector/detail/x86/simd_wrapper_sse.ipp"
#endif

#ifdef __AVX__
    #include "cyme/core/simd_vector/detail/x86/simd_wrapper_avx.ipp"
#endif

#ifdef _ARCH_QP
    #include "cyme/core/simd_vector/detail/powerpc64/simd_wrapper_qpx.ipp"
#endif

#ifdef __MIC__
    #include "cyme/core/simd_vector/detail/mic/simd_wrapper_mic.ipp"
#endif

#endif
