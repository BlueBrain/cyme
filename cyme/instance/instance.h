/*
 * Cyme - instance.h, Copyright (c), 2014,
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

#ifndef CYME_INSTANCE_H
#define CYME_INSTANCE_H


#if defined ( __SSE__) ||  (__AVX__)
   #define  __SIMD_VALUE__ sse
#endif

#ifdef _ARCH_QP
   #define  __SIMD_VALUE__ qpx
#endif

    /*
    \brief Construction of the serial exponential, 32-bit precision. Ths single function load/unload 
    a serial number only.
    */
    inline float sexp(float a){
        float res __attribute__((aligned (32)));
        numeric::vec_simd<float, memory::__SIMD_VALUE__, 1> v;
        v.single(a);
        v = exp(v);
        v.single(&res);
        return res; 
    }

    /*
    \brief Construction of the serial logarithm, 32-bit precision. Ths single function load/unload 
    a serial number only.
    */
    inline float slog(float a){
        float res __attribute__((aligned (32)));
        numeric::vec_simd<float, memory::__SIMD_VALUE__, 1> v;
        v.single(a);
        v = log(v);
        v.single(&res);
        return res; 
    }

    /*
    \brief Construction of the serial square root, 32-bit precision. Ths single function load/unload 
    a serial number only.
    */
    inline float ssqrt(float a){
        float res __attribute__((aligned (32)));
        numeric::vec_simd<float, memory::__SIMD_VALUE__, 1> v;
        v.single(a);
        v = sqrt(v);
        v.single(&res);
        return res; 
    }
    
    /*
    \brief Construction of the serial exponential, 64-bit precision. Ths single function load/unload 
    a serial number only.
    */
    inline double sexp(double a){
        double res __attribute__((aligned (32)));
        numeric::vec_simd<double, memory::__SIMD_VALUE__, 1> v;
        v.single(a);
        v = exp(v);
        v.single(&res);
        return res; 
    }
   
    /*
    \brief Construction of the serial logarithm, 64-bit precision. Ths single function load/unload 
    a serial number only.
    */
    inline double slog(double a){
        double res __attribute__((aligned (32)));
        numeric::vec_simd<double, memory::__SIMD_VALUE__, 1> v;
        v.single(a);
        v = log(v);
        v.single(&res);
        return res; 
    }
   
    /*
    \brief Construction of the serial square root, 64-bit precision. Ths single function load/unload 
    a serial number only.
    */
    inline double ssqrt(double a){
        double res __attribute__((aligned (32)));
        numeric::vec_simd<double, memory::__SIMD_VALUE__, 1> v;
        v.single(a);
        v = sqrt(v);
        v.single(&res);
        return res; 
    }

    extern "C"{
        float cyme_fexp(float a){return sexp(a);} 
        float cyme_flog(float a){return slog(a);} 
        float cyme_fsqrt(float a){return ssqrt(a);} 
    
        double cyme_exp(double a){return sexp(a);} 
        double cyme_log(double a){return slog(a);} 
        double cyme_sqrt(double a){return ssqrt(a);} 
    }

#endif
