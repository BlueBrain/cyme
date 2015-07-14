/*
 * Cyme - simd_sin.hpp, Copyright (c), 2015,
 * Timothee Ewart - Swiss Federal Institute of technology in Lausanne,
 * timothee.ewart@epfl.ch,
 * kai.langen@usask.ca,
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
 * @file cyme/core/simd_vector/math/simd_sin.ipp
 * Implements sin for vec_simd class
 */

#ifndef CYME_SIMD_SIN_IPP
#define CYME_SIMD_SIN_IPP

//#include "cyme/core/simd_vector/math/detail/sin_helper.ipp"
#include <assert.h>
namespace cyme{

    /** Sin helper to compute magic pass*/
    template<class T, cyme::simd O, int N,std::size_t n>
    struct Sin_helper{
        static forceinline vec_simd<T,O,N> exp(vec_simd<T,O,N> const& a){
            //return helper_horner<T,O,N,coeff_remez_exp,n>::horner(a);
	    assert(false);
        }
    };

    /** Base struct*/
    template<class T, cyme::simd O, int N, int p, std::size_t n>
    struct Poly_helper;

   
    /** Helper for polynom where 0 <= x <= Pi/4 (sin_lo)*/
    template<class T, cyme::simd O, int N, std::size_t n>
    struct Poly_helper<T,O,N,0,n>{
	static forceinline vec_simd<T,O,N> poly(vec_simd<T,O,N> x){
	    vec_simd<T,O,N> neg(-1);
	    return x*neg;
	}
    };
 
    /** Helper for polynom where Pi/4 <= x <= Pi/2 (sin_hi)*/ 
    template<class T, cyme::simd O, int N, std::size_t n>
    struct Poly_helper<T,O,N,1,n>{
	static forceinline vec_simd<T,O,N> poly(vec_simd<T,O,N> x){
	    vec_simd<T,O,N> pos(1);
	    return x*pos;
	}
    };

    /** Selector for the polynomial algorithm (sin_hi or sin_lo) */
    template<class T, cyme::simd O, int N, int p, std::size_t n = poly_order<T,coeff_remez_exp>::value,//coeff_sin_cos
	    class Solver = Poly_helper<T,O,N,p,n> > //sin_hi or sin_lo
    struct Selector_poly{
        static forceinline vec_simd<T,O,N> poly(vec_simd<T,O,N> x){
	    x = Solver::poly(x);
	    return x;
	}
    };

    /** free function for sin */ 
    template<class T,cyme::simd O, int N>
    forceinline vec_simd<T,O,N> sin(const vec_simd<T,O,N>& rhs){
#define POLY 0
	//get sign
	//take abs value
	//magic pass (call sin_helper)
	//Call Selector_Poly::poly(x) 
	//assert(false);
	vec_simd<T,O,N> result = Selector_poly<T,O,N,POLY>::poly(rhs);
#undef POLY
	return result;
    }
}
#endif
