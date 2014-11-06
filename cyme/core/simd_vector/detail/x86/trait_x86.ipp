/*
* Cyme - trait_x86.ipp, Copyright (c), 2014,
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

#ifndef CYME_TRAIT_X86_IPP
#define CYME_TRAIT_X86_IPP

#ifdef __AVX__
#include <immintrin.h> //type SIMD, memory::memory::avx
#else
#include <smmintrin.h> //type SIMD, memory::sse4.1
#endif

#include "cyme/core/simd_vector/detail/x86/simd_svml.h"

namespace numeric{

    template<class T, memory::simd O>
    struct register_trait;

    template<>
    struct register_trait<int, memory::sse>{
        typedef __m128i trait_register_type;
    };

    template<>
    struct register_trait<float, memory::sse>{
        typedef __m128 trait_register_type;
    };

    template<>
    struct register_trait<double, memory::sse>{
        typedef __m128d trait_register_type;
    };

#ifdef __AVX__
    template<>
    struct register_trait<int, memory::avx>{
        typedef __m256i trait_register_type;
    };

    template<>
    struct register_trait<float, memory::avx>{
        typedef __m256 trait_register_type;
    };

    template<>
    struct register_trait<double, memory::avx>{
        typedef __m256d trait_register_type;
    };
#endif

    /**
        \brief definition of the type for the trait class, with unroll 4,2 and 1 for double/sse
    */
    template <>
    struct simd_trait<double, memory::sse, 4> : trait<double>{
        typedef simd_unroll<double, memory::sse, 4> register_type;
    };

    template <>
    struct simd_trait<double, memory::sse, 2> : trait<double>{
        typedef simd_unroll<double,  memory::sse, 2> register_type;
    };

    template <>
    struct simd_trait<double, memory::sse, 1> : trait<double>{
        typedef __m128d register_type;
    };

    /**
        \brief definition of the type for the trait class, with unroll 4,2 and 1 for float/sse
    */
    template <>
    struct simd_trait<float, memory::sse, 4> : trait<float>{
        typedef simd_unroll<float, memory::sse, 4> register_type;
    };

    template <>
    struct simd_trait<float, memory::sse, 2> : trait<float>{
        typedef simd_unroll<float,  memory::sse, 2> register_type;
    };

    template <>
    struct simd_trait<float, memory::sse, 1> : trait<float>{
        typedef __m128 register_type;
    };

    /**
    \brief definition of the type for the trait class, with unroll 4,2 and 1 for int/sse
    */
    template <>
    struct simd_trait<int, memory::sse, 4> : trait<int>{
        typedef simd_unroll<int, memory::sse, 4> register_type;
    };

    template <>
    struct simd_trait<int, memory::sse, 2> : trait<int>{
        typedef simd_unroll<int,  memory::sse, 2> register_type;
    };

    template <>
    struct simd_trait<int, memory::sse, 1> : trait<int>{
        typedef __m128i register_type;
    };

    /**
     \brief Specialization trait for float  Newton-Raphson division
     */
    template<>
    struct div_recursion<float, memory::sse>{
        static const std::size_t value = 1; // cardinal([0-1])=2
    };

    template<>
    struct div_recursion<float, memory::avx>{
        static const std::size_t value = 1; // cardinal([0-1])=2
    };

    /**
     \brief Specialization trait for double  Newton-Raphson division
     */
    template<>
    struct div_recursion<double, memory::sse>{
        static const std::size_t value = 2; // card([0-2])=3, should be 3
    };

    template<>
    struct div_recursion<double, memory::avx>{
        static const std::size_t value = 2; // card([0-2])=3, should be 3
    };
    
    
    /**
     \brief Specialization trait for float  Newton-Raphson square root 
     */
    template<>
    struct sqrt_recursion<float, memory::sse>{
        static const std::size_t value = 1; // cardinal([0-1])=2
    };
    
    template<>
    struct sqrt_recursion<float, memory::avx>{
        static const std::size_t value = 1; // cardinal([0-1])=2
    };
    
    /**
     \brief Specialization trait for double  Newton-Raphson square root 
     */
    template<>
    struct sqrt_recursion<double, memory::sse>{
        static const std::size_t value = 2; // card([0-2])=3, should be 3
    };
    
    template<>
    struct sqrt_recursion<double, memory::avx>{
        static const std::size_t value = 2; // card([0-2])=3, should be 3
    };

    
#ifdef __AVX__
    /**
        \brief definition of the type for the trait class, with unroll 4,2 and 1 for double/sse
    */
    template <>
    struct simd_trait<double, memory::avx, 4> : trait<double>{
        typedef simd_unroll<double, memory::avx, 4> register_type;
    };

    template <>
    struct simd_trait<double, memory::avx, 2> : trait<double>{
        typedef simd_unroll<double,  memory::avx, 2> register_type;
    };

    template <>
    struct simd_trait<double, memory::avx, 1> : trait<double>{
        typedef __m256d register_type;
    };

    /**
        \brief definition of the type for the trait class, with unroll 4,2 and 1 for float/avx
    */
    template <>
    struct simd_trait<float, memory::avx, 4> : trait<float>{
        typedef simd_unroll<float, memory::avx, 4> register_type;
    };

    template <>
    struct simd_trait<float, memory::avx, 2> : trait<float>{
        typedef simd_unroll<float,  memory::avx, 2> register_type;
    };

    template <>
    struct simd_trait<float, memory::avx, 1> : trait<float>{
        typedef __m256 register_type;
    };

    /**
        \brief definition of the type for the trait class, with unroll 4,2 and 1 for int/avx
    */

    template <>
    struct simd_trait<int, memory::avx, 4> : trait<int>{
        typedef simd_unroll<int, memory::avx, 4> register_type;
    };

    template <>
    struct simd_trait<int, memory::avx, 2> : trait<int>{
        typedef simd_unroll<int,  memory::avx, 2> register_type;
    };

    template <>
    struct simd_trait<int, memory::avx, 1> : trait<int>{
        typedef __m256i register_type;
    };
#endif
    /** \endcond I do not need this part in the doc */
}
#endif
