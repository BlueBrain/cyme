/*
* Cyme - trait_arm.ipp, Copyright (c), 2014,
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
 * @file cyme/core/simd_vector/detail/arm/trait_arm.ipp
 * Specialisation of the register_trait, simd_trait, Newton-Raphson
 * classes for the ARM architecture
 */

#ifndef CYME_TRAIT_ARM_IPP
#define CYME_TRAIT_ARM_IPP

namespace cyme{

    /** trait class that defined the hardware register
     */
    template<class T, cyme::simd O>
    struct register_trait;

    /** Specialisation of the trait class for int, cyme::neon  */
    template <>
    struct register_trait<int, cyme::neon>{
	typedef int32x4_t trait_register_type;
    };

    /** Specialisation of the trait class for float, cyme::neon  */
    template <>
    struct register_trait<float,cyme::neon>{
	typedef float32x4_t trait_register_type;
    };

    /** Specialisation of the trait class for double, cyme::neon  */
    template <>
    struct register_trait<double,cyme::neon>{
	typedef float64x2_t trait_register_type;
    };

    /** Specialisation of the trait class for the composite vector int,cyme::neon,4 regs*/
    template <>
    struct simd_trait<int, cyme::neon, 4> : trait<int>{
        typedef simd_unroll<int, cyme::neon, 4> register_type;
    };

    /** Specialisation of the trait class for the composite vector int,cyme::neon,2 regs*/
    template <>
    struct simd_trait<int, cyme::neon, 2> : trait<int>{
        typedef simd_unroll<int, cyme::neon, 2> register_type;
    };

    /** Specialisation of the trait class for the composite vector int,cyme::neon,1 reg*/
    template <>
    struct simd_trait<int, cyme::neon, 1> : trait<int>{
	typedef int32x4_t register_type;
    };

    /** Specialisation of the trait class for the composite vector double,cyme::neon,4 regs*/
    template <>
    struct simd_trait<double, cyme::neon, 4> : trait<double>{
	typedef simd_unroll<double, cyme::neon, 4> register_type;
    };

    /** Specialisation of the trait class for the composite vector double,cyme::neon,2 regs*/
    template <>
    struct simd_trait<double, cyme::neon, 2> : trait<double>{
	typedef simd_unroll<double, cyme::neon, 2> register_type;
    };

    /** Specialisation of the trait class for the composite vector double,cyme::neon,1 reg*/
    template <>
    struct simd_trait<double, cyme::neon, 1> : trait<double>{
	typedef float64x2_t register_type;
    };

    /** Specialisation of the trait class for the composite vector float,cyme::neon,4 regs*/
    template <>
    struct simd_trait<float, cyme::neon, 4> : trait<float>{
	typedef simd_unroll<float, cyme::neon, 4> register_type;	
    };

    /** Specialisation of the trait class for the composite vector float,cyme::neon,2 regs*/
    template <>
    struct simd_trait<float, cyme::neon, 2> : trait<float>{
	typedef simd_unroll<float, cyme::neon, 2> register_type;
    };

    /** Specialisation of the trait class for the composite vector float,cyme::neon,1 regs*/
    template <>
    struct simd_trait<float, cyme::neon, 1> : trait<float>{
	typedef float32x4_t register_type;
    };

    /** Specialization trait for float  Newton-Raphson division: number of iteration */
    template<>
    struct div_recursion<float, cyme::neon>{
        static const std::size_t value = 3; // cardinal([0-2])=3
    };

    /** Specialization trait for float Newton-Raphson sqrt: number of iteration */
    template<>
    struct sqrt_recursion<float, cyme::neon>{
        static const std::size_t value = 3; // cardinal([0-2])=3
    };

    /** Specialization trait for float  Newton-Raphson division: number of iteration */
    template<>
    struct div_recursion<double, cyme::neon>{
        static const std::size_t value = 4; // cardinal([0-3])=4
    };

    /** Specialization trait for float Newton-Raphson sqrt: number of iteration */
    template<>
    struct sqrt_recursion<double, cyme::neon>{
        static const std::size_t value = 4; // cardinal([0-3])=4
    };
}
#endif //CYME_TRAIT_ARM_IPP
