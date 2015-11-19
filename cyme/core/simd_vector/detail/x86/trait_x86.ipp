/*
* Cyme - trait_x86.ipp, Copyright (c), 2014,
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
 * @file cyme/core/simd_vector/detail/x86/trait_x86.ipp
 * Specialisation of the register_trait, simd_trait, Newton-Raphson
 * classes for the x86 architecture
 */

#ifndef CYME_TRAIT_X86_IPP
#define CYME_TRAIT_X86_IPP

#ifdef __AVX__
#include <immintrin.h> //type SIMD, avx
#else
#include <smmintrin.h> //type SIMD, sse4.1
#endif

namespace cyme{

    /** trait class that defined the hardware register  */
    template<class T, cyme::simd O>
    struct register_trait;

    /** Specialisation of the trait class for int, cyme::sse  
       integer register name is standard whatever the size 4,8,16,32 or 64 bits
    */
    template<>
    struct register_trait<int, cyme::sse>{
        typedef __m128i trait_register_type;
    };

    /** Specialisation of the trait class for float, cyme::sse  */
    template<>
    struct register_trait<float, cyme::sse>{
        typedef __m128 trait_register_type;
    };

    /** Specialisation of the trait class for double, cyme::sse  */
    template<>
    struct register_trait<double, cyme::sse>{
        typedef __m128d trait_register_type;
    };

#ifdef __AVX__
    /** Specialisation of the trait class for int, cyme::avx 
        integer register name is standard whatever the size 4,8,16,32 or 64 bits
    */
    template<>
    struct register_trait<int, cyme::avx>{
        typedef __m256i trait_register_type;
    };

    /** Specialisation of the trait class for float, cyme::avx  */
    template<>
    struct register_trait<float, cyme::avx>{
        typedef __m256 trait_register_type;
    };

    /** Specialisation of the trait class for double, cyme::avx  */
    template<>
    struct register_trait<double, cyme::avx>{
        typedef __m256d trait_register_type;
    };
#endif

    /** Specialisation of the trait class for the composite vector double,cyme::sse,4 regs*/
    template <>
    struct simd_trait<double, cyme::sse, 4> : trait<double>{
        typedef simd_unroll<double, cyme::sse, 4> register_type;
    };

    /** Specialisation of the trait class for the composite vector double,cyme::sse,2 regs */
    template <>
    struct simd_trait<double, cyme::sse, 2> : trait<double>{
        typedef simd_unroll<double,  cyme::sse, 2> register_type;
    };

    /** Specialisation of the trait class for the composite vector double,cyme::sse,1 reg */
    template <>
    struct simd_trait<double, cyme::sse, 1> : trait<double>{
        typedef __m128d register_type;
    };

    /** Specialisation of the trait class for the composite vector float,cyme::sse,4 regs*/
    template <>
    struct simd_trait<float, cyme::sse, 4> : trait<float>{
        typedef simd_unroll<float, cyme::sse, 4> register_type;
    };

    /** Specialisation of the trait class for the composite vector float,cyme::sse,2 regs*/
    template <>
    struct simd_trait<float, cyme::sse, 2> : trait<float>{
        typedef simd_unroll<float,  cyme::sse, 2> register_type;
    };

    /** Specialisation of the trait class for the composite vector float,cyme::sse,1 reg*/
    template <>
    struct simd_trait<float, cyme::sse, 1> : trait<float>{
        typedef __m128 register_type;
    };

    /** Specialisation of the trait class for the composite vector int,cyme::sse,4 regs*/
    template <>
    struct simd_trait<int, cyme::sse, 4> : trait<int>{
        typedef simd_unroll<int, cyme::sse, 4> register_type;
    };

    /** Specialisation of the trait class for the composite vector int,cyme::sse,2 regs*/
    template <>
    struct simd_trait<int, cyme::sse, 2> : trait<int>{
        typedef simd_unroll<int,  cyme::sse, 2> register_type;
    };

    /** Specialisation of the trait class for the composite vector int,cyme::sse,1 reg*/
    template <>
    struct simd_trait<int, cyme::sse, 1> : trait<int>{
        typedef __m128i register_type;
    };

