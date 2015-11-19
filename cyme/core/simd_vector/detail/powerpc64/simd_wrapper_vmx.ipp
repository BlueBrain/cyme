/*
* Cyme - simd_wrapper_vmx.ipp, Copyright (c), 2014,
* Timothee Ewart - Swiss Federal Institute of technology in Lausanne,
* timothee.ewart@epfl.ch,
* Kai Langen,
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
* @file cyme/core/simd_vector/detail/powerpc64/simd_wrapper_vmx.ipp
* Final specialisation for math functions and vmx technology
*/
#ifndef CYME_SIMD_WRAPPER_VMX_IPP
#define CYME_SIMD_WRAPPER_VMX_IPP

#define vec_ctd __builtin_vsx_xvcvsxwdp
#define vec_cdts __builtin_vsx_xvcvdpsxws

extern "C" vector float expf4(vector float vx);// link to the fortran one
extern "C" vector float logf4(vector float vx);// link to the fortran one
extern "C" vector double expd4(vector double vx);// link to the fortran one
extern "C" vector double logd4(vector double vx);// link to the fortran one

namespace cyme{

    /**
      Rounds xmm0 up to the next even integer.
      Specialisation int, cyme::vmx, 1 reg
    */
    template<>
    forceinline simd_trait<int,cyme::vmx,1>::register_type
    _mm_round_up_even<cyme::vmx,1>( simd_trait<int,cyme::vmx,1>::register_type xmm0){
	xmm0 = vec_add(xmm0,vec_splats(1));
	xmm0 = vec_and(xmm0,vec_splats(~1));
	return xmm0;
    }

    /**
      Rounds xmm0 up to the next even integer.
      Specialisation int, cyme::vmx, 2 reg
    */
    template<>
    forceinline simd_trait<int,cyme::vmx,2>::register_type
    _mm_round_up_even<cyme::vmx,2>( simd_trait<int,cyme::vmx,2>::register_type xmm0){
	vector int one = vec_splats(1);
	vector int inv_one = vec_splats(~1);
	xmm0.r0 = vec_add(xmm0.r0,one);
	xmm0.r1 = vec_add(xmm0.r1,one);
	xmm0.r0 = vec_and(xmm0.r0,inv_one);
	xmm0.r1 = vec_and(xmm0.r1,inv_one);
        return simd_trait<int,cyme::vmx,2>::register_type(xmm0.r0,
							  xmm0.r1);
    }

    /**
      Rounds xmm0 up to the next even integer.
      Specialisation int, cyme::vmx, 4 reg
    */
    template<>
    forceinline simd_trait<int,cyme::vmx,4>::register_type
    _mm_round_up_even<cyme::vmx,4>( simd_trait<int,cyme::vmx,4>::register_type xmm0){
	vector int one = vec_splats(1);
	vector int inv_one = vec_splats(~1);
	xmm0.r0 = vec_add(xmm0.r0,one);
	xmm0.r1 = vec_add(xmm0.r1,one);
	xmm0.r2 = vec_add(xmm0.r2,one);
	xmm0.r3 = vec_add(xmm0.r3,one);
	xmm0.r0 = vec_and(xmm0.r0,inv_one);
	xmm0.r1 = vec_and(xmm0.r1,inv_one);
	xmm0.r2 = vec_and(xmm0.r2,inv_one);
	xmm0.r3 = vec_and(xmm0.r3,inv_one);
        return simd_trait<int,cyme::vmx,4>::register_type(xmm0.r0,xmm0.r1,
							  xmm0.r2,xmm0.r3);
    }

