/*
 * Cyme - simd_fms.hpp, Copyright (c), 2014,
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

#ifndef CYME_SIMD_FMS_HPP
#define CYME_SIMD_FMS_HPP

namespace numeric{
    /**
    \brief free function FMS between 3 vectors, only a*b - c, - is not commutative
    */
    template<class T,memory::simd O, int N>
    forceinline vec_simd<T,O,N> mulsub(const vec_simd<T,O,N>& lhs, const vec_simd<T,O,N>& mhs, const vec_simd<T,O,N>& rhs){
        vec_simd<T,O,N> nrv(lhs);
        nrv.ms(mhs,rhs);
        return nrv;
    }

    /**
     \brief free function nFMA 
     */
    template<class T,memory::simd O, int N>
    forceinline vec_simd<T,O,N> negatemulsub(const vec_simd<T,O,N>& lhs, const vec_simd<T,O,N>& mhs, const vec_simd<T,O,N>& rhs){
        vec_simd<T,O,N> nrv(lhs);
        nrv.nms(mhs,rhs);
        return nrv;
    }
} //end namespace

#endif

