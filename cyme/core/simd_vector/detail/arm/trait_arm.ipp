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

    /** Specialisation of the trait class for int, cyme::arm  */
    template <>
    struct register_trait<int, cyme::arm>{
    };

    /** Specialisation of the trait class for float, cyme::arm  */
    template <>
    struct register_trait<float,cyme::arm>{
    };

    /** Specialisation of the trait class for double, cyme::arm  */
    template <>
    struct register_trait<double,cyme::arm>{
    };

    /** Specialisation of the trait class for the composite vector int,cyme::arm,4 regs*/
    template <>
    struct simd_trait<int, cyme::arm, 4> : trait<int>{
    };

    /** Specialisation of the trait class for the composite vector int,cyme::arm,2 regs*/
    template <>
    struct simd_trait<int, cyme::arm, 2> : trait<int>{
    };

    /** Specialisation of the trait class for the composite vector int,cyme::arm,1 reg*/
    template <>
    struct simd_trait<int, cyme::arm, 1> : trait<int>{
    };

    /** Specialisation of the trait class for the composite vector double,cyme::arm,4 regs*/
    template <>
    struct simd_trait<double, cyme::arm, 4> : trait<double>{
    };

    /** Specialisation of the trait class for the composite vector double,cyme::arm,2 regs*/
    template <>
    struct simd_trait<double, cyme::arm, 2> : trait<double>{
    };

    /** Specialisation of the trait class for the composite vector double,cyme::arm,1 reg*/
    template <>
    struct simd_trait<double, cyme::arm, 1> : trait<double>{
    };

    /** Specialisation of the trait class for the composite vector float,cyme::arm,4 regs*/
    template <>
    struct simd_trait<float, cyme::arm, 4> : trait<float>{
    };

    /** Specialisation of the trait class for the composite vector float,cyme::arm,2 regs*/
    template <>
    struct simd_trait<float, cyme::arm, 2> : trait<float>{
    };

    /** Specialisation of the trait class for the composite vector float,cyme::arm,1 regs*/
    template <>
    struct simd_trait<float, cyme::arm, 1> : trait<float>{
    };

    /** Specialization trait for float  Newton-Raphson division: number of iteration */
    template<>
    struct div_recursion<float, cyme::arm>{
    };

    /** Specialization trait for float Newton-Raphson sqrt: number of iteration */
    template<>
    struct sqrt_recursion<float, cyme::arm>{
    };

    /** Specialization trait for float  Newton-Raphson division: number of iteration */
    template<>
    struct div_recursion<double, cyme::arm>{
    };

    /** Specialization trait for float Newton-Raphson sqrt: number of iteration */
    template<>
    struct sqrt_recursion<double, cyme::arm>{
    };
}
#endif //CYME_TRAIT_ARM_IPP
