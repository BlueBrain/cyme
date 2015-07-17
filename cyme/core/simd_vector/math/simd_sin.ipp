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

#include "cyme/core/simd_vector/math/detail/sin_helper.ipp"
#include <assert.h>
namespace cyme{
    /** Base struct*/
    template<class T, cyme::simd O, int N, int p, std::size_t n>
    struct Poly_helper;

    /** Helper for polynom where 0 <= x <= Pi/4 (sin_lo)*/
    template<class T, cyme::simd O, int N, std::size_t n>
    struct Poly_helper<T,O,N,0,n>{
	static forceinline vec_simd<T,O,N> poly(vec_simd<T,O,N> x){
	    vec_simd<T,O,N> z(x*x);
	    vec_simd<T,O,N> y = helper_sin<T,O,N,coeff_cephes_cos,n>::poly_sin(z);
	    y *= z;
	    y -= (z*vec_simd<T,O,N>(0.5));
	    y += vec_simd<T,O,N>(1);
	    return y;
	}
    };
 
    /** Helper for polynom where Pi/4 <= x <= Pi/2 (sin_hi)*/ 
    template<class T, cyme::simd O, int N, std::size_t n>
    struct Poly_helper<T,O,N,1,n>{
	static forceinline vec_simd<T,O,N> poly(vec_simd<T,O,N> x){
	    vec_simd<T,O,N> z(x*x);
	    vec_simd<T,O,N> y = helper_sin<T,O,N,coeff_cephes_sin,n>::poly_sin(z);
	    y *= x;
	    y += x;
	    return y;
	}
    };

    /** Selector for the polynomial algorithm (sin_hi or sin_lo) */
    template<class T, cyme::simd O, int N, int p, std::size_t n = poly_order<T,coeff_cephes_sin>::value,//coeff_sin_cos
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
	//constants
	const vec_simd<T,O,N> cephes_FOPI(1.27323954473516); // 4/PI

	//get sign
	//create function

	//take abs value
	vec_simd<T,O,N> x = abs(rhs);

	//modify y
	vec_simd<T,O,N> y = x*cephes_FOPI;
	const vec_simd<int,O,N> j = floor(y);//+vec_simd<T,O,N>(1.0));
	//j += vec_simd<int,O,N>(1);
	vec_simd<T,O,N>   p(cast<T,O>(j)); // j float
	//j &= (~1)

	//get swap sign flag
	//magic pass
	/*x = ((x - y * DP1) - y * DP2) - y * DP3; */
 	vec_simd<T,O,N> neg_DP1(-0.78515625);
 	vec_simd<T,O,N> neg_DP2(-2.4187564849853515625e-4);
 	vec_simd<T,O,N> neg_DP3(-3.77489497744594108e-8);
 	neg_DP1 *= p;
 	neg_DP2 *= p;
 	neg_DP3 *= p;
 	x += neg_DP1;
 	x += neg_DP2;
 	x += neg_DP3;

	//Call Selector_Poly::poly(x) 
 	vec_simd<T,O,N> poly1 = Selector_poly<T,O,N,0>::poly(x);
 	vec_simd<T,O,N> poly2 = Selector_poly<T,O,N,1>::poly(x);
	return select_poly(j,poly1,poly2);
    }
}
#endif
