/*
 * Cyme - simd_recsqrt.hpp, Copyright (c), 2014,
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

#ifndef CYME_SIMD_RSQRT_IPP
#define CYME_SIMD_RSQRT_IPP

namespace numeric{
    /**
    \brief free function for call the reciprocal for the Newton-Raphson square root (initialization only), this function uses the return value optimization
    */
    template<class T,memory::simd O, int N>
    forceinline vec_simd<T,O,N> recsqrt(vec_simd<T,O,N> const& rhs){
        vec_simd<T,O,N> nrv;
        nrv.xmm = _mm_rsqrt<T,O,N>(rhs.xmm);
        return nrv;
    }
} //end namespace

#endif