    /**
       Load a single-precision (32-bit) floating-point element from cyme into lower element of dst.
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_single_load<float,cyme::vmx,1>(const simd_trait<float,cyme::vmx,1>::value_type b){
        return vec_vsx_ld(0, (vector float*)&b);
    }

    /**
       store a single-precision (32-bit) floating-point element from register lower element to cyme.
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::value_type
    _mm_single_store<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0,
                                        simd_trait<float,cyme::vmx,1>::pointer b){
       vec_vsx_st(xmm0, 0, (vector float*)b);
       return *b;
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_load1<float,cyme::vmx,1>(const simd_trait<float,cyme::vmx,1>::value_type &a){
       return vec_splats(a);
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_load1<float,cyme::vmx,2>(const simd_trait<float,cyme::vmx,2>::value_type &a){
        return simd_trait<float,cyme::vmx,2>::register_type(vec_splats(a),vec_splats(a));
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_load1<float,cyme::vmx,4>(const simd_trait<float,cyme::vmx,4>::value_type &a){
        return simd_trait<float,cyme::vmx,4>::register_type(vec_splats(a),vec_splats(a),
							    vec_splats(a),vec_splats(a));
    }

    /**
      Loads a vector from the given cyme address.
       specialisation float,cyme::vmx,1 regs
    */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_load<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::const_pointer a){
        return vec_vsx_ld(0, (vector float*)a);
    }

    /**
      Loads a vector from the given cyme address.
       specialisation float,cyme::vmx,2 regs
    */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_load<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::const_pointer a){
        return simd_trait<float,cyme::vmx,2>::register_type(vec_vsx_ld(0,(vector float*)a),
							    vec_vsx_ld(16,(vector float*)a));
    }

    /**
      Loads a vector from the given cyme address.
       specialisation float,cyme::vmx,4 regs
    */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_load<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::const_pointer a){
        return simd_trait<float,cyme::vmx,4>::register_type(vec_vsx_ld(0,(vector float*)a),
							    vec_vsx_ld(16,(vector float*)a),
							    vec_vsx_ld(32,(vector float*)a),
							    vec_vsx_ld(48,(vector float*)a));
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation float,cyme::vmx,1 regs
    */
    template<>
    forceinline void
    _mm_store<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0,
                                 simd_trait<float,cyme::vmx,1>::pointer  a){
        vec_vsx_st(xmm0,0,(vector float*)a);
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation float,cyme::vmx,2 regs
    */
    template<>
    forceinline void
    _mm_store<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0,
                                 simd_trait<float,cyme::vmx,2>::pointer a){
        vec_vsx_st(xmm0.r0,0,(vector float*)a);
	vec_vsx_st(xmm0.r1,16,(vector float*)a);
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation float,cyme::vmx,4 regs
    */
    template<>
    forceinline void
    _mm_store<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0,
                                 simd_trait<float,cyme::vmx,4>::pointer a){
        vec_vsx_st(xmm0.r0,0,(vector float*)a);
	vec_vsx_st(xmm0.r1,16,(vector float*)a);
	vec_vsx_st(xmm0.r2,32,(vector float*)a);
	vec_vsx_st(xmm0.r3,48,(vector float*)a);
    }

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_mul<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0,
                               simd_trait<float,cyme::vmx,1>::register_type xmm1){
        return vec_mul(xmm0, xmm1);
    }

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_mul<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0,
                               simd_trait<float,cyme::vmx,2>::register_type xmm1){
        return simd_trait<float,cyme::vmx,2>::register_type(vec_mul(xmm0.r0,xmm1.r0),
							    vec_mul(xmm0.r1,xmm1.r1));
    }

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_mul<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0,
                               simd_trait<float,cyme::vmx,4>::register_type xmm1){
        return simd_trait<float,cyme::vmx,4>::register_type(vec_mul(xmm0.r0,xmm1.r0),
							    vec_mul(xmm0.r1,xmm1.r1),
							    vec_mul(xmm0.r2,xmm1.r2),
							    vec_mul(xmm0.r3,xmm1.r3));
    }

    /**
       Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_div<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0,
                               simd_trait<float,cyme::vmx,1>::register_type xmm1){
        return vec_div(xmm0,xmm1);
    }

    /**
       Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_div<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0,
                               simd_trait<float,cyme::vmx,2>::register_type xmm1){
        return simd_trait<float,cyme::vmx,2>::register_type(vec_div(xmm0.r0,xmm1.r0),
							    vec_div(xmm0.r1,xmm1.r1));
    }

    /**
       Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_div<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0,
                               simd_trait<float,cyme::vmx,4>::register_type xmm1){
        return simd_trait<float,cyme::vmx,4>::register_type(vec_div(xmm0.r0,xmm1.r0),
							    vec_div(xmm0.r1,xmm1.r1),
							    vec_div(xmm0.r2,xmm1.r2),
							    vec_div(xmm0.r3,xmm1.r3));
    }

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_add<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0,
                               simd_trait<float,cyme::vmx,1>::register_type xmm1){
        return vec_add(xmm0,xmm1);
    }

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_add<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0,
                               simd_trait<float,cyme::vmx,2>::register_type xmm1){
        return simd_trait<float,cyme::vmx,2>::register_type(vec_add(xmm0.r0,xmm1.r0),
							    vec_add(xmm0.r1,xmm1.r1));
    }

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_add<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0,
                               simd_trait<float,cyme::vmx,4>::register_type xmm1){
        return simd_trait<float,cyme::vmx,4>::register_type(vec_add(xmm0.r0,xmm1.r0),
							    vec_add(xmm0.r1,xmm1.r1),
							    vec_add(xmm0.r2,xmm1.r2),
							    vec_add(xmm0.r3,xmm1.r3));
    }

    /**
      Returns a vector containing the result of subtracting each element of b
     from the corresponding element of a.
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_sub<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0,
                               simd_trait<float,cyme::vmx,1>::register_type xmm1){
        return vec_sub(xmm0,xmm1);
    }

    /**
      Returns a vector containing the result of subtracting each element of b
     from the corresponding element of a.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_sub<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0,
                               simd_trait<float,cyme::vmx,2>::register_type xmm1){
	return simd_trait<float,cyme::vmx,2>::register_type(vec_sub(xmm0.r0,xmm1.r0),
							    vec_sub(xmm0.r1,xmm1.r1));
    }

    /**
      Returns a vector containing the result of subtracting each element of b
     from the corresponding element of a.
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_sub<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0,
                               simd_trait<float,cyme::vmx,4>::register_type xmm1){
	return simd_trait<float,cyme::vmx,4>::register_type(vec_sub(xmm0.r0,xmm1.r0),
							    vec_sub(xmm0.r1,xmm1.r1),
							    vec_sub(xmm0.r2,xmm1.r2),
							    vec_sub(xmm0.r3,xmm1.r3));
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_exp<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0){
	return expf4(xmm0);
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_exp<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0){
	return simd_trait<float,cyme::vmx,2>::register_type(expf4(xmm0.r0),expf4(xmm0.r1));
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_exp<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0){
	return simd_trait<float,cyme::vmx,4>::register_type(expf4(xmm0.r0),expf4(xmm0.r1),
							    expf4(xmm0.r2),expf4(xmm0.r3));
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_log<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0){
	return logf4(xmm0);
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_log<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0){
	return simd_trait<float,cyme::vmx,2>::register_type(logf4(xmm0.r0),logf4(xmm0.r1));
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_log<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0){
	return simd_trait<float,cyme::vmx,4>::register_type(logf4(xmm0.r0),logf4(xmm0.r1),
							    logf4(xmm0.r2),logf4(xmm0.r3));
    }

    /**
      Returns a vector containing estimates of the reciprocals of the corresponding elements of the given vector.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x) / (1/x) | ≤ 1/256
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_rec<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0){
        return vec_re(xmm0);
    }

    /**
      Returns a vector containing estimates of the reciprocals of the corresponding elements of the given vector.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x) / (1/x) | ≤ 1/256
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_rec<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0){
        return simd_trait<float,cyme::vmx,2>::register_type(vec_re(xmm0.r0),
							    vec_re(xmm0.r1));
    }

    /**
      Returns a vector containing estimates of the reciprocals of the corresponding elements of the given vector.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x) / (1/x) | ≤ 1/256
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_rec<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0){
        return simd_trait<float,cyme::vmx,4>::register_type(vec_re(xmm0.r0),
							    vec_re(xmm0.r1),
							    vec_re(xmm0.r2),
							    vec_re(xmm0.r3));
    }

    /**
      Compute 1/recsqrt (32-bit) floating point elements in xmm0 to packed single-precision
     (32-bit) floating-point elements, and store the results in dst.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
       of a and r is the value of the corresponding element of the result value:
     | (r-1/x^0.5) / (1/x^0.5) | ≤ 1/256
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_rsqrt<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0){
        return vec_rsqrte(xmm0);
    }

    /**
      Compute 1/recsqrt (32-bit) floating point elements in xmm0 to packed single-precision
     (32-bit) floating-point elements, and store the results in dst.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
       of a and r is the value of the corresponding element of the result value:
     | (r-1/x^0.5) / (1/x^0.5) | ≤ 1/256
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_rsqrt<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0){
        return simd_trait<float,cyme::vmx,2>::register_type(vec_rsqrte(xmm0.r0),
                                                            vec_rsqrte(xmm0.r1));
    }

    /**
      Compute 1/recsqrt (32-bit) floating point elements in xmm0 to packed single-precision
     (32-bit) floating-point elements, and store the results in dst.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
       of a and r is the value of the corresponding element of the result value:
     | (r-1/x^0.5) / (1/x^0.5) | ≤ 1/256
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_rsqrt<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0){
        return simd_trait<float,cyme::vmx,4>::register_type(vec_rsqrte(xmm0.r0),
                                                            vec_rsqrte(xmm0.r1),
                                                            vec_rsqrte(xmm0.r2),
                                                            vec_rsqrte(xmm0.r3));
    }

    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_neg<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0){
	vector float mask = (vector float)vec_splats(0x80000000);
	return vec_xor(xmm0,mask);
	//return vec_xor(xmm0, vec_splats((float)-0.));
    }

    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_neg<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0){
	vector float mask = (vector float)vec_splats(0x80000000);
	return simd_trait<float,cyme::vmx,2>::register_type(vec_xor(xmm0.r0,mask),
							    vec_xor(xmm0.r1,mask));

    }

    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_neg<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0){
	vector float mask = (vector float)vec_splats(0x80000000);
	return simd_trait<float,cyme::vmx,4>::register_type(vec_xor(xmm0.r0,mask),
							    vec_xor(xmm0.r1,mask),
							    vec_xor(xmm0.r2,mask),
							    vec_xor(xmm0.r3,mask));
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed single-precision (32-bit) floating-point elements,
     and store the results in dst.
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_cast<float,cyme::vmx,1>(simd_trait<int,cyme::vmx,1>::register_type xmm0){
	return vec_ctf(xmm0,0);
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed single-precision (32-bit) floating-point elements,
     and store the results in dst.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_cast<float,cyme::vmx,2>(simd_trait<int,cyme::vmx,2>::register_type xmm0){
        return simd_trait<float,cyme::vmx,2>::register_type(vec_ctf(xmm0.r0,0),
							    vec_ctf(xmm0.r1,0));
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed single-precision (32-bit) floating-point elements,
     and store the results in dst.
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_cast<float,cyme::vmx,4>(simd_trait<int,cyme::vmx,4>::register_type xmm0){
        return simd_trait<float,cyme::vmx,4>::register_type(vec_ctf(xmm0.r0,0),
							    vec_ctf(xmm0.r1,0),
							    vec_ctf(xmm0.r2,0),
							    vec_ctf(xmm0.r3,0));
    }

    /**
      Returns a vector containing the largest representable floating-point integral
     values less than or equal to the values of the corresponding elements of the given vector.
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<int,cyme::vmx,1>::register_type
    _mm_floor<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0){
	return vec_cts(vec_floor(xmm0),0);
}

    /**
      Returns a vector containing the largest representable floating-point integral
     values less than or equal to the values of the corresponding elements of the given vector.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<int,cyme::vmx,2>::register_type
    _mm_floor<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0){
        return simd_trait<int,cyme::vmx,2>::register_type(vec_cts(vec_floor(xmm0.r0),0),
							  vec_cts(vec_floor(xmm0.r1),0));
}

    /**
      Returns a vector containing the largest representable floating-point integral
     values less than or equal to the values of the corresponding elements of the given vector.
       specialisation float,cyme::vmx,4 regs
     */

    template<>
    forceinline simd_trait<int,cyme::vmx,4>::register_type
    _mm_floor<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0){
        return simd_trait<int,cyme::vmx,4>::register_type(vec_cts(vec_floor(xmm0.r0),0),
							  vec_cts(vec_floor(xmm0.r1),0),
							  vec_cts(vec_floor(xmm0.r2),0),
							  vec_cts(vec_floor(xmm0.r3),0));
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_twok<float,cyme::vmx,1>(simd_trait<int,cyme::vmx,1>::register_type xmm0){
        return vec_expte(vec_ctf(xmm0,0));
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_twok<float,cyme::vmx,2>(simd_trait<int,cyme::vmx,2>::register_type xmm0){
        return simd_trait<float,cyme::vmx,2>::register_type(vec_expte(vec_ctf(xmm0.r0,0)),
							    vec_expte(vec_ctf(xmm0.r1,0)));
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_twok<float,cyme::vmx,4>(simd_trait<int,cyme::vmx,4>::register_type xmm0){
        return simd_trait<float,cyme::vmx,4>::register_type(vec_expte(vec_ctf(xmm0.r0,0)),
							    vec_expte(vec_ctf(xmm0.r1,0)),
							    vec_expte(vec_ctf(xmm0.r2,0)),
							    vec_expte(vec_ctf(xmm0.r3,0)));
    }

    /**
      Extract the exponent of floating-point exponent (32-bit) elements and store the results in dst.
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_ge<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0){
	vector signed int tmp = (vector signed int)xmm0;
	tmp = vec_sr(tmp,vec_splats((unsigned int)23));
	tmp = vec_sub(tmp, vec_splats(127));
	return vec_ctf(tmp,0);
    }

    /**
      Extract the exponent of floating-point exponent (32-bit) elements and store the results in dst.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_ge<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0){
	vector signed int tmp0 = (vector signed int)xmm0.r0;
	vector signed int tmp1 = (vector signed int)xmm0.r1;
	tmp0 = vec_sr(tmp0,vec_splats((unsigned int)23));
	tmp1 = vec_sr(tmp1,vec_splats((unsigned int)23));
	tmp0 = vec_sub(tmp0, vec_splats(127));
	tmp1 = vec_sub(tmp1, vec_splats(127));
	return simd_trait<float,cyme::vmx,2>::register_type(vec_ctf(tmp0,0),
							    vec_ctf(tmp1,0));
    }

    /**
      Extract the exponent of floating-point exponent (32-bit) elements and store the results in dst.
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_ge<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0){
	vector signed int tmp0 =(vector signed int)xmm0.r0;
	vector signed int tmp1 =(vector signed int)xmm0.r1;
	vector signed int tmp2 =(vector signed int)xmm0.r2;
	vector signed int tmp3 =(vector signed int)xmm0.r3;
	tmp0 = vec_sr(tmp0,vec_splats((unsigned int)23));
	tmp1 = vec_sr(tmp1,vec_splats((unsigned int)23));
	tmp2 = vec_sr(tmp2,vec_splats((unsigned int)23));
	tmp3 = vec_sr(tmp3,vec_splats((unsigned int)23));
	tmp0 = vec_sub(tmp0,vec_splats(127));
	tmp1 = vec_sub(tmp1,vec_splats(127));
	tmp2 = vec_sub(tmp2,vec_splats(127));
	tmp3 = vec_sub(tmp3,vec_splats(127));
	return simd_trait<float,cyme::vmx,4>::register_type(vec_ctf(tmp0,0),
							    vec_ctf(tmp1,0),
							    vec_ctf(tmp2,0),
							    vec_ctf(tmp3,0));
    }

    /**
      Extract the fraction of floating-point exponent (32-bit) elements and store the results in dst.
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_gf<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0){
	vector signed int tmp =(vector signed int)xmm0;
	tmp = vec_and(tmp, vec_splats((signed int)0x7fffff));
	tmp = vec_add(tmp, vec_splats((signed int)0x3f800000));
	return (vector float)tmp;
    }

    /**
      Extract the fraction of floating-point exponent (32-bit) elements and store the results in dst.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_gf<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0){
	vector signed int tmp0 = (vector signed int)xmm0.r0;
	vector signed int tmp1 = (vector signed int)xmm0.r1;
	tmp0 = vec_and(tmp0, vec_splats((signed int)0x7fffff));
	tmp1 = vec_and(tmp1, vec_splats((signed int)0x7fffff));
	tmp0 = vec_add(tmp0, vec_splats((signed int)0x3f800000));
	tmp1 = vec_add(tmp1, vec_splats((signed int)0x3f800000));
	return simd_trait<float,cyme::vmx,2>::register_type((vector float)tmp0,
							    (vector float)tmp1);
    }

    /**
      Extract the fraction of floating-point exponent (32-bit) elements and store the results in dst.
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_gf<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0){
	vector signed int tmp0 = (vector signed int)xmm0.r0;
	vector signed int tmp1 = (vector signed int)xmm0.r1;
	vector signed int tmp2 = (vector signed int)xmm0.r2;
	vector signed int tmp3 = (vector signed int)xmm0.r3;
	tmp0 = vec_and(tmp0, vec_splats((signed int)0x7fffff));
	tmp1 = vec_and(tmp1, vec_splats((signed int)0x7fffff));
	tmp2 = vec_and(tmp2, vec_splats((signed int)0x7fffff));
	tmp3 = vec_and(tmp3, vec_splats((signed int)0x7fffff));
	tmp0 = vec_add(tmp0, vec_splats((signed int)0x3f800000));
	tmp1 = vec_add(tmp1, vec_splats((signed int)0x3f800000));
	tmp2 = vec_add(tmp2, vec_splats((signed int)0x3f800000));
	tmp3 = vec_add(tmp3, vec_splats((signed int)0x3f800000));
	return simd_trait<float,cyme::vmx,4>::register_type((vector float)tmp0,
							    (vector float)tmp1,
							    (vector float)tmp2,
							    (vector float)tmp3);
    }

    /**
      Computes the absolute value for single-precision (32-bit) floating point elements and stores
      the result in dst.
      specialisation float,cyme::vmx,1 reg
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_fabs<float,cyme::vmx,1>( simd_trait<float,cyme::vmx,1>::register_type xmm0){
	return vec_abs(xmm0);
    }

    /**
      Computes the absolute value for single-precision (32-bit) floating point elements and stores
      the result in dst.
      specialisation float,cyme::vmx,2 reg
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_fabs<float,cyme::vmx,2>( simd_trait<float,cyme::vmx,2>::register_type xmm0){
	return simd_trait<float,cyme::vmx,2>::register_type(vec_abs(xmm0.r0),
							    vec_abs(xmm0.r1));
    }

    /**
      Computes the absolute value for single-precision (32-bit) floating point elements and stores
      the result in dst.
      specialisation float,cyme::vmx,4 reg
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_fabs<float,cyme::vmx,4>( simd_trait<float,cyme::vmx,4>::register_type xmm0){
	return simd_trait<float,cyme::vmx,4>::register_type(vec_abs(xmm0.r0),
							    vec_abs(xmm0.r1),
							    vec_abs(xmm0.r2),
							    vec_abs(xmm0.r3));
    }

    /**
      Selects the polynomial for sin function. Inputs are:
	- Selector int
	- Option one
	- Option two
      specialisation float,cyme::vmx, 1 reg
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_select_poly<float,cyme::vmx,1>( simd_trait<int,cyme::vmx,1>::register_type sel,
                                         simd_trait<float,cyme::vmx,1>::register_type xmm0,
                                         simd_trait<float,cyme::vmx,1>::register_type xmm1){
	vector int mask = vec_splats(2);
	vector int zero = vec_splats(0);
	sel = vec_and(sel,mask);
	sel = (vector int)vec_cmpeq(sel,zero);

	xmm0 = vec_andc(xmm0,(vector float)sel);
	xmm1 = vec_and(xmm1,(vector float)sel);
	return vec_add(xmm0,xmm1);
    }

    /**
      Selects the polynomial for sin function. Inputs are:
	- Selector int
	- Option one
	- Option two
      specialisation float,cyme::vmx, 2 reg
     */
   template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_select_poly<float,cyme::vmx,2>( simd_trait<int,cyme::vmx,2>::register_type sel,
                                         simd_trait<float,cyme::vmx,2>::register_type xmm0,
                                         simd_trait<float,cyme::vmx,2>::register_type xmm1){
	vector int mask = vec_splats(2);
	vector int zero = vec_splats(0);
	sel.r0 = vec_and(sel.r0,mask);
	sel.r1 = vec_and(sel.r1,mask);
	sel.r0 = (vector int)vec_cmpeq(sel.r0,zero);
	sel.r1 = (vector int)vec_cmpeq(sel.r1,zero);

	xmm0.r0 = vec_andc(xmm0.r0,(vector float)sel.r0);
	xmm0.r1 = vec_andc(xmm0.r1,(vector float)sel.r1);
	xmm1.r0 = vec_and(xmm1.r0,(vector float)sel.r0);
	xmm1.r1 = vec_and(xmm1.r1,(vector float)sel.r1);
	return simd_trait<float,cyme::vmx,2>::register_type(vec_add(xmm0.r0,xmm1.r0),
							    vec_add(xmm0.r1,xmm1.r1));
    }

    /**
      Selects the polynomial for sin function. Inputs are:
	- Selector int
	- Option one
	- Option two
      specialisation float,cyme::vmx, 4 reg
     */
   template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_select_poly<float,cyme::vmx,4>( simd_trait<int,cyme::vmx,4>::register_type sel,
                                         simd_trait<float,cyme::vmx,4>::register_type  xmm0,
                                         simd_trait<float,cyme::vmx,4>::register_type xmm1){
	vector int mask = vec_splats(2);
	vector int zero = vec_splats(0);
	sel.r0 = vec_and(sel.r0,mask);
	sel.r1 = vec_and(sel.r1,mask);
	sel.r2 = vec_and(sel.r2,mask);
	sel.r3 = vec_and(sel.r3,mask);
	sel.r0 = (vector int)vec_cmpeq(sel.r0,zero);
	sel.r1 = (vector int)vec_cmpeq(sel.r1,zero);
	sel.r2 = (vector int)vec_cmpeq(sel.r2,zero);
	sel.r3 = (vector int)vec_cmpeq(sel.r3,zero);

	xmm0.r0 = vec_andc(xmm0.r0,(vector float)sel.r0);
	xmm0.r1 = vec_andc(xmm0.r1,(vector float)sel.r1);
	xmm0.r2 = vec_andc(xmm0.r2,(vector float)sel.r2);
	xmm0.r3 = vec_andc(xmm0.r3,(vector float)sel.r3);
	xmm1.r0 = vec_and(xmm1.r0,(vector float)sel.r0);
	xmm1.r1 = vec_and(xmm1.r1,(vector float)sel.r1);
	xmm1.r2 = vec_and(xmm1.r2,(vector float)sel.r2);
	xmm1.r3 = vec_and(xmm1.r3,(vector float)sel.r3);
	return simd_trait<float,cyme::vmx,4>::register_type(vec_add(xmm0.r0,xmm1.r0),
							    vec_add(xmm0.r1,xmm1.r1),
							    vec_add(xmm0.r2,xmm1.r2),
							    vec_add(xmm0.r3,xmm1.r3));
    }

    /**
      Selects the sign (+/-) for sin function. Inputs are:
	- swap int
	- Original input
	- Final calculated sin value
      specialisation float,cyme::vmx,1 reg
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_select_sign_sin<float,cyme::vmx,1>( simd_trait<int,cyme::vmx,1>::register_type swap,
                                            simd_trait<float,cyme::vmx,1>::register_type xmm0,
                                            simd_trait<float,cyme::vmx,1>::register_type xmm1){
	vector float mask = (vector float)vec_splats(0x80000000);
	vector int four = vec_splats(4);
	/* extract the sign bit (upper one) from original val */
	xmm0 = vec_and(xmm0, mask);

	/* get the swap sign flag */
	swap = vec_and(swap, four);
	swap = vec_sl(swap, vec_splats((unsigned int)29));

	/* update the sign of the final value*/
	xmm1 = vec_xor(xmm1, (vector float)swap);
	xmm1 = vec_xor(xmm1, xmm0);
	return xmm1;
    }

    /**
      Selects the sign (+/-) for sin function. Inputs are:
	- swap int
	- Original input
	- Final calculated sin value
      specialisation float,cyme::vmx,2 reg
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_select_sign_sin<float,cyme::vmx,2>( simd_trait<int,cyme::vmx,2>::register_type swap,
                                            simd_trait<float,cyme::vmx,2>::register_type xmm0,
                                            simd_trait<float,cyme::vmx,2>::register_type xmm1){
	vector float mask = (vector float)vec_splats(0x80000000);
	vector int four = vec_splats(4);
	/* extract the sign bit (upper one) from original val */
	xmm0.r0 = vec_and(xmm0.r0, mask);
	xmm0.r1 = vec_and(xmm0.r1, mask);

	/* get the swap sign flag */
	swap.r0 = vec_and(swap.r0, four);
	swap.r1 = vec_and(swap.r1, four);
	swap.r0 = vec_sl(swap.r0, vec_splats((unsigned int)29));
	swap.r1 = vec_sl(swap.r1, vec_splats((unsigned int)29));

	/* update the sign of the final value*/
	xmm1.r0 = vec_xor(xmm1.r0, (vector float)swap.r0);
	xmm1.r1 = vec_xor(xmm1.r1, (vector float)swap.r1);
	xmm1.r0 = vec_xor(xmm1.r0, xmm0.r0);
	xmm1.r1 = vec_xor(xmm1.r1, xmm0.r1);
	return simd_trait<float,cyme::vmx,2>::register_type(xmm1.r0,xmm1.r1);
    }

    /**
      Selects the sign (+/-) for sin function. Inputs are:
	- swap int
	- Original input
	- Final calculated sin value
      specialisation float,cyme::vmx,4 reg
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_select_sign_sin<float,cyme::vmx,4>( simd_trait<int,cyme::vmx,4>::register_type swap,
                                            simd_trait<float,cyme::vmx,4>::register_type xmm0,
                                            simd_trait<float,cyme::vmx,4>::register_type xmm1){
	vector float mask = (vector float)vec_splats(0x80000000);
	vector int four = vec_splats(4);
	/* extract the sign bit (upper one) from original val */
	xmm0.r0 = vec_and(xmm0.r0, mask);
	xmm0.r1 = vec_and(xmm0.r1, mask);
	xmm0.r2 = vec_and(xmm0.r2, mask);
	xmm0.r3 = vec_and(xmm0.r3, mask);

	/* get the swap sign flag */
	swap.r0 = vec_and(swap.r0, four);
	swap.r1 = vec_and(swap.r1, four);
	swap.r2 = vec_and(swap.r2, four);
	swap.r3 = vec_and(swap.r3, four);
	swap.r0 = vec_sl(swap.r0, vec_splats((unsigned int)29));
	swap.r1 = vec_sl(swap.r1, vec_splats((unsigned int)29));
	swap.r2 = vec_sl(swap.r2, vec_splats((unsigned int)29));
	swap.r3 = vec_sl(swap.r3, vec_splats((unsigned int)29));

	/* update the sign of the final value*/
	xmm1.r0 = vec_xor(xmm1.r0, (vector float)swap.r0);
	xmm1.r1 = vec_xor(xmm1.r1, (vector float)swap.r1);
	xmm1.r2 = vec_xor(xmm1.r2, (vector float)swap.r2);
	xmm1.r3 = vec_xor(xmm1.r3, (vector float)swap.r3);
	xmm1.r0 = vec_xor(xmm1.r0, xmm0.r0);
	xmm1.r1 = vec_xor(xmm1.r1, xmm0.r1);
	xmm1.r2 = vec_xor(xmm1.r2, xmm0.r2);
	xmm1.r3 = vec_xor(xmm1.r3, xmm0.r3);
	return simd_trait<float,cyme::vmx,4>::register_type(xmm1.r0,xmm1.r1,
							     xmm1.r2,xmm1.r3);
    }

    /**
      Selects the sign (+/-) for cos function. Inputs are:
	- swap int
	- Final calculated cos value
      specialisation float,cyme::vmx,1 reg
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_select_sign_cos<float,cyme::vmx,1>( simd_trait<int,cyme::vmx,1>::register_type swap,
                                            simd_trait<float,cyme::vmx,1>::register_type xmm0){
	vector int four = vec_splats(4);

	/* get the swap sign flag */
	swap = vec_andc(four,swap);
	swap = vec_sl(swap, vec_splats((unsigned int)29));

	/* update the sign of the final value*/
	xmm0 = vec_xor(xmm0, (vector float)swap);
	return xmm0;
    }

    /**
      Selects the sign (+/-) for cos function. Inputs are:
	- swap int
	- Final calculated cos value
      specialisation float,cyme::vmx,2 reg
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_select_sign_cos<float,cyme::vmx,2>( simd_trait<int,cyme::vmx,2>::register_type swap,
                                            simd_trait<float,cyme::vmx,2>::register_type xmm0){
	vector int four = vec_splats(4);

	/* get the swap sign flag */
	swap.r0 = vec_andc(four,swap.r0);
	swap.r1 = vec_andc(four,swap.r1);
	swap.r0 = vec_sl(swap.r0, vec_splats((unsigned int)29));
	swap.r1 = vec_sl(swap.r1, vec_splats((unsigned int)29));

	/* update the sign of the final value*/
	xmm0.r0 = vec_xor(xmm0.r0, (vector float)swap.r0);
	xmm0.r1 = vec_xor(xmm0.r1, (vector float)swap.r1);
	return simd_trait<float,cyme::vmx,2>::register_type (xmm0.r0,xmm0.r1);
    }

    /**
      Selects the sign (+/-) for cos function. Inputs are:
	- swap int
	- Final calculated cos value
      specialisation float,cyme::vmx,4 reg
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_select_sign_cos<float,cyme::vmx,4>( simd_trait<int,cyme::vmx,4>::register_type swap,
                                            simd_trait<float,cyme::vmx,4>::register_type xmm0){
	vector int four = vec_splats(4);

	/* get the swap sign flag */
	swap.r0 = vec_andc(four,swap.r0);
	swap.r1 = vec_andc(four,swap.r1);
	swap.r2 = vec_andc(four,swap.r2);
	swap.r3 = vec_andc(four,swap.r3);
	swap.r0 = vec_sl(swap.r0, vec_splats((unsigned int)29));
	swap.r1 = vec_sl(swap.r1, vec_splats((unsigned int)29));
	swap.r2 = vec_sl(swap.r2, vec_splats((unsigned int)29));
	swap.r3 = vec_sl(swap.r3, vec_splats((unsigned int)29));

	/* update the sign of the final value*/
	xmm0.r0 = vec_xor(xmm0.r0, (vector float)swap.r0);
	xmm0.r1 = vec_xor(xmm0.r1, (vector float)swap.r1);
	xmm0.r2 = vec_xor(xmm0.r2, (vector float)swap.r2);
	xmm0.r3 = vec_xor(xmm0.r3, (vector float)swap.r3);
	return simd_trait<float,cyme::vmx,4>::register_type (xmm0.r0,xmm0.r1,
							     xmm0.r2,xmm0.r3);
    }

