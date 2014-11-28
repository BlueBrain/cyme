/*
 * Cyme - simd_exp.hpp, Copyright (c), 2014,
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

#ifndef CYME_SIMD_EXP_IPP
#define CYME_SIMD_EXP_IPP

#include "cyme/core/simd_vector/math/detail/remez.ipp"

namespace numeric{

    /**
     \cond
     */
    template<class T, memory::simd O, int N,std::size_t n>
    struct Remez_exp{
        static forceinline vec_simd<T,O,N> exp(vec_simd<T,O,N> const& a){
            return helper_horner<T,O,N,coeff_remez_exp,n>::horner(a);
        }
    };
    /**
     \endcond
     */

    /** \brief implementation of the exp,the algorithm is based on e^x = 2^k e^y, where k is signed integer and y belongs to [0,log 2].
               e^y is determined using a Pade approximation of the order n with an third value program.
               The algo does:
                    x = y + k*log(2)
                    x/log(2) = y/log(2) + k
                    floor(x/log(2)) =floor(y/log(2)) + floor(k)
                    floor(x/log(2)) = k

               We get k so easy y.

               e^y simply calculates with the approximation
               2^k use the internal representation of the floating point number
    */

    template<class T, memory::simd O, int N,std::size_t n = poly_order<T,coeff_remez_exp>::value, class Solver = Remez_exp<T,O,N,n> > // Remez, series ...
    struct my_exp{
        static forceinline vec_simd<T,O,N> exp(vec_simd<T,O,N> x){
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
            return x;
        }
    };

    /**
    \brief free function for call the vendor exponential, this function uses the return value optimization
    */
    template<class T,memory::simd O, int N>
    forceinline vec_simd<T,O,N> exp_v(const vec_simd<T,O,N>& rhs){
        vec_simd<T,O,N> nrv(_mm_exp<T,O,N>(rhs.xmm));
        return nrv;
    }

    /**
     \brief function object for the vendor exponential algorithm
     */
    template<class T, memory::simd O, int N, std::size_t n>
    struct Vendor_exp{
        static forceinline vec_simd<T,O,N> exp(vec_simd<T,O,N> const& a){
            return exp_v(a); /* call vendor wrapper */
        }
    };

    /**
     \brief selector for the exponential algorithm (vendor or my implementation)
     */
    template<class T, memory::simd O, int N, std::size_t n = poly_order<T,coeff_remez_exp>::value, class Solver = my_exp<T,O,N,n> > // my_exp ou vendor
    struct Selector_exp{
         static forceinline vec_simd<T,O,N> exp(vec_simd<T,O,N> x){
               x = Solver::exp(x);
               return x;
         }
    };

    /**
        \brief free function for the  exp
    */
    template<class T,memory::simd O, int N>
    forceinline vec_simd<T,O,N> exp(const vec_simd<T,O,N>& rhs){
        return Selector_exp<T,O,N>::exp(rhs);
    }
}
#endif

