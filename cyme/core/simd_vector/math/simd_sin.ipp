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

#include "cyme/core/simd_vector/math/detail/horner.ipp"
#include "cyme/core/simd_vector/math/detail/coeff_sin_cos.ipp"

namespace cyme{
    /** Base struct*/
    template<class T, cyme::simd O, int N, template <typename,std::size_t> class C>
    struct Poly_helper;

    /** Helper for polynom where 0 <= x <= Pi/4 (sin_lo)*/
    template<class T, cyme::simd O, int N>
    struct Poly_helper<T,O,N,coeff_cephes_cos>{
	static forceinline vec_simd<T,O,N> poly(vec_simd<T,O,N> x){
	    vec_simd<T,O,N> z(x*x);
	    vec_simd<T,O,N> y = helper_horner<T,O,N,coeff_cephes_cos,
					      poly_order<T,coeff_cephes_cos>::value>::horner(z);
	    y *= z;
	    y -= (z*vec_simd<T,O,N>(0.5));
	    y += vec_simd<T,O,N>(1);
	    return y;
	}
    };
 
    /** Helper for polynom where Pi/4 <= x <= Pi/2 (sin_hi)*/ 
    template<class T, cyme::simd O, int N>
    struct Poly_helper<T,O,N,coeff_cephes_sin>{
	static forceinline vec_simd<T,O,N> poly(vec_simd<T,O,N> x){
	    vec_simd<T,O,N> z(x*x);
	    vec_simd<T,O,N> y = helper_horner<T,O,N,coeff_cephes_sin,
					      poly_order<T,coeff_cephes_sin>::value>::horner(z);
	    y *= x;
	    y += x;
	    return y;
	}
    };

    /** Selector for the polynomial algorithm (sin_hi or sin_lo) */
/*    template<class T, cyme::simd O, int N, int p, std::size_t n = poly_order<T,coeff_cephes_sin>::value,//coeff_sin_cos
	    class Solver = Poly_helper<T,O,N,p,n> > //sin_hi or sin_lo
    struct Selector_poly{
        static forceinline vec_simd<T,O,N> poly(vec_simd<T,O,N> x){
	    x = Solver::poly(x);
	    return x;
	}
    };
*/
    /** free function for sin 
    Used references:
    (http://github.com/jeremybarnes/cephes)
    (http://gruntthepeon.free.fr/ssemath/sse_mathfun.h)
    */
    template<class T,cyme::simd O, int N>
    forceinline vec_simd<T,O,N> sin(const vec_simd<T,O,N>& rhs){
	//constants
	const vec_simd<T,O,N> cephes_FOPI(1.27323954473516); // 4/PI

	//take abs value
	vec_simd<T,O,N> x = abs(rhs);

	//create values p and j
	vec_simd<T,O,N> y = x*cephes_FOPI;
	const vec_simd<int,O,N> j = floor(y);// + vec_simd<T,O,N>(1.0));
	vec_simd<T,O,N> p(cast<T,O,N>(j)); // j float

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

	//Select Polynomial
 	vec_simd<T,O,N> poly1 = Poly_helper<T,O,N,coeff_cephes_cos>::poly(x);
 	vec_simd<T,O,N> poly2 = Poly_helper<T,O,N,coeff_cephes_sin>::poly(x);
	x = select_poly(j,poly1,poly2);
	//Select Sign
	return select_sign(j,rhs,x);
    }
}
#endif
