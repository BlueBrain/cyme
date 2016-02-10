/*
* Cyme - simd_wrapper_qpx.ipp, Copyright (c), 2014,
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
* @file cyme/core/simd_vector/detail/powerpc64/simd_wrapper_qpx.ipp
* Final specialisation for math functions and qpx technology
*/
#ifndef CYME_SIMD_WRAPPER_QPX_IPP
#define CYME_SIMD_WRAPPER_QPX_IPP

#include <boost/cstdint.hpp>
#include <assert.h>

extern "C" vector4double expd4(vector4double);// link to the fortran one
extern "C" vector4double logd4(vector4double);// link to the fortran one

namespace cyme{
    /**helper to calculate 2^k because vectorial integer operations are not supported */
    typedef union {
        double d;
        boost::int64_t ll;
    } ieee754;

    /**helper to calculate 2^k because vectorial integer operations are not supported */
    forceinline double uint642dp(boost::uint64_t ll) {
        ieee754 tmp;
        tmp.ll=ll;
        return tmp.d;
    }

    /**
      Rounds xmm0 up to the next even integer.
      Specialisation int, cyme::qpx, 1 reg
    */
    template<>
    forceinline simd_trait<int,cyme::qpx,1>::register_type
    _mm_round_up_even<cyme::qpx,1>( simd_trait<int,cyme::qpx,1>::register_type __attribute__((unused))xmm0){
	int64_t ll;
	for (int i=0; i<4; i++){
	    ll = vec_extract(xmm0,i);
	    ll = ((ll + 1) & ~1);
            xmm0 = vec_insert(ll,xmm0,i);
	}
	return xmm0;
    }

    /**
      Rounds xmm0 up to the next even integer.
      Specialisation int, cyme::qpx, 2 reg
    */
    template<>
    forceinline simd_trait<int,cyme::qpx,2>::register_type
    _mm_round_up_even<cyme::qpx,2>( simd_trait<int,cyme::qpx,2>::register_type __attribute__((unused))xmm0){
	int64_t ll1, ll2;
	for (int i=0; i<4; i++){
	    ll1 = vec_extract(xmm0.r0,i);
	    ll2 = vec_extract(xmm0.r1,i);
	    ll1 = ((ll1 + 1) & ~1);
	    ll2 = ((ll2 + 1) & ~1);
            xmm0.r0 = vec_insert(ll1,xmm0.r0,i);
            xmm0.r1 = vec_insert(ll2,xmm0.r1,i);
	}
        return simd_trait<int,cyme::qpx,2>::register_type(xmm0.r0,xmm0.r1);
    }

    /**
      Rounds xmm0 up to the next even integer.
      Specialisation int, cyme::qpx, 4 reg
    */
    template<>
    forceinline simd_trait<int,cyme::qpx,4>::register_type
    _mm_round_up_even<cyme::qpx,4>( simd_trait<int,cyme::qpx,4>::register_type __attribute__((unused))xmm0){
	int64_t ll1, ll2, ll3, ll4;
	for (int i=0; i<4; i++){
	    ll1 = vec_extract(xmm0.r0,i);
	    ll2 = vec_extract(xmm0.r1,i);
	    ll3 = vec_extract(xmm0.r2,i);
	    ll4 = vec_extract(xmm0.r3,i);
	    ll1 = ((ll1 + 1) & ~1);
	    ll2 = ((ll2 + 1) & ~1);
	    ll3 = ((ll3 + 1) & ~1);
	    ll4 = ((ll4 + 1) & ~1);
            xmm0.r0 = vec_insert(ll1,xmm0.r0,i);
            xmm0.r1 = vec_insert(ll2,xmm0.r1,i);
            xmm0.r2 = vec_insert(ll3,xmm0.r2,i);
            xmm0.r3 = vec_insert(ll4,xmm0.r3,i);
	}
        return simd_trait<int,cyme::qpx,4>::register_type(xmm0.r0,xmm0.r1,
							  xmm0.r2,xmm0.r3);
    }

    /**
       Load a single-precision (32-bit) floating-point element from cyme into lower element of dst.
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,1>::register_type
    _mm_single_load<float,cyme::qpx,1>(const simd_trait<float,cyme::qpx,1>::value_type b){
        return vec_lds(0,(float*)(void*)&b);
    }

    /**
       store a double-precision (32-bit) floating-point element from register lower element to cyme.
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,1>::value_type
    _mm_single_store<float,cyme::qpx,1>(simd_trait<float,cyme::qpx,1>::register_type xmm0,
                                        simd_trait<float,cyme::qpx,1>::pointer b){
        vec_sts(xmm0,0,b);
        return *b;
    }


    /**
      Returns a vector of which the value of each element is set to a.
       specialisation float,cyme::qpx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,1>::register_type
    _mm_load1<float,cyme::qpx,1>(const simd_trait<float,cyme::qpx,1>::value_type& a){
        return vec_splats(a);
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation float,cyme::qpx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,2>::register_type
    _mm_load1<float,cyme::qpx,2>(const simd_trait<float,cyme::qpx,2>::value_type& a){
        return simd_trait<float,cyme::qpx,2>::register_type(vec_splats(a),vec_splats(a));
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation float,cyme::qpx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,4>::register_type
    _mm_load1<float,cyme::qpx,4>(const simd_trait<float,cyme::qpx,4>::value_type& a){
        return simd_trait<float,cyme::qpx,4>::register_type(vec_splats(a),vec_splats(a),
                                                            vec_splats(a),vec_splats(a));
    }

    /**
      Loads a vector from the given cyme address.
       specialisation float,cyme::qpx,1 regs
    */
    template<>
    forceinline simd_trait<float,cyme::qpx,1>::register_type
    _mm_load<float,cyme::qpx,1>(simd_trait<float,cyme::qpx,1>::const_pointer a){
        return vec_lda(0L,(float*)(void*)a); // QPX does not support const keyword ...
    }

    /**
      Loads a vector from the given cyme address.
       specialisation float,cyme::qpx,2 regs
    */
    template<>
    forceinline simd_trait<float,cyme::qpx,2>::register_type
    _mm_load<float,cyme::qpx,2>(simd_trait<float,cyme::qpx,2>::const_pointer a){
        return simd_trait<float,cyme::qpx,2>::register_type(vec_lda(0L,(float*)(void*)a),
                                                            vec_lda(16L,(float*)(void*)a));
    }

