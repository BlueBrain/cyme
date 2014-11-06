/*
 * Cyme - simd.h, Copyright (c), 2014,
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

#ifndef CYME_SIMD_H
#define CYME_SIMD_H

namespace memory{
    struct unroll_factor{
        const static int N = __CYME_UNROLL_VALUE__ ;
    };

    /** \cond I do not need this part in the doc*/
    enum simd{sse, avx, qpx, mic}; 
    enum order{AoS, AoSoA};

    #define __GETSIMD__() __CYME_SIMD_VALUE__


    template<class T, memory::simd O>
    struct trait_register;

    /*
        size = size of the datas (byte) that can fit into the register, WARNING it is not NECESSARILY equal to the size of the register e.g. BG/q float
        a = needed alignement
    */

    template<class T>
    struct trait_register<T,sse>{
        const static size_t size=16;
        const static size_t a=16;
    };

    template<class T>
    struct trait_register<T,avx>{
        const static size_t size=32;
        const static size_t a=32;
    };

    template<class T>
    struct trait_register<T,mic>{
        const static size_t size=64;
        const static size_t a=64;
    };

    template<>
    struct trait_register<float,qpx>{
        const static size_t size=16; // 16 / sizeof(T) = 4 BG/Q does not support native 8 floats
        const static size_t a=32; // align 32 byte on BG/Q EVEN for float
    };

    template<class T>
    struct trait_register<T,qpx>{
        const static size_t size=32;
        const static size_t a=32;
    };


    template<class T, order O>
    struct stride;

    // just stride using meta-function
    template<class T>
    struct stride<T,AoS>{
        static inline std::size_t helper_stride(){return 1;}
    };

    template<class T>
    struct stride<T,AoSoA>{
        static inline std::size_t helper_stride(){return  unroll_factor::N*trait_register<T,__GETSIMD__()>::size/sizeof(T);}
    };
    /** \endcond I do not need this part in the doc*/

} //end namespace


#endif