#ifdef __FMA__
    /**
      Returns a vector containing the results of performing a fused multiply/add
     for each corresponding of a set of elements of the given vectors.
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_fma<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0,
                               simd_trait<float,cyme::vmx,1>::register_type xmm1,
                               simd_trait<float,cyme::vmx,1>::register_type xmm2){
	return vec_madd(xmm0,xmm1,xmm2);
    }

    /**
      Returns a vector containing the results of performing a fused multiply/add
     for each corresponding of a set of elements of the given vectors.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_fma<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0,
                               simd_trait<float,cyme::vmx,2>::register_type xmm1,
                               simd_trait<float,cyme::vmx,2>::register_type xmm2){
        return simd_trait<float,cyme::vmx,2>::register_type(vec_madd(xmm0.r0,xmm1.r0,xmm2.r0),
							    vec_madd(xmm0.r1,xmm1.r1,xmm2.r1));
    }

    /**
      Returns a vector containing the results of performing a fused multiply/add
     for each corresponding of a set of elements of the given vectors.
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_fma<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0,
                               simd_trait<float,cyme::vmx,4>::register_type xmm1,
                               simd_trait<float,cyme::vmx,4>::register_type xmm2){
        return simd_trait<float,cyme::vmx,4>::register_type(vec_madd(xmm0.r0,xmm1.r0,xmm2.r0),
							    vec_madd(xmm0.r1,xmm1.r1,xmm2.r1),
							    vec_madd(xmm0.r2,xmm1.r2,xmm2.r2),
							    vec_madd(xmm0.r3,xmm1.r3,xmm2.r3));
    }

    /**
      Returns a vector containing the results of performing a negative
      multiply-subtract operation on the given vectors.
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_nfma<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0,
                                simd_trait<float,cyme::vmx,1>::register_type xmm1,
                                simd_trait<float,cyme::vmx,1>::register_type xmm2){
	return vec_nmsub(xmm0,xmm1,xmm2);
    }

    /**
      Returns a vector containing the results of performing a negative
      multiply-subtract operation on the given vectors.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_nfma<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0,
                                simd_trait<float,cyme::vmx,2>::register_type xmm1,
                                simd_trait<float,cyme::vmx,2>::register_type xmm2){
        return simd_trait<float,cyme::vmx,2>::register_type(vec_nmsub(xmm0.r0,xmm1.r0,xmm2.r0),
							    vec_nmsub(xmm0.r1,xmm1.r1,xmm2.r1));
    }

    /**
      Returns a vector containing the results of performing a negative
      multiply-subtract operation on the given vectors.
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_nfma<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0,
                                simd_trait<float,cyme::vmx,4>::register_type xmm1,
                                simd_trait<float,cyme::vmx,4>::register_type xmm2){
        return simd_trait<float,cyme::vmx,4>::register_type(vec_nmsub(xmm0.r0,xmm1.r0,xmm2.r0),
							    vec_nmsub(xmm0.r1,xmm1.r1,xmm2.r1),
							    vec_nmsub(xmm0.r2,xmm1.r2,xmm2.r2),
							    vec_nmsub(xmm0.r3,xmm1.r3,xmm2.r3));
    }

    /**
      Returns a vector containing the results of performing a multiply-substract
      operation using the given vectors.
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_fms<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0,
                               simd_trait<float,cyme::vmx,1>::register_type xmm1,
                               simd_trait<float,cyme::vmx,1>::register_type xmm2){
	return vec_msub(xmm0,xmm1,xmm2);
    }

    /**
      Returns a vector containing the results of performing a multiply-substract
      operation using the given vectors.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_fms<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0,
                               simd_trait<float,cyme::vmx,2>::register_type xmm1,
                               simd_trait<float,cyme::vmx,2>::register_type xmm2){
        return simd_trait<float,cyme::vmx,2>::register_type(vec_msub(xmm0.r0,xmm1.r0,xmm2.r0),
							    vec_msub(xmm0.r1,xmm1.r1,xmm2.r1));
    }

    /**
      Returns a vector containing the results of performing a multiply-substract
      operation using the given vectors.
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_fms<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0,
                               simd_trait<float,cyme::vmx,4>::register_type xmm1,
                               simd_trait<float,cyme::vmx,4>::register_type xmm2){
        return simd_trait<float,cyme::vmx,4>::register_type(vec_msub(xmm0.r0,xmm1.r0,xmm2.r0),
							    vec_msub(xmm0.r1,xmm1.r1,xmm2.r1),
							    vec_msub(xmm0.r2,xmm1.r2,xmm2.r2),
							    vec_msub(xmm0.r3,xmm1.r3,xmm2.r3));
    }

    /**
     Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
       specialisation float,cyme::vmx,1 regs
    */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_nfms<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0,
                                simd_trait<float,cyme::vmx,1>::register_type xmm1,
                                simd_trait<float,cyme::vmx,1>::register_type xmm2){
	return vec_nmadd(xmm0,xmm1,xmm2);
    }

    /**
     Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
       specialisation float,cyme::vmx,2 regs
    */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_nfms<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0,
                                simd_trait<float,cyme::vmx,2>::register_type xmm1,
                                simd_trait<float,cyme::vmx,2>::register_type xmm2){
        return simd_trait<float,cyme::vmx,2>::register_type(vec_nmadd(xmm0.r0,xmm1.r0,xmm2.r0),
							    vec_nmadd(xmm0.r1,xmm1.r1,xmm2.r1));
    }

    /**
     Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
       specialisation float,cyme::vmx,4 regs
    */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_nfms<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0,
                                simd_trait<float,cyme::vmx,4>::register_type xmm1,
                                simd_trait<float,cyme::vmx,4>::register_type xmm2){
        return simd_trait<float,cyme::vmx,4>::register_type(vec_nmadd(xmm0.r0,xmm1.r0,xmm2.r0),
							    vec_nmadd(xmm0.r1,xmm1.r1,xmm2.r1),
							    vec_nmadd(xmm0.r2,xmm1.r2,xmm2.r2),
							    vec_nmadd(xmm0.r3,xmm1.r3,xmm2.r3));
    }