    /** Specialization trait for float  Newton-Raphson division: number of iteration */
    template<>
    struct div_recursion<float, cyme::sse>{
        static const std::size_t value = 1; // cardinal([0-1])=2
    };

    /** Specialization trait for float  Newton-Raphson division: number of iteration */
    template<>
    struct div_recursion<float, cyme::avx>{
        static const std::size_t value = 1; // cardinal([0-1])=2
    };

    /** Specialization trait for double Newton-Raphson division: number of iteration */
    template<>
    struct div_recursion<double, cyme::sse>{
        static const std::size_t value = 2; // card([0-2])=3, should be 3
    };

    /** Specialization trait for double Newton-Raphson division: number of iteration */
    template<>
    struct div_recursion<double, cyme::avx>{
        static const std::size_t value = 2; // card([0-2])=3, should be 3
    };

    /** Specialization trait for float  Newton-Raphson sqrt: number of iteration */
    template<>
    struct sqrt_recursion<float, cyme::sse>{
        static const std::size_t value = 1; // cardinal([0-1])=2
    };

    /** Specialization trait for float Newton-Raphson sqrt: number of iteration */
    template<>
    struct sqrt_recursion<float, cyme::avx>{
        static const std::size_t value = 1; // cardinal([0-1])=2
    };

    /** Specialization trait for double Newton-Raphson sqrt: number of iteration */
    template<>
    struct sqrt_recursion<double, cyme::sse>{
        static const std::size_t value = 2; // card([0-2])=3, should be 3
    };

    /** Specialization trait for double Newton-Raphson sqrt: number of iteration */
    template<>
    struct sqrt_recursion<double, cyme::avx>{
        static const std::size_t value = 2; // card([0-2])=3, should be 3
    };

#ifdef __AVX__
    /** Specialisation of the trait class for the composite vector double,cyme::avx,4 regs*/
    template <>
    struct simd_trait<double, cyme::avx, 4> : trait<double>{
        typedef simd_unroll<double, cyme::avx, 4> register_type;
    };

    /** Specialisation of the trait class for the composite vector double,cyme::avx,2 regs*/
    template <>
    struct simd_trait<double, cyme::avx, 2> : trait<double>{
        typedef simd_unroll<double,  cyme::avx, 2> register_type;
    };

    /** Specialisation of the trait class for the composite vector double,cyme::avx,1 reg*/
    template <>
    struct simd_trait<double, cyme::avx, 1> : trait<double>{
        typedef __m256d register_type;
    };

    /** Specialisation of the trait class for the composite vector float,cyme::avx,4 regs*/
    template <>
    struct simd_trait<float, cyme::avx, 4> : trait<float>{
        typedef simd_unroll<float, cyme::avx, 4> register_type;
    };

    /** Specialisation of the trait class for the composite vector float,cyme::avx,2 regs*/
    template <>
    struct simd_trait<float, cyme::avx, 2> : trait<float>{
        typedef simd_unroll<float,  cyme::avx, 2> register_type;
    };

    /** Specialisation of the trait class for the composite vector float,cyme::avx,1 reg*/
    template <>
    struct simd_trait<float, cyme::avx, 1> : trait<float>{
        typedef __m256 register_type;
    };

    /** Specialisation of the trait class for the composite vector int,cyme::avx,4 regs*/
    template <>
    struct simd_trait<int, cyme::avx, 4> : trait<int>{
        typedef simd_unroll<int, cyme::avx, 4> register_type;
    };

    /** Specialisation of the trait class for the composite vector int,cyme::avx,2 regs*/
    template <>
    struct simd_trait<int, cyme::avx, 2> : trait<int>{
        typedef simd_unroll<int,  cyme::avx, 2> register_type;
    };

    /** Specialisation of the trait class for the composite vector int,cyme::avx,1 reg*/
    template <>
    struct simd_trait<int, cyme::avx, 1> : trait<int>{
        typedef __m256i register_type;
    };

#endif
    /** \endcond */
}
#endif
