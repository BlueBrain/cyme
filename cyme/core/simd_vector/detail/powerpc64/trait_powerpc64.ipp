/*
* Cyme - trait_powerpc64.ipp, Copyright (c), 2014,
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
 * @file cyme/core/simd_vector/detail/powerpc64/trait_powerpc64.ipp
 * Specialisation of the register_trait, simd_trait, Newton-Raphson
 * classes for the powerA2 architecture
 */

#ifndef CYME_TRAIT_POWERPC64_IPP
#define CYME_TRAIT_POWERPC64_IPP

#ifdef __PPC64__
#include <altivec.h>
#endif

namespace cyme{

    /** trait class that defined the hardware register
    \warning Specialization trait for int with QPX QPX does not support int they are store into double
     */
    template<class T, cyme::simd O>
    struct register_trait;
    
#ifdef __PPC64__
    /** Specialisation of the trait class for int, cyme::qpx  */
    template <>
    struct register_trait<int, cyme::qpx>{
        typedef vector double trait_register_type;
    };

    /** Specialisation of the trait class for float, cyme::qpx  */
    template <>
    struct register_trait<float,cyme::qpx>{
        typedef vector double trait_register_type;
    };

    /** Specialisation of the trait class for double, cyme::qpx  */
    template <>
    struct register_trait<double,cyme::qpx>{
        typedef vector double trait_register_type;
    };
#endif

#ifdef _ARCH_QP
    /** Specialisation of the trait class for int, cyme::qpx  */
    template <>
    struct register_trait<int, cyme::qpx>{
        typedef vector4double trait_register_type;
    };

    /** Specialisation of the trait class for float, cyme::qpx  */
    template <>
    struct register_trait<float,cyme::qpx>{
        typedef vector4double trait_register_type;
    };

    /** Specialisation of the trait class for double, cyme::qpx  */
    template <>
    struct register_trait<double,cyme::qpx>{
        typedef vector4double trait_register_type;
    };
#endif
    
#ifdef __PPC64__
#endif
    
#ifdef _ARCH_QP
    /** Specialisation of the trait class for the composite vector int,cyme::qpx,4 regs*/
    template <>
    struct simd_trait<int, cyme::qpx, 4> : trait<int>{
        typedef simd_unroll<double, cyme::qpx, 4> register_type;
    };

    /** Specialisation of the trait class for the composite vector int,cyme::qpx,2 regs*/
    template <>
    struct simd_trait<int, cyme::qpx, 2> : trait<int>{
        typedef simd_unroll<double,  cyme::qpx, 2> register_type;
    };

    /** Specialisation of the trait class for the composite vector int,cyme::qpx,1 reg*/
    template <>
    struct simd_trait<int, cyme::qpx, 1> : trait<int>{
        typedef vector4double register_type;
    /** Specialisation of the trait class for the composite vector double,cyme::qpx,4 regs*/
    template <>
    struct simd_trait<double, cyme::qpx, 4> : trait<double>{
        typedef simd_unroll<double, cyme::qpx, 4> register_type;
    };

    /** Specialisation of the trait class for the composite vector double,cyme::qpx,2 regs*/
    template <>
    struct simd_trait<double, cyme::qpx, 2> : trait<double>{
        typedef simd_unroll<double ,  cyme::qpx, 2> register_type;
    };

    /** Specialisation of the trait class for the composite vector double,cyme::qpx,1 reg*/
    template <>
    struct simd_trait<double, cyme::qpx, 1> : trait<double>{
        typedef vector4double register_type;
    };

    /** Specialisation of the trait class for the composite vector float,cyme::qpx,4 regs*/
    template <>
    struct simd_trait<float, cyme::qpx, 4> : trait<float>{
        typedef simd_unroll<double, cyme::qpx, 4> register_type;
    };

    /** Specialisation of the trait class for the composite vector float,cyme::qpx,2 regs*/
    template <>
    struct simd_trait<float, cyme::qpx, 2> : trait<float>{
        typedef simd_unroll<double,  cyme::qpx, 2> register_type;
    };

    /** Specialisation of the trait class for the composite vector float,cyme::qpx,1 regs*/
    template <>
    struct simd_trait<float, cyme::qpx, 1> : trait<float>{
        typedef vector4double register_type;
    };

    /** Specialization trait for float  Newton-Raphson division: number of iteration */
    template<>
    struct div_recursion<float, cyme::qpx>{
        static const std::size_t value = 3; // cardinal([0-2])=3
    };

    /** Specialization trait for float Newton-Raphson sqrt: number of iteration */
    template<>
    struct sqrt_recursion<float, cyme::qpx>{
        static const std::size_t value = 3; // cardinal([0-2])=3
    };

    /** Specialization trait for float  Newton-Raphson division: number of iteration */
    template<>
    struct div_recursion<double, cyme::qpx>{
        static const std::size_t value = 4; // card([0-3])=4
    };

    /** Specialization trait for float Newton-Raphson sqrt: number of iteration */
    template<>
    struct sqrt_recursion<double, cyme::qpx>{
        static const std::size_t value = 4; // card([0-3])=4
    };

}
#endif //CYME_TRAIT_POWERPC64_IPP
