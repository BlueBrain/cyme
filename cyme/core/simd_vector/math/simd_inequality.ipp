
/*
 * Cyme - simd_inequality.ipp, Copyright (c), 2015,
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
 * @file cyme/core/simd_vector/math/simd_inequality.ipp
 * Implements  several inequalities (and equality) for vec_simd class
 */

#ifndef SIMD_INEQUALITY_IPP
#define SIMD_INEQUALITY_IPP

namespace cyme{

    /* create a new vector that contains the results of the quality == */
    template<class T,cyme::simd O, int N>
    vec_simd<T,O,N> operator== (const vec_simd<T,O,N>& lhs, const vec_simd<T,O,N>& rhs){
        vec_simd<T,O,N> nrv(_mm_eq<T,O,N>(lhs.xmm,rhs.xmm));
        return nrv;
    }

    /* create a new vector that contains the results of the inequality < */
    template<class T,cyme::simd O, int N>
    vec_simd<T,O,N> operator< (const vec_simd<T,O,N>& lhs, const vec_simd<T,O,N>& rhs){
        vec_simd<T,O,N> nrv(_mm_lt<T,O,N>(lhs.xmm,rhs.xmm));
        return nrv;
    }

    /* create a new vector that contains the results of the inequality > */
    template<class T,cyme::simd O, int N>
    vec_simd<T,O,N> operator> (const vec_simd<T,O,N>& lhs, const vec_simd<T,O,N>& rhs){
        vec_simd<T,O,N> nrv(_mm_gt<T,O,N>(lhs.xmm,rhs.xmm));
        return nrv;
    }

}

#endif

