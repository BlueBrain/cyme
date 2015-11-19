/*
 * Cyme - P6.ipp, Copyright (c), 2014,
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
 * @file cyme/core/simd_vector/math/detail/method/coefficients/P6.ipp
 * Provide the coefficients for all the polynomial of degree 6, exp only
 */

#ifndef POLY_P6_IPP
#define POLY_P6_IPP

namespace poly{

    template<class T,int n>
    struct coeffP6{
    };

    template<class T>
    struct coeffP6<T,0>{
         const static inline T coefficient() {return 1;}
    };

    template<class T>
    struct coeffP6<T,1>{
         const static inline T coefficient() {return 1.196842960540944e+00;}
    };

    template<class T>
    struct coeffP6<T,2>{
         const static inline T coefficient() {return 6.678244594777292e-01;}
    };

    template<class T>
    struct coeffP6<T,3>{
         const static inline T coefficient() {return 2.243525483119196e-01;}
    };

    template<class T>
    struct coeffP6<T,4>{
         const static inline T coefficient() {return 4.846362961615892e-02;}
    };

    template<class T>
    struct coeffP6<T,5>{
         const static inline T coefficient() {return 6.505325568828364e-03;}
    };

    template<class T>
    struct coeffP6<T,6>{
         const static inline T coefficient() {return 4.379922390875640e-04;}
    };
}

#endif
