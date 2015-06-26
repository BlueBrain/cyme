/*
 * Cyme - simd.hpp, Copyright (c), 2014,
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
* @file cyme/memory/detail/simd.hpp
* Defines simd properties of target machine.
*/

#ifndef CYME_SIMD_HPP
#define CYME_SIMD_HPP


/** Generic cyme interfaces and implementations.
    The namespace contains two components.
    First "the core" inside the core directory. It contains the generic
    simd vector with backend and the "template expression" engine.
    Second "the memory" inside the memory directory. It contains the
    cyme container.
 */
namespace cyme{

/**  Number of simd registers contained in the composite vector.
*
*  This class is used to define the number of simd registers to be put in a
*  composite vector. __CYME_UNROLL_VALUE__ is a macro passed to the compiler
*  automatically by CMake.
*
*/
    struct unroll_factor{
        const static int N = __CYME_UNROLL_VALUE__ ;
    };

/**   Simd technology type.
*
*  cyme::simd defines the simd technology for which the cyme code will be
*  compiled. This is automatically detected by CMake at compile time.
*/
    enum simd{sse, avx, neon, vmx, qpx, mic};

/**   Memory layout of composite vector.
*
*  cyme::order defines the memory layout for the data encapsulated by the
*  composite vector. AoS (Array of Structures) corresponds to serial layout,
*  whereas AoSoA (Array of Structures of Arrays) corresponds to packed simd
*  layout.
*/
    enum order{AoS, AoSoA};

    #define __GETSIMD__() __CYME_SIMD_VALUE__

/** Size of simd registers and memory alignment.
*
*  cyme::trait_register::size defines the size (in bytes) of the simd registers
*  of the target machine.
*  cyme::trait_register::a defines the memory alignment boundary (in bytes).
*
*  \warning cyme::trait_register::a is not NECESSARILY equal to the size of
*  the register.
*
*  For example, float variables on BG/q are aligned on 32 byte boundaries
*  even though their registers are 16 byte wide.
*
*/
    template<class T, cyme::simd O>
    struct trait_register;

/** Partial specialisation for sse technology.  */
    template<class T>
    struct trait_register<T,cyme::sse>{
        const static size_t size=16;
        const static size_t a=16;
    };

/** Partial specialisation for arm technology. */
    template<class T>
    struct trait_register<T,cyme::neon>{
	/*Filler for now. Will replace with actual ARM values*/
        const static size_t size=16;
        const static size_t a=16;
    };

/** Partial specialisation for vmx technology. */
    template<class T>
    struct trait_register<T,cyme::vmx>{
        const static size_t size=16;
        const static size_t a=16;
    };

/** Partial specialisation for avx technology.  */
    template<class T>
    struct trait_register<T,cyme::avx>{
        const static size_t size=32;
        const static size_t a=32;
    };

/** Partial specialisation for intel mic.  */
    template<class T>
    struct trait_register<T,cyme::mic>{
        const static size_t size=64;
        const static size_t a=64;
    };

/**  Partial specialisation for qpx technology.
*
*  \warning cyme::trait_register::a is not NECESSARILY equal to the size of
*  the register.
*
*  BG/Q does not support native 8 floats registers, so the memory must be
*  aligned on 32 byte boundaries on even for floats
*/
    template<>
    struct trait_register<float,cyme::qpx>{
        const static size_t size=16;
        const static size_t a=32;
    };

/** Partial specialisation for qpx technology.  */
    template<class T>
    struct trait_register<T,cyme::qpx>{
        const static size_t size=32;
        const static size_t a=32;
    };

/** stride length for the asssociated iterator.
*
*   cyme::stride defines the length of the step to reach the next element of a
*   structure inside a composite vector, as explained in the \ref tuto2 section.
*/
    template<class T, order O>
    struct stride;

/** Partial specialisation for AoS layout.  */
    template<class T>
    struct stride<T,cyme::AoS>{
        static inline std::size_t helper_stride(){return 1;}
    };

/** Partial specialisation for AoSoA layout.  */
    template<class T>
    struct stride<T,cyme::AoSoA>{
        static inline std::size_t helper_stride(){return unroll_factor::N*trait_register<T,__GETSIMD__()>::size/sizeof(T);}
    };

} //end namespace

#endif
