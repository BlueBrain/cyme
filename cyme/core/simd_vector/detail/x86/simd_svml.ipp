/*
 * Cyme - simd_svml.h, Copyright (c), 2014,
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
 * @file cyme/core/simd_vector/detail/x86/simd_svml.ipp
 * Declaration of the Intel SVML function "C" siganture
 */

#ifndef CYME_SIMD_SVML_IPP
#define CYME_SIMD_SVML_IPP

#ifndef __PPC64__
#ifndef _ARCH_QP
#ifdef __AVX__
extern "C"{
    __m128 __svml_expf4(__m128);
    __m128 __svml_logf4(__m128);

    __m128d __svml_exp2(__m128d);
    __m128d __svml_log2(__m128d);

    __m256 __svml_expf8(__m256);
    __m256 __svml_logf8(__m256);

    __m256d __svml_exp4(__m256d);
    __m256d __svml_log4(__m256d);
}
#else
extern "C"{
    __m128 __svml_expf4(__m128);
    __m128 __svml_logf4(__m128);

    __m128d __svml_exp2(__m128d);
    __m128d __svml_log2(__m128d);
}
#endif
#endif
#endif

#endif