#endif
/*--------------------------------------------------------------------- double ---------------*/
    /**
       Single load a double-precision (64-bit) floating-point element from cyme into lower element of dst.
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_single_load<double,cyme::vmx,1>(const simd_trait<double,cyme::vmx,1>::value_type b){
        return vec_vsx_ld(0, (vector double*)&b);
    }

    /**
       Single store a double-precision (64-bit) floating-point element from register lower element to cyme.
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::value_type
    _mm_single_store<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0,
                                           simd_trait<double,cyme::vmx,1>::pointer b){
        vec_vsx_st(xmm0,0,(vector double*)b);
	return *b;
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_load1<double,cyme::vmx,1>(const simd_trait<double,cyme::vmx,1>::value_type &a){
        return vec_splats(a);
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_load1<double,cyme::vmx,2>(const simd_trait<double,cyme::vmx,2>::value_type &a){
        return simd_trait<double,cyme::vmx,2>::register_type(vec_splats(a),vec_splats(a));
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_load1<double,cyme::vmx,4>(const simd_trait<double,cyme::vmx,4>::value_type &a){
        return simd_trait<double,cyme::vmx,4>::register_type(vec_splats(a),vec_splats(a),
							     vec_splats(a),vec_splats(a));
    }

    /**
      Loads a vector from the given cyme address.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_load<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::const_pointer a){
        return vec_vsx_ld(0,(vector double*)a);
    }

    /**
      Loads a vector from the given cyme address.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_load<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::const_pointer a){
        return simd_trait<double,cyme::vmx,2>::register_type(vec_vsx_ld(0,(vector double*)a),
							     vec_vsx_ld(16,(vector double*)a));
    }

    /**
      Loads a vector from the given cyme address.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_load<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::const_pointer a){
        return simd_trait<double,cyme::vmx,4>::register_type(vec_vsx_ld(0,(vector double*)a),
							     vec_vsx_ld(16,(vector double*)a),
							     vec_vsx_ld(32,(vector double*)a),
							     vec_vsx_ld(48,(vector double*)a));
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline void
    _mm_store<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0,
                                  simd_trait<double,cyme::vmx,1>::pointer  a){
        vec_vsx_st(xmm0,0,(vector double*)a);
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline void
    _mm_store<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0,
                                  simd_trait<double,cyme::vmx,2>::pointer  a){
        vec_vsx_st(xmm0.r0,0,(vector double*)a);
	vec_vsx_st(xmm0.r1,16,(vector double*)a);
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline void
    _mm_store<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0,
                                  simd_trait<double,cyme::vmx,4>::pointer  a){
        vec_vsx_st(xmm0.r0,0,(vector double*)a);
	vec_vsx_st(xmm0.r1,16,(vector double*)a);
	vec_vsx_st(xmm0.r2,32,(vector double*)a);
	vec_vsx_st(xmm0.r3,48,(vector double*)a);
    }

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_mul<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0,
                                simd_trait<double,cyme::vmx,1>::register_type xmm1){
        return vec_mul(xmm0,xmm1);
    }

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_mul<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0,
                                simd_trait<double,cyme::vmx,2>::register_type xmm1){
         return simd_trait<double,cyme::vmx,2>::register_type(vec_mul(xmm0.r0,xmm1.r0),
							      vec_mul(xmm0.r1,xmm1.r1));
    }

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_mul<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0,
                                simd_trait<double,cyme::vmx,4>::register_type xmm1){
         return simd_trait<double,cyme::vmx,4>::register_type(vec_mul(xmm0.r0,xmm1.r0),
         						      vec_mul(xmm0.r1,xmm1.r1),
         						      vec_mul(xmm0.r2,xmm1.r2),
         						      vec_mul(xmm0.r3,xmm1.r3));
    }

    /**
      Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_div<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0,
                                simd_trait<double,cyme::vmx,1>::register_type xmm1){
        return vec_div(xmm0,xmm1);
    }

    /**
      Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_div<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0,
                                simd_trait<double,cyme::vmx,2>::register_type xmm1){
         return simd_trait<double,cyme::vmx,2>::register_type(vec_div(xmm0.r0,xmm1.r0),
							      vec_div(xmm0.r1,xmm1.r1));
    }

    /**
      Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_div<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0,
                                simd_trait<double,cyme::vmx,4>::register_type xmm1){
         return simd_trait<double,cyme::vmx,4>::register_type(vec_div(xmm0.r0,xmm1.r0),
							      vec_div(xmm0.r1,xmm1.r1),
							      vec_div(xmm0.r2,xmm1.r2),
							      vec_div(xmm0.r3,xmm1.r3));
    }

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_add<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0,
                                simd_trait<double,cyme::vmx,1>::register_type xmm1){
        return vec_add(xmm0,xmm1);
    }

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_add<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0,
                                simd_trait<double,cyme::vmx,2>::register_type xmm1){
         return simd_trait<double,cyme::vmx,2>::register_type(vec_add(xmm0.r0,xmm1.r0),
							      vec_add(xmm0.r1,xmm1.r1));
    }

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_add<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0,
                                simd_trait<double,cyme::vmx,4>::register_type xmm1){
         return simd_trait<double,cyme::vmx,4>::register_type(vec_add(xmm0.r0,xmm1.r0),
         						      vec_add(xmm0.r1,xmm1.r1),
         						      vec_add(xmm0.r2,xmm1.r2),
         						      vec_add(xmm0.r3,xmm1.r3));
    }

    /**
      Returns a vector containing the result of subtracting each element of b from the corresponding element of a.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_sub<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0,
                                simd_trait<double,cyme::vmx,1>::register_type xmm1){
        return vec_sub(xmm0,xmm1);
    }

    /**
      Returns a vector containing the result of subtracting each element of b from the corresponding element of a.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_sub<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0,
                                simd_trait<double,cyme::vmx,2>::register_type xmm1){
         return simd_trait<double,cyme::vmx,2>::register_type(vec_sub(xmm0.r0,xmm1.r0),
							      vec_sub(xmm0.r1,xmm1.r1));
    }

    /**
      Returns a vector containing the result of subtracting each element of b from the corresponding element of a.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_sub<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0,
                                simd_trait<double,cyme::vmx,4>::register_type xmm1){
         return simd_trait<double,cyme::vmx,4>::register_type(vec_sub(xmm0.r0,xmm1.r0),
							      vec_sub(xmm0.r1,xmm1.r1),
							      vec_sub(xmm0.r2,xmm1.r2),
							      vec_sub(xmm0.r3,xmm1.r3));
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_exp<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0){
	return expd4(xmm0);
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_exp<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0){
	return simd_trait<double,cyme::vmx,2>::register_type(expd4(xmm0.r0),expd4(xmm0.r1));
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_exp<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0){
	return simd_trait<double,cyme::vmx,4>::register_type(expd4(xmm0.r0),expd4(xmm0.r1),
							     expd4(xmm0.r2),expd4(xmm0.r3));
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_log<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0){
	return logd4(xmm0);
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_log<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0){
	return simd_trait<double,cyme::vmx,2>::register_type(logd4(xmm0.r0),logd4(xmm0.r1));
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_log<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0){
	return simd_trait<double,cyme::vmx,4>::register_type(logd4(xmm0.r0),logd4(xmm0.r1),
							     logd4(xmm0.r2), logd4(xmm0.r3));
    }

    /**
      Returns a vector containing estimates of the reciprocals of the corresponding elements of the given vector.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x) / (1/x) | ≤ 1/256
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_rec<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0){
        return vec_re(xmm0);
    }

    /**
      Returns a vector containing estimates of the reciprocals of the corresponding elements of the given vector.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x) / (1/x) | ≤ 1/256
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_rec<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0){
        return simd_trait<double,cyme::vmx,2>::register_type(vec_re(xmm0.r0),
							     vec_re(xmm0.r1));
    }

    /**
      Returns a vector containing estimates of the reciprocals of the corresponding elements of the given vector.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x) / (1/x) | ≤ 1/256
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_rec<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0){
        return simd_trait<double,cyme::vmx,4>::register_type(vec_re(xmm0.r0),
							     vec_re(xmm0.r1),
							     vec_re(xmm0.r2),
							     vec_re(xmm0.r3));
    }

    /**
      Compute 1/recsqrt (64-bit) floating point elements in xmm0 to packed double-precision (64-bit)
     floating-point elements, and store the results in dst.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x^0,5) / (1/x^0.5) | ≤ 1/256
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_rsqrt<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0){
        return vec_rsqrte(xmm0);
    }

    /**
      Compute 1/recsqrt (64-bit) floating point elements in xmm0 to packed double-precision (64-bit)
     floating-point elements, and store the results in dst.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x^0,5) / (1/x^0.5) | ≤ 1/256
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_rsqrt<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0){
        return simd_trait<double,cyme::vmx,2>::register_type(vec_rsqrte(xmm0.r0),
							     vec_rsqrte(xmm0.r1));
    }

    /**
      Compute 1/recsqrt (64-bit) floating point elements in xmm0 to packed double-precision (64-bit)
     floating-point elements, and store the results in dst.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x^0,5) / (1/x^0.5) | ≤ 1/256
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_rsqrt<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0){
        return simd_trait<double,cyme::vmx,4>::register_type(vec_rsqrte(xmm0.r0),
							     vec_rsqrte(xmm0.r1),
							     vec_rsqrte(xmm0.r2),
							     vec_rsqrte(xmm0.r3));
    }


    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_neg<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0){
	vector double mask = (vector double)vec_splats(0x8000000000000000);
	return vec_xor(xmm0,mask);
	//return vec_xor(xmm0, vec_splats(-0.));
}

    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_neg<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0){
	vector double mask = (vector double)vec_splats(0x8000000000000000);
	return simd_trait<double,cyme::vmx,2>::register_type(vec_xor(xmm0.r0,mask),
							     vec_xor(xmm0.r1,mask));
    }

    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_neg<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0){
	vector double mask = (vector double)vec_splats(0x8000000000000000);
	return simd_trait<double,cyme::vmx,4>::register_type(vec_xor(xmm0.r0,mask),
							     vec_xor(xmm0.r1,mask),
							     vec_xor(xmm0.r2,mask),
							     vec_xor(xmm0.r3,mask));
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_cast<double,cyme::vmx,1>(simd_trait<int,cyme::vmx,1>::register_type xmm0){
	return vec_ctd(xmm0);
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_cast<double,cyme::vmx,2>(simd_trait<int,cyme::vmx,2>::register_type xmm0){
        return simd_trait<double,cyme::vmx,2>::register_type(vec_ctd(xmm0.r0),
							     vec_ctd(xmm0.r1));
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_cast<double,cyme::vmx,4>(simd_trait<int,cyme::vmx,4>::register_type xmm0){
        return simd_trait<double,cyme::vmx,4>::register_type(vec_ctd(xmm0.r0),
							     vec_ctd(xmm0.r1),
							     vec_ctd(xmm0.r2),
							     vec_ctd(xmm0.r3));
    }

    /**
      Returns a vector containing the largest representable floating-point integral values less than or equal
     to the values of the corresponding elements of the given vector.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<int,cyme::vmx,1>::register_type
    _mm_floor<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0){
	return vec_cdts(vec_floor(xmm0));
    }

    /**
      Returns a vector containing the largest representable floating-point integral values less than or equal
     to the values of the corresponding elements of the given vector.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<int,cyme::vmx,2>::register_type
    _mm_floor<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0){
        return simd_trait<int,cyme::vmx,2>::register_type(vec_cdts(vec_floor(xmm0.r0)),
							  vec_cdts(vec_floor(xmm0.r1)));
    }

    /**
      Returns a vector containing the largest representable floating-point integral values less than or equal
     to the values of the corresponding elements of the given vector.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<int,cyme::vmx,4>::register_type
    _mm_floor<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0){
        return simd_trait<int,cyme::vmx,4>::register_type(vec_cdts(vec_floor(xmm0.r0)),
							  vec_cdts(vec_floor(xmm0.r1)),
							  vec_cdts(vec_floor(xmm0.r2)),
							  vec_cdts(vec_floor(xmm0.r3)));
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer, because there is no builtin function
      for 2^k in double, the computation is done using a C trick.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_twok<double,cyme::vmx,1>(simd_trait<int,cyme::vmx,1>::register_type xmm0){
	vector int tmp = vec_splats(1023);
	return (vector double)vec_sl(vec_add(xmm0,tmp),vec_splats((unsigned int)20));
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer, because there is no builtin function
      for 2^k in double, the computation is done using a C trick.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_twok<double,cyme::vmx,2>(simd_trait<int,cyme::vmx,2>::register_type xmm0){
	vector int tmp = vec_splats(1023);
	xmm0.r0 = vec_add(xmm0.r0,tmp);
	xmm0.r1 = vec_add(xmm0.r1,tmp);
	xmm0.r0 = vec_sl(xmm0.r0,vec_splats((unsigned int)20));
	xmm0.r1 = vec_sl(xmm0.r1,vec_splats((unsigned int)20));
	return simd_trait<double,cyme::vmx,2>::register_type((vector double)xmm0.r0,
							     (vector double)xmm0.r1);
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer, because there is no builtin function
      for 2^k in double, the computation is done using a C trick.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_twok<double,cyme::vmx,4>(simd_trait<int,cyme::vmx,4>::register_type xmm0){
	vector int tmp = vec_splats(1023);
	xmm0.r0 = vec_add(xmm0.r0,tmp);
	xmm0.r1 = vec_add(xmm0.r1,tmp);
	xmm0.r2 = vec_add(xmm0.r2,tmp);
	xmm0.r3 = vec_add(xmm0.r3,tmp);
	xmm0.r0 = vec_sl(xmm0.r0,vec_splats((unsigned int)20));
	xmm0.r1 = vec_sl(xmm0.r1,vec_splats((unsigned int)20));
	xmm0.r2 = vec_sl(xmm0.r2,vec_splats((unsigned int)20));
	xmm0.r3 = vec_sl(xmm0.r3,vec_splats((unsigned int)20));
	return simd_trait<double,cyme::vmx,4>::register_type((vector double)xmm0.r0,
							     (vector double)xmm0.r1,
							     (vector double)xmm0.r2,
							     (vector double)xmm0.r3);
    }

   /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
      Because we are casting from vector2double -> vector4int, must use specific mask and tmp_sub vectors.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_ge<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0){
	vector signed int tmp = (vector signed int)xmm0;
#ifdef __BIG_ENDIAN__ //Power7
	vector signed int mask = {(signed int)0xffffffff,(signed int)0x00000000,
				  (signed int)0xffffffff,(signed int)0x00000000};
	vector signed int tmp_sub = {1023,0,1023,0};
#endif
#ifdef __LITTLE_ENDIAN__ //Power8
	vector signed int mask = {(signed int)0x00000000,(signed int)0xffffffff,
				  (signed int)0x00000000,(signed int)0xffffffff};
	vector signed int tmp_sub = {0,1023,0,1023};
#endif
	tmp = vec_and(tmp,mask);
	tmp = vec_sr(tmp,vec_splats((unsigned int)20));
	tmp = vec_sub(tmp,tmp_sub);
	return vec_ctd(tmp);
    }

   /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
      Because we are casting from vector2double -> vector4int, must use specific mask and tmp_sub vectors.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_ge<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0){
	vector signed int tmp0 = (vector signed int)xmm0.r0;
	vector signed int tmp1 = (vector signed int)xmm0.r1;
#ifdef __BIG_ENDIAN__ //Power7
	vector signed int mask = {(signed int)0xffffffff,(signed int)0x00000000,
				  (signed int)0xffffffff,(signed int)0x00000000};
	vector signed int tmp_sub = {1023,0,1023,0};
#endif
#ifdef __LITTLE_ENDIAN__ //Power8
	vector signed int mask = {(signed int)0x00000000,(signed int)0xffffffff,
				  (signed int)0x00000000,(signed int)0xffffffff};
	vector signed int tmp_sub = {0,1023,0,1023};
#endif
	tmp0 = vec_and(tmp0,mask);
	tmp1 = vec_and(tmp1,mask);
	tmp0 = vec_sr(tmp0,vec_splats((unsigned int)20));
	tmp1 = vec_sr(tmp1,vec_splats((unsigned int)20));
	tmp0 = vec_sub(tmp0,tmp_sub);
	tmp1 = vec_sub(tmp1,tmp_sub);
        return simd_trait<double,cyme::vmx,2>::register_type(vec_ctd(tmp0),
        						     vec_ctd(tmp1));
    }

   /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
      Because we are casting from vector2double -> vector4int, must use specific mask and tmp_sub vectors.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_ge<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0){
	vector signed int tmp0 = (vector signed int)xmm0.r0;
	vector signed int tmp1 = (vector signed int)xmm0.r1;
	vector signed int tmp2 = (vector signed int)xmm0.r2;
	vector signed int tmp3 = (vector signed int)xmm0.r3;
#ifdef __BIG_ENDIAN__ //Power7
	vector signed int mask = {(signed int)0xffffffff,(signed int)0x00000000,
				  (signed int)0xffffffff,(signed int)0x00000000};
	vector signed int tmp_sub = {1023,0,1023,0};
#endif
#ifdef __LITTLE_ENDIAN__ //Power8
	vector signed int mask = {(signed int)0x00000000,(signed int)0xffffffff,
				  (signed int)0x00000000,(signed int)0xffffffff};
	vector signed int tmp_sub = {0,1023,0,1023};
#endif
	tmp0 = vec_and(tmp0,mask);
	tmp1 = vec_and(tmp1,mask);
	tmp2 = vec_and(tmp2,mask);
	tmp3 = vec_and(tmp3,mask);
	tmp0 = vec_sr(tmp0,vec_splats((unsigned int)20));
	tmp1 = vec_sr(tmp1,vec_splats((unsigned int)20));
	tmp2 = vec_sr(tmp2,vec_splats((unsigned int)20));
	tmp3 = vec_sr(tmp3,vec_splats((unsigned int)20));
	tmp0 = vec_sub(tmp0,tmp_sub);
	tmp1 = vec_sub(tmp1,tmp_sub);
	tmp2 = vec_sub(tmp2,tmp_sub);
	tmp3 = vec_sub(tmp3,tmp_sub);
        return simd_trait<double,cyme::vmx,4>::register_type(vec_ctd(tmp0),
        						     vec_ctd(tmp1),
        						     vec_ctd(tmp2),
        						     vec_ctd(tmp3));
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
      Because we are casting from vector2double -> vector4int, must use specific mask and tmp_add vectors.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_gf<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0){
	vector signed int tmp = (vector signed int)xmm0;
#ifdef __BIG_ENDIAN__ //Power7
        vector signed int mask = {(signed int)0x000fffff,(signed int)0xffffffff,
				  (signed int)0x000fffff,(signed int)0xffffffff};
        vector signed int tmp_add = {(signed int)0x3ff00000,(signed int)0x00000000,
				     (signed int)0x3ff00000,(signed int)0x00000000};
#endif
#ifdef __LITTLE_ENDIAN__ //Power8
        vector signed int mask = {(signed int)0xffffffff,(signed int)0x000fffff,
				  (signed int)0xffffffff,(signed int)0x000fffff};
        vector signed int tmp_add = {(signed int)0x00000000,(signed int)0x3ff00000,
				     (signed int)0x00000000,(signed int)0x3ff00000};
#endif
	tmp = vec_and(tmp,mask);
	tmp = vec_add(tmp,tmp_add);
	return (vector double)tmp;
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
      Because we are casting from vector2double -> vector4int, must use specific mask and tmp_add vectors.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_gf<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0){
	vector signed int tmp0 = (vector signed int)xmm0.r0;
	vector signed int tmp1 = (vector signed int)xmm0.r1;
#ifdef __BIG_ENDIAN__ //Power7
        vector signed int mask = {(signed int)0x000fffff,(signed int)0xffffffff,
				  (signed int)0x000fffff,(signed int)0xffffffff};
        vector signed int tmp_add = {(signed int)0x3ff00000,(signed int)0x00000000,
				     (signed int)0x3ff00000,(signed int)0x00000000};
#endif
#ifdef __LITTLE_ENDIAN__ //Power8
        vector signed int mask = {(signed int)0xffffffff,(signed int)0x000fffff,
				  (signed int)0xffffffff,(signed int)0x000fffff};
        vector signed int tmp_add = {(signed int)0x00000000,(signed int)0x3ff00000,
				     (signed int)0x00000000,(signed int)0x3ff00000};
#endif
	tmp0 = vec_and(tmp0,mask);
	tmp1 = vec_and(tmp1,mask);
        tmp0 = vec_add(tmp0,tmp_add);
        tmp1 = vec_add(tmp1,tmp_add);
        return simd_trait<double,cyme::vmx,2>::register_type((vector double)tmp0,
							     (vector double)tmp1);
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
      Because we are casting from vector2double -> vector4int, must use specific mask and tmp_add vectors.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_gf<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0){
	vector signed int tmp0 = (vector signed int)xmm0.r0;
	vector signed int tmp1 = (vector signed int)xmm0.r1;
	vector signed int tmp2 = (vector signed int)xmm0.r2;
	vector signed int tmp3 = (vector signed int)xmm0.r3;
#ifdef __BIG_ENDIAN__ //Power7
        vector signed int mask = {(signed int)0x000fffff,(signed int)0xffffffff,
				  (signed int)0x000fffff,(signed int)0xffffffff};
        vector signed int tmp_add = {(signed int)0x3ff00000,(signed int)0x00000000,
				     (signed int)0x3ff00000,(signed int)0x00000000};
#endif
#ifdef __LITTLE_ENDIAN__ //Power8
        vector signed int mask = {(signed int)0xffffffff,(signed int)0x000fffff,
				  (signed int)0xffffffff,(signed int)0x000fffff};
        vector signed int tmp_add = {(signed int)0x00000000,(signed int)0x3ff00000,
				     (signed int)0x00000000,(signed int)0x3ff00000};
#endif
        tmp0 = vec_and(tmp0,mask);
        tmp1 = vec_and(tmp1,mask);
        tmp2 = vec_and(tmp2,mask);
        tmp3 = vec_and(tmp3,mask);
        tmp0 = vec_add(tmp0,tmp_add);
        tmp1 = vec_add(tmp1,tmp_add);
        tmp2 = vec_add(tmp2,tmp_add);
        tmp3 = vec_add(tmp3,tmp_add);
        return simd_trait<double,cyme::vmx,4>::register_type((vector double)tmp0,
							     (vector double)tmp1,
							     (vector double)tmp2,
							     (vector double)tmp3);
    }

    /**
      Computes the absolute value for double-precision (64-bit) floating point elements and stores
      the result in dst.
      specialisation double,cyme::vmx,1 reg
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_fabs<double,cyme::vmx,1>( simd_trait<double,cyme::vmx,1>::register_type xmm0){
	return vec_abs(xmm0);
    }

    /**
      Computes the absolute value for double-precision (64-bit) floating point elements and stores
      the result in dst.
      specialisation double,cyme::vmx,2 reg
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_fabs<double,cyme::vmx,2>( simd_trait<double,cyme::vmx,2>::register_type xmm0){
	return simd_trait<double,cyme::vmx,2>::register_type(vec_abs(xmm0.r0),
							     vec_abs(xmm0.r1));
    }

    /**
      Computes the absolute value for double-precision (64-bit) floating point elements and stores
      the result in dst.
      specialisation double,cyme::vmx,4 reg
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_fabs<double,cyme::vmx,4>( simd_trait<double,cyme::vmx,4>::register_type xmm0){
	return simd_trait<double,cyme::vmx,4>::register_type(vec_abs(xmm0.r0),
							     vec_abs(xmm0.r1),
							     vec_abs(xmm0.r2),
							     vec_abs(xmm0.r3));
    }

    /**
      Selects the polynomial for sin function. Inputs are:
	- Selector int
	- Option one
	- Option two
      specialisation double,cyme::vmx, 1 reg
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_select_poly<double,cyme::vmx,1>( simd_trait<int,cyme::vmx,1>::register_type sel,
                                         simd_trait<double,cyme::vmx,1>::register_type xmm0,
                                         simd_trait<double,cyme::vmx,1>::register_type xmm1){
	vector int mask = vec_splats(2);
	vector int zero = vec_splats(0);
	sel = vec_and(sel,mask);
	sel = (vector int)vec_cmpeq(sel,zero);

	xmm0 = vec_andc(xmm0,(vector double)sel);
	xmm1 = vec_and(xmm1,(vector double)sel);
	return vec_add(xmm0,xmm1);
    }

    /**
      Selects the polynomial for sin function. Inputs are:
	- Selector int
	- Option one
	- Option two
      specialisation double,cyme::vmx, 2 reg
     */
   template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_select_poly<double,cyme::vmx,2>( simd_trait<int,cyme::vmx,2>::register_type sel,
                                         simd_trait<double,cyme::vmx,2>::register_type xmm0,
                                         simd_trait<double,cyme::vmx,2>::register_type xmm1){
	vector int mask = vec_splats(2);
	vector int zero = vec_splats(0);
	sel.r0 = vec_and(sel.r0,mask);
	sel.r1 = vec_and(sel.r1,mask);
	sel.r0 = (vector int)vec_cmpeq(sel.r0,zero);
	sel.r1 = (vector int)vec_cmpeq(sel.r1,zero);

	xmm0.r0 = vec_andc(xmm0.r0,(vector double)sel.r0);
	xmm0.r1 = vec_andc(xmm0.r1,(vector double)sel.r1);
	xmm1.r0 = vec_and(xmm1.r0,(vector double)sel.r0);
	xmm1.r1 = vec_and(xmm1.r1,(vector double)sel.r1);
	return simd_trait<double,cyme::vmx,2>::register_type (vec_add(xmm0.r0,xmm1.r0),
							      vec_add(xmm0.r1,xmm1.r1));
    }

    /**
      Selects the polynomial for sin function. Inputs are:
	- Selector int
	- Option one
	- Option two
      specialisation double,cyme::vmx, 4 reg
     */
   template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_select_poly<double,cyme::vmx,4>( simd_trait<int,cyme::vmx,4>::register_type sel,
                                         simd_trait<double,cyme::vmx,4>::register_type  xmm0,
                                         simd_trait<double,cyme::vmx,4>::register_type xmm1){
	vector int mask = vec_splats(2);
	vector int zero = vec_splats(0);
	sel.r0 = vec_and(sel.r0,mask);
	sel.r1 = vec_and(sel.r1,mask);
	sel.r2 = vec_and(sel.r2,mask);
	sel.r3 = vec_and(sel.r3,mask);
	sel.r0 = (vector int)vec_cmpeq(sel.r0,zero);
	sel.r1 = (vector int)vec_cmpeq(sel.r1,zero);
	sel.r2 = (vector int)vec_cmpeq(sel.r2,zero);
	sel.r3 = (vector int)vec_cmpeq(sel.r3,zero);

	xmm0.r0 = vec_andc(xmm0.r0,(vector double)sel.r0);
	xmm0.r1 = vec_andc(xmm0.r1,(vector double)sel.r1);
	xmm0.r2 = vec_andc(xmm0.r2,(vector double)sel.r2);
	xmm0.r3 = vec_andc(xmm0.r3,(vector double)sel.r3);
	xmm1.r0 = vec_and(xmm1.r0,(vector double)sel.r0);
	xmm1.r1 = vec_and(xmm1.r1,(vector double)sel.r1);
	xmm1.r2 = vec_and(xmm1.r2,(vector double)sel.r2);
	xmm1.r3 = vec_and(xmm1.r3,(vector double)sel.r3);
	return simd_trait<double,cyme::vmx,4>::register_type (vec_add(xmm0.r0,xmm1.r0),
							      vec_add(xmm0.r1,xmm1.r1),
							      vec_add(xmm0.r2,xmm1.r2),
							      vec_add(xmm0.r3,xmm1.r3));
    }

    /**
      Selects the sign (+/-) for sin function. Inputs are:
	- swap int
	- Original input
	- Final calculated sin value
      specialisation double,cyme::vmx,1 reg
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_select_sign_sin<double,cyme::vmx,1>( simd_trait<int,cyme::vmx,1>::register_type swap,
                                             simd_trait<double,cyme::vmx,1>::register_type xmm0,
                                             simd_trait<double,cyme::vmx,1>::register_type xmm1){
	vector double mask = (vector double)vec_splats(0x80000000);
	vector int four = vec_splats(4);
	/* extract the sign bit (upper one) from original val */
	xmm0 = vec_and(xmm0, mask);

	/* get the swap sign flag */
	swap = vec_and(swap, four);
	swap = vec_sl(swap, vec_splats((unsigned int)29));

	/* update the sign of the final value*/
	xmm1 = vec_xor(xmm1, (vector double)swap);
	xmm1 = vec_xor(xmm1, xmm0);
	return xmm1;
    }

    /**
      Selects the sign (+/-) for sin function. Inputs are:
	- swap int
	- Original input
	- Final calculated sin value
      specialisation double,cyme::vmx,2 reg
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_select_sign_sin<double,cyme::vmx,2>( simd_trait<int,cyme::vmx,2>::register_type swap,
                                             simd_trait<double,cyme::vmx,2>::register_type xmm0,
                                             simd_trait<double,cyme::vmx,2>::register_type xmm1){
	vector double mask = (vector double)vec_splats(0x80000000);
	vector int four = vec_splats(4);
	/* extract the sign bit (upper one) from original val */
	xmm0.r0 = vec_and(xmm0.r0, mask);
	xmm0.r1 = vec_and(xmm0.r1, mask);

	/* get the swap sign flag */
	swap.r0 = vec_and(swap.r0, four);
	swap.r1 = vec_and(swap.r1, four);
	swap.r0 = vec_sl(swap.r0, vec_splats((unsigned int)29));
	swap.r1 = vec_sl(swap.r1, vec_splats((unsigned int)29));

	/* update the sign of the final value*/
	xmm1.r0 = vec_xor(xmm1.r0, (vector double)swap.r0);
	xmm1.r1 = vec_xor(xmm1.r1, (vector double)swap.r1);
	xmm1.r0 = vec_xor(xmm1.r0, xmm0.r0);
	xmm1.r1 = vec_xor(xmm1.r1, xmm0.r1);
	return simd_trait<double,cyme::vmx,2>::register_type (xmm1.r0,xmm1.r1);
    }

    /**
      Selects the sign (+/-) for sin function. Inputs are:
	- swap int
	- Original input
	- Final calculated sin value
      specialisation double,cyme::vmx,4 reg
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_select_sign_sin<double,cyme::vmx,4>( simd_trait<int,cyme::vmx,4>::register_type swap,
                                             simd_trait<double,cyme::vmx,4>::register_type xmm0,
                                             simd_trait<double,cyme::vmx,4>::register_type xmm1){
	vector double mask = (vector double)vec_splats(0x80000000);
	vector int four = vec_splats(4);
	/* extract the sign bit (upper one) from original val */
	xmm0.r0 = vec_and(xmm0.r0, mask);
	xmm0.r1 = vec_and(xmm0.r1, mask);
	xmm0.r2 = vec_and(xmm0.r2, mask);
	xmm0.r3 = vec_and(xmm0.r3, mask);

	/* get the swap sign flag */
	swap.r0 = vec_and(swap.r0, four);
	swap.r1 = vec_and(swap.r1, four);
	swap.r2 = vec_and(swap.r2, four);
	swap.r3 = vec_and(swap.r3, four);
	swap.r0 = vec_sl(swap.r0, vec_splats((unsigned int)29));
	swap.r1 = vec_sl(swap.r1, vec_splats((unsigned int)29));
	swap.r2 = vec_sl(swap.r2, vec_splats((unsigned int)29));
	swap.r3 = vec_sl(swap.r3, vec_splats((unsigned int)29));

	/* update the sign of the final value*/
	xmm1.r0 = vec_xor(xmm1.r0, (vector double)swap.r0);
	xmm1.r1 = vec_xor(xmm1.r1, (vector double)swap.r1);
	xmm1.r2 = vec_xor(xmm1.r2, (vector double)swap.r2);
	xmm1.r3 = vec_xor(xmm1.r3, (vector double)swap.r3);
	xmm1.r0 = vec_xor(xmm1.r0, xmm0.r0);
	xmm1.r1 = vec_xor(xmm1.r1, xmm0.r1);
	xmm1.r2 = vec_xor(xmm1.r2, xmm0.r2);
	xmm1.r3 = vec_xor(xmm1.r3, xmm0.r3);
	return simd_trait<double,cyme::vmx,4>::register_type (xmm1.r0,xmm1.r1,
							      xmm1.r2,xmm1.r3);
    }

    /**
      Selects the sign (+/-) for cos function. Inputs are:
	- swap int
	- Final calculated cos value
      specialisation double,cyme::vmx,1 reg
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_select_sign_cos<double,cyme::vmx,1>( simd_trait<int,cyme::vmx,1>::register_type swap,
                                             simd_trait<double,cyme::vmx,1>::register_type xmm0){
	vector int four = vec_splats(4);

	/* get the swap sign flag */
	swap = vec_andc(four,swap);
	swap = vec_sl(swap, vec_splats((unsigned int)29));

	/* update the sign of the final value*/
	xmm0 = vec_xor(xmm0, (vector double)swap);
	return xmm0;
    }

    /**
      Selects the sign (+/-) for cos function. Inputs are:
	- swap int
	- Final calculated cos value
      specialisation double,cyme::vmx,2 reg
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_select_sign_cos<double,cyme::vmx,2>( simd_trait<int,cyme::vmx,2>::register_type swap,
                                             simd_trait<double,cyme::vmx,2>::register_type xmm0){
	vector int four = vec_splats(4);

	/* get the swap sign flag */
	swap.r0 = vec_andc(four,swap.r0);
	swap.r1 = vec_andc(four,swap.r1);
	swap.r0 = vec_sl(swap.r0, vec_splats((unsigned int)29));
	swap.r1 = vec_sl(swap.r1, vec_splats((unsigned int)29));

	/* update the sign of the final value*/
	xmm0.r0 = vec_xor(xmm0.r0, (vector double)swap.r0);
	xmm0.r1 = vec_xor(xmm0.r1, (vector double)swap.r1);
	return simd_trait<double,cyme::vmx,2>::register_type (xmm0.r0,xmm0.r1);
    }

    /**
      Selects the sign (+/-) for cos function. Inputs are:
	- swap int
	- Final calculated cos value
      specialisation double,cyme::vmx,4 reg
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_select_sign_cos<double,cyme::vmx,4>( simd_trait<int,cyme::vmx,4>::register_type swap,
                                             simd_trait<double,cyme::vmx,4>::register_type xmm0){
	vector int four = vec_splats(4);

	/* get the swap sign flag */
	swap.r0 = vec_andc(four,swap.r0);
	swap.r1 = vec_andc(four,swap.r1);
	swap.r2 = vec_andc(four,swap.r2);
	swap.r3 = vec_andc(four,swap.r3);
	swap.r0 = vec_sl(swap.r0, vec_splats((unsigned int)29));
	swap.r1 = vec_sl(swap.r1, vec_splats((unsigned int)29));
	swap.r2 = vec_sl(swap.r2, vec_splats((unsigned int)29));
	swap.r3 = vec_sl(swap.r3, vec_splats((unsigned int)29));

	/* update the sign of the final value*/
	xmm0.r0 = vec_xor(xmm0.r0, (vector double)swap.r0);
	xmm0.r1 = vec_xor(xmm0.r1, (vector double)swap.r1);
	xmm0.r2 = vec_xor(xmm0.r2, (vector double)swap.r2);
	xmm0.r3 = vec_xor(xmm0.r3, (vector double)swap.r3);
	return simd_trait<double,cyme::vmx,4>::register_type (xmm0.r0,xmm0.r1,
							      xmm0.r2,xmm0.r3);
    }

