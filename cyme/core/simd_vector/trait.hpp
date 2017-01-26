/*
 * Cyme - trait.hpp, Copyright (c), 2014,
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
 * @file cyme/core/simd_vector/trait.hpp
 * Trait class for the composite SIMD register
 */

#ifndef CYME_TRAIT_HPP
#define CYME_TRAIT_HPP

namespace cyme {
/** Basic trait to avoid duplication
\warning The trait class does not check the validity of your type, only float-double
*/
template <typename T>
struct trait {
    typedef T value_type;
    typedef value_type *pointer;
    typedef value_type const *const_pointer;
    typedef value_type &reference;
    typedef value_type const &const_reference;
};

/** This trait class associates basic type SIMD register */
template <typename T, cyme::simd O, int N>
struct simd_trait : public trait<T> {};

/** \cond */
template <class T, cyme::simd O>
struct register_trait; // forward declaration
/** \endcond */

/** Composite (or unroll) vector, contain up to 4 SIMD registers */
template <class T, cyme::simd O, int n>
struct simd_unroll;

/** Partial specialisation of the composite vector for 4 SIMD registers */
template <class T, cyme::simd O>
struct simd_unroll<T, O, 4> {
    /** composition with the register_trait class specific to each architecture */
    typedef typename register_trait<T, O>::trait_register_type register_simd;
    /** Default constructor doing nothing, because I do not want pollute with useless instructions */
    simd_unroll(){};
    /** Basic copy constructor */
    simd_unroll(register_simd _r0, register_simd _r1, register_simd _r2, register_simd _r3)
        : r0(_r0), r1(_r1), r2(_r2), r3(_r3) {}
    /** 4 SIMD registers */
    register_simd r0;
    register_simd r1;
    register_simd r2;
    register_simd r3;
};

/** Partial specialisation of the composite vector for contains 2 SIMD registers */
template <class T, cyme::simd O>
struct simd_unroll<T, O, 2> {
    /** composition with the register_trait class specific to each architecture */
    typedef typename register_trait<T, O>::trait_register_type register_simd;
    /** Default constructor doing nothing, because I do not want pollute with useless instructions */
    simd_unroll(){};
    /** Basic copy constructor */
    simd_unroll(register_simd _r0, register_simd _r1) : r0(_r0), r1(_r1) {}
    /** 2 SIMD registers */
    register_simd r0;
    register_simd r1;
};

/** Helper class for the Newton-Raphson division algorithm.

The structure gives the maximum number of the recursion for the
Newton-Raphson division algorithm.  the precision of the Newton-Raphson algo
double at every step. As the approximation of the SIMD _mm_rcp_ps function is
12 bits on (x86), I need 2 iterations for the float (mantissa 24 bit) and 3/4
iterations for double (mantissa 52 bit). _mm_rcp_ps gives the same precision 12
bit for SSE2 and AVX.  On Mic the precision is 14 bit (so 3 iterations) and QPX
the prevision is 8 bits (3 iterations float, 4 iterations double)
*/
template <typename T, cyme::simd O>
struct div_recursion;

/** Helper class for the Newton-Raphson square-root algorithm.  */
template <typename T, cyme::simd O>
struct sqrt_recursion;
}

#ifdef __x86_64__
#include "cyme/core/simd_vector/detail/x86/trait_x86.ipp"
#endif

#ifdef __aarch64__
#include "cyme/core/simd_vector/detail/arm/trait_arm.ipp"
#endif

#if defined(_ARCH_QP) || defined(__PPC64__)
#include "cyme/core/simd_vector/detail/powerpc64/trait_powerpc64.ipp"
#endif

#ifdef __MIC__
#include "cyme/core/simd_vector/detail/mic/trait_mic.ipp"
#endif

#endif // CYME_TRAIT_HPP
