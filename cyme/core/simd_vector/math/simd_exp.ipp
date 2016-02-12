/*
 * Cyme - simd_exp.hpp, Copyright (c), 2014,
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
 * @file cyme/core/simd_vector/math/simd_exp.ipp
 * Implements exp for vec_simd class
 */

#ifndef CYME_SIMD_EXP_IPP
#define CYME_SIMD_EXP_IPP

#include <limits>
#include "cyme/core/simd_vector/math/detail/horner.ipp"
#include "cyme/core/simd_vector/math/detail/coeff_exp.ipp"

namespace cyme{

    /** Function object that compute the Remez approximation of e^x using Horner method */
    template<class T, cyme::simd O, int N,std::size_t n>
    struct Remez_exp{
        static forceinline vec_simd<T,O,N> exp(vec_simd<T,O,N> const& a){
            return helper_horner<T,O,N,coeff_remez_exp,n>::horner(a);
        }
    };

    /** range for the exp, exponent*log(2) **/
    template<class T>
    struct exp_limits{};

    template<>
    struct exp_limits<double>{
        static inline  double max_range()  { return 709.089565713;}
    };

    template<>
    struct exp_limits<float>{
        static inline  float max_range() { return 88.0296919311;}
    };

    /** Implementation of the exp,the algorithm is based on e^x = 2^k e^y

         where k is signed integer and y belongs to [0,log 2].
         e^y is determined using a Pade approximation of the order n with an third value program.
         The algo does:
         \code{.cpp}
                x = y + k*log(2)
                x/log(2) = y/log(2) + k
                floor(x/log(2)) =floor(y/log(2)) + floor(k)
                floor(x/log(2)) = k
         \endcode
         We get k so easy y.  e^y simply calculates with the approximation
         2^k use the internal representation of the floating point number

        working range:
            x > exp_limits<T>::exp_limits() : +inf
            x < exp_limits<T>::exp_limits() : -inf
            x == 0                          : 1.0
            x == NaN                        : NaN
     */
    template<class T, cyme::simd O, int N,std::size_t n = poly_order<T,coeff_remez_exp>::value,
             class Solver = Remez_exp<T,O,N,n> > // Remez, series ...
    struct cyme_exp{
        static forceinline vec_simd<T,O,N> exp(vec_simd<T,O,N> x){
            vec_simd<T,O,N> mask0(~(fabs(x) > vec_simd<T,O,N>(exp_limits<T>::max_range()))); // mask for the boundary
            vec_simd<T,O,N> mask1(x < vec_simd<T,O,N>(exp_limits<T>::max_range()));  // mask for the boundary
            vec_simd<T,O,N> mask2(std::numeric_limits<T>::infinity());

            /* calculate k,  k = (int)floor(a); p = (float)k; */
            vec_simd<T,O,N>   log2e(1.4426950408889634073599);
            vec_simd<T,O,N>   y(x*log2e);
            vec_simd<int,O,N> k = floor(y); // k int
            vec_simd<T,O,N>   p(cast<T,O>(k)); // k float

            /* x -= p * log2; */
            vec_simd<T,O,N> c1(6.93145751953125E-1);
            vec_simd<T,O,N> c2(1.42860682030941723212E-6);
#ifdef __FMA__
            x = negatemuladd(p,c1,x);
            x = negatemuladd(p,c2,x);
#else
            x -= p*c1;
            x -= p*c2; // this corection I do not know ><
#endif
            /* Compute e^x using a polynomial approximation, remez order 9 by default */
            x = Solver::exp(x);
            /* p = 2^k; */
            p = twok<T,O,N>(k);
            /* e^x = 2^k * e^y */
            x *= p;
            x &= mask0; // lower than -max_range becomes 0
            mask2 &= ~mask1; // larger than max_range becomes +inf, step1
            x |= mask2;  // larger than max_range becomes +inf, step2
            return x;
        }
    };

    /** Free function for call the vendor exp */
    template<class T,cyme::simd O, int N>
    forceinline vec_simd<T,O,N> exp_v(const vec_simd<T,O,N>& rhs){
        vec_simd<T,O,N> nrv(_mm_exp<T,O,N>(rhs.xmm));
        return nrv;
    }

    /** Function object for the vendor exp algorithm */
    template<class T, cyme::simd O, int N, std::size_t n>
    struct Vendor_exp{
        static forceinline vec_simd<T,O,N> exp(vec_simd<T,O,N> const& a){
            return exp_v(a); /* call vendor wrapper */
        }
    };

    /** Selector for the exp algorithm (vendor or cyme implementation) */
    template<class T, cyme::simd O, int N, std::size_t n = poly_order<T,coeff_remez_exp>::value,
             class Solver = cyme_exp<T,O,N,n> > // cyme_exp ou vendor
    struct Selector_exp{
         static forceinline vec_simd<T,O,N> exp(vec_simd<T,O,N> x){
               x = Solver::exp(x);
               return x;
         }
    };

    /** free function for the exp */
    template<class T,cyme::simd O, int N>
    forceinline vec_simd<T,O,N> exp(const vec_simd<T,O,N>& rhs){
        return Selector_exp<T,O,N>::exp(rhs);
    }

    /** Implementation of the function 2^x

	  Uses previous function for calculating exp(x), or e^x, using exponential
	  function identities.
         \code{.cpp}
                a^k = e^r

                where:
                r = ln(a^k)
                r = k*ln(a)

                so for a = 2:
                a^k = e^(k*CONSTANT)
         \endcode
    */
    template<class T,cyme::simd O, int N>
    forceinline vec_simd<T,O,N> exp2(const vec_simd<T,O,N>& rhs){
	vec_simd<T,O,N>   ln2(0.6931471805599453094172);
	return exp(rhs*ln2);
    }

    /** Implementation of the function 10^x

         Uses previous function for calculating exp(x), or e^x, using exponential
         function identities.
         \code{.cpp}
                a^k = e^r

                where:
                r = ln(a^k)
                r = k*ln(a)

                so for a = 10:
                a^k = e^(k*CONSTANT)
         \endcode
    */
    template<class T,cyme::simd O, int N>
    forceinline vec_simd<T,O,N> exp10(const vec_simd<T,O,N>& rhs){
	vec_simd<T,O,N>   ln10(2.3025850929940456840179);
        return exp(rhs*ln10);
    }
}
#endif

