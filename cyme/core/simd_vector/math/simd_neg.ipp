/*
 * Cyme - simd_neg.ipp, Copyright (c), 2014,
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
 * @file cyme/core/simd_vector/math/simd_neg.ipp
 * Implements negate operator for vec_simd class
 */

#ifndef CYME_SIMD_NEG_IPP
#define CYME_SIMD_NEG_IPP

namespace cyme {

/** Implements negate operator for cyme::vec_simd */
template <class T, cyme::simd O, int N>
forceinline vec_simd<T, O, N> neg(vec_simd<T, O, N> const &rhs) {
    vec_simd<T, O, N> nrv(rhs);
    nrv.neg();
    return nrv;
}
}
#endif
