/*
 * Cyme - P2.ipp, Copyright (c), 2014,
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
 * @file cyme/core/simd_vector/math/detail/method/coefficients/P2.ipp
 * Provide the coefficients for all the quadratics, exp only
 */

#ifndef POLY_P2_IPP
#define POLY_P2_IPP

namespace poly{

    template<class T, int n>
    struct coeffP2_1;

    template<class T, int n>
    struct coeffP2_2;

    template<class T, int n>
    struct coeffP2_3;

    template<class T, int n>
    struct coeffP2_4;

    template<class T, int n>
    struct coeffP2_5;

    /* P1 */
    template<class T>
    struct coeffP2_1<T,0>{
         const static inline T coefficient() {return 1.000000000000000e00;}
    };

    template<class T>
    struct coeffP2_1<T,1>{
         const static inline T coefficient() {return 5.863999468698624e-01;}
    };

    template<class T>
    struct coeffP2_1<T,2>{
         const static inline T coefficient() {return 9.111669706698734e-02;}
    };

    /* P2 */
    template<class T>
    struct coeffP2_2<T,0>{
         const static inline T coefficient() {return 1.000000000000000e00;}
    };

    template<class T>
    struct coeffP2_2<T,1>{
         const static inline T coefficient() {return 4.250022501401942e-01;}
    };

    template<class T>
    struct coeffP2_2<T,2>{
         const static inline T coefficient() {return 7.935993577895180e-02;}
    };

    /* P3 */
    template<class T>
    struct coeffP2_3<T,0>{
         const static inline T coefficient() {return 1.000000000000000e00;}
    };

    template<class T>
    struct coeffP2_3<T,1>{
         const static inline T coefficient() {return 1.854407635308873e-01;}
    };

    template<class T>
    struct coeffP2_3<T,2>{
         const static inline T coefficient() {return 6.057133407964636e-02;}
    };

    /* P4 */
    template<class T>
    struct coeffP2_4<T,0>{
         const static inline T coefficient() {return 1.000000000000000e00;}
    };

    template<class T>
    struct coeffP2_4<T,1>{
         const static inline T coefficient() {return -3.311114389316798e-02;}
    };

    template<class T>
    struct coeffP2_4<T,2>{
         const static inline T coefficient() {return 4.034499642737116e-02;}
    };

    /* P5 */
    template<class T>
    struct coeffP2_5<T,0>{
         const static inline T coefficient() {return 1.000000000000000e00;}
    };

    template<class T>
    struct coeffP2_5<T,1>{
         const static inline T coefficient() {return -1.637318166478535e-01;}
    };

    template<class T>
    struct coeffP2_5<T,2>{
         const static inline T coefficient() {return 2.199930801424831e-02;}
    };
}
#endif
