/*
* Cyme - trait_mic.ipp, Copyright (c), 2014,
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

#ifndef CYME_TRAIT_MIC_IPP
#define CYME_TRAIT_MIC_IPP

#include <immintrin.h> //for rcp

namespace numeric{
    /** \cond I do not need this part in the doc
        \brief Specialization trait for float with MIC SIMD 
    */
    template<>
    struct register_trait<float, memory::mic>{
        typedef __m512 trait_register_type;
    };

    /**
        \brief Specialization trait for double with MIC SIMD
    */
    template<>
    struct register_trait<double, memory::mic>{
        typedef __m512d trait_register_type;
    };

    template<>
    struct register_trait<int, memory::mic>{
        typedef __m512i trait_register_type;
    };

    /**
        \brief definition of the type for the trait class, with unroll 4,2 and 1 for double/sse
    */
    template <>
    struct simd_trait<double, memory::mic, 4> : trait<double>{
        typedef simd_unroll<double, memory::mic, 4> register_type;
    };

    template <>
    struct simd_trait<double, memory::mic, 2> : trait<double>{
        typedef simd_unroll<double,  memory::mic, 2> register_type;
    };

    template <>
    struct simd_trait<double, memory::mic, 1> : trait<double>{
        typedef __m512d register_type;
    };

    /**
        \brief definition of the type for the trait class, with unroll 4,2 and 1 for double/sse
    */
    template <>
    struct simd_trait<float, memory::mic, 4> : trait<float>{
        typedef simd_unroll<float,memory::mic, 4> register_type;
    };

    template <>
    struct simd_trait<float, memory::mic, 2> : trait<float>{
        typedef simd_unroll<float,memory::mic, 2> register_type;
    };

    template <>
    struct simd_trait<float, memory::mic, 1> : trait<float>{
        typedef __m512 register_type;
    };

    /**
        \brief definition of the type for the trait class, with unroll 4,2 and 1 for double/sse
    */
    template <>
    struct simd_trait<int, memory::mic, 4> : trait<int>{
        typedef simd_unroll<int,memory::mic, 4> register_type;
    };

    template <>
    struct simd_trait<int, memory::mic, 2> : trait<int>{
        typedef simd_unroll<int,memory::mic, 2> register_type;
    };

    template <>
    struct simd_trait<int, memory::mic, 1> : trait<int>{
        typedef __m512i register_type;
    };
    /**
     \brief Specialization trait for float  Newton-Raphson division
     */
    template<>
    struct div_recursion<float, memory::mic>{
        static const std::size_t value = 1; // cardinal([0-1])=2
    };

    /**
     \brief Specialization trait for double  Newton-Raphson division
     */
    template<>
    struct div_recursion<double, memory::mic>{
        static const std::size_t value = 3; // card([0-2])=3, should be 3
    };
}
#endif
