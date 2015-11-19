/*
 * Cyme - P4.ipp, Copyright (c), 2014,
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
 * @file cyme/core/simd_vector/math/detail/method/coefficients/P4.ipp
 * Provide the coefficients for all the polynomial of degree 4, exp only
 */

#ifndef POLY_P4_IPP
#define POLY_P4_IPP

namespace poly{
    /* from P4P2P2P2 */
    template<class T,int n>
    struct coeffP4_1{
    };

    template<class T>
    struct coeffP4_1<T,0>{
         const static inline T coefficient() {return 1;}
    };

    template<class T>
    struct coeffP4_1<T,1>{
         const static inline T coefficient() {return 1.011402197010057e+00;}
    };

    template<class T>
    struct coeffP4_1<T,2>{
         const static inline T coefficient() {return   4.196979297477210e-01;}
    };

    template<class T>
    struct coeffP4_1<T,3>{
         const static inline T coefficient() {return 8.526146340318508e-02;}
    };

    template<class T>
    struct coeffP4_1<T,4>{
         const static inline T coefficient() {return  7.231015227626321e-03;}
    };

    /* from P4P4P2 */
    template<class T,int n>
    struct coeffP4_2{
    };

    template<class T>
    struct coeffP4_2<T,0>{
         const static inline T coefficient() {return 1;}
    };

    template<class T>
    struct coeffP4_2<T,1>{
         const static inline T coefficient() {return 1.523296196377193e-01;}
    };

    template<class T>
    struct coeffP4_2<T,2>{
         const static inline T coefficient() {return 9.477617470208738e-02;}
    };

    template<class T>
    struct coeffP4_2<T,3>{
         const static inline T coefficient() {return 5.476020783630308e-03;}
    };

    template<class T>
    struct coeffP4_2<T,4>{
         const static inline T coefficient() {return 2.443750257044438e-03;}
    };

    /* from P6P4 */
    template<class T,int n>
    struct coeffP4_3{
    };

    template<class T>
    struct coeffP4_3<T,0>{
         const static inline T coefficient() {return 1;}
    };

    template<class T>
    struct coeffP4_3<T,1>{
         const static inline T coefficient() {return -1.968429605410215e-01;}
    };

    template<class T>
    struct coeffP4_3<T,2>{
         const static inline T coefficient() {return  6.776565218253636e-02;}
    };

    template<class T>
    struct coeffP4_3<T,3>{
         const static inline T coefficient() {return -7.334181810914540e-03;}
    };

    template<class T>
    struct coeffP4_3<T,4>{
         const static inline T coefficient() {return  8.875620032394859e-04;}
    };
}

#endif