#ifdef __FMA__
    /**
      Returns a vector containing the results of performing a fused multiply/add for each corresponding
     set of elements of the given vectors.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_fma<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0,
                                simd_trait<double,cyme::vmx,1>::register_type xmm1,
                                simd_trait<double,cyme::vmx,1>::register_type xmm2){
	return vec_madd(xmm0,xmm1,xmm2);
    }

    /**
      Returns a vector containing the results of performing a fused multiply/add for each corresponding
     set of elements of the given vectors.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_fma<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0,
                                simd_trait<double,cyme::vmx,2>::register_type xmm1,
                                simd_trait<double,cyme::vmx,2>::register_type xmm2){
        return simd_trait<double,cyme::vmx,2>::register_type(vec_madd(xmm0.r0,xmm1.r0,xmm2.r0),
							     vec_madd(xmm0.r1,xmm1.r1,xmm2.r1));
    }

    /**
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_fma<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0,
                                simd_trait<double,cyme::vmx,4>::register_type xmm1,
                                simd_trait<double,cyme::vmx,4>::register_type xmm2){
        return simd_trait<double,cyme::vmx,4>::register_type(vec_madd(xmm0.r0,xmm1.r0,xmm2.r0),
							     vec_madd(xmm0.r1,xmm1.r1,xmm2.r1),
							     vec_madd(xmm0.r2,xmm1.r2,xmm2.r2),
							     vec_madd(xmm0.r3,xmm1.r3,xmm2.r3));
    }

    /**
      Returns a vector containing the results of performing a negative multiply-subtract
     operation on the given vectors.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_nfma<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0,
                                 simd_trait<double,cyme::vmx,1>::register_type xmm1,
                                 simd_trait<double,cyme::vmx,1>::register_type xmm2){
        return vec_nmsub(xmm0,xmm1,xmm2);
    }

    /**
      Returns a vector containing the results of performing a negative multiply-subtract
     operation on the given vectors.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_nfma<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0,
                                 simd_trait<double,cyme::vmx,2>::register_type xmm1,
                                 simd_trait<double,cyme::vmx,2>::register_type xmm2){
        return simd_trait<double,cyme::vmx,2>::register_type(vec_nmsub(xmm0.r0,xmm1.r0,xmm2.r0),
							     vec_nmsub(xmm0.r1,xmm1.r1,xmm2.r1));
    }

    /**
      Returns a vector containing the results of performing a negative multiply-subtract
     operation on the given vectors.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_nfma<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0,
                                 simd_trait<double,cyme::vmx,4>::register_type xmm1,
                                 simd_trait<double,cyme::vmx,4>::register_type xmm2){
        return simd_trait<double,cyme::vmx,4>::register_type(vec_nmsub(xmm0.r0,xmm1.r0,xmm2.r0),
							     vec_nmsub(xmm0.r1,xmm1.r1,xmm2.r1),
							     vec_nmsub(xmm0.r2,xmm1.r2,xmm2.r2),
							     vec_nmsub(xmm0.r3,xmm1.r3,xmm2.r3));
    }

    /**
      Returns a vector containing the results of performing a multiply-substract operation using the given vectors.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_fms<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0,
                                simd_trait<double,cyme::vmx,1>::register_type xmm1,
                                simd_trait<double,cyme::vmx,1>::register_type xmm2){
	return vec_msub(xmm0,xmm1,xmm2);
    }

    /**
      Returns a vector containing the results of performing a multiply-substract operation using the given vectors.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_fms<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0,
                                simd_trait<double,cyme::vmx,2>::register_type xmm1,
                                simd_trait<double,cyme::vmx,2>::register_type xmm2){
        return simd_trait<double,cyme::vmx,2>::register_type(vec_msub(xmm0.r0,xmm1.r0,xmm2.r0),
							     vec_msub(xmm0.r1,xmm1.r1,xmm2.r1));
    }

    /**
      Returns a vector containing the results of performing a multiply-substract operation using the given vectors.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_fms<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0,
                                simd_trait<double,cyme::vmx,4>::register_type xmm1,
                                simd_trait<double,cyme::vmx,4>::register_type xmm2){
        return simd_trait<double,cyme::vmx,4>::register_type(vec_msub(xmm0.r0,xmm1.r0,xmm2.r0),
							     vec_msub(xmm0.r1,xmm1.r1,xmm2.r1),
							     vec_msub(xmm0.r2,xmm1.r2,xmm2.r2),
							     vec_msub(xmm0.r3,xmm1.r3,xmm2.r3));
    }

    /**
     Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
       specialisation double,cyme::vmx,1 regs
    */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_nfms<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0,
                                 simd_trait<double,cyme::vmx,1>::register_type xmm1,
                                 simd_trait<double,cyme::vmx,1>::register_type xmm2){
	return vec_nmadd(xmm0,xmm1,xmm2);
    }

    /**
     Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
       specialisation double,cyme::vmx,2 regs
    */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_nfms<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0,
                                 simd_trait<double,cyme::vmx,2>::register_type xmm1,
                                 simd_trait<double,cyme::vmx,2>::register_type xmm2){
        return simd_trait<double,cyme::vmx,2>::register_type(vec_nmadd(xmm0.r0,xmm1.r0,xmm2.r0),
							     vec_nmadd(xmm0.r1,xmm1.r1,xmm2.r1));
    }

    /**
     Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
       specialisation double,cyme::vmx,4 regs
    */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_nfms<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0,
                                 simd_trait<double,cyme::vmx,4>::register_type xmm1,
                                 simd_trait<double,cyme::vmx,4>::register_type xmm2){
        return simd_trait<double,cyme::vmx,4>::register_type(vec_nmadd(xmm0.r0,xmm1.r0,xmm2.r0),
							     vec_nmadd(xmm0.r1,xmm1.r1,xmm2.r1),
							     vec_nmadd(xmm0.r2,xmm1.r2,xmm2.r2),
							     vec_nmadd(xmm0.r3,xmm1.r3,xmm2.r3));
    }
