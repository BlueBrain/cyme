/*
 * Cyme - simd_math.hpp, Copyright (c), 2014,
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

#ifndef CYME_SIMD_MATH_HPP
#define CYME_SIMD_MATH_HPP
// C - order mater !
    #include "cyme/core/simd_vector/math/simd_neg.hpp" 
    #include "cyme/core/simd_vector/math/simd_recsqrt.hpp"
    #include "cyme/core/simd_vector/math/simd_rec.hpp"
    #include "cyme/core/simd_vector/math/simd_div.hpp"
    #include "cyme/core/simd_vector/math/simd_add.hpp"
    #include "cyme/core/simd_vector/math/simd_sub.hpp"
    #include "cyme/core/simd_vector/math/simd_mul.hpp"
    #include "cyme/core/simd_vector/math/simd_exp.hpp"
    #include "cyme/core/simd_vector/math/simd_log.hpp"
    #include "cyme/core/simd_vector/math/simd_sqrt.hpp"
    #include "cyme/core/simd_vector/math/simd_pow.hpp"
#ifdef __FMA__
    #include "cyme/core/simd_vector/math/simd_fma.hpp"
    #include "cyme/core/simd_vector/math/simd_fms.hpp"
#endif

#endif
