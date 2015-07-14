/*
 * Cyme - math.h, Copyright (c), 2014,
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
 * @file cyme/math/math.h
 * Implement the cyme serial math library
 *
 * This file (cyme.h) exposed signature for serial use library C-only. cyme.h
 * contains everything, specially perform computation with the cyme container.
 */


#ifndef CYME_MATH_H
#define CYME_MATH_H

#ifdef __cplusplus

#ifdef __aarch64__
#  define  __SIMD_VALUE__ neon
#endif

#if defined (__SSE__) || (__AVX__)
#  define  __SIMD_VALUE__ sse
#endif

#if !defined(_ARCH_QP) && defined(__PPC64__)
#  define  __SIMD_VALUE__ vmx
#endif

#ifdef _ARCH_QP
#  define  __SIMD_VALUE__ qpx
#endif


//this file is used for c++ only not install for the library
namespace cyme {
/** Construction of the serial exponential, 32-bit precision.

   The single function load/unload a serial number only.
*/
inline float sexp(float a){
    float res __attribute__((aligned (32)));
    cyme::vec_simd<float, cyme::__SIMD_VALUE__, 1> v;
    v.single(a);
    v = exp(v);
    v.single(&res);
    return res;
}

/** Construction of the serial 2^x, 32-bit precision.

   The single function load/unload a serial number only.
*/
inline float sexp2(float a){
    float res __attribute__((aligned (32)));
    cyme::vec_simd<float, cyme::__SIMD_VALUE__, 1> v;
    v.single(a);
    v = exp2(v);
    v.single(&res);
    return res;
}

/** Construction of the serial 10^x, 32-bit precision.

   The single function load/unload a serial number only.
*/
inline float sexp10(float a){
    float res __attribute__((aligned (32)));
    cyme::vec_simd<float, cyme::__SIMD_VALUE__, 1> v;
    v.single(a);
    v = exp10(v);
    v.single(&res);
    return res;
}

/**  Construction of the serial logarithm, 32-bit precision.

  The single function load/unload a serial number only.
*/
inline float slog(float a){
    float res __attribute__((aligned (32)));
    cyme::vec_simd<float, cyme::__SIMD_VALUE__, 1> v;
    v.single(a);
    v = log(v);
    v.single(&res);
    return res;
}

/**  Construction of the serial logarithm base 2, 32-bit precision.

  The single function load/unload a serial number only.
*/
inline float slog2(float a){
    float res __attribute__((aligned (32)));
    cyme::vec_simd<float, cyme::__SIMD_VALUE__, 1> v;
    v.single(a);
    v = log2(v);
    v.single(&res);
    return res;
}

/**  Construction of the serial logarithm base 10, 32-bit precision.

  The single function load/unload a serial number only.
*/
inline float slog10(float a){
    float res __attribute__((aligned (32)));
    cyme::vec_simd<float, cyme::__SIMD_VALUE__, 1> v;
    v.single(a);
    v = log10(v);
    v.single(&res);
    return res;
}

/** Construction of the serial square root, 32-bit precision.

  The single function load/unload a serial number only.
*/
inline float ssqrt(float a){
    float res __attribute__((aligned (32)));
    cyme::vec_simd<float, cyme::__SIMD_VALUE__, 1> v;
    v.single(a);
    v = sqrt(v);
    v.single(&res);
    return res;
}

/** Construction of the serial sin function, 32-bit precision.

  The single function load/unload a serial number only.
*/
inline float ssin(float a){
    float res __attribute__((aligned (32)));
    cyme::vec_simd<float, cyme::__SIMD_VALUE__, 1> v;
    v.single(a);
    v = sin(v);
    v.single(&res);
    return res;
}

/** Construction of the serial exponential, 64-bit precision.

   The single function load/unload a serial number only.
*/
inline double sexp(double a){
    double res __attribute__((aligned (32)));
    cyme::vec_simd<double, cyme::__SIMD_VALUE__, 1> v;
    v.single(a);
    v = exp(v);
    v.single(&res);
    return res;
}

/** Construction of the serial 2^x, 64-bit precision.

   The single function load/unload a serial number only.
*/
inline double sexp2(double a){
    double res __attribute__((aligned (32)));
    cyme::vec_simd<double, cyme::__SIMD_VALUE__, 1> v;
    v.single(a);
    v = exp2(v);
    v.single(&res);
    return res;
}

/** Construction of the serial 10^x, 64-bit precision.

   The single function load/unload a serial number only.
*/
inline double sexp10(double a){
    double res __attribute__((aligned (32)));
    cyme::vec_simd<double, cyme::__SIMD_VALUE__, 1> v;
    v.single(a);
    v = exp10(v);
    v.single(&res);
    return res;
}

/** Construction of the serial logarithm, 64-bit precision.

   The single function load/unload a serial number only.
*/
inline double slog(double a){
    double res __attribute__((aligned (32)));
    cyme::vec_simd<double, cyme::__SIMD_VALUE__, 1> v;
    v.single(a);
    v = log(v);
    v.single(&res);
    return res;
}

/** Construction of the serial logarithm base 2, 64-bit precision.

   The single function load/unload a serial number only.
*/
inline double slog2(double a){
    double res __attribute__((aligned (32)));
    cyme::vec_simd<double, cyme::__SIMD_VALUE__, 1> v;
    v.single(a);
    v = log2(v);
    v.single(&res);
    return res;
}

/** Construction of the serial logarithm base 10, 64-bit precision.

   The single function load/unload a serial number only.
*/
inline double slog10(double a){
    double res __attribute__((aligned (32)));
    cyme::vec_simd<double, cyme::__SIMD_VALUE__, 1> v;
    v.single(a);
    v = log10(v);
    v.single(&res);
    return res;
}

/** Brief Constructon of the serial square root, 64-bit precision.

   The single function load/unload a serial number only.
*/
inline double ssqrt(double a){
    double res __attribute__((aligned (32)));
    cyme::vec_simd<double, cyme::__SIMD_VALUE__, 1> v;
    v.single(a);
    v = sqrt(v);
    v.single(&res);
    return res;
}

/** Brief Constructon of the serial sin function, 64-bit precision.

   The single function load/unload a serial number only.
*/
inline double ssin(double a){
    double res __attribute__((aligned (32)));
    cyme::vec_simd<double, cyme::__SIMD_VALUE__, 1> v;
    v.single(a);
    v = sin(v);
    v.single(&res);
    return res;
}

} // end namespace

