/*
* Cyme - trait_powerpc64.ipp, Copyright (c), 2014,
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

#ifndef CYME_TRAIT_POWERPC64_IPP
#define CYME_TRAIT_POWERPC64_IPP

namespace numeric{

    template<class T, memory::simd O>
    struct register_trait;
    /** \cond I do not need this part in the doc
        \brief Specialization trait for int with QPX
              QPX does not support int they are store into double ....
    */
    template <>
    struct register_trait<int, memory::qpx>{
        typedef vector4double trait_register_type;
    };

    /** \cond I do not need this part in the doc
        \brief Specialization trait for float with QPX
    */
    template <>
    struct register_trait<float,memory::qpx>{
        typedef vector4double trait_register_type;
    };

    /**
        \brief Specialization trait for double with QPX
    */
    template <>
    struct register_trait<double,memory::qpx>{
        typedef vector4double trait_register_type;
    };
    /* \endcond I do not need this part in the doc*/

    /**
        \brief definition of the type for the trait class, with unroll 4,2 and 1 for double/vector4double
    */
    template <>
    struct simd_trait<int, memory::qpx, 4> : trait<int>{
        typedef simd_unroll<double, memory::qpx, 4> register_type;
    };

    template <>
    struct simd_trait<int, memory::qpx, 2> : trait<int>{
        typedef simd_unroll<double,  memory::qpx, 2> register_type;
    };

    template <>
    struct simd_trait<int, memory::qpx, 1> : trait<int>{
        typedef vector4double register_type;
    };


    /**
        \brief definition of the type for the trait class, with unroll 4,2 and 1 for double/vector4double
    */
    template <>
    struct simd_trait<double, memory::qpx, 4> : trait<double>{
        typedef simd_unroll<double, memory::qpx, 4> register_type;
    };

    template <>
    struct simd_trait<double, memory::qpx, 2> : trait<double>{
        typedef simd_unroll<double ,  memory::qpx, 2> register_type;
    };

    template <>
    struct simd_trait<double, memory::qpx, 1> : trait<double>{
        typedef vector4double register_type;
    };


    /**
        \brief definition of the type for the trait class, with unroll 4,2 and 1 for float/vector4double
    */
    template <>
    struct simd_trait<float, memory::qpx, 4> : trait<float>{
        typedef simd_unroll<double, memory::qpx, 4> register_type;
    };

    template <>
    struct simd_trait<float, memory::qpx, 2> : trait<float>{
        typedef simd_unroll<double,  memory::qpx, 2> register_type;
    };

    template <>
    struct simd_trait<float, memory::qpx, 1> : trait<float>{
        typedef vector4double register_type;
    };

    /**
     \brief Specialization trait for float  Newton-Raphson division and square root 
     */
    template<>
    struct div_recursion<float, memory::qpx>{
        static const std::size_t value = 3; // cardinal([0-2])=3
    };

    template<>
    struct sqrt_recursion<float, memory::qpx>{
        static const std::size_t value = 3; // cardinal([0-2])=3
    };

    
    /**
     \brief Specialization trait for double  Newton-Raphson division and square root
     */
    template<>
    struct div_recursion<double, memory::qpx>{
        static const std::size_t value = 4; // card([0-3])=4
    };

    template<>
    struct sqrt_recursion<double, memory::qpx>{
        static const std::size_t value = 4; // card([0-3])=4
    };
    
}
#endif
