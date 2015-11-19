/*
 * Cyme - P8.ipp, Copyright (c), 2014,
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
 * @file cyme/core/simd_vector/math/detail/method/coefficients/P8.ipp
 * Provide the coefficients for all the polynomial of degree 8, exp only
 */

#ifndef POLY_P8_IPP
#define POLY_P8_IPP

namespace poly{

    template<class T,int n>
    struct coeffP8{
    };

    template<class T>
    struct coeffP8<T,0>{
         static inline T coefficient() {return 1;}
    };

    template<class T>
    struct coeffP8<T,1>{
         static inline T coefficient() {return 1.163731816647776e+00;}
    };

    template<class T>
    struct coeffP8<T,2>{
         static inline T coefficient() {return  6.685406164211041e-01;}
    };

    template<class T>
    struct coeffP8<T,3>{
         static inline T coefficient() {return 2.505267415059241e-01;}
    };

    template<class T>
    struct coeffP8<T,4>{
         static inline T coefficient() {return 6.797843553794408e-02;}
    };

    template<class T>
    struct coeffP8<T,5>{
         static inline T coefficient() {return 1.395214211513854e-02;}
    };

    template<class T>
    struct coeffP8<T,6>{
         static inline T coefficient() {return 2.177858431827554e-03;}
    };

    template<class T>
    struct coeffP8<T,7>{
         static inline T coefficient() {return 2.479549127807474e-04;}
    };

    template<class T>
    struct coeffP8<T,8>{
         static inline T coefficient() {return 1.767079532120407e-05;}
    };
}

#endif
