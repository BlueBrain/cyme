/*
 * Cyme - simd_math.ipp, Copyright (c), 2014,
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
 * @file cyme/core/simd_vector/simd_math.ipp
 * Defines "include" order for the mathematical operators and functions
 */

#ifndef CYME_SIMD_MATH_IPP
#define CYME_SIMD_MATH_IPP
    #include "cyme/core/simd_vector/math/simd_neg.ipp"
    #include "cyme/core/simd_vector/math/simd_recsqrt.ipp"
    #include "cyme/core/simd_vector/math/simd_rec.ipp"
    #include "cyme/core/simd_vector/math/simd_div.ipp"
    #include "cyme/core/simd_vector/math/simd_add.ipp"
    #include "cyme/core/simd_vector/math/simd_sub.ipp"
    #include "cyme/core/simd_vector/math/simd_mul.ipp"
    #include "cyme/core/simd_vector/math/simd_exp.ipp"
    #include "cyme/core/simd_vector/math/simd_log.ipp"
    #include "cyme/core/simd_vector/math/simd_sqrt.ipp"
    #include "cyme/core/simd_vector/math/simd_pow.ipp"
    #include "cyme/core/simd_vector/math/simd_sin.ipp"
#ifdef __FMA__
    #include "cyme/core/simd_vector/math/simd_fma.ipp"
    #include "cyme/core/simd_vector/math/simd_fms.ipp"
#endif

#endif