    /**
      Loads a vector from the given cyme address.
       specialisation float,cyme::qpx,4 regs
    */
    template<>
    forceinline simd_trait<float,cyme::qpx,4>::register_type
    _mm_load<float,cyme::qpx,4>(simd_trait<float,cyme::qpx,4>::const_pointer a){
        return simd_trait<float,cyme::qpx,4>::register_type(vec_lda(0L,(float*)(void*)a),
                                                            vec_lda(16L,(float*)(void*)a),
                                                            vec_lda(32L,(float*)(void*)a),
                                                            vec_lda(48L,(float*)(void*)a));
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation float,cyme::qpx,1 regs
    */
    template<>
    forceinline void
    _mm_store<float,cyme::qpx,1>(simd_trait<float,cyme::qpx,1>::register_type xmm0,
                                 simd_trait<float,cyme::qpx,1>::pointer a){
        vec_sta(xmm0,0L,a);
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation float,cyme::qpx,2 regs
    */
    template<>
    forceinline void
    _mm_store<float,cyme::qpx,2>(simd_trait<float,cyme::qpx,2>::register_type xmm0,
                                 simd_trait<float,cyme::qpx,2>::pointer a){
        vec_sta(xmm0.r0,0L,a);
        vec_sta(xmm0.r1,16L,a);
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation float,cyme::qpx,4 regs
    */
    template<>
    forceinline void
    _mm_store<float,cyme::qpx,4>(simd_trait<float,cyme::qpx,4>::register_type xmm0,
                                 simd_trait<float,cyme::qpx,4>::pointer a){
        vec_sta(xmm0.r0,0L,a);
        vec_sta(xmm0.r1,16L,a);
        vec_sta(xmm0.r2,32L,a);
        vec_sta(xmm0.r3,48L,a);
    }

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation float,cyme::qpx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,1>::register_type
    _mm_mul<float,cyme::qpx,1>(simd_trait<float,cyme::qpx,1>::register_type xmm0,
                               simd_trait<float,cyme::qpx,1>::register_type xmm1){
        return vec_mul(xmm0, xmm1);
    };

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation float,cyme::qpx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,2>::register_type
    _mm_mul<float,cyme::qpx,2>(simd_trait<float,cyme::qpx,2>::register_type xmm0,
                               simd_trait<float,cyme::qpx,2>::register_type xmm1){
         return simd_trait<float,cyme::qpx,2>::register_type(vec_mul(xmm0.r0,xmm1.r0),
                                                             vec_mul(xmm0.r1,xmm1.r1));
    };

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation float,cyme::qpx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,4>::register_type
    _mm_mul<float,cyme::qpx,4>(simd_trait<float,cyme::qpx,4>::register_type xmm0,
                               simd_trait<float,cyme::qpx,4>::register_type xmm1){
         return simd_trait<float,cyme::qpx,4>::register_type(vec_mul(xmm0.r0,xmm1.r0),
                                                             vec_mul(xmm0.r1,xmm1.r1),
                                                             vec_mul(xmm0.r2,xmm1.r2),
                                                             vec_mul(xmm0.r3,xmm1.r3));
    };

    /**
       Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation float,cyme::qpx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,1>::register_type
    _mm_div<float,cyme::qpx,1>(simd_trait<float,cyme::qpx,1>::register_type xmm0,
                               simd_trait<float,cyme::qpx,1>::register_type xmm1){
        return vec_swdivs(xmm0, xmm1);
    };

    /**
       Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation float,cyme::qpx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,2>::register_type
    _mm_div<float,cyme::qpx,2>(simd_trait<float,cyme::qpx,2>::register_type xmm0,
                               simd_trait<float,cyme::qpx,2>::register_type xmm1){
         return simd_trait<float,cyme::qpx,2>::register_type(vec_swdivs(xmm0.r0,xmm1.r0),
                                                             vec_swdivs(xmm0.r1,xmm1.r1));
    };

    /**
       Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation float,cyme::qpx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,4>::register_type
    _mm_div<float,cyme::qpx,4>(simd_trait<float,cyme::qpx,4>::register_type xmm0,
                               simd_trait<float,cyme::qpx,4>::register_type xmm1){
         return simd_trait<float,cyme::qpx,4>::register_type(vec_swdivs(xmm0.r0,xmm1.r0),
                                                             vec_swdivs(xmm0.r1,xmm1.r1),
                                                             vec_swdivs(xmm0.r2,xmm1.r2),
                                                             vec_swdivs(xmm0.r3,xmm1.r3));
    };

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation float,cyme::qpx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,1>::register_type
    _mm_add<float,cyme::qpx,1>(simd_trait<float,cyme::qpx,1>::register_type xmm0,
                               simd_trait<float,cyme::qpx,1>::register_type xmm1){
        return vec_add(xmm0, xmm1);
    };

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation float,cyme::qpx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,2>::register_type
    _mm_add<float,cyme::qpx,2>(simd_trait<float,cyme::qpx,2>::register_type xmm0,
                               simd_trait<float,cyme::qpx,2>::register_type xmm1){
         return simd_trait<float,cyme::qpx,2>::register_type(vec_add(xmm0.r0,xmm1.r0),
                                                             vec_add(xmm0.r1,xmm1.r1));
    };

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation float,cyme::qpx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,4>::register_type
    _mm_add<float,cyme::qpx,4>(simd_trait<float,cyme::qpx,4>::register_type xmm0,
                               simd_trait<float,cyme::qpx,4>::register_type xmm1){
         return simd_trait<float,cyme::qpx,4>::register_type(vec_add(xmm0.r0,xmm1.r0),
                                                             vec_add(xmm0.r1,xmm1.r1),
                                                             vec_add(xmm0.r2,xmm1.r2),
                                                             vec_add(xmm0.r3,xmm1.r3));
    };

    /**
      Returns a vector containing the result of subtracting each element of b
     from the corresponding element of a.
       specialisation float,cyme::qpx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,1>::register_type
    _mm_sub<float,cyme::qpx,1>(simd_trait<float,cyme::qpx,1>::register_type xmm0,
                               simd_trait<float,cyme::qpx,1>::register_type xmm1){
        return vec_sub(xmm0, xmm1);
    };

    /**
      Returns a vector containing the result of subtracting each element of b
     from the corresponding element of a.
       specialisation float,cyme::qpx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,2>::register_type
    _mm_sub<float,cyme::qpx,2>(simd_trait<float,cyme::qpx,2>::register_type xmm0,
                               simd_trait<float,cyme::qpx,2>::register_type xmm1){
         return simd_trait<float,cyme::qpx,2>::register_type(vec_sub(xmm0.r0,xmm1.r0),
                                                             vec_sub(xmm0.r1,xmm1.r1));
    };

    /**
      Returns a vector containing the result of subtracting each element of b
     from the corresponding element of a.
       specialisation float,cyme::qpx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,4>::register_type
    _mm_sub<float,cyme::qpx,4>(simd_trait<float,cyme::qpx,4>::register_type xmm0,
                               simd_trait<float,cyme::qpx,4>::register_type xmm1){
         return simd_trait<float,cyme::qpx,4>::register_type(vec_sub(xmm0.r0,xmm1.r0),
                                                             vec_sub(xmm0.r1,xmm1.r1),
                                                             vec_sub(xmm0.r2,xmm1.r2),
                                                             vec_sub(xmm0.r3,xmm1.r3));
    };

    /**
      Computes the exponential function of each element of vx.
       specialisation float,cyme::qpx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,1>::register_type
    _mm_exp<float,cyme::qpx,1>(simd_trait<float,cyme::qpx,1>::register_type xmm0){
        return expd4(xmm0);
    };

    /**
      Computes the exponential function of each element of vx.
       specialisation float,cyme::qpx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,2>::register_type
    _mm_exp<float,cyme::qpx,2>(simd_trait<float,cyme::qpx,2>::register_type xmm0){
         return simd_trait<float,cyme::qpx,2>::register_type(expd4(xmm0.r0),
                                                             expd4(xmm0.r1));
    };

    /**
      Computes the exponential function of each element of vx.
       specialisation float,cyme::qpx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,4>::register_type
    _mm_exp<float,cyme::qpx,4>(simd_trait<float,cyme::qpx,4>::register_type xmm0){
         return simd_trait<float,cyme::qpx,4>::register_type(expd4(xmm0.r0),
                                                             expd4(xmm0.r1),
                                                             expd4(xmm0.r2),
                                                             expd4(xmm0.r3));
    };

    /**
      Computes the logarithm function of each element of vx.
       specialisation float,cyme::qpx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,1>::register_type
    _mm_log<float,cyme::qpx,1>(simd_trait<float,cyme::qpx,1>::register_type xmm0){
        return logd4(xmm0);
    };

    /**
      Computes the logarithm function of each element of vx.
       specialisation float,cyme::qpx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,2>::register_type
    _mm_log<float,cyme::qpx,2>(simd_trait<float,cyme::qpx,2>::register_type xmm0){
         return simd_trait<float,cyme::qpx,2>::register_type(logd4(xmm0.r0),
                                                             logd4(xmm0.r1));
    };

    /**
      Computes the logarithm function of each element of vx.
       specialisation float,cyme::qpx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,4>::register_type
    _mm_log<float,cyme::qpx,4>(simd_trait<float,cyme::qpx,4>::register_type xmm0){
         return simd_trait<float,cyme::qpx,4>::register_type(logd4(xmm0.r0),
                                                             logd4(xmm0.r1),
                                                             logd4(xmm0.r2),
                                                             logd4(xmm0.r3));
    };

    /**
      Returns a vector containing estimates of the reciprocals of the corresponding elements of the given vector.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x) / (1/x) | ≤ 1/256
       specialisation float,cyme::qpx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,1>::register_type
    _mm_rec<float,cyme::qpx,1>(simd_trait<float,cyme::qpx,1>::register_type xmm0){
        return vec_re(xmm0);
    };

    /**
      Returns a vector containing estimates of the reciprocals of the corresponding elements of the given vector.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x) / (1/x) | ≤ 1/256
       specialisation float,cyme::qpx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,2>::register_type
    _mm_rec<float,cyme::qpx,2>(simd_trait<float,cyme::qpx,2>::register_type xmm0){
         return simd_trait<float,cyme::qpx,2>::register_type(vec_re(xmm0.r0),
                                                             vec_re(xmm0.r1));
    };

    /**
      Returns a vector containing estimates of the reciprocals of the corresponding elements of the given vector.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x) / (1/x) | ≤ 1/256
       specialisation float,cyme::qpx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,4>::register_type
    _mm_rec<float,cyme::qpx,4>(simd_trait<float,cyme::qpx,4>::register_type xmm0){
         return simd_trait<float,cyme::qpx,4>::register_type(vec_re(xmm0.r0),
                                                             vec_re(xmm0.r1),
                                                             vec_re(xmm0.r2),
                                                             vec_re(xmm0.r3));
    };
    /**
      Compute 1/recsqrt (32-bit) floating point elements in xmm0 to packed double-precision
     (64-bit) floating-point elements, and store the results in dst.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
       of a and r is the value of the corresponding element of the result value:
     | (r-1/x^0.5) / (1/x^0.5) | ≤ 1/256
       specialisation float,cyme::qpx,1 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::qpx,1>::register_type
    _mm_rsqrt<float,cyme::qpx,1>(simd_trait<float,cyme::qpx,1>::register_type xmm0){
        return vec_rsqrte(xmm0);
    }

    /**
      Compute 1/recsqrt (32-bit) floating point elements in xmm0 to packed double-precision
     (64-bit) floating-point elements, and store the results in dst.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
       of a and r is the value of the corresponding element of the result value:
     | (r-1/x^0.5) / (1/x^0.5) | ≤ 1/256
       specialisation float,cyme::qpx,2 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::qpx,2>::register_type
    _mm_rsqrt<float,cyme::qpx,2>(simd_trait<float,cyme::qpx,2>::register_type xmm0){
        return simd_trait<float,cyme::qpx,2>::register_type(vec_rsqrte(xmm0.r0),
                                                            vec_rsqrte(xmm0.r1));
    }

    /**
      Compute 1/recsqrt (32-bit) floating point elements in xmm0 to packed double-precision
     (64-bit) floating-point elements, and store the results in dst.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
       of a and r is the value of the corresponding element of the result value:
     | (r-1/x^0.5) / (1/x^0.5) | ≤ 1/256
       specialisation float,cyme::qpx,4 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::qpx,4>::register_type
    _mm_rsqrt<float,cyme::qpx,4>(simd_trait<float,cyme::qpx,4>::register_type xmm0){
        return simd_trait<float,cyme::qpx,4>::register_type(vec_rsqrte(xmm0.r0),
                                                            vec_rsqrte(xmm0.r1),
                                                            vec_rsqrte(xmm0.r2),
                                                            vec_rsqrte(xmm0.r3));
    }

    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation float,cyme::qpx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,1>::register_type
    _mm_neg<float,cyme::qpx,1>(simd_trait<float,cyme::qpx,1>::register_type xmm0){
        return vec_neg(xmm0);
    };

    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation float,cyme::qpx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,2>::register_type
    _mm_neg<float,cyme::qpx,2>(simd_trait<float,cyme::qpx,2>::register_type xmm0){
         return simd_trait<float,cyme::qpx,2>::register_type(vec_neg(xmm0.r0),
                                                             vec_neg(xmm0.r1));
    };

    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation float,cyme::qpx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,4>::register_type
    _mm_neg<float,cyme::qpx,4>(simd_trait<float,cyme::qpx,4>::register_type xmm0){
         return simd_trait<float,cyme::qpx,4>::register_type(vec_neg(xmm0.r0),
                                                             vec_neg(xmm0.r1),
                                                             vec_neg(xmm0.r2),
                                                             vec_neg(xmm0.r3));
    };

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation float,cyme::qpx,1 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::qpx,1>::register_type
    _mm_cast<float,cyme::qpx,1>(simd_trait<int,cyme::qpx,1>::register_type xmm0){
        return  xmm0; // this int is already a float as floor is saved into vec_double
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation float,cyme::qpx,2 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::qpx,2>::register_type
    _mm_cast<float,cyme::qpx,2>(simd_trait<int,cyme::qpx,2>::register_type xmm0){
        return  xmm0; // this int is already a float as floor is saved into vec_double
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation float,cyme::qpx,4 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::qpx,4>::register_type
    _mm_cast<float,cyme::qpx,4>(simd_trait<int,cyme::qpx,4>::register_type xmm0){
        return  xmm0; // this int is already a float as floor is saved into vec_double
    }

    /**
      Returns a vector containing the largest representable floating-point integral
     values less than or equal to the values of the corresponding elements of the given vector.
       specialisation float,cyme::qpx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,1>::register_type
    _mm_floor<float,cyme::qpx,1>(simd_trait<float,cyme::qpx,1>::register_type xmm0){
        return vec_floor(xmm0);
    };

    /**
      Returns a vector containing the largest representable floating-point integral
     values less than or equal to the values of the corresponding elements of the given vector.
       specialisation float,cyme::qpx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,2>::register_type
    _mm_floor<float,cyme::qpx,2>(simd_trait<float,cyme::qpx,2>::register_type xmm0){
         return simd_trait<float,cyme::qpx,2>::register_type(vec_floor(xmm0.r0),
                                                             vec_floor(xmm0.r1));
    };

    /**
      Returns a vector containing the largest representable floating-point integral
     values less than or equal to the values of the corresponding elements of the given vector.
       specialisation float,cyme::qpx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,4>::register_type
    _mm_floor<float,cyme::qpx,4>(simd_trait<float,cyme::qpx,4>::register_type xmm0){
         return simd_trait<float,cyme::qpx,4>::register_type(vec_floor(xmm0.r0),
                                                             vec_floor(xmm0.r1),
                                                             vec_floor(xmm0.r2),
                                                             vec_floor(xmm0.r3));
    };

    /**
      Returns a vector containing 2^k where k is a vector of integer, as the BG/Q does not
     support QPX integer the computation is done serialy using C trick
       specialisation float,cyme::qpx,1 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::qpx,1>::register_type
    _mm_twok<float,cyme::qpx,1>(simd_trait<int,cyme::qpx,1>::register_type xmm0){
        boost::int32_t n;
        for(int i=0; i<4; ++i){
            ieee754 u;
            u.d = 0;
            n = vec_extract(xmm0,i);
            double d = uint642dp(( ((boost::uint64_t)n) +1023)<<52);
            xmm0 = vec_insert(d,xmm0,i);
        }
        return xmm0;
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer, as the BG/Q does not
     support QPX integer the computation is done serialy using C trick
       specialisation float,cyme::qpx,2 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::qpx,2>::register_type
    _mm_twok<float,cyme::qpx,2>(simd_trait<int,cyme::qpx,2>::register_type xmm0){
        boost::int32_t n1,n2;
        for(int i=0; i<4; ++i){
            ieee754 u1,u2;
            u1.d = 0;
            u2.d = 0;
            n1 = vec_extract(xmm0.r0,i);
            n2 = vec_extract(xmm0.r1,i);
            double d1 = uint642dp(( ((boost::uint64_t)n1) +1023)<<52);
            double d2 = uint642dp(( ((boost::uint64_t)n2) +1023)<<52);
            xmm0.r0 = vec_insert(d1,xmm0.r0,i);
            xmm0.r1 = vec_insert(d2,xmm0.r1,i);
        }
        return simd_trait<float,cyme::qpx,2>::register_type(xmm0.r0, xmm0.r1);
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer, as the BG/Q does not
     support QPX integer the computation is done serialy using C trick
       specialisation float,cyme::qpx,4 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::qpx,4>::register_type
    _mm_twok<float,cyme::qpx,4>(simd_trait<int,cyme::qpx,4>::register_type xmm0){
        boost::int32_t n1,n2,n3,n4;
        for(int i=0; i<4; ++i){
            ieee754 u1,u2,u3,u4;
            u1.d = 0;
            u2.d = 0;
            u3.d = 0;
            u4.d = 0;
            n1 = vec_extract(xmm0.r0,i);
            n2 = vec_extract(xmm0.r1,i);
            n3 = vec_extract(xmm0.r2,i);
            n4 = vec_extract(xmm0.r3,i);
            double d1 = uint642dp(( ((boost::uint64_t)n1) +1023)<<52);
            double d2 = uint642dp(( ((boost::uint64_t)n2) +1023)<<52);
            double d3 = uint642dp(( ((boost::uint64_t)n3) +1023)<<52);
            double d4 = uint642dp(( ((boost::uint64_t)n4) +1023)<<52);
            xmm0.r0 = vec_insert(d1,xmm0.r0,i);
            xmm0.r1 = vec_insert(d2,xmm0.r1,i);
            xmm0.r2 = vec_insert(d3,xmm0.r2,i);
            xmm0.r3 = vec_insert(d4,xmm0.r3,i);
        }
         return simd_trait<float,cyme::qpx,4>::register_type(xmm0.r0, xmm0.r1, xmm0.r2, xmm0.r3);
    }

    /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
      arithmetic are very badly supported with AVX, I am presently glue I so do the compuation in SSE;
       specialisation float,cyme::qpx,1 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::qpx,1>::register_type
    _mm_ge<float,cyme::qpx,1>(simd_trait<float,cyme::qpx,1>::register_type xmm0){
        for(int i=0; i<4; ++i){
            ieee754 u;
            u.d = vec_extract(xmm0,i);
            u.ll =(u.ll>>52)-1023;
            xmm0 = vec_insert((double)u.ll,xmm0,i);
        }
        return xmm0;
    }

    /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
      arithmetic are very badly supported with AVX, I am presently glue I so do the compuation in SSE;
       specialisation float,cyme::qpx,2 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::qpx,2>::register_type
    _mm_ge<float,cyme::qpx,2>(simd_trait<float,cyme::qpx,2>::register_type xmm0){
        for(int i=0; i<4; ++i){
            ieee754 u1,u2;
            u1.d = vec_extract(xmm0.r0,i);
            u2.d = vec_extract(xmm0.r1,i);
            u1.ll =(u1.ll>>52)-1023;
            u2.ll =(u2.ll>>52)-1023;
            xmm0.r0 = vec_insert((double)u1.ll,xmm0.r0,i);
            xmm0.r1 = vec_insert((double)u2.ll,xmm0.r1,i);
        }
        return simd_trait<float,cyme::qpx,2>::register_type(xmm0.r0,xmm0.r1);
    }

    /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
      arithmetic are very badly supported with AVX, I am presently glue I so do the compuation in SSE;
       specialisation float,cyme::qpx,4 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::qpx,4>::register_type
    _mm_ge<float,cyme::qpx,4>(simd_trait<float,cyme::qpx,4>::register_type xmm0){
        for(int i=0; i<4; ++i){
            ieee754 u1,u2,u3,u4;
            u1.d = vec_extract(xmm0.r0,i);
            u2.d = vec_extract(xmm0.r1,i);
            u3.d = vec_extract(xmm0.r2,i);
            u4.d = vec_extract(xmm0.r3,i);
            u1.ll =(u1.ll>>52)-1023;
            u2.ll =(u2.ll>>52)-1023;
            u3.ll =(u3.ll>>52)-1023;
            u4.ll =(u4.ll>>52)-1023;
            xmm0.r0 = vec_insert((double)u1.ll,xmm0.r0,i);
            xmm0.r1 = vec_insert((double)u2.ll,xmm0.r1,i);
            xmm0.r2 = vec_insert((double)u3.ll,xmm0.r2,i);
            xmm0.r3 = vec_insert((double)u4.ll,xmm0.r3,i);
        }
        return simd_trait<float,cyme::qpx,4>::register_type(xmm0.r0,xmm0.r1,xmm0.r2,xmm0.r3);
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
       specialisation float,cyme::qpx,1 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::qpx,1>::register_type
    _mm_gf<float,cyme::qpx,1>(simd_trait<float,cyme::qpx,1>::register_type xmm0){
        for(int i=0; i<4; ++i){
            ieee754 u;
            u.d = vec_extract(xmm0,i);
            u.ll = (u.ll&0xfffffffffffff)+0x3ff0000000000000;
            xmm0 = vec_insert(u.d,xmm0,i);
        }
        return xmm0;
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
       specialisation float,cyme::qpx,2 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::qpx,2>::register_type
    _mm_gf<float,cyme::qpx,2>(simd_trait<float,cyme::qpx,2>::register_type xmm0){
        for(int i=0; i<4; ++i){
            ieee754 u1,u2;
            u1.d = vec_extract(xmm0.r0,i);
            u2.d = vec_extract(xmm0.r1,i);
            u1.ll = (u1.ll&0xfffffffffffff)+0x3ff0000000000000;
            u2.ll = (u2.ll&0xfffffffffffff)+0x3ff0000000000000;
            xmm0.r0 = vec_insert(u1.d,xmm0.r0,i);
            xmm0.r1 = vec_insert(u2.d,xmm0.r1,i);
        }
        return simd_trait<float,cyme::qpx,2>::register_type(xmm0.r0,xmm0.r1);
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
       specialisation float,cyme::qpx,4 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::qpx,4>::register_type
    _mm_gf<float,cyme::qpx,4>(simd_trait<float,cyme::qpx,4>::register_type xmm0){
        for(int i=0; i<4; ++i){
            ieee754 u1,u2,u3,u4;
            u1.d = vec_extract(xmm0.r0,i);
            u2.d = vec_extract(xmm0.r1,i);
            u3.d = vec_extract(xmm0.r2,i);
            u4.d = vec_extract(xmm0.r3,i);
            u1.ll = (u1.ll&0xfffffffffffff)+0x3ff0000000000000;
            u2.ll = (u2.ll&0xfffffffffffff)+0x3ff0000000000000;
            u3.ll = (u3.ll&0xfffffffffffff)+0x3ff0000000000000;
            u4.ll = (u4.ll&0xfffffffffffff)+0x3ff0000000000000;
            xmm0.r0 = vec_insert(u1.d,xmm0.r0,i);
            xmm0.r1 = vec_insert(u2.d,xmm0.r1,i);
            xmm0.r2 = vec_insert(u3.d,xmm0.r2,i);
            xmm0.r3 = vec_insert(u4.d,xmm0.r3,i);
        }
        return simd_trait<float,cyme::qpx,4>::register_type(xmm0.r0,xmm0.r1,xmm0.r2,xmm0.r3);
    }

    /**
      Computes the absolute value for single-precision (32-bit) floating point elements and stores
      the result in dst.
      specialisation float,cyme::qpx,1 reg
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,1>::register_type
    _mm_fabs<float,cyme::qpx,1>( simd_trait<float,cyme::qpx,1>::register_type xmm0){
	return vec_abs(xmm0);
    }

    /**
      Computes the absolute value for single-precision (32-bit) floating point elements and stores
      the result in dst.
      specialisation float,cyme::qpx,2 reg
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,2>::register_type
    _mm_fabs<float,cyme::qpx,2>( simd_trait<float,cyme::qpx,2>::register_type xmm0){
        return simd_trait<float,cyme::qpx,2>::register_type(vec_abs(xmm0.r0),vec_abs(xmm0.r1));
    }

    /**
      Computes the absolute value for single-precision (32-bit) floating point elements and stores
      the result in dst.
      specialisation float,cyme::qpx,4 reg
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,4>::register_type
    _mm_fabs<float,cyme::qpx,4>( simd_trait<float,cyme::qpx,4>::register_type __attribute__((unused))xmm0){
        return simd_trait<float,cyme::qpx,4>::register_type(vec_abs(xmm0.r0),vec_abs(xmm0.r1),
                                                            vec_abs(xmm0.r2),vec_abs(xmm0.r3));
    }

    /**
      Selects the polynomial for sin function. Inputs are:
	- Selector int
	- Option one
	- Option two
      specialisation float,cyme::qpx, 1 reg
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,1>::register_type
    _mm_select_poly<float,cyme::qpx,1>( simd_trait<int,cyme::qpx,1>::register_type __attribute__((unused))sel,
                                         simd_trait<float,cyme::qpx,1>::register_type __attribute__((unused))xmm0,
                                         simd_trait<float,cyme::qpx,1>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Selects the polynomial for sin function. Inputs are:
	- Selector int
	- Option one
	- Option two
      specialisation float,cyme::qpx, 2 reg
     */
   template<>
    forceinline simd_trait<float,cyme::qpx,2>::register_type
    _mm_select_poly<float,cyme::qpx,2>( simd_trait<int,cyme::qpx,2>::register_type __attribute__((unused))sel,
                                         simd_trait<float,cyme::qpx,2>::register_type __attribute__((unused))xmm0,
                                         simd_trait<float,cyme::qpx,2>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Selects the polynomial for sin function. Inputs are:
	- Selector int
	- Option one
	- Option two
      specialisation float,cyme::qpx, 4 reg
     */
   template<>
    forceinline simd_trait<float,cyme::qpx,4>::register_type
    _mm_select_poly<float,cyme::qpx,4>( simd_trait<int,cyme::qpx,4>::register_type __attribute__((unused))sel,
                                         simd_trait<float,cyme::qpx,4>::register_type  __attribute__((unused))xmm0,
                                         simd_trait<float,cyme::qpx,4>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Selects the sign (+/-) for sin function. Inputs are:
	- swap int
	- Original input
	- Final calculated sin value
      specialisation float,cyme::qpx,1 reg
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,1>::register_type
    _mm_select_sign_sin<float,cyme::qpx,1>( simd_trait<int,cyme::qpx,1>::register_type __attribute__((unused))swap,
                                            simd_trait<float,cyme::qpx,1>::register_type __attribute__((unused))xmm0,
                                            simd_trait<float,cyme::qpx,1>::register_type __attribute__((unused))xmm1){
	assert(false);
    }


    /**
      Selects the sign (+/-) for sin function. Inputs are:
	- swap int
	- Original input
	- Final calculated sin value
      specialisation float,cyme::qpx,2 reg
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,2>::register_type
    _mm_select_sign_sin<float,cyme::qpx,2>( simd_trait<int,cyme::qpx,2>::register_type __attribute__((unused))swap,
                                            simd_trait<float,cyme::qpx,2>::register_type __attribute__((unused))xmm0,
                                            simd_trait<float,cyme::qpx,2>::register_type __attribute__((unused))xmm1){
	assert(false);
    }


    /**
      Selects the sign (+/-) for sin function. Inputs are:
	- swap int
	- Original input
	- Final calculated sin value
      specialisation float,cyme::qpx,4 reg
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,4>::register_type
    _mm_select_sign_sin<float,cyme::qpx,4>( simd_trait<int,cyme::qpx,4>::register_type __attribute__((unused))swap,
                                            simd_trait<float,cyme::qpx,4>::register_type __attribute__((unused))xmm0,
                                            simd_trait<float,cyme::qpx,4>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Selects the sign (+/-) for cos function. Inputs are:
	- swap int
	- Final calculated cos value
      specialisation float,cyme::qpx,1 reg
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,1>::register_type
    _mm_select_sign_cos<float,cyme::qpx,1>( simd_trait<int,cyme::qpx,1>::register_type __attribute__((unused))swap,
                                            simd_trait<float,cyme::qpx,1>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Selects the sign (+/-) for cos function. Inputs are:
	- swap int
	- Final calculated cos value
      specialisation float,cyme::qpx,2 reg
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,2>::register_type
    _mm_select_sign_cos<float,cyme::qpx,2>( simd_trait<int,cyme::qpx,2>::register_type __attribute__((unused))swap,
                                            simd_trait<float,cyme::qpx,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Selects the sign (+/-) for cos function. Inputs are:
	- swap int
	- Final calculated cos value
      specialisation float,cyme::qpx,4 reg
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,4>::register_type
    _mm_select_sign_cos<float,cyme::qpx,4>( simd_trait<int,cyme::qpx,4>::register_type __attribute__((unused))swap,
                                            simd_trait<float,cyme::qpx,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

#ifdef __FMA__
    /**
      Returns a vector containing the results of performing a fused multiply/add
     for each corresponding of a set of elements of the given vectors.
       specialisation float,cyme::qpx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,1>::register_type
    _mm_fma<float,cyme::qpx,1>(simd_trait<float,cyme::qpx,1>::register_type xmm0,
                               simd_trait<float,cyme::qpx,1>::register_type xmm1,
                               simd_trait<float,cyme::qpx,1>::register_type xmm2){
        return vec_madd(xmm0, xmm1, xmm2);
    };

    /**
      Returns a vector containing the results of performing a fused multiply/add
     for each corresponding of a set of elements of the given vectors.
       specialisation float,cyme::qpx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,2>::register_type
    _mm_fma<float,cyme::qpx,2>(simd_trait<float,cyme::qpx,2>::register_type xmm0,
                                 simd_trait<float,cyme::qpx,2>::register_type xmm1,
                                 simd_trait<float,cyme::qpx,2>::register_type xmm2){
         return simd_trait<float,cyme::qpx,2>::register_type(vec_madd(xmm0.r0,xmm1.r0,xmm2.r0),
                                                             vec_madd(xmm0.r1,xmm1.r1,xmm2.r1));
    };

    /**
      Returns a vector containing the results of performing a fused multiply/add
     for each corresponding of a set of elements of the given vectors.
       specialisation float,cyme::qpx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,4>::register_type
    _mm_fma<float,cyme::qpx,4>(simd_trait<float,cyme::qpx,4>::register_type xmm0,
                               simd_trait<float,cyme::qpx,4>::register_type xmm1,
                               simd_trait<float,cyme::qpx,4>::register_type xmm2){
         return simd_trait<float,cyme::qpx,4>::register_type(vec_madd(xmm0.r0,xmm1.r0,xmm2.r0),
                                                             vec_madd(xmm0.r1,xmm1.r1,xmm2.r1),
                                                             vec_madd(xmm0.r2,xmm1.r2,xmm2.r2),
                                                             vec_madd(xmm0.r3,xmm1.r3,xmm2.r3));
    };

    /**
      Returns a vector containing the results of performing a negative
      multiply-subtract operation on the given vectors.
       specialisation float,cyme::qpx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,1>::register_type
    _mm_nfma<float,cyme::qpx,1>(simd_trait<float,cyme::qpx,1>::register_type xmm0,
                                simd_trait<float,cyme::qpx,1>::register_type xmm1,
                                simd_trait<float,cyme::qpx,1>::register_type xmm2){
        return vec_nmsub(xmm0, xmm1, xmm2);
    };

    /**
      Returns a vector containing the results of performing a negative
      multiply-subtract operation on the given vectors.
       specialisation float,cyme::qpx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,2>::register_type
    _mm_nfma<float,cyme::qpx,2>(simd_trait<float,cyme::qpx,2>::register_type xmm0,
                                simd_trait<float,cyme::qpx,2>::register_type xmm1,
                                simd_trait<float,cyme::qpx,2>::register_type xmm2){
         return simd_trait<float,cyme::qpx,2>::register_type(vec_nmsub(xmm0.r0,xmm1.r0,xmm2.r0),
                                                             vec_nmsub(xmm0.r1,xmm1.r1,xmm2.r1));
    };

    /**
      Returns a vector containing the results of performing a negative
      multiply-subtract operation on the given vectors.
       specialisation float,cyme::qpx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,4>::register_type
    _mm_nfma<float,cyme::qpx,4>(simd_trait<float,cyme::qpx,4>::register_type xmm0,
                                simd_trait<float,cyme::qpx,4>::register_type xmm1,
                                simd_trait<float,cyme::qpx,4>::register_type xmm2){
         return simd_trait<float,cyme::qpx,4>::register_type(vec_nmsub(xmm0.r0,xmm1.r0,xmm2.r0),
                                                             vec_nmsub(xmm0.r1,xmm1.r1,xmm2.r1),
                                                             vec_nmsub(xmm0.r2,xmm1.r2,xmm2.r2),
                                                             vec_nmsub(xmm0.r3,xmm1.r3,xmm2.r3));
    };

    /**
      Returns a vector containing the results of performing a multiply-substracti
      operation using the given vectors.
       specialisation float,cyme::qpx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,1>::register_type
    _mm_fms<float,cyme::qpx,1>(simd_trait<float,cyme::qpx,1>::register_type xmm0,
                               simd_trait<float,cyme::qpx,1>::register_type xmm1,
                               simd_trait<float,cyme::qpx,1>::register_type xmm2){
        return vec_msub(xmm0, xmm1, xmm2);
    };

    /**
      Returns a vector containing the results of performing a multiply-substracti
      operation using the given vectors.
       specialisation float,cyme::qpx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,2>::register_type
    _mm_fms<float,cyme::qpx,2>(simd_trait<float,cyme::qpx,2>::register_type xmm0,
                               simd_trait<float,cyme::qpx,2>::register_type xmm1,
                               simd_trait<float,cyme::qpx,2>::register_type xmm2){
         return simd_trait<float,cyme::qpx,2>::register_type(vec_msub(xmm0.r0,xmm1.r0,xmm2.r0),
                                                             vec_msub(xmm0.r1,xmm1.r1,xmm2.r1));
    };

    /**
      Returns a vector containing the results of performing a multiply-substracti
      operation using the given vectors.
       specialisation float,cyme::qpx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,4>::register_type
    _mm_fms<float,cyme::qpx,4>(simd_trait<float,cyme::qpx,4>::register_type xmm0,
                               simd_trait<float,cyme::qpx,4>::register_type xmm1,
                               simd_trait<float,cyme::qpx,4>::register_type xmm2){
         return simd_trait<float,cyme::qpx,4>::register_type(vec_msub(xmm0.r0,xmm1.r0,xmm2.r0),
                                                             vec_msub(xmm0.r1,xmm1.r1,xmm2.r1),
                                                             vec_msub(xmm0.r2,xmm1.r2,xmm2.r2),
                                                             vec_msub(xmm0.r3,xmm1.r3,xmm2.r3));
    };


    /**
     Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
       specialisation float,cyme::qpx,1 regs
    */
    template<>
    forceinline simd_trait<float,cyme::qpx,1>::register_type
    _mm_nfms<float,cyme::qpx,1>(simd_trait<float,cyme::qpx,1>::register_type xmm0,
                                simd_trait<float,cyme::qpx,1>::register_type xmm1,
                                simd_trait<float,cyme::qpx,1>::register_type xmm2){
        return vec_nmadd(xmm0, xmm1, xmm2);
    };

    /**
     Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
       specialisation float,cyme::qpx,2 regs
    */
    template<>
    forceinline simd_trait<float,cyme::qpx,2>::register_type
    _mm_nfms<float,cyme::qpx,2>(simd_trait<float,cyme::qpx,2>::register_type xmm0,
                                simd_trait<float,cyme::qpx,2>::register_type xmm1,
                                simd_trait<float,cyme::qpx,2>::register_type xmm2){
         return simd_trait<float,cyme::qpx,2>::register_type(vec_nmadd(xmm0.r0,xmm1.r0,xmm2.r0),
                                                             vec_nmadd(xmm0.r1,xmm1.r1,xmm2.r1));
    };

    /**
     Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
       specialisation float,cyme::qpx,4 regs
    */
    template<>
    forceinline simd_trait<float,cyme::qpx,4>::register_type
    _mm_nfms<float,cyme::qpx,4>(simd_trait<float,cyme::qpx,4>::register_type xmm0,
                                simd_trait<float,cyme::qpx,4>::register_type xmm1,
                                simd_trait<float,cyme::qpx,4>::register_type xmm2){
         return simd_trait<float,cyme::qpx,4>::register_type(vec_nmadd(xmm0.r0,xmm1.r0,xmm2.r0),
                                                             vec_nmadd(xmm0.r1,xmm1.r1,xmm2.r1),
                                                             vec_nmadd(xmm0.r2,xmm1.r2,xmm2.r2),
                                                             vec_nmadd(xmm0.r3,xmm1.r3,xmm2.r3));
    };
#endif //__FMA__
/*--------------------------------------------------------------------- double ---------------*/
    /**
       Single load a double-precision (64-bit) floating-point element from cyme into lower element of dst.
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,1>::register_type
    _mm_single_load<double,cyme::qpx,1>(const simd_trait<double,cyme::qpx,1>::value_type b){
        return vec_lds(0,(double*)(void*)&b);
    }

    /**
       Single store a double-precision (64-bit) floating-point element from register lower element to cyme.
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,1>::value_type
    _mm_single_store<double,cyme::qpx,1>(simd_trait<double,cyme::qpx,1>::register_type xmm0,
                                           simd_trait<double,cyme::qpx,1>::pointer b){
        vec_sts(xmm0,0,b);
        return *b;
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation double,cyme::qpx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,1>::register_type
    _mm_load1<double,cyme::qpx,1>(const simd_trait<double,cyme::qpx,1>::value_type& a){
        return vec_splats(a);
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation double,cyme::qpx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,2>::register_type
    _mm_load1<double,cyme::qpx,2>(const simd_trait<double,cyme::qpx,2>::value_type& a){
        return simd_trait<double,cyme::qpx,2>::register_type(vec_splats(a),vec_splats(a));
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation double,cyme::qpx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,4>::register_type
    _mm_load1<double,cyme::qpx,4>(const simd_trait<double,cyme::qpx,4>::value_type& a){
        return simd_trait<double,cyme::qpx,4>::register_type(vec_splats(a),vec_splats(a),
                                                             vec_splats(a),vec_splats(a));
    }

    /**
      Loads a vector from the given cyme address.
       specialisation double,cyme::qpx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,1>::register_type
    _mm_load<double,cyme::qpx,1>(simd_trait<double,cyme::qpx,1>::const_pointer a){
        return vec_lda(0L,(double*)(void*)a);
    }

    /**
      Loads a vector from the given cyme address.
       specialisation double,cyme::qpx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,2>::register_type
    _mm_load<double,cyme::qpx,2>(simd_trait<double,cyme::qpx,2>::const_pointer a){
        return simd_trait<double,cyme::qpx,2>::register_type(vec_lda(0L,(double*)(void*)a),
                                                             vec_lda(32L,(double*)(void*)a));
    }

    /**
      Loads a vector from the given cyme address.
       specialisation double,cyme::qpx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,4>::register_type
    _mm_load<double,cyme::qpx,4>(simd_trait<double,cyme::qpx,4>::const_pointer a){
        return simd_trait<double,cyme::qpx,4>::register_type(vec_lda(0L,(double*)(void*)a),
                                                             vec_lda(32L,(double*)(void*)a),
                                                             vec_lda(64L,(double*)(void*)a),
                                                             vec_lda(96L,(double*)(void*)a));
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation double,cyme::qpx,1 regs
     */
    template<>
    forceinline void
    _mm_store<double,cyme::qpx,1>(simd_trait<double,cyme::qpx,1>::register_type xmm0,
                                  simd_trait<double,cyme::qpx,1>::pointer a){
        vec_sta(xmm0,0L,a);
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation double,cyme::qpx,2 regs
     */
    template<>
    forceinline void
    _mm_store<double,cyme::qpx,2>(simd_trait<double,cyme::qpx,2>::register_type xmm0,
                                  simd_trait<double,cyme::qpx,2>::pointer a){
        vec_sta(xmm0.r0,0L,a);
        vec_sta(xmm0.r1,32L,a);
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation double,cyme::qpx,4 regs
     */
    template<>
    forceinline void
    _mm_store<double,cyme::qpx,4>(simd_trait<double,cyme::qpx,4>::register_type xmm0,
                                  simd_trait<double,cyme::qpx,4>::pointer a){
        vec_sta(xmm0.r0,0L,a);
        vec_sta(xmm0.r1,32L,a);
        vec_sta(xmm0.r2,64L,a);
        vec_sta(xmm0.r3,96L,a);
    }

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation double,cyme::qpx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,1>::register_type
    _mm_mul<double,cyme::qpx,1>(simd_trait<double,cyme::qpx,1>::register_type xmm0,
                                simd_trait<double,cyme::qpx,1>::register_type xmm1){
        return vec_mul(xmm0, xmm1);
    };

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation double,cyme::qpx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,2>::register_type
    _mm_mul<double,cyme::qpx,2>(simd_trait<double,cyme::qpx,2>::register_type xmm0,
                                simd_trait<double,cyme::qpx,2>::register_type xmm1){
         return simd_trait<double,cyme::qpx,2>::register_type(vec_mul(xmm0.r0,xmm1.r0),
                                                              vec_mul(xmm0.r1,xmm1.r1));
    };

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation double,cyme::qpx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,4>::register_type
    _mm_mul<double,cyme::qpx,4>(simd_trait<double,cyme::qpx,4>::register_type xmm0,
                                simd_trait<double,cyme::qpx,4>::register_type xmm1){
         return simd_trait<double,cyme::qpx,4>::register_type(vec_mul(xmm0.r0,xmm1.r0),
                                                              vec_mul(xmm0.r1,xmm1.r1),
                                                              vec_mul(xmm0.r2,xmm1.r2),
                                                              vec_mul(xmm0.r3,xmm1.r3));
    };

    /**
      Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation double,cyme::qpx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,1>::register_type
    _mm_div<double,cyme::qpx,1>(simd_trait<double,cyme::qpx,1>::register_type xmm0,
                                simd_trait<double,cyme::qpx,1>::register_type xmm1){
        return vec_swdiv(xmm0, xmm1);
    };

    /**
      Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation double,cyme::qpx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,2>::register_type
    _mm_div<double,cyme::qpx,2>(simd_trait<double,cyme::qpx,2>::register_type xmm0,
                                simd_trait<double,cyme::qpx,2>::register_type xmm1){
         return simd_trait<double,cyme::qpx,2>::register_type(vec_swdiv(xmm0.r0,xmm1.r0),
                                                              vec_swdiv(xmm0.r1,xmm1.r1));
    };

    /**
      Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation double,cyme::qpx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,4>::register_type
    _mm_div<double,cyme::qpx,4>(simd_trait<double,cyme::qpx,4>::register_type xmm0,
                                simd_trait<double,cyme::qpx,4>::register_type xmm1){
         return simd_trait<double,cyme::qpx,4>::register_type(vec_swdiv(xmm0.r0,xmm1.r0),
                                                              vec_swdiv(xmm0.r1,xmm1.r1),
                                                              vec_swdiv(xmm0.r2,xmm1.r2),
                                                              vec_swdiv(xmm0.r3,xmm1.r3));
    };

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation double,cyme::qpx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,1>::register_type
    _mm_add<double,cyme::qpx,1>(simd_trait<double,cyme::qpx,1>::register_type xmm0,
                                simd_trait<double,cyme::qpx,1>::register_type xmm1){
        return vec_add(xmm0, xmm1);
    };

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation double,cyme::qpx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,2>::register_type
    _mm_add<double,cyme::qpx,2>(simd_trait<double,cyme::qpx,2>::register_type xmm0,
                                simd_trait<double,cyme::qpx,2>::register_type xmm1){
         return simd_trait<double,cyme::qpx,2>::register_type(vec_add(xmm0.r0,xmm1.r0),
                                                              vec_add(xmm0.r1,xmm1.r1));
    };

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation double,cyme::qpx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,4>::register_type
    _mm_add<double,cyme::qpx,4>(simd_trait<double,cyme::qpx,4>::register_type xmm0,
                                simd_trait<double,cyme::qpx,4>::register_type xmm1){
         return simd_trait<double,cyme::qpx,4>::register_type(vec_add(xmm0.r0,xmm1.r0),
                                                              vec_add(xmm0.r1,xmm1.r1),
                                                              vec_add(xmm0.r2,xmm1.r2),
                                                              vec_add(xmm0.r3,xmm1.r3));
    };

    /**
      Returns a vector containing the result of subtracting each element of b from the corresponding element of a.
       specialisation double,cyme::qpx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,1>::register_type
    _mm_sub<double,cyme::qpx,1>(simd_trait<double,cyme::qpx,1>::register_type xmm0,
                                simd_trait<double,cyme::qpx,1>::register_type xmm1){
        return vec_sub(xmm0, xmm1);
    };

    /**
      Returns a vector containing the result of subtracting each element of b from the corresponding element of a.
       specialisation double,cyme::qpx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,2>::register_type
    _mm_sub<double,cyme::qpx,2>(simd_trait<double,cyme::qpx,2>::register_type xmm0,
                                simd_trait<double,cyme::qpx,2>::register_type xmm1){
         return simd_trait<double,cyme::qpx,2>::register_type(vec_sub(xmm0.r0,xmm1.r0),
                                                              vec_sub(xmm0.r1,xmm1.r1));
    };

    /**
      Returns a vector containing the result of subtracting each element of b from the corresponding element of a.
       specialisation double,cyme::qpx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,4>::register_type
    _mm_sub<double,cyme::qpx,4>(simd_trait<double,cyme::qpx,4>::register_type xmm0,
                                simd_trait<double,cyme::qpx,4>::register_type xmm1){
         return simd_trait<double,cyme::qpx,4>::register_type(vec_sub(xmm0.r0,xmm1.r0),
                                                              vec_sub(xmm0.r1,xmm1.r1),
                                                              vec_sub(xmm0.r2,xmm1.r2),
                                                              vec_sub(xmm0.r3,xmm1.r3));
    };

    /**
      Computes the exponential function of each element of vx.
       specialisation double,cyme::qpx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,1>::register_type
    _mm_exp<double,cyme::qpx,1>(simd_trait<double,cyme::qpx,1>::register_type xmm0){
        return expd4(xmm0);
    };

    /**
      Computes the exponential function of each element of vx.
       specialisation double,cyme::qpx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,2>::register_type
    _mm_exp<double,cyme::qpx,2>(simd_trait<double,cyme::qpx,2>::register_type xmm0){
         return simd_trait<double,cyme::qpx,2>::register_type(expd4(xmm0.r0),
                                                              expd4(xmm0.r1));
    };

    /**
      Computes the exponential function of each element of vx.
       specialisation double,cyme::qpx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,4>::register_type
    _mm_exp<double,cyme::qpx,4>(simd_trait<double,cyme::qpx,4>::register_type xmm0){
         return simd_trait<double,cyme::qpx,4>::register_type(expd4(xmm0.r0),
                                                              expd4(xmm0.r1),
                                                              expd4(xmm0.r2),
                                                              expd4(xmm0.r3));
    };

    /**
      Computes the logarithm function of each element of vx.
       specialisation double,cyme::qpx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,1>::register_type
    _mm_log<double,cyme::qpx,1>(simd_trait<double,cyme::qpx,1>::register_type xmm0){
        return logd4(xmm0);
    };

    /**
      Computes the logarithm function of each element of vx.
       specialisation double,cyme::qpx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,2>::register_type
    _mm_log<double,cyme::qpx,2>(simd_trait<double,cyme::qpx,2>::register_type xmm0){
         return simd_trait<double,cyme::qpx,2>::register_type(logd4(xmm0.r0),
                                                              logd4(xmm0.r1));
    };

    /**
      Computes the logarithm function of each element of vx.
       specialisation double,cyme::qpx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,4>::register_type
    _mm_log<double,cyme::qpx,4>(simd_trait<double,cyme::qpx,4>::register_type xmm0){
         return simd_trait<double,cyme::qpx,4>::register_type(logd4(xmm0.r0),
                                                              logd4(xmm0.r1),
                                                              logd4(xmm0.r2),
                                                              logd4(xmm0.r3));
    };

    /**
      Returns a vector containing estimates of the reciprocals of the corresponding elements of the given vector.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x) / (1/x) | ≤ 1/256
       specialisation double,cyme::qpx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,1>::register_type
    _mm_rec<double,cyme::qpx,1>(simd_trait<double,cyme::qpx,1>::register_type xmm0){
        return vec_re(xmm0);
    };

    /**
      Returns a vector containing estimates of the reciprocals of the corresponding elements of the given vector.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x) / (1/x) | ≤ 1/256
       specialisation double,cyme::qpx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,2>::register_type
    _mm_rec<double,cyme::qpx,2>(simd_trait<double,cyme::qpx,2>::register_type xmm0){
         return simd_trait<double,cyme::qpx,2>::register_type(vec_re(xmm0.r0),
                                                              vec_re(xmm0.r1));
    };

    /**
      Returns a vector containing estimates of the reciprocals of the corresponding elements of the given vector.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x) / (1/x) | ≤ 1/256
       specialisation double,cyme::qpx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,4>::register_type
    _mm_rec<double,cyme::qpx,4>(simd_trait<double,cyme::qpx,4>::register_type xmm0){
         return simd_trait<double,cyme::qpx,4>::register_type(vec_re(xmm0.r0),
                                                              vec_re(xmm0.r1),
                                                              vec_re(xmm0.r2),
                                                              vec_re(xmm0.r3));
    };


    /**
      Compute 1/recsqrt (64-bit) floating point elements in xmm0 to packed double-precision (64-bit)
     floating-point elements, and store the results in dst.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x^0,5) / (1/x^0.5) | ≤ 1/256
       specialisation double,cyme::qpx,1 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::qpx,1>::register_type
    _mm_rsqrt<double,cyme::qpx,1>(simd_trait<double,cyme::qpx,1>::register_type xmm0){
        return vec_rsqrte(xmm0);
    }

    /**
      Compute 1/recsqrt (64-bit) floating point elements in xmm0 to packed double-precision (64-bit)
     floating-point elements, and store the results in dst.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x^0,5) / (1/x^0.5) | ≤ 1/256
       specialisation double,cyme::qpx,2 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::qpx,2>::register_type
    _mm_rsqrt<double,cyme::qpx,2>(simd_trait<double,cyme::qpx,2>::register_type xmm0){
        return simd_trait<double,cyme::qpx,2>::register_type(vec_rsqrte(xmm0.r0),
                                                             vec_rsqrte(xmm0.r1));
    }

    /**
      Compute 1/recsqrt (64-bit) floating point elements in xmm0 to packed double-precision (64-bit)
     floating-point elements, and store the results in dst.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x^0,5) / (1/x^0.5) | ≤ 1/256
       specialisation double,cyme::qpx,4 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::qpx,4>::register_type
    _mm_rsqrt<double,cyme::qpx,4>(simd_trait<double,cyme::qpx,4>::register_type xmm0){
        return simd_trait<double,cyme::qpx,4>::register_type(vec_rsqrte(xmm0.r0),
                                                             vec_rsqrte(xmm0.r1),
                                                             vec_rsqrte(xmm0.r2),
                                                             vec_rsqrte(xmm0.r3));
    }


    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation double,cyme::qpx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,1>::register_type
    _mm_neg<double,cyme::qpx,1>(simd_trait<double,cyme::qpx,1>::register_type xmm0){
        return vec_neg(xmm0);
    };

    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation double,cyme::qpx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,2>::register_type
    _mm_neg<double,cyme::qpx,2>(simd_trait<double,cyme::qpx,2>::register_type xmm0){
         return simd_trait<double,cyme::qpx,2>::register_type(vec_neg(xmm0.r0),
                                                              vec_neg(xmm0.r1));
    };

    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation double,cyme::qpx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,4>::register_type
    _mm_neg<double,cyme::qpx,4>(simd_trait<double,cyme::qpx,4>::register_type xmm0){
         return simd_trait<double,cyme::qpx,4>::register_type(vec_neg(xmm0.r0),
                                                              vec_neg(xmm0.r1),
                                                              vec_neg(xmm0.r2),
                                                              vec_neg(xmm0.r3));
    };

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation double,cyme::qpx,1 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::qpx,1>::register_type
    _mm_cast<double,cyme::qpx,1>(simd_trait<int,cyme::qpx,1>::register_type xmm0){
        return  xmm0; // this int is already a float as floor is saved into vec_double
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation double,cyme::qpx,2 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::qpx,2>::register_type
    _mm_cast<double,cyme::qpx,2>(simd_trait<int,cyme::qpx,2>::register_type xmm0){
        return  xmm0; // this int is already a float as floor is saved into vec_double
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation double,cyme::qpx,4 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::qpx,4>::register_type
    _mm_cast<double,cyme::qpx,4>(simd_trait<int,cyme::qpx,4>::register_type xmm0){
        return  xmm0; // this int is already a float as floor is saved into vec_double
    }


    /**
      Returns a vector containing the largest representable floating-point integral values less than or equal
     to the values of the corresponding elements of the given vector.
       specialisation double,cyme::qpx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,1>::register_type
    _mm_floor<double,cyme::qpx,1>(simd_trait<double,cyme::qpx,1>::register_type xmm0){
        return vec_floor(xmm0);
    };

    /**
      Returns a vector containing the largest representable floating-point integral values less than or equal
     to the values of the corresponding elements of the given vector.
       specialisation double,cyme::qpx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,2>::register_type
    _mm_floor<double,cyme::qpx,2>(simd_trait<double,cyme::qpx,2>::register_type xmm0){
         return simd_trait<double,cyme::qpx,2>::register_type(vec_floor(xmm0.r0),
                                                             vec_floor(xmm0.r1));
    };

    /**
      Returns a vector containing the largest representable floating-point integral values less than or equal
     to the values of the corresponding elements of the given vector.
       specialisation double,cyme::qpx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,4>::register_type
    _mm_floor<double,cyme::qpx,4>(simd_trait<double,cyme::qpx,4>::register_type xmm0){
         return simd_trait<double,cyme::qpx,4>::register_type(vec_floor(xmm0.r0),
                                                              vec_floor(xmm0.r1),
                                                              vec_floor(xmm0.r2),
                                                              vec_floor(xmm0.r3));
    };

    /**
      Returns a vector containing 2^k where k is a vector of integer, as the BG/Q does not support QPX integer
     the computation is done serialy using C trick
       specialisation double,cyme::qpx,1 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::qpx,1>::register_type
    _mm_twok<double,cyme::qpx,1>(simd_trait<int,cyme::qpx,1>::register_type xmm0){
        boost::int32_t n;
        for(int i=0; i<4; ++i){
            ieee754 u;
            u.d = 0;
            n = vec_extract(xmm0,i);
            double d = uint642dp(( ((boost::uint64_t)n) +1023)<<52);
            xmm0 = vec_insert(d,xmm0,i);
        }

        return xmm0;
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer, as the BG/Q does not support QPX integer
     the computation is done serialy using C trick
       specialisation double,cyme::qpx,2 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::qpx,2>::register_type
    _mm_twok<double,cyme::qpx,2>(simd_trait<int,cyme::qpx,2>::register_type xmm0){
        boost::int32_t n1,n2;
        for(int i=0; i<4; ++i){
            ieee754 u1,u2;
            u1.d = 0;
            u2.d = 0;
            n1 = vec_extract(xmm0.r0,i);
            n2 = vec_extract(xmm0.r1,i);
            double d1 = uint642dp(( ((boost::uint64_t)n1) +1023)<<52);
            double d2 = uint642dp(( ((boost::uint64_t)n2) +1023)<<52);
            xmm0.r0 = vec_insert(d1,xmm0.r0,i);
            xmm0.r1 = vec_insert(d2,xmm0.r1,i);
        }
        return simd_trait<double,cyme::qpx,2>::register_type(xmm0.r0, xmm0.r1);
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer, as the BG/Q does not support QPX integer
     the computation is done serialy using C trick
       specialisation double,cyme::qpx,4 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::qpx,4>::register_type
    _mm_twok<double,cyme::qpx,4>(simd_trait<int,cyme::qpx,4>::register_type xmm0){
        boost::int32_t n1,n2,n3,n4;
        for(int i=0; i<4; ++i){
            ieee754 u1,u2,u3,u4;
            u1.d = 0;
            u2.d = 0;
            u3.d = 0;
            u4.d = 0;
            n1 = vec_extract(xmm0.r0,i);
            n2 = vec_extract(xmm0.r1,i);
            n3 = vec_extract(xmm0.r2,i);
            n4 = vec_extract(xmm0.r3,i);
            double d1 = uint642dp(( ((boost::uint64_t)n1) +1023)<<52);
            double d2 = uint642dp(( ((boost::uint64_t)n2) +1023)<<52);
            double d3 = uint642dp(( ((boost::uint64_t)n3) +1023)<<52);
            double d4 = uint642dp(( ((boost::uint64_t)n4) +1023)<<52);
            xmm0.r0 = vec_insert(d1,xmm0.r0,i);
            xmm0.r1 = vec_insert(d2,xmm0.r1,i);
            xmm0.r2 = vec_insert(d3,xmm0.r2,i);
            xmm0.r3 = vec_insert(d4,xmm0.r3,i);
        }
	return simd_trait<double,cyme::qpx,4>::register_type(xmm0.r0, xmm0.r1, xmm0.r2, xmm0.r3);
    }

   /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
      arithmetic are very badly supported with AVX, I am presently glue I so do the compuation in SSE;
       specialisation double,cyme::qpx,1 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::qpx,1>::register_type
    _mm_ge<double,cyme::qpx,1>(simd_trait<double,cyme::qpx,1>::register_type xmm0){
        for(int i=0; i<4; ++i){
            ieee754 u;
            u.d = vec_extract(xmm0,i);
            u.ll =(u.ll>>52)-1023;
            xmm0 = vec_insert((double)u.ll,xmm0,i);
        }
        return xmm0;
    }

   /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
      arithmetic are very badly supported with AVX, I am presently glue I so do the compuation in SSE;
       specialisation double,cyme::qpx,2 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::qpx,2>::register_type
    _mm_ge<double,cyme::qpx,2>(simd_trait<double,cyme::qpx,2>::register_type xmm0){
        for(int i=0; i<4; ++i){
            ieee754 u1,u2;
            u1.d = vec_extract(xmm0.r0,i);
            u2.d = vec_extract(xmm0.r1,i);
            u1.ll =(u1.ll>>52)-1023;
            u2.ll =(u2.ll>>52)-1023;
            xmm0.r0 = vec_insert((double)u1.ll,xmm0.r0,i);
            xmm0.r1 = vec_insert((double)u2.ll,xmm0.r1,i);
        }
        return simd_trait<double,cyme::qpx,2>::register_type(xmm0.r0,xmm0.r1);
    }

   /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
      arithmetic are very badly supported with AVX, I am presently glue I so do the compuation in SSE;
       specialisation double,cyme::qpx,4 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::qpx,4>::register_type
    _mm_ge<double,cyme::qpx,4>(simd_trait<double,cyme::qpx,4>::register_type xmm0){
        for(int i=0; i<4; ++i){
            ieee754 u1,u2,u3,u4;
            u1.d = vec_extract(xmm0.r0,i);
            u2.d = vec_extract(xmm0.r1,i);
            u3.d = vec_extract(xmm0.r2,i);
            u4.d = vec_extract(xmm0.r3,i);
            u1.ll =(u1.ll>>52)-1023;
            u2.ll =(u2.ll>>52)-1023;
            u3.ll =(u3.ll>>52)-1023;
            u4.ll =(u4.ll>>52)-1023;
            xmm0.r0 = vec_insert((double)u1.ll,xmm0.r0,i);
            xmm0.r1 = vec_insert((double)u2.ll,xmm0.r1,i);
            xmm0.r2 = vec_insert((double)u3.ll,xmm0.r2,i);
            xmm0.r3 = vec_insert((double)u4.ll,xmm0.r3,i);
        }
        return simd_trait<double,cyme::qpx,4>::register_type(xmm0.r0,xmm0.r1,xmm0.r2,xmm0.r3);
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
       specialisation double,cyme::qpx,1 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::qpx,1>::register_type
    _mm_gf<double,cyme::qpx,1>(simd_trait<double,cyme::qpx,1>::register_type xmm0){
        for(int i=0; i<4; ++i){
            ieee754 u;
            u.d = vec_extract(xmm0,i);
            u.ll = (u.ll&0xfffffffffffff)+0x3ff0000000000000;
            xmm0 = vec_insert(u.d,xmm0,i);
        }
        return xmm0;
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
       specialisation double,cyme::qpx,2 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::qpx,2>::register_type
    _mm_gf<double,cyme::qpx,2>(simd_trait<double,cyme::qpx,2>::register_type xmm0){
        for(int i=0; i<4; ++i){
            ieee754 u1,u2;
            u1.d = vec_extract(xmm0.r0,i);
            u2.d = vec_extract(xmm0.r1,i);
            u1.ll = (u1.ll&0xfffffffffffff)+0x3ff0000000000000;
            u2.ll = (u2.ll&0xfffffffffffff)+0x3ff0000000000000;
            xmm0.r0 = vec_insert(u1.d,xmm0.r0,i);
            xmm0.r1 = vec_insert(u2.d,xmm0.r1,i);
        }
        return simd_trait<double,cyme::qpx,2>::register_type(xmm0.r0,xmm0.r1);
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
       specialisation double,cyme::qpx,4 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::qpx,4>::register_type
    _mm_gf<double,cyme::qpx,4>(simd_trait<double,cyme::qpx,4>::register_type xmm0){
        for(int i=0; i<4; ++i){
            ieee754 u1,u2,u3,u4;
            u1.d = vec_extract(xmm0.r0,i);
            u2.d = vec_extract(xmm0.r1,i);
            u3.d = vec_extract(xmm0.r2,i);
            u4.d = vec_extract(xmm0.r3,i);
            u1.ll = (u1.ll&0xfffffffffffff)+0x3ff0000000000000;
            u2.ll = (u2.ll&0xfffffffffffff)+0x3ff0000000000000;
            u3.ll = (u3.ll&0xfffffffffffff)+0x3ff0000000000000;
            u4.ll = (u4.ll&0xfffffffffffff)+0x3ff0000000000000;
            xmm0.r0 = vec_insert(u1.d,xmm0.r0,i);
            xmm0.r1 = vec_insert(u2.d,xmm0.r1,i);
            xmm0.r2 = vec_insert(u3.d,xmm0.r2,i);
            xmm0.r3 = vec_insert(u4.d,xmm0.r3,i);
        }
        return simd_trait<double,cyme::qpx,4>::register_type(xmm0.r0,xmm0.r1,xmm0.r2,xmm0.r3);
    }

    /**
      Computes the absolute value for double-precision (64-bit) floating point elements and stores
      the result in dst.
      specialisation double,cyme::qpx,1 reg
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,1>::register_type
    _mm_fabs<double,cyme::qpx,1>( simd_trait<double,cyme::qpx,1>::register_type xmm0){
        return vec_abs(xmm0);
    }

    /**
      Computes the absolute value for double-precision (64-bit) floating point elements and stores
      the result in dst.
      specialisation double,cyme::qpx,2 reg
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,2>::register_type
    _mm_fabs<double,cyme::qpx,2>( simd_trait<double,cyme::qpx,2>::register_type xmm0){
        return simd_trait<double,cyme::qpx,2>::register_type(vec_abs(xmm0.r0),vec_abs(xmm0.r1));
    }

    /**
      Computes the absolute value for double-precision (64-bit) floating point elements and stores
      the result in dst.
      specialisation double,cyme::qpx,4 reg
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,4>::register_type
    _mm_fabs<double,cyme::qpx,4>( simd_trait<double,cyme::qpx,4>::register_type xmm0){
        return simd_trait<double,cyme::qpx,4>::register_type(vec_abs(xmm0.r0),vec_abs(xmm0.r1),
                                                             vec_abs(xmm0.r2),vec_abs(xmm0.r3));
    }

    /**
      Selects the polynomial for sin function. Inputs are:
	- Selector int
	- Option one
	- Option two
      specialisation double,cyme::qpx, 1 reg
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,1>::register_type
    _mm_select_poly<double,cyme::qpx,1>( simd_trait<int,cyme::qpx,1>::register_type __attribute__((unused))sel,
                                         simd_trait<double,cyme::qpx,1>::register_type __attribute__((unused))xmm0,
                                         simd_trait<double,cyme::qpx,1>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Selects the polynomial for sin function. Inputs are:
	- Selector int
	- Option one
	- Option two
      specialisation double,cyme::qpx, 2 reg
     */
   template<>
    forceinline simd_trait<double,cyme::qpx,2>::register_type
    _mm_select_poly<double,cyme::qpx,2>( simd_trait<int,cyme::qpx,2>::register_type __attribute__((unused))sel,
                                         simd_trait<double,cyme::qpx,2>::register_type __attribute__((unused))xmm0,
                                         simd_trait<double,cyme::qpx,2>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Selects the polynomial for sin function. Inputs are:
	- Selector int
	- Option one
	- Option two
      specialisation double,cyme::qpx, 4 reg
     */
   template<>
    forceinline simd_trait<double,cyme::qpx,4>::register_type
    _mm_select_poly<double,cyme::qpx,4>( simd_trait<int,cyme::qpx,4>::register_type __attribute__((unused))sel,
                                         simd_trait<double,cyme::qpx,4>::register_type  __attribute__((unused))xmm0,
                                         simd_trait<double,cyme::qpx,4>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Selects the sign (+/-) for sin function. Inputs are:
	- swap int
	- Original input
	- Final calculated sin value
      specialisation double,cyme::qpx,1 reg
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,1>::register_type
    _mm_select_sign_sin<double,cyme::qpx,1>( simd_trait<int,cyme::qpx,1>::register_type __attribute__((unused))swap,
                                             simd_trait<double,cyme::qpx,1>::register_type __attribute__((unused))xmm0,
                                             simd_trait<double,cyme::qpx,1>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Selects the sign (+/-) for sin function. Inputs are:
	- swap int
	- Original input
	- Final calculated sin value
      specialisation double,cyme::qpx,2 reg
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,2>::register_type
    _mm_select_sign_sin<double,cyme::qpx,2>( simd_trait<int,cyme::qpx,2>::register_type __attribute__((unused))swap,
                                             simd_trait<double,cyme::qpx,2>::register_type __attribute__((unused))xmm0,
                                             simd_trait<double,cyme::qpx,2>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Selects the sign (+/-) for sin function. Inputs are:
	- swap int
	- Original input
	- Final calculated sin value
      specialisation double,cyme::qpx,4 reg
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,4>::register_type
    _mm_select_sign_sin<double,cyme::qpx,4>( simd_trait<int,cyme::qpx,4>::register_type __attribute__((unused))swap,
                                             simd_trait<double,cyme::qpx,4>::register_type __attribute__((unused))xmm0,
                                             simd_trait<double,cyme::qpx,4>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Selects the sign (+/-) for cos function. Inputs are:
	- swap int
	- Final calculated cos value
      specialisation double,cyme::qpx,1 reg
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,1>::register_type
    _mm_select_sign_cos<double,cyme::qpx,1>( simd_trait<int,cyme::qpx,1>::register_type __attribute__((unused))swap,
                                             simd_trait<double,cyme::qpx,1>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Selects the sign (+/-) for cos function. Inputs are:
	- swap int
	- Final calculated cos value
      specialisation double,cyme::qpx,2 reg
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,2>::register_type
    _mm_select_sign_cos<double,cyme::qpx,2>( simd_trait<int,cyme::qpx,2>::register_type __attribute__((unused))swap,
                                             simd_trait<double,cyme::qpx,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Selects the sign (+/-) for cos function. Inputs are:
	- swap int
	- Final calculated cos value
      specialisation double,cyme::qpx,4 reg
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,4>::register_type
    _mm_select_sign_cos<double,cyme::qpx,4>( simd_trait<int,cyme::qpx,4>::register_type __attribute__((unused))swap,
                                             simd_trait<double,cyme::qpx,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

#ifdef __FMA__
    /**
      Returns a vector containing the results of performing a fused multiply/add for each corresponding
     set of elements of the given vectors.
       specialisation double,cyme::qpx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,1>::register_type
    _mm_fma<double,cyme::qpx,1>(simd_trait<double,cyme::qpx,1>::register_type xmm0,
                                simd_trait<double,cyme::qpx,1>::register_type xmm1,
                                simd_trait<double,cyme::qpx,1>::register_type xmm2){
        return vec_madd(xmm0, xmm1, xmm2);
    };

    /**
      Returns a vector containing the results of performing a fused multiply/add for each corresponding
     set of elements of the given vectors.
       specialisation double,cyme::qpx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,2>::register_type
    _mm_fma<double,cyme::qpx,2>(simd_trait<double,cyme::qpx,2>::register_type xmm0,
                                simd_trait<double,cyme::qpx,2>::register_type xmm1,
                                simd_trait<double,cyme::qpx,2>::register_type xmm2){
         return simd_trait<double,cyme::qpx,2>::register_type(vec_madd(xmm0.r0,xmm1.r0,xmm2.r0),
                                                              vec_madd(xmm0.r1,xmm1.r1,xmm2.r1));
    };

    /**
      Returns a vector containing the results of performing a fused multiply/add for each corresponding
     set of elements of the given vectors.
       specialisation double,cyme::qpx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,4>::register_type
    _mm_fma<double,cyme::qpx,4>(simd_trait<double,cyme::qpx,4>::register_type xmm0,
                                simd_trait<double,cyme::qpx,4>::register_type xmm1,
                                simd_trait<double,cyme::qpx,4>::register_type xmm2){
         return simd_trait<double,cyme::qpx,4>::register_type(vec_madd(xmm0.r0,xmm1.r0,xmm2.r0),
                                                              vec_madd(xmm0.r1,xmm1.r1,xmm2.r1),
                                                              vec_madd(xmm0.r2,xmm1.r2,xmm2.r2),
                                                              vec_madd(xmm0.r3,xmm1.r3,xmm2.r3));
    };

    /**
      Returns a vector containing the results of performing a negative multiply-subtract
     operation on the given vectors.
       specialisation double,cyme::qpx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::qpx,1>::register_type
    _mm_nfma<double,cyme::qpx,1>(simd_trait<double,cyme::qpx,1>::register_type xmm0,
                                 simd_trait<double,cyme::qpx,1>::register_type xmm1,
                                 simd_trait<double,cyme::qpx,1>::register_type xmm2){
        return vec_nmsub(xmm0, xmm1, xmm2);
    };

    /**
      Returns a vector containing the results of performing a negative multiply-subtract
     operation on the given vectors.
       specialisation double,cyme::qpx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,2>::register_type
    _mm_nfma<double,cyme::qpx,2>(simd_trait<double,cyme::qpx,2>::register_type xmm0,
                                 simd_trait<double,cyme::qpx,2>::register_type xmm1,
                                 simd_trait<double,cyme::qpx,2>::register_type xmm2){
         return simd_trait<double,cyme::qpx,2>::register_type(vec_nmsub(xmm0.r0,xmm1.r0,xmm2.r0),
                                                              vec_nmsub(xmm0.r1,xmm1.r1,xmm2.r1));
    };

    /**
      Returns a vector containing the results of performing a negative multiply-subtract
     operation on the given vectors.
       specialisation double,cyme::qpx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,4>::register_type
    _mm_nfma<double,cyme::qpx,4>(simd_trait<double,cyme::qpx,4>::register_type xmm0,
                                 simd_trait<double,cyme::qpx,4>::register_type xmm1,
                                 simd_trait<double,cyme::qpx,4>::register_type xmm2){
         return simd_trait<double,cyme::qpx,4>::register_type(vec_nmsub(xmm0.r0,xmm1.r0,xmm2.r0),
                                                              vec_nmsub(xmm0.r1,xmm1.r1,xmm2.r1),
                                                              vec_nmsub(xmm0.r2,xmm1.r2,xmm2.r2),
                                                              vec_nmsub(xmm0.r3,xmm1.r3,xmm2.r3));
    };

    /**
      Returns a vector containing the results of performing a multiply-substract operation using the given vectors.
       specialisation double,cyme::qpx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,1>::register_type
    _mm_fms<double,cyme::qpx,1>(simd_trait<double,cyme::qpx,1>::register_type xmm0,
                                simd_trait<double,cyme::qpx,1>::register_type xmm1,
                                simd_trait<double,cyme::qpx,1>::register_type xmm2){
        return vec_msub(xmm0, xmm1, xmm2);
    };

    /**
      Returns a vector containing the results of performing a multiply-substract operation using the given vectors.
       specialisation double,cyme::qpx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,2>::register_type
    _mm_fms<double,cyme::qpx,2>(simd_trait<double,cyme::qpx,2>::register_type xmm0,
                                simd_trait<double,cyme::qpx,2>::register_type xmm1,
                                simd_trait<double,cyme::qpx,2>::register_type xmm2){
         return simd_trait<double,cyme::qpx,2>::register_type(vec_msub(xmm0.r0,xmm1.r0,xmm2.r0),
                                                              vec_msub(xmm0.r1,xmm1.r1,xmm2.r1));
    };

    /**
      Returns a vector containing the results of performing a multiply-substract operation using the given vectors.
       specialisation double,cyme::qpx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::qpx,4>::register_type
    _mm_fms<double,cyme::qpx,4>(simd_trait<double,cyme::qpx,4>::register_type xmm0,
                                simd_trait<double,cyme::qpx,4>::register_type xmm1,
                                simd_trait<double,cyme::qpx,4>::register_type xmm2){
         return simd_trait<double,cyme::qpx,4>::register_type(vec_msub(xmm0.r0,xmm1.r0,xmm2.r0),
                                                              vec_msub(xmm0.r1,xmm1.r1,xmm2.r1),
                                                              vec_msub(xmm0.r2,xmm1.r2,xmm2.r2),
                                                              vec_msub(xmm0.r3,xmm1.r3,xmm2.r3));
    };


    /**
     Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
       specialisation double,cyme::qpx,1 regs
    */
    template<>
    forceinline simd_trait<double,cyme::qpx,1>::register_type
    _mm_nfms<double,cyme::qpx,1>(simd_trait<double,cyme::qpx,1>::register_type xmm0,
                                 simd_trait<double,cyme::qpx,1>::register_type xmm1,
                                 simd_trait<double,cyme::qpx,1>::register_type xmm2){
        return vec_nmadd(xmm0, xmm1, xmm2);
    };

    /**
     Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
       specialisation double,cyme::qpx,2 regs
    */
    template<>
    forceinline simd_trait<double,cyme::qpx,2>::register_type
    _mm_nfms<double,cyme::qpx,2>(simd_trait<double,cyme::qpx,2>::register_type xmm0,
                                 simd_trait<double,cyme::qpx,2>::register_type xmm1,
                                 simd_trait<double,cyme::qpx,2>::register_type xmm2){
         return simd_trait<double,cyme::qpx,2>::register_type(vec_nmadd(xmm0.r0,xmm1.r0,xmm2.r0),
                                                              vec_nmadd(xmm0.r1,xmm1.r1,xmm2.r1));
    };

    /**
     Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
       specialisation double,cyme::qpx,4 regs
    */
    template<>
    forceinline simd_trait<double,cyme::qpx,4>::register_type
    _mm_nfms<double,cyme::qpx,4>(simd_trait<double,cyme::qpx,4>::register_type xmm0,
                                 simd_trait<double,cyme::qpx,4>::register_type xmm1,
                                 simd_trait<double,cyme::qpx,4>::register_type xmm2){
         return simd_trait<double,cyme::qpx,4>::register_type(vec_nmadd(xmm0.r0,xmm1.r0,xmm2.r0),
                                                              vec_nmadd(xmm0.r1,xmm1.r1,xmm2.r1),
                                                              vec_nmadd(xmm0.r2,xmm1.r2,xmm2.r2),
                                                              vec_nmadd(xmm0.r3,xmm1.r3,xmm2.r3));
    };
#endif //__FMA__
} //end namespace

#endif //CYME_SIMD_WRAPPER_QPX_IPP
