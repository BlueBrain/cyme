/*
 * Cyme - simd_log.ipp, Copyright (c), 2014,
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
 * @file cyme/core/simd_vector/math/simd_log.ipp
 * Implements log for vec_simd class
 */

#ifndef CYME_SIMD_LOG_IPP
#define CYME_SIMD_LOG_IPP

#include <iostream>

namespace cyme{

    /** Function object that compute the Remez approximation of ln(x) using Horner method */
    template<class T, cyme::simd O, int N,std::size_t n>
    struct Remez_log{
        static forceinline vec_simd<T,O,N> log(vec_simd<T,O,N> const& a){
            return helper_horner<T,O,N,coeff_remez_log,n>::horner(a);
        }
    };

    /** Implementation of the logarithm log

    It is built on the binary representation of the float in the machine
    which is x = s*x0*2^n (where s the sign, always +), x0 (fraction) belongs between 1<=x0<2
    and n the exponent (integer). Thus,
         \code{.cpp}
            log2(x) = log2(x0) + log2(2^n)
            log2(x) = log2(x0) + n
            log(x) = log(2)*log2(x)
            log(x) = log(2)*log2(x0) + log(2)*n
            log(x) = log(x0) + log2*n
         \endcode
    x0 and n are determinated by bit tips (manipulating the float representation). log(x0) as the "exponential solver"
    utilizes Remez approximation of log(1+x0) between 0 and 1. Using this tips I avoid rounding error, consenquently
    I must translate my x by -1.
    */
    template<class T, cyme::simd O, int N,std::size_t n = poly_order<T,coeff_remez_log>::value,
             class Solver = Remez_log<T,O,N,n> >
    struct cyme_log{
        static forceinline vec_simd<T,O,N> log(vec_simd<T,O,N> x){
            vec_simd<T,O,N> log2(0.6931471805599453); // note futur: change this we get log10, etc ....
            vec_simd<T,O,N> e = ge(x); // ge = get exponent
            vec_simd<T,O,N> f = gf(x); // gf = get fraction
	    
	    
	    
#ifdef __FMA__
            f-=vec_simd<T,O,N>(1.0); //translate for rounding see comment before
            x = muladd(log2,e,Solver::log(f));
#else
            f-=vec_simd<T,O,N>(1.0);
            x = Solver::log(f)+log2*e;
#endif
            return x;
        }
    };
    
    /** Implementation of the logarithm log2

    It is built on the binary representation of the float in the machine
    which is x = s*x0*2^n (where s the sign, always +), x0 (fraction) belongs between 1<=x0<2
    and n the exponent (integer). Thus,
         \code{.cpp}
            log2(x) = log2(x0) + log2(2^n)
            log2(x) = log2(x0) + n
            log2(x) = log2(e)*ln(x0) + n
         \endcode
    x0 and n are determinated by bit tips (manipulating the float representation). log(x0) as the "exponential solver"
    utilizes Remez approximation of log(1+x0) between 0 and 1. Using this tips I avoid rounding error, consenquently
    I must translate my x by -1.
    */
    template<class T, cyme::simd O, int N,std::size_t n = poly_order<T,coeff_remez_log>::value,
             class Solver = Remez_log<T,O,N,n> >
    struct cyme_log2{
        static forceinline vec_simd<T,O,N> log2(vec_simd<T,O,N> x){
            vec_simd<T,O,N> e = ge(x); // ge = get exponent
            vec_simd<T,O,N> f = gf(x); // gf = get fraction
	    vec_simd<T,O,N> c(1.4426950408889634); //get const value log2(e)
	    
#ifdef __FMA__
	    f-=vec_simd<T,O,N>(1.0); //translate for rounding see comment before
            x = muladd(Solver::log(f), c, e);
#else
            f-=vec_simd<T,O,N>(1.0);
            x = (Solver::log(f))*c + e;
#endif
	    return x;
        }
    };
    
    /** Implementation of the logarithm log10

    It is built on the binary representation of the float in the machine
    which is x = s*x0*2^n (where s the sign, always +), x0 (fraction) belongs between 1<=x0<2
    and n the exponent (integer). Thus,
         \code{.cpp}
            log2(x) = log2(x0) + log2(2^n)
            log2(x) = log2(x0) + n

            log10(x) = log10(2)*log2(x)
            log10(x) = log10(2)*(log2(x0) + n)
            log10(x) = log10(2)*(log2(e)*ln(x0) + n)
            log10(x) = log10(2)*log2(e)*ln(x0) + log10(2)*n
         \endcode
    x0 and n are determinated by bit tips (manipulating the float representation). log(x0) as the "exponential solver"
    utilizes Remez approximation of log(1+x0) between 0 and 1. Using this tips I avoid rounding error, consenquently
    I must translate my x by -1.
    */
   /* template<class T, cyme::simd O, int N,std::size_t n = poly_order<T,coeff_remez_log>::value,
             class Solver = Remez_log<T,O,N,n> >
    struct cyme_log2{
        static forceinline vec_simd<T,O,N> log2(vec_simd<T,O,N> x){
            vec_simd<T,O,N> e = ge(x); // ge = get exponent
            vec_simd<T,O,N> f = gf(x); // gf = get fraction
	    //get const value log2(e)
	    //c = log2(e)
            f-=vec_simd<T,O,N>(1.0); //translate for rounding see comment before
            x = (Solver::log(f))*c + e;
            return x;
        }
    };*/
    
    /** Free function for call the vendor log */
    template<class T,cyme::simd O, int N>
    forceinline vec_simd<T,O,N> log_v(const vec_simd<T,O,N>& rhs){
        vec_simd<T,O,N> nrv(_mm_log<T,O,N>(rhs.xmm));
        return nrv;
    }

    /** Function object for the vendor log algorithm */
    template<class T, cyme::simd O, int N, std::size_t n>
    struct Vendor_log{
        static forceinline vec_simd<T,O,N> log(vec_simd<T,O,N> const& a){
            return log_v(a); /* call vendor wrapper */
        }
    };

    /** Selector for the log algorithm (vendor or cyme implementation) */
    template<class T, cyme::simd O, int N, std::size_t n = poly_order<T,coeff_remez_log>::value,
             class Solver = cyme_log<T,O,N,n> > // cyme_log (to do) ou vendor
    struct Selector_log{
         static forceinline vec_simd<T,O,N> log(vec_simd<T,O,N> x){
               x = Solver::log(x);
               return x;
         }
    };

    /** free function for the log */
    template<class T,cyme::simd O, int N>
    forceinline vec_simd<T,O,N> log(const vec_simd<T,O,N>& rhs){
        return Selector_log<T,O,N>::log(rhs);
    }
    
    
    /** Selector for the log algorithm (vendor or cyme implementation) */
    template<class T, cyme::simd O, int N, std::size_t n = poly_order<T,coeff_remez_log>::value,
             class Solver = cyme_log2<T,O,N,n> > // cyme_log (to do) or vendor
    struct Selector_log2{
         static forceinline vec_simd<T,O,N> log2(vec_simd<T,O,N> x){
               x = Solver::log2(x);
               return x;
         }
    };

    /** free function for the log2 */
    template<class T,cyme::simd O, int N>
    forceinline vec_simd<T,O,N> log2(const vec_simd<T,O,N>& rhs){
        return Selector_log2<T,O,N>::log2(rhs);
    }
}
#endif