#endif

    /**
      Loads a vector from the given cyme address.
       specialisation int,cyme::vmx,1 regs
    */
    template<>
    forceinline simd_trait<int,cyme::vmx,1>::register_type
    _mm_load<int,cyme::vmx,1>(simd_trait<int,cyme::vmx,1>::const_pointer a){
        return vec_vsx_ld(0, (vector int*)a);
    }

    /**
      Loads a vector from the given cyme address.
       specialisation int,cyme::vmx,2 regs
    */
    template<>
    forceinline simd_trait<int,cyme::vmx,2>::register_type
    _mm_load<int,cyme::vmx,2>(simd_trait<int,cyme::vmx,2>::const_pointer a){
        return simd_trait<int,cyme::vmx,2>::register_type(vec_vsx_ld(0,(vector int*)a),
			                                  vec_vsx_ld(16,(vector int*)a));
    }

    /**
      Loads a vector from the given cyme address.
       specialisation int,cyme::vmx,4 regs
    */
    template<>
    forceinline simd_trait<int,cyme::vmx,4>::register_type
    _mm_load<int,cyme::vmx,4>(simd_trait<int,cyme::vmx,4>::const_pointer a){
        return simd_trait<int,cyme::vmx,4>::register_type(vec_vsx_ld(0,(vector int*)a),
							  vec_vsx_ld(16,(vector int*)a),
							  vec_vsx_ld(32,(vector int*)a),
							  vec_vsx_ld(48,(vector int*)a));
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation float,cyme::vmx,1 regs
    */
    template<>
    forceinline void
    _mm_store<int,cyme::vmx,1>(simd_trait<int,cyme::vmx,1>::register_type xmm0,
                                 simd_trait<int,cyme::vmx,1>::pointer  a){
        vec_vsx_st(xmm0,0,(vector int*)a);
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation int,cyme::vmx,2 regs
    */
    template<>
    forceinline void
    _mm_store<int,cyme::vmx,2>(simd_trait<int,cyme::vmx,2>::register_type xmm0,
                                 simd_trait<int,cyme::vmx,2>::pointer a){
        vec_vsx_st(xmm0.r0,0,(vector int*)a);
	vec_vsx_st(xmm0.r1,16,(vector int*)a);
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation int,cyme::vmx,4 regs
    */
    template<>
    forceinline void
    _mm_store<int,cyme::vmx,4>(simd_trait<int,cyme::vmx,4>::register_type xmm0,
                                 simd_trait<int,cyme::vmx,4>::pointer a){
        vec_vsx_st(xmm0.r0,0,(vector int*)a);
	vec_vsx_st(xmm0.r1,16,(vector int*)a);
	vec_vsx_st(xmm0.r2,32,(vector int*)a);
	vec_vsx_st(xmm0.r3,48,(vector int*)a);
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation int,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<int,cyme::vmx,1>::register_type
    _mm_load1<int,cyme::vmx,1>(const simd_trait<int,cyme::vmx,1>::value_type &a){
       return vec_splats(a);
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation int,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<int,cyme::vmx,2>::register_type
    _mm_load1<int,cyme::vmx,2>(const simd_trait<int,cyme::vmx,2>::value_type &a){
        return simd_trait<int,cyme::vmx,2>::register_type(vec_splats(a),vec_splats(a));
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation int,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<int,cyme::vmx,4>::register_type
    _mm_load1<int,cyme::vmx,4>(const simd_trait<int,cyme::vmx,4>::value_type &a){
        return simd_trait<int,cyme::vmx,4>::register_type(vec_splats(a),vec_splats(a),
	                                                  vec_splats(a),vec_splats(a));
    }
} //end namespace

#undef vec_ctd
#undef vec_ctds

#endif