#endif


#ifndef __cplusplus
/** single-precision 32-bit serial exponential base e, C library only */
float  cyme_fexp(float a);

/** single-precision 32-bit serial exponential base 2, C library only */
float  cyme_fexp2(float a);

/** single-precision 32-bit serial exponential base 10, C library only */
float  cyme_fexp10(float a);

/** single-precision 32-bit serial logarithm base e, C library only */
float  cyme_flog(float a);

/** single-precision 32-bit serial logarithm base 2, C library only */
float  cyme_flog2(float a);

/** single-precision 32-bit serial logarithm base 10, C library only */
float  cyme_flog10(float a);

/** single-precision 32-bit serial sqrt, C library only */
float  cyme_fsqrt(float a);

/** single-precision 32-bit serial sin function, C library only */
float  cyme_fsin(float a);

/** double-precision 64-bit serial exponential base e, C library only */
double cyme_exp(double a);

/** double-precision 64-bit serial exponential base 2, C library only */
double cyme_exp2(double a);

/** double-precision 64-bit serial exponential base 10, C library only */
double cyme_exp10(double a);

/** double-precision 64-bit serial exponential base e, C library only */
double cyme_log(double a);

/** double-precision 64-bit serial exponential base 2, C library only */
double cyme_log2(double a);

/** double-precision 64-bit serial exponential base 10, C library only */
double cyme_log10(double a);

/** double-precision 64-bit serial sqrt, C library only */
double cyme_sqrt(double a);

/** double-precision 64-bit serial sin function, C library only */
double cyme_sin(double a);

#endif

#endif
