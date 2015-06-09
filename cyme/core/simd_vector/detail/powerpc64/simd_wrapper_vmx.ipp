/*
* Cyme - simd_wrapper_vmx.ipp, Copyright (c), 2014,
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
* @file cyme/core/simd_vector/detail/powerpc64/simd_wrapper_vmx.ipp
* Final specialisation for math functions and vmx technology
*/
#ifndef CYME_SIMD_WRAPPER_VMX_IPP
#define CYME_SIMD_WRAPPER_VMX_IPP

#include <boost/cstdint.hpp>
#include <assert.h>
/*
extern "C" vector4double expd4(vector4double);// link to the fortran one
extern "C" vector4double logd4(vector4double);// link to the fortran one
*/
namespace cyme{
    /**
       Load a single-precision (32-bit) floating-point element from cyme into lower element of dst.
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_single_load<float,cyme::vmx,1>(const simd_trait<float,cyme::vmx,1>::value_type b){
        return vec_vsx_ld(0, (vector float*)&b);
    }

    /**
       store a double-precision (32-bit) floating-point element from register lower element to cyme.
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
    _mm_exp<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type __attribute__((unused))xmm0){
        assert(false);
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_exp<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type __attribute__((unused))xmm0){
        assert(false);
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_exp<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type __attribute__((unused))xmm0){
        assert(false);
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_log<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type __attribute__((unused))xmm0){
        assert(false);
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_log<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type __attribute__((unused))xmm0){
        assert(false);
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_log<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type __attribute__((unused))xmm0){
        assert(false);
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
      Compute 1/recsqrt (32-bit) floating point elements in xmm0 to packed double-precision
     (64-bit) floating-point elements, and store the results in dst.
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
      Compute 1/recsqrt (32-bit) floating point elements in xmm0 to packed double-precision
     (64-bit) floating-point elements, and store the results in dst.
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
      Compute 1/recsqrt (32-bit) floating point elements in xmm0 to packed double-precision
     (64-bit) floating-point elements, and store the results in dst.
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
        simd_trait<float,cyme::vmx,1>::register_type mask(__builtin_vsx_xvcvsxwsp(vec_splats((signed int)0x80000000)));
	return vec_xor(xmm0,mask);
	//return vec_neg(xmm0);
    }

    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_neg<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0){
        simd_trait<float,cyme::vmx,1>::register_type mask(__builtin_vsx_xvcvsxwsp(vec_splats((signed int)0x80000000)));
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
        simd_trait<float,cyme::vmx,1>::register_type mask(__builtin_vsx_xvcvsxwsp(vec_splats((signed int)0x80000000)));
	return simd_trait<float,cyme::vmx,4>::register_type(vec_xor(xmm0.r0,mask),
							    vec_xor(xmm0.r1,mask),
							    vec_xor(xmm0.r2,mask),
							    vec_xor(xmm0.r3,mask));
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_cast<float,cyme::vmx,1>(simd_trait<int,cyme::vmx,1>::register_type xmm0){
        return __builtin_vsx_xvcvsxwsp(xmm0);
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_cast<float,cyme::vmx,2>(simd_trait<int,cyme::vmx,2>::register_type xmm0){
        return simd_trait<float,cyme::vmx,2>::register_type(__builtin_vsx_xvcvsxwsp(xmm0.r0),
							    __builtin_vsx_xvcvsxwsp(xmm0.r1));
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_cast<float,cyme::vmx,4>(simd_trait<int,cyme::vmx,4>::register_type xmm0){
        return simd_trait<float,cyme::vmx,4>::register_type(__builtin_vsx_xvcvsxwsp(xmm0.r0),
							    __builtin_vsx_xvcvsxwsp(xmm0.r1),
							    __builtin_vsx_xvcvsxwsp(xmm0.r2),
							    __builtin_vsx_xvcvsxwsp(xmm0.r3));
    }

    /**
      Returns a vector containing the largest representable floating-point integral
     values less than or equal to the values of the corresponding elements of the given vector.
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<int,cyme::vmx,1>::register_type
    _mm_floor<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0){
	return __builtin_vsx_xvcvspsxws(vec_floor(xmm0));
}

    /**
      Returns a vector containing the largest representable floating-point integral
     values less than or equal to the values of the corresponding elements of the given vector.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<int,cyme::vmx,2>::register_type
    _mm_floor<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0){
        return simd_trait<int,cyme::vmx,2>::register_type(__builtin_vsx_xvcvspsxws(vec_floor(xmm0.r0)),
							  __builtin_vsx_xvcvspsxws(vec_floor(xmm0.r1)));
}

    /**
      Returns a vector containing the largest representable floating-point integral
     values less than or equal to the values of the corresponding elements of the given vector.
       specialisation float,cyme::vmx,4 regs
     */

