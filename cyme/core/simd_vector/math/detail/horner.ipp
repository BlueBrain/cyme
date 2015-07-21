/*
 * Cyme - horner.ipp, Copyright (c), 2014,
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
 * @file cyme/core/simd_vector/math/detail/horner.ipp
 * Implements polynomial computation using horner's method
 */

#ifndef CYME_HORNER_IPP
#define CYME_HORNER_IPP

namespace cyme{

    /** Implementation of a polynomial computation using Horner's method

    (http://en.wikipedia.org/wiki/Horner's_method)
     The template parameter C represents the coefficients described (log or exp coeff). This function is called
     into simd_log.hpp or simd_exp.log with the needed coefficient.
     */
    template<class T, cyme::simd O, int N, template <typename,std::size_t> class C, std::size_t n>
    struct helper_horner{
        static forceinline vec_simd<T,O,N> horner(vec_simd<T,O,N> const& a){
#ifdef __FMA__
            return muladd(helper_horner<T,O,N,C,n-1>::horner(a),a,vec_simd<T,O,N>(C<T,poly_order<T,C>::value-n>::coeff()));
#else
            return vec_simd<T,O,N>(C<T,poly_order<T,C>::value-n>::coeff()) + helper_horner<T,O,N,C,n-1>::horner(a)*a;
#endif
        }
    };

    /** Implementation of the polynomial computation recursive template, final specialization */
    template<class T, cyme::simd O, int N, template <typename,std::size_t> class C>
    struct helper_horner<T,O,N,C,0>{
        static forceinline vec_simd<T,O,N> horner(vec_simd<T,O,N> const&){
            return vec_simd<T,O,N>(C<T,poly_order<T,C>::value>::coeff());
        }
    };

} //end namespace

#endif