    template<>
    forceinline simd_trait<int,cyme::vmx,4>::register_type
    _mm_floor<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0){
        return simd_trait<int,cyme::vmx,4>::register_type(__builtin_vsx_xvcvspsxws(vec_floor(xmm0.r0)),
							  __builtin_vsx_xvcvspsxws(vec_floor(xmm0.r1)),
							  __builtin_vsx_xvcvspsxws(vec_floor(xmm0.r2)),
							  __builtin_vsx_xvcvspsxws(vec_floor(xmm0.r3)));
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer, as the BG/Q does not
     support vmx integer the computation is done serialy using C trick
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_twok<float,cyme::vmx,1>(simd_trait<int,cyme::vmx,1>::register_type xmm0){
        return vec_expte(__builtin_vsx_xvcvsxwsp(xmm0));
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer, as the BG/Q does not
     support vmx integer the computation is done serialy using C trick
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_twok<float,cyme::vmx,2>(simd_trait<int,cyme::vmx,2>::register_type xmm0){
        return simd_trait<float,cyme::vmx,2>::register_type(vec_expte(__builtin_vsx_xvcvsxwsp(xmm0.r0)),
							    vec_expte(__builtin_vsx_xvcvsxwsp(xmm0.r1)));
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer, as the BG/Q does not
     support vmx integer the computation is done serialy using C trick
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_twok<float,cyme::vmx,4>(simd_trait<int,cyme::vmx,4>::register_type xmm0){
        return simd_trait<float,cyme::vmx,4>::register_type(vec_expte(__builtin_vsx_xvcvsxwsp(xmm0.r0)),
							    vec_expte(__builtin_vsx_xvcvsxwsp(xmm0.r1)),
							    vec_expte(__builtin_vsx_xvcvsxwsp(xmm0.r2)),
							    vec_expte(__builtin_vsx_xvcvsxwsp(xmm0.r3)));
    }

    /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
      arithmetic are very badly supported with AVX, I am presently glue I so do the compuation in SSE;
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_ge<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0){
	vector signed int tmp = __builtin_vsx_xvcvspsxws(xmm0);
	tmp = vec_sr(tmp,vec_splats((unsigned int)23));
	tmp = vec_sub(tmp, vec_splats(127));
	return __builtin_vsx_xvcvsxwsp(tmp);
    }

    /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
      arithmetic are very badly supported with AVX, I am presently glue I so do the compuation in SSE;
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_ge<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0){
	vector signed int tmp0 =__builtin_vsx_xvcvspsxws(xmm0.r0);
	vector signed int tmp1 =__builtin_vsx_xvcvspsxws(xmm0.r1);
	tmp0 = vec_sr(tmp0,vec_splats((unsigned int)23));
	tmp1 = vec_sr(tmp1,vec_splats((unsigned int)23));
	tmp0 = vec_sub(tmp0, vec_splats(127));
	tmp1 = vec_sub(tmp1, vec_splats(127));
	return simd_trait<float,cyme::vmx,2>::register_type(__builtin_vsx_xvcvsxwsp(tmp0),
							    __builtin_vsx_xvcvsxwsp(tmp1));
    }

    /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
      arithmetic are very badly supported with AVX, I am presently glue I so do the compuation in SSE;
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_ge<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0){
	vector signed int tmp0 =__builtin_vsx_xvcvspsxws(xmm0.r0);
	vector signed int tmp1 =__builtin_vsx_xvcvspsxws(xmm0.r1);
	vector signed int tmp2 =__builtin_vsx_xvcvspsxws(xmm0.r2);
	vector signed int tmp3 =__builtin_vsx_xvcvspsxws(xmm0.r3);
	tmp0 = vec_sr(tmp0,vec_splats((unsigned int)23));
	tmp1 = vec_sr(tmp1,vec_splats((unsigned int)23));
	tmp2 = vec_sr(tmp2,vec_splats((unsigned int)23));
	tmp3 = vec_sr(tmp3,vec_splats((unsigned int)23));
	tmp0 = vec_sub(tmp0, vec_splats(127));
	tmp1 = vec_sub(tmp1, vec_splats(127));
	tmp2 = vec_sub(tmp2, vec_splats(127));
	tmp3 = vec_sub(tmp3, vec_splats(127));
	return simd_trait<float,cyme::vmx,4>::register_type(__builtin_vsx_xvcvsxwsp(tmp0),
							    __builtin_vsx_xvcvsxwsp(tmp1),
							    __builtin_vsx_xvcvsxwsp(tmp2),
							    __builtin_vsx_xvcvsxwsp(tmp3));
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_gf<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0){
	vector signed int tmp = __builtin_vsx_xvcvspsxws(xmm0);
	tmp = vec_and(tmp, vec_splats((signed int)0x7fffff));
	tmp = vec_add(tmp, vec_splats((signed int)0x3f800000));
	return __builtin_vsx_xvcvsxwsp(tmp);
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_gf<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0){
	vector signed int tmp0 = __builtin_vsx_xvcvspsxws(xmm0.r0);
	vector signed int tmp1 = __builtin_vsx_xvcvspsxws(xmm0.r1);
	tmp0 = vec_and(tmp0, vec_splats((signed int)0x7fffff));
	tmp1 = vec_and(tmp1, vec_splats((signed int)0x7fffff));
	tmp0 = vec_add(tmp0, vec_splats((signed int)0x3f800000));
	tmp1 = vec_add(tmp1, vec_splats((signed int)0x3f800000));
	return simd_trait<float,cyme::vmx,2>::register_type(__builtin_vsx_xvcvsxwsp(tmp0),
							    __builtin_vsx_xvcvsxwsp(tmp1));
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_gf<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0){
	vector signed int tmp0 = __builtin_vsx_xvcvspsxws(xmm0.r0);
	vector signed int tmp1 = __builtin_vsx_xvcvspsxws(xmm0.r1);
	vector signed int tmp2 = __builtin_vsx_xvcvspsxws(xmm0.r2);
	vector signed int tmp3 = __builtin_vsx_xvcvspsxws(xmm0.r3);
	tmp0 = vec_and(tmp0, vec_splats((signed int)0x7fffff));
	tmp1 = vec_and(tmp1, vec_splats((signed int)0x7fffff));
	tmp2 = vec_and(tmp2, vec_splats((signed int)0x7fffff));
	tmp3 = vec_and(tmp3, vec_splats((signed int)0x7fffff));
	tmp0 = vec_add(tmp0, vec_splats((signed int)0x3f800000));
	tmp1 = vec_add(tmp1, vec_splats((signed int)0x3f800000));
	tmp2 = vec_add(tmp2, vec_splats((signed int)0x3f800000));
	tmp3 = vec_add(tmp3, vec_splats((signed int)0x3f800000));
	return simd_trait<float,cyme::vmx,4>::register_type(__builtin_vsx_xvcvsxwsp(tmp0),
							    __builtin_vsx_xvcvsxwsp(tmp1),
							    __builtin_vsx_xvcvsxwsp(tmp2),
							    __builtin_vsx_xvcvsxwsp(tmp3));
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
      Returns a vector containing the results of performing a multiply-substracti
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
      Returns a vector containing the results of performing a multiply-substracti
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
      Returns a vector containing the results of performing a multiply-substracti
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
							     vec_vsx_ld(32,(vector double*)a));
    }

    /**
      Loads a vector from the given cyme address.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_load<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::const_pointer a){
        return simd_trait<double,cyme::vmx,4>::register_type(vec_vsx_ld(0,(vector double*)a),
							     vec_vsx_ld(32,(vector double*)a),
							     vec_vsx_ld(64,(vector double*)a),
							     vec_vsx_ld(96,(vector double*)a));
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
	vec_vsx_st(xmm0.r1,32,(vector double*)a);
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
	vec_vsx_st(xmm0.r1,32,(vector double*)a);
	vec_vsx_st(xmm0.r2,64,(vector double*)a);
	vec_vsx_st(xmm0.r3,96,(vector double*)a);
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
        return vec_div(xmm0,xmm1);
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
    _mm_exp<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type __attribute__((unused))xmm0){
        assert(false);
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_exp<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type __attribute__((unused))xmm0){
         assert(false);
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_exp<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type __attribute__((unused))xmm0){
         assert(false);
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_log<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type __attribute__((unused))xmm0){
        assert(false);
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_log<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type __attribute__((unused))xmm0){
         assert(false);
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_log<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type __attribute__((unused))xmm0){
         assert(false);
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
        simd_trait<double,cyme::vmx,1>::register_type mask(__builtin_vsx_xvcvsxwdp(vec_splats((signed int)0x8000000000000000)));
	return vec_xor(xmm0, mask);
}

    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_neg<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0){
        simd_trait<double,cyme::vmx,1>::register_type mask(__builtin_vsx_xvcvsxwdp(vec_splats((signed int)0x8000000000000000)));
        return simd_trait<double,cyme::vmx,2>::register_type(vec_xor(xmm0.r0, mask),
							     vec_xor(xmm0.r1, mask));
    }

    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_neg<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0){
        simd_trait<double,cyme::vmx,1>::register_type mask(__builtin_vsx_xvcvsxwdp(vec_splats((signed int)0x8000000000000000)));
        return simd_trait<double,cyme::vmx,4>::register_type(vec_xor(xmm0.r0, mask),
							     vec_xor(xmm0.r1, mask),
							     vec_xor(xmm0.r2, mask),
							     vec_xor(xmm0.r3, mask));
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_cast<double,cyme::vmx,1>(simd_trait<int,cyme::vmx,1>::register_type xmm0){
	return __builtin_vsx_xvcvsxwdp(xmm0);
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_cast<double,cyme::vmx,2>(simd_trait<int,cyme::vmx,2>::register_type xmm0){
        return simd_trait<double,cyme::vmx,2>::register_type( __builtin_vsx_xvcvsxwdp(xmm0.r0),
							      __builtin_vsx_xvcvsxwdp(xmm0.r1));
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_cast<double,cyme::vmx,4>(simd_trait<int,cyme::vmx,4>::register_type xmm0){
        return simd_trait<double,cyme::vmx,4>::register_type(__builtin_vsx_xvcvsxwdp(xmm0.r0),
							     __builtin_vsx_xvcvsxwdp(xmm0.r1),
							     __builtin_vsx_xvcvsxwdp(xmm0.r2),
							     __builtin_vsx_xvcvsxwdp(xmm0.r3));
    }


    /**
      Returns a vector containing the largest representable floating-point integral values less than or equal
     to the values of the corresponding elements of the given vector.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<int,cyme::vmx,1>::register_type
    _mm_floor<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0){
	return __builtin_vsx_xvcvdpsxws(vec_floor(xmm0));
    }

    /**
      Returns a vector containing the largest representable floating-point integral values less than or equal
     to the values of the corresponding elements of the given vector.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<int,cyme::vmx,2>::register_type
    _mm_floor<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0){
        return simd_trait<int,cyme::vmx,2>::register_type(__builtin_vsx_xvcvdpsxws(vec_floor(xmm0.r0)),
							  __builtin_vsx_xvcvdpsxws(vec_floor(xmm0.r1)));
    }

    /**
      Returns a vector containing the largest representable floating-point integral values less than or equal
     to the values of the corresponding elements of the given vector.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<int,cyme::vmx,4>::register_type
    _mm_floor<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0){
        return simd_trait<int,cyme::vmx,4>::register_type(__builtin_vsx_xvcvdpsxws(vec_floor(xmm0.r0)),
							  __builtin_vsx_xvcvdpsxws(vec_floor(xmm0.r1)),
							  __builtin_vsx_xvcvdpsxws(vec_floor(xmm0.r2)),
							  __builtin_vsx_xvcvdpsxws(vec_floor(xmm0.r3)));
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer, as the BG/Q does not support vmx integer
     the computation is done serialy using C trick
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_twok<double,cyme::vmx,1>(simd_trait<int,cyme::vmx,1>::register_type __attribute__((unused))xmm0){
        assert(false);
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer, as the BG/Q does not support vmx integer
     the computation is done serialy using C trick
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_twok<double,cyme::vmx,2>(simd_trait<int,cyme::vmx,2>::register_type __attribute__((unused))xmm0){
        assert(false);
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer, as the BG/Q does not support vmx integer
     the computation is done serialy using C trick
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_twok<double,cyme::vmx,4>(simd_trait<int,cyme::vmx,4>::register_type __attribute__((unused))xmm0){
        assert(false);
    }

   /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
      arithmetic are very badly supported with AVX, I am presently glue I so do the compuation in SSE;
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_ge<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type __attribute__((unused))xmm0){
	//vector signed int tmp = __builtin_vsx_xvcvspsxws(xmm0);
	//tmp = vec_sr(tmp,vec_splats((unsigned int)52));
	//tmp = vec_sub(tmp,vec_splats(1023));
	//shuffle???
	//return __builtin_vsx_xvcvdpsxws(tmp);
        assert(false);
    }

   /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
      arithmetic are very badly supported with AVX, I am presently glue I so do the compuation in SSE;
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_ge<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type __attribute__((unused))xmm0){
	//vector signed int tmp0 = __builtin_vsx_xvcvspsxws(xmm0.r0);
	//vector signed int tmp1 = __builtin_vsx_xvcvspsxws(xmm0.r1);
	//tmp0 = vec_sr(tmp0,vec_splats((unsigned int)52));
	//tmp1 = vec_sr(tmp1,vec_splats((unsigned int)52));
	//tmp0 = vec_sub(tmp0,vec_splats(1023));
	//tmp1 = vec_sub(tmp1,vec_splats(1023));
	//shuffle???
        //return simd_trait<double,cyme::vmx,2>::register_type(__builtin_vsx_xvcvdpsxws(tmp0),
        //						       __builtin_vsx_xvcvdpsxws(tmp1));
        assert(false);
    }

   /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
      arithmetic are very badly supported with AVX, I am presently glue I so do the compuation in SSE;
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_ge<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type __attribute__((unused))xmm0){
	//vector signed int tmp0 = __builtin_vsx_xvcvspsxws(xmm0.r0);
	//vector signed int tmp1 = __builtin_vsx_xvcvspsxws(xmm0.r1);
	//vector signed int tmp2 = __builtin_vsx_xvcvspsxws(xmm0.r2);
	//vector signed int tmp3 = __builtin_vsx_xvcvspsxws(xmm0.r3);
	//tmp0 = vec_sr(tmp0,vec_splats((unsigned int)52));
	//tmp1 = vec_sr(tmp1,vec_splats((unsigned int)52));
	//tmp2 = vec_sr(tmp2,vec_splats((unsigned int)52));
	//tmp3 = vec_sr(tmp3,vec_splats((unsigned int)52));
	//tmp0 = vec_sub(tmp0,vec_splats(1023));
	//tmp1 = vec_sub(tmp1,vec_splats(1023));
	//tmp2 = vec_sub(tmp2,vec_splats(1023));
	//tmp3 = vec_sub(tmp3,vec_splats(1023));
	//shuffle???
        //return simd_trait<double,cyme::vmx,4>::register_type(__builtin_vsx_xvcvdpsxws(tmp0),
        //						       __builtin_vsx_xvcvdpsxws(tmp1),
        //						       __builtin_vsx_xvcvdpsxws(tmp2),
        //						       __builtin_vsx_xvcvdpsxws(tmp3));
        assert(false);
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_gf<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0){
	vector signed int tmp = __builtin_vsx_xvcvdpsxws(xmm0);
        tmp = vec_and(tmp,vec_splats((signed int)0xfffffffffffff));
        tmp = vec_add(tmp,vec_splats((signed int)0x3ff0000000000000));
	return __builtin_vsx_xvcvsxwdp(tmp);
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_gf<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0){
	vector signed int tmp0 = __builtin_vsx_xvcvdpsxws(xmm0.r0);
	vector signed int tmp1 = __builtin_vsx_xvcvdpsxws(xmm0.r1);
        tmp0 = vec_and(tmp0,vec_splats((signed int)0xfffffffffffff));
        tmp1 = vec_and(tmp1,vec_splats((signed int)0xfffffffffffff));
        tmp0 = vec_add(tmp0,vec_splats((signed int)0x3ff0000000000000));
        tmp1 = vec_add(tmp1,vec_splats((signed int)0x3ff0000000000000));
        return simd_trait<double,cyme::vmx,2>::register_type(__builtin_vsx_xvcvsxwdp(tmp0),
							     __builtin_vsx_xvcvsxwdp(tmp1));
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_gf<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0){
	vector signed int tmp0 = __builtin_vsx_xvcvdpsxws(xmm0.r0);
	vector signed int tmp1 = __builtin_vsx_xvcvdpsxws(xmm0.r1);
	vector signed int tmp2 = __builtin_vsx_xvcvdpsxws(xmm0.r2);
	vector signed int tmp3 = __builtin_vsx_xvcvdpsxws(xmm0.r3);
        tmp0 = vec_and(tmp0,vec_splats((signed int)0xfffffffffffff));
        tmp1 = vec_and(tmp1,vec_splats((signed int)0xfffffffffffff));
        tmp2 = vec_and(tmp2,vec_splats((signed int)0xfffffffffffff));
        tmp3 = vec_and(tmp3,vec_splats((signed int)0xfffffffffffff));
        tmp0 = vec_add(tmp0,vec_splats((signed int)0x3ff0000000000000));
        tmp1 = vec_add(tmp1,vec_splats((signed int)0x3ff0000000000000));
        tmp2 = vec_add(tmp2,vec_splats((signed int)0x3ff0000000000000));
        tmp3 = vec_add(tmp3,vec_splats((signed int)0x3ff0000000000000));
        return simd_trait<double,cyme::vmx,4>::register_type(__builtin_vsx_xvcvsxwdp(tmp0),
							     __builtin_vsx_xvcvsxwdp(tmp1),
							     __builtin_vsx_xvcvsxwdp(tmp2),
							     __builtin_vsx_xvcvsxwdp(tmp3));
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
      Returns a vector containing the results of performing a fused multiply/add for each corresponding
     set of elements of the given vectors.
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
							     vec_nmsub(xmm0.r1,xmm1.r1,xmm2.r1),
							     vec_nmsub(xmm0.r1,xmm1.r1,xmm2.r1));
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
} //end namespace

#endif
