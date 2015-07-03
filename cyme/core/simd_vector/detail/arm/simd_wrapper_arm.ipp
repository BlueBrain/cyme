/*
* Cyme - simd_wrapper_arm.ipp, Copyright (c), 2014,
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
* @file cyme/core/simd_vector/detail/arm/simd_wrapper_arm.ipp
* Final specialisation for math functions and arm technology
*/
#ifndef CYME_SIMD_WRAPPER_ARM_IPP
#define CYME_SIMD_WRAPPER_ARM_IPP

#include <boost/cstdint.hpp>
#include <assert.h>
#include <iostream>
//extern "C" vector float expf4(vector float vx);// link to the fortran one
//extern "C" vector float logf4(vector float vx);// link to the fortran one
//extern "C" vector double expd4(vector double vx);// link to the fortran one
//extern "C" vector double logd4(vector double vx);// link to the fortran one

namespace cyme{
    /**
       Load a single-precision (32-bit) floating-point element from cyme into lower element of dst.
     */
    template<>
    forceinline simd_trait<float,cyme::neon,1>::register_type
    _mm_single_load<float,cyme::neon,1>(const simd_trait<float,cyme::neon,1>::value_type b){
	return vld1q_f32(&b);
    }

    /**
       store a single-precision (32-bit) floating-point element from register lower element to cyme.
     */
    template<>
    forceinline simd_trait<float,cyme::neon,1>::value_type
    _mm_single_store<float,cyme::neon,1>(simd_trait<float,cyme::neon,1>::register_type xmm0,
                                         simd_trait<float,cyme::neon,1>::pointer b){
	vst1q_f32(b,xmm0);
	return *b;
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation float,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,1>::register_type
    _mm_load1<float,cyme::neon,1>(const simd_trait<float,cyme::neon,1>::value_type &a){
	return vld1q_dup_f32(&a);
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation float,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,2>::register_type
    _mm_load1<float,cyme::neon,2>(const simd_trait<float,cyme::neon,2>::value_type &a){
	return simd_trait<float,cyme::neon,2>::register_type(vld1q_dup_f32(&a),vld1q_dup_f32(&a));
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation float,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,4>::register_type
    _mm_load1<float,cyme::neon,4>(const simd_trait<float,cyme::neon,4>::value_type &a){
	return simd_trait<float,cyme::neon,4>::register_type(vld1q_dup_f32(&a),vld1q_dup_f32(&a),
							     vld1q_dup_f32(&a),vld1q_dup_f32(&a));
    }

    /**
      Loads a vector from the given cyme address.
       specialisation float,cyme::neon,1 regs
    */
    template<>
    forceinline simd_trait<float,cyme::neon,1>::register_type
    _mm_load<float,cyme::neon,1>(simd_trait<float,cyme::neon,1>::const_pointer a){
	return vld1q_f32(a);
    }

    /**
      Loads a vector from the given cyme address.
       specialisation float,cyme::neon,2 regs
    */
    template<>
    forceinline simd_trait<float,cyme::neon,2>::register_type
    _mm_load<float,cyme::neon,2>(simd_trait<float,cyme::neon,2>::const_pointer a){
	return simd_trait<float,cyme::neon,2>::register_type(vld1q_f32(a),
							     vld1q_f32(a+4));
    }

    /**
      Loads a vector from the given cyme address.
       specialisation float,cyme::neon,4 regs
    */
    template<>
    forceinline simd_trait<float,cyme::neon,4>::register_type
    _mm_load<float,cyme::neon,4>(simd_trait<float,cyme::neon,4>::const_pointer a){
	return simd_trait<float,cyme::neon,4>::register_type(vld1q_f32(a),
							     vld1q_f32(a+4),
							     vld1q_f32(a+8),
							     vld1q_f32(a+12));
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation float,cyme::neon,1 regs
    */
    template<>
    forceinline void
    _mm_store<float,cyme::neon,1>(simd_trait<float,cyme::neon,1>::register_type xmm0,
                                  simd_trait<float,cyme::neon,1>::pointer a){
	vst1q_f32(a,xmm0);
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation float,cyme::neon,2 regs
    */
    template<>
    forceinline void
    _mm_store<float,cyme::neon,2>(simd_trait<float,cyme::neon,2>::register_type xmm0,
                                  simd_trait<float,cyme::neon,2>::pointer a){
	vst1q_f32(a,xmm0.r0);
	vst1q_f32((a+4),xmm0.r1);
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation float,cyme::neon,4 regs
    */
    template<>
    forceinline void
    _mm_store<float,cyme::neon,4>(simd_trait<float,cyme::neon,4>::register_type xmm0,
                                  simd_trait<float,cyme::neon,4>::pointer a){
	vst1q_f32(a,xmm0.r0);
	vst1q_f32((a+4),xmm0.r1);
	vst1q_f32((a+8),xmm0.r2);
	vst1q_f32((a+12),xmm0.r3);
    }

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation float,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,1>::register_type
    _mm_mul<float,cyme::neon,1>(simd_trait<float,cyme::neon,1>::register_type xmm0,
                                simd_trait<float,cyme::neon,1>::register_type xmm1){
	return vmulq_f32(xmm0,xmm1);
    }

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation float,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,2>::register_type
    _mm_mul<float,cyme::neon,2>(simd_trait<float,cyme::neon,2>::register_type xmm0,
                                simd_trait<float,cyme::neon,2>::register_type xmm1){
	return simd_trait<float,cyme::neon,2>::register_type(vmulq_f32(xmm0.r0,xmm1.r0),
							     vmulq_f32(xmm0.r1,xmm1.r1));
    }

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation float,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,4>::register_type
    _mm_mul<float,cyme::neon,4>(simd_trait<float,cyme::neon,4>::register_type xmm0,
                                simd_trait<float,cyme::neon,4>::register_type xmm1){
	return simd_trait<float,cyme::neon,4>::register_type(vmulq_f32(xmm0.r0,xmm1.r0),
							     vmulq_f32(xmm0.r1,xmm1.r1),
							     vmulq_f32(xmm0.r2,xmm1.r2),
							     vmulq_f32(xmm0.r3,xmm1.r3));
    }

    /**
       Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation float,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,1>::register_type
    _mm_div<float,cyme::neon,1>(simd_trait<float,cyme::neon,1>::register_type xmm0,
                                simd_trait<float,cyme::neon,1>::register_type xmm1){
	return vdivq_f32(xmm0,xmm1);
    }

    /**
       Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation float,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,2>::register_type
    _mm_div<float,cyme::neon,2>(simd_trait<float,cyme::neon,2>::register_type xmm0,
                                simd_trait<float,cyme::neon,2>::register_type xmm1){
	return simd_trait<float,cyme::neon,2>::register_type(vdivq_f32(xmm0.r0,xmm1.r0),
							     vdivq_f32(xmm0.r1,xmm1.r1));
    }

    /**
       Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation float,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,4>::register_type
    _mm_div<float,cyme::neon,4>(simd_trait<float,cyme::neon,4>::register_type xmm0,
                                simd_trait<float,cyme::neon,4>::register_type xmm1){
	return simd_trait<float,cyme::neon,4>::register_type(vdivq_f32(xmm0.r0,xmm1.r0),
							     vdivq_f32(xmm0.r1,xmm1.r1),
							     vdivq_f32(xmm0.r2,xmm1.r2),
							     vdivq_f32(xmm0.r3,xmm1.r3));
    }

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation float,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,1>::register_type
    _mm_add<float,cyme::neon,1>(simd_trait<float,cyme::neon,1>::register_type xmm0,
                                simd_trait<float,cyme::neon,1>::register_type xmm1){
	return vaddq_f32(xmm0,xmm1);
    }

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation float,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,2>::register_type
    _mm_add<float,cyme::neon,2>(simd_trait<float,cyme::neon,2>::register_type xmm0,
                                simd_trait<float,cyme::neon,2>::register_type xmm1){
	return simd_trait<float,cyme::neon,2>::register_type(vaddq_f32(xmm0.r0,xmm1.r0),
							     vaddq_f32(xmm0.r1,xmm1.r1));
    }

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation float,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,4>::register_type
    _mm_add<float,cyme::neon,4>(simd_trait<float,cyme::neon,4>::register_type xmm0,
                                simd_trait<float,cyme::neon,4>::register_type xmm1){
	return simd_trait<float,cyme::neon,4>::register_type(vaddq_f32(xmm0.r0,xmm1.r0),
							     vaddq_f32(xmm0.r1,xmm1.r1),
							     vaddq_f32(xmm0.r2,xmm1.r2),
							     vaddq_f32(xmm0.r3,xmm1.r3));
    }

    /**
      Returns a vector containing the result of subtracting each element of b
     from the corresponding element of a.
       specialisation float,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,1>::register_type
    _mm_sub<float,cyme::neon,1>(simd_trait<float,cyme::neon,1>::register_type xmm0,
                                simd_trait<float,cyme::neon,1>::register_type xmm1){
	return vsubq_f32(xmm0,xmm1);
    }

    /**
      Returns a vector containing the result of subtracting each element of b
     from the corresponding element of a.
       specialisation float,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,2>::register_type
    _mm_sub<float,cyme::neon,2>(simd_trait<float,cyme::neon,2>::register_type xmm0,
                                simd_trait<float,cyme::neon,2>::register_type xmm1){
	return simd_trait<float,cyme::neon,2>::register_type(vsubq_f32(xmm0.r0,xmm1.r0),
							     vsubq_f32(xmm0.r1,xmm1.r1));
    }

    /**
      Returns a vector containing the result of subtracting each element of b
     from the corresponding element of a.
       specialisation float,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,4>::register_type
    _mm_sub<float,cyme::neon,4>(simd_trait<float,cyme::neon,4>::register_type xmm0,
                                simd_trait<float,cyme::neon,4>::register_type xmm1){
	return simd_trait<float,cyme::neon,4>::register_type(vsubq_f32(xmm0.r0,xmm1.r0),
							     vsubq_f32(xmm0.r1,xmm1.r1),
							     vsubq_f32(xmm0.r2,xmm1.r2),
							     vsubq_f32(xmm0.r3,xmm1.r3));
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation float,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,1>::register_type
    _mm_exp<float,cyme::neon,1>(simd_trait<float,cyme::neon,1>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation float,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,2>::register_type
    _mm_exp<float,cyme::neon,2>(simd_trait<float,cyme::neon,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation float,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,4>::register_type
    _mm_exp<float,cyme::neon,4>(simd_trait<float,cyme::neon,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation float,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,1>::register_type
    _mm_log<float,cyme::neon,1>(simd_trait<float,cyme::neon,1>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation float,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,2>::register_type
    _mm_log<float,cyme::neon,2>(simd_trait<float,cyme::neon,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation float,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,4>::register_type
    _mm_log<float,cyme::neon,4>(simd_trait<float,cyme::neon,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Returns a vector containing estimates of the reciprocals of the corresponding elements of the given vector.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x) / (1/x) | ≤ 1/256
       specialisation float,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,1>::register_type
    _mm_rec<float,cyme::neon,1>(simd_trait<float,cyme::neon,1>::register_type xmm0){
	return vrecpeq_f32(xmm0);
    }

    /**
      Returns a vector containing estimates of the reciprocals of the corresponding elements of the given vector.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x) / (1/x) | ≤ 1/256
       specialisation float,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,2>::register_type
    _mm_rec<float,cyme::neon,2>(simd_trait<float,cyme::neon,2>::register_type xmm0){
	return simd_trait<float,cyme::neon,2>::register_type(vrecpeq_f32(xmm0.r0),
							     vrecpeq_f32(xmm0.r1));
    }

    /**
      Returns a vector containing estimates of the reciprocals of the corresponding elements of the given vector.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x) / (1/x) | ≤ 1/256
       specialisation float,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,4>::register_type
    _mm_rec<float,cyme::neon,4>(simd_trait<float,cyme::neon,4>::register_type xmm0){
	return simd_trait<float,cyme::neon,4>::register_type(vrecpeq_f32(xmm0.r0),
							     vrecpeq_f32(xmm0.r1),
							     vrecpeq_f32(xmm0.r2),
							     vrecpeq_f32(xmm0.r3));
    }

    /**
      Compute 1/recsqrt (32-bit) floating point elements in xmm0 to packed single-precision
     (32-bit) floating-point elements, and store the results in dst.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
       of a and r is the value of the corresponding element of the result value:
     | (r-1/x^0.5) / (1/x^0.5) | ≤ 1/256
       specialisation float,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,1>::register_type
    _mm_rsqrt<float,cyme::neon,1>(simd_trait<float,cyme::neon,1>::register_type xmm0){
	return vrsqrteq_f32(xmm0);
    }

    /**
      Compute 1/recsqrt (32-bit) floating point elements in xmm0 to packed single-precision
     (32-bit) floating-point elements, and store the results in dst.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
       of a and r is the value of the corresponding element of the result value:
     | (r-1/x^0.5) / (1/x^0.5) | ≤ 1/256
       specialisation float,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,2>::register_type
    _mm_rsqrt<float,cyme::neon,2>(simd_trait<float,cyme::neon,2>::register_type xmm0){
	return simd_trait<float,cyme::neon,2>::register_type(vrsqrteq_f32(xmm0.r0),
							     vrsqrteq_f32(xmm0.r1));
    }

    /**
      Compute 1/recsqrt (32-bit) floating point elements in xmm0 to packed single-precision
     (32-bit) floating-point elements, and store the results in dst.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
       of a and r is the value of the corresponding element of the result value:
     | (r-1/x^0.5) / (1/x^0.5) | ≤ 1/256
       specialisation float,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,4>::register_type
    _mm_rsqrt<float,cyme::neon,4>(simd_trait<float,cyme::neon,4>::register_type xmm0){
	return simd_trait<float,cyme::neon,4>::register_type(vrsqrteq_f32(xmm0.r0),
							     vrsqrteq_f32(xmm0.r1),
							     vrsqrteq_f32(xmm0.r2),
							     vrsqrteq_f32(xmm0.r3));
    }

    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation float,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,1>::register_type
    _mm_neg<float,cyme::neon,1>(simd_trait<float,cyme::neon,1>::register_type xmm0){
	return vnegq_f32(xmm0);
    }

    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation float,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,2>::register_type
    _mm_neg<float,cyme::neon,2>(simd_trait<float,cyme::neon,2>::register_type xmm0){
	return simd_trait<float,cyme::neon,2>::register_type(vnegq_f32(xmm0.r0),
							     vnegq_f32(xmm0.r1));
    }

    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation float,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,4>::register_type
    _mm_neg<float,cyme::neon,4>(simd_trait<float,cyme::neon,4>::register_type xmm0){
	return simd_trait<float,cyme::neon,4>::register_type(vnegq_f32(xmm0.r0),
							     vnegq_f32(xmm0.r1),
							     vnegq_f32(xmm0.r2),
							     vnegq_f32(xmm0.r3));
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed single-precision (32-bit) floating-point elements,
     and store the results in dst.
       specialisation float,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,1>::register_type
    _mm_cast<float,cyme::neon,1>(simd_trait<int,cyme::neon,1>::register_type xmm0){
	return vcvtq_f32_s32(xmm0);
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed single-precision (32-bit) floating-point elements,
     and store the results in dst.
       specialisation float,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,2>::register_type
    _mm_cast<float,cyme::neon,2>(simd_trait<int,cyme::neon,2>::register_type xmm0){
	return simd_trait<float,cyme::neon,2>::register_type(vcvtq_f32_s32(xmm0.r0),
							     vcvtq_f32_s32(xmm0.r1));
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed single-precision (32-bit) floating-point elements,
     and store the results in dst.
       specialisation float,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,4>::register_type
    _mm_cast<float,cyme::neon,4>(simd_trait<int,cyme::neon,4>::register_type xmm0){
	return simd_trait<float,cyme::neon,4>::register_type(vcvtq_f32_s32(xmm0.r0),
							     vcvtq_f32_s32(xmm0.r1),
							     vcvtq_f32_s32(xmm0.r2),
							     vcvtq_f32_s32(xmm0.r3));
    }

    /**
      Returns a vector containing the largest representable floating-point integral
     values less than or equal to the values of the corresponding elements of the given vector.
       specialisation float,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<int,cyme::neon,1>::register_type
    _mm_floor<float,cyme::neon,1>(simd_trait<float,cyme::neon,1>::register_type xmm0){
	//Conversion truncates
	return vcvtq_s32_f32(xmm0);
    }

    /**
      Returns a vector containing the largest representable floating-point integral
     values less than or equal to the values of the corresponding elements of the given vector.
       specialisation float,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<int,cyme::neon,2>::register_type
    _mm_floor<float,cyme::neon,2>(simd_trait<float,cyme::neon,2>::register_type xmm0){
	return simd_trait<int,cyme::neon,2>::register_type(vcvtq_s32_f32(xmm0.r0),
							   vcvtq_s32_f32(xmm0.r1));
    }

    /**
      Returns a vector containing the largest representable floating-point integral
     values less than or equal to the values of the corresponding elements of the given vector.
       specialisation float,cyme::neon,4 regs
     */

    template<>
    forceinline simd_trait<int,cyme::neon,4>::register_type
    _mm_floor<float,cyme::neon,4>(simd_trait<float,cyme::neon,4>::register_type xmm0){
	return simd_trait<int,cyme::neon,4>::register_type(vcvtq_s32_f32(xmm0.r0),
							   vcvtq_s32_f32(xmm0.r1),
							   vcvtq_s32_f32(xmm0.r2),
							   vcvtq_s32_f32(xmm0.r3));
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer
       specialisation float,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,1>::register_type
    _mm_twok<float,cyme::neon,1>(simd_trait<int,cyme::neon,1>::register_type xmm0){
	xmm0 = vaddq_s32(xmm0,vmovq_n_s32(127));
	xmm0 = vshlq_s32(xmm0,vmovq_n_s32(23));
	return (float32x4_t)xmm0; 
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer
       specialisation float,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,2>::register_type
    _mm_twok<float,cyme::neon,2>(simd_trait<int,cyme::neon,2>::register_type xmm0){
	xmm0.r0 = vaddq_s32(xmm0.r0,vmovq_n_s32(127));
	xmm0.r1 = vaddq_s32(xmm0.r1,vmovq_n_s32(127));
	xmm0.r0 = vshlq_s32(xmm0.r0,vmovq_n_s32(23));
	xmm0.r1 = vshlq_s32(xmm0.r1,vmovq_n_s32(23));
	return simd_trait<float,cyme::neon,2>::register_type((float32x4_t)xmm0.r0,
							     (float32x4_t)xmm0.r1);
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer
       specialisation float,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,4>::register_type
    _mm_twok<float,cyme::neon,4>(simd_trait<int,cyme::neon,4>::register_type xmm0){
	xmm0.r0 = vaddq_s32(xmm0.r0,vmovq_n_s32(127));
	xmm0.r1 = vaddq_s32(xmm0.r1,vmovq_n_s32(127));
	xmm0.r2 = vaddq_s32(xmm0.r3,vmovq_n_s32(127));
	xmm0.r3 = vaddq_s32(xmm0.r2,vmovq_n_s32(127));
	xmm0.r0 = vshlq_s32(xmm0.r0,vmovq_n_s32(23));
	xmm0.r1 = vshlq_s32(xmm0.r1,vmovq_n_s32(23));
	xmm0.r2 = vshlq_s32(xmm0.r2,vmovq_n_s32(23));
	xmm0.r3 = vshlq_s32(xmm0.r3,vmovq_n_s32(23));
	return simd_trait<float,cyme::neon,4>::register_type((float32x4_t)xmm0.r0,
							     (float32x4_t)xmm0.r1,
							     (float32x4_t)xmm0.r2,
							     (float32x4_t)xmm0.r3);
    }

    /**
      Extract the exponent of floating-point exponent (32-bit) elements and store the results in dst.
       specialisation float,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,1>::register_type
    _mm_ge<float,cyme::neon,1>(simd_trait<float,cyme::neon,1>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Extract the exponent of floating-point exponent (32-bit) elements and store the results in dst.
       specialisation float,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,2>::register_type
    _mm_ge<float,cyme::neon,2>(simd_trait<float,cyme::neon,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Extract the exponent of floating-point exponent (32-bit) elements and store the results in dst.
       specialisation float,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,4>::register_type
    _mm_ge<float,cyme::neon,4>(simd_trait<float,cyme::neon,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Extract the fraction of floating-point exponent (32-bit) elements and store the results in dst.
       specialisation float,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,1>::register_type
    _mm_gf<float,cyme::neon,1>(simd_trait<float,cyme::neon,1>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Extract the fraction of floating-point exponent (32-bit) elements and store the results in dst.
       specialisation float,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,2>::register_type
    _mm_gf<float,cyme::neon,2>(simd_trait<float,cyme::neon,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Extract the fraction of floating-point exponent (32-bit) elements and store the results in dst.
       specialisation float,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,4>::register_type
    _mm_gf<float,cyme::neon,4>(simd_trait<float,cyme::neon,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

#ifdef __FMA__
    /**
      Returns a vector containing the results of performing a fused multiply/add
     for each corresponding of a set of elements of the given vectors.
     Given arguments a,b, and c,
     result = a*b+c
       specialisation float,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,1>::register_type
    _mm_fma<float,cyme::neon,1>(simd_trait<float,cyme::neon,1>::register_type xmm0,
                                simd_trait<float,cyme::neon,1>::register_type xmm1,
                                simd_trait<float,cyme::neon,1>::register_type xmm2){
	return vfmaq_f32(xmm2,xmm0,xmm1);
    }

    /**
      Returns a vector containing the results of performing a fused multiply/add
     for each corresponding of a set of elements of the given vectors.
     Given arguments a,b, and c,
     result = a*b+c
       specialisation float,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,2>::register_type
    _mm_fma<float,cyme::neon,2>(simd_trait<float,cyme::neon,2>::register_type xmm0,
                                simd_trait<float,cyme::neon,2>::register_type xmm1,
                                simd_trait<float,cyme::neon,2>::register_type xmm2){
	return simd_trait<float,cyme::neon,2>::register_type(vfmaq_f32(xmm2.r0,xmm0.r0,xmm1.r0),
							     vfmaq_f32(xmm2.r1,xmm0.r1,xmm1.r1));
    }

    /**
      Returns a vector containing the results of performing a fused multiply/add
     for each corresponding of a set of elements of the given vectors.
     Given arguments a,b, and c,
     result = a*b+c
       specialisation float,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,4>::register_type
    _mm_fma<float,cyme::neon,4>(simd_trait<float,cyme::neon,4>::register_type xmm0,
                                simd_trait<float,cyme::neon,4>::register_type xmm1,
                                simd_trait<float,cyme::neon,4>::register_type xmm2){
	return simd_trait<float,cyme::neon,4>::register_type(vfmaq_f32(xmm2.r0,xmm0.r0,xmm1.r0),
							     vfmaq_f32(xmm2.r1,xmm0.r1,xmm1.r1),
							     vfmaq_f32(xmm2.r2,xmm0.r2,xmm1.r2),
							     vfmaq_f32(xmm2.r3,xmm0.r3,xmm1.r3));
    }

    /**
      Returns a vector containing the results of performing a negative
      multiply-subtract operation on the given vectors. Given arguments a, b, and c,
      result = -(a*b-c)
      result = c - a*b.
       specialisation float,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,1>::register_type
    _mm_nfma<float,cyme::neon,1>(simd_trait<float,cyme::neon,1>::register_type xmm0,
                                 simd_trait<float,cyme::neon,1>::register_type xmm1,
                                 simd_trait<float,cyme::neon,1>::register_type xmm2){
	return vfmsq_f32(xmm2,xmm0,xmm1);
    }

    /**
      Returns a vector containing the results of performing a negative
      multiply-subtract operation on the given vectors. Given arguments a, b, and c,
      result = -(a*b-c)
      result = c - a*b.
       specialisation float,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,2>::register_type
    _mm_nfma<float,cyme::neon,2>(simd_trait<float,cyme::neon,2>::register_type xmm0,
                                 simd_trait<float,cyme::neon,2>::register_type xmm1,
                                 simd_trait<float,cyme::neon,2>::register_type xmm2){
	return simd_trait<float,cyme::neon,2>::register_type(vfmsq_f32(xmm2.r0,xmm0.r0,xmm1.r0),
							     vfmsq_f32(xmm2.r1,xmm0.r1,xmm1.r1));
    }

    /**
      Returns a vector containing the results of performing a negative
      multiply-subtract operation on the given vectors. Given arguments a, b, and c,
      result = -(a*b-c)
      result = c - a*b.
       specialisation float,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,4>::register_type
    _mm_nfma<float,cyme::neon,4>(simd_trait<float,cyme::neon,4>::register_type xmm0,
                                 simd_trait<float,cyme::neon,4>::register_type xmm1,
                                 simd_trait<float,cyme::neon,4>::register_type xmm2){
	return simd_trait<float,cyme::neon,4>::register_type(vfmsq_f32(xmm2.r0,xmm0.r0,xmm1.r0),
							     vfmsq_f32(xmm2.r1,xmm0.r1,xmm1.r1),
							     vfmsq_f32(xmm2.r2,xmm0.r2,xmm1.r2),
							     vfmsq_f32(xmm2.r3,xmm0.r3,xmm1.r3));
    }

    /**
      Returns a vector containing the results of performing a multiply-substract
      operation on the given vectors. Given arguments a, b, and c,
      result = a*b-c.
       specialisation float,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,1>::register_type
    _mm_fms<float,cyme::neon,1>(simd_trait<float,cyme::neon,1>::register_type xmm0,
                                simd_trait<float,cyme::neon,1>::register_type xmm1,
                                simd_trait<float,cyme::neon,1>::register_type xmm2){
	float32x4_t temp = vfmsq_f32(xmm2,xmm0,xmm1);
	return vnegq_f32(temp);
    }

    /**
      Returns a vector containing the results of performing a multiply-substract
      operation on the given vectors. Given arguments a, b, and c,
      result = a*b-c.
       specialisation float,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,2>::register_type
    _mm_fms<float,cyme::neon,2>(simd_trait<float,cyme::neon,2>::register_type xmm0,
                                simd_trait<float,cyme::neon,2>::register_type xmm1,
                                simd_trait<float,cyme::neon,2>::register_type xmm2){
	float32x4_t temp1 = vfmsq_f32(xmm2.r0,xmm0.r0,xmm1.r0);
	float32x4_t temp2 = vfmsq_f32(xmm2.r1,xmm0.r1,xmm1.r1);
	return simd_trait<float,cyme::neon,2>::register_type(vnegq_f32(temp1),
							     vnegq_f32(temp2));
    }

    /**
      Returns a vector containing the results of performing a multiply-substract
      operation on the given vectors. Given arguments a, b, and c,
      result = a*b-c.
       specialisation float,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,4>::register_type
    _mm_fms<float,cyme::neon,4>(simd_trait<float,cyme::neon,4>::register_type xmm0,
                                simd_trait<float,cyme::neon,4>::register_type xmm1,
                                simd_trait<float,cyme::neon,4>::register_type xmm2){
	float32x4_t temp1 = vfmsq_f32(xmm2.r0,xmm0.r0,xmm1.r0);
	float32x4_t temp2 = vfmsq_f32(xmm2.r1,xmm0.r1,xmm1.r1);
	float32x4_t temp3 = vfmsq_f32(xmm2.r2,xmm0.r2,xmm1.r2);
	float32x4_t temp4 = vfmsq_f32(xmm2.r3,xmm0.r3,xmm1.r3);
	return simd_trait<float,cyme::neon,4>::register_type(vnegq_f32(temp1),
							     vnegq_f32(temp2),
							     vnegq_f32(temp3),
							     vnegq_f32(temp4));
    }

    /**
     Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
     Given arguments a,b, and c,
     result = -(a*b+c)
       specialisation float,cyme::neon,1 regs
    */
    template<>
    forceinline simd_trait<float,cyme::neon,1>::register_type
    _mm_nfms<float,cyme::neon,1>(simd_trait<float,cyme::neon,1>::register_type xmm0,
                                 simd_trait<float,cyme::neon,1>::register_type xmm1,
                                 simd_trait<float,cyme::neon,1>::register_type xmm2){
	float32x4_t temp = vfmaq_f32(xmm2,xmm0,xmm1);
	return vnegq_f32(temp);
    }

    /**
     Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
     Given arguments a,b, and c,
     result = -(a*b+c)
       specialisation float,cyme::neon,2 regs
    */
    template<>
    forceinline simd_trait<float,cyme::neon,2>::register_type
    _mm_nfms<float,cyme::neon,2>(simd_trait<float,cyme::neon,2>::register_type xmm0,
                                 simd_trait<float,cyme::neon,2>::register_type xmm1,
                                 simd_trait<float,cyme::neon,2>::register_type xmm2){
	float32x4_t temp1 = vfmaq_f32(xmm2.r0,xmm0.r0,xmm1.r0);
	float32x4_t temp2 = vfmaq_f32(xmm2.r1,xmm0.r1,xmm1.r1);
	return simd_trait<float,cyme::neon,2>::register_type(vnegq_f32(temp1),
							     vnegq_f32(temp2));
    }

    /**
     Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
     Given arguments a,b, and c,
     result = -(a*b+c)
       specialisation float,cyme::neon,4 regs
    */
    template<>
    forceinline simd_trait<float,cyme::neon,4>::register_type
    _mm_nfms<float,cyme::neon,4>(simd_trait<float,cyme::neon,4>::register_type xmm0,
                                 simd_trait<float,cyme::neon,4>::register_type xmm1,
                                 simd_trait<float,cyme::neon,4>::register_type xmm2){
	float32x4_t temp1 = vfmaq_f32(xmm2.r0,xmm0.r0,xmm1.r0);
	float32x4_t temp2 = vfmaq_f32(xmm2.r1,xmm0.r1,xmm1.r1);
	float32x4_t temp3 = vfmaq_f32(xmm2.r2,xmm0.r2,xmm1.r2);
	float32x4_t temp4 = vfmaq_f32(xmm2.r3,xmm0.r3,xmm1.r3);
	return simd_trait<float,cyme::neon,4>::register_type(vnegq_f32(temp1),
							     vnegq_f32(temp2),
							     vnegq_f32(temp3),
							     vnegq_f32(temp4));
    }
#endif
/*--------------------------------------------------------------------- double ---------------*/
    /**
       Single load a double-precision (64-bit) floating-point element from cyme into lower element of dst.
     */
    template<>
    forceinline simd_trait<double,cyme::neon,1>::register_type
    _mm_single_load<double,cyme::neon,1>(const simd_trait<double,cyme::neon,1>::value_type b){
	return vld1q_f64(&b);
    }

    /**
       Single store a double-precision (64-bit) floating-point element from register lower element to cyme.
     */
    template<>
    forceinline simd_trait<double,cyme::neon,1>::value_type
    _mm_single_store<double,cyme::neon,1>(simd_trait<double,cyme::neon,1>::register_type xmm0,
                                          simd_trait<double,cyme::neon,1>::pointer b){
	vst1q_f64(b,xmm0);
	return *b;
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation double,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,1>::register_type
    _mm_load1<double,cyme::neon,1>(const simd_trait<double,cyme::neon,1>::value_type &a){
	return vld1q_dup_f64(&a);
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation double,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,2>::register_type
    _mm_load1<double,cyme::neon,2>(const simd_trait<double,cyme::neon,2>::value_type &a){
	return simd_trait<double,cyme::neon,2>::register_type(vld1q_dup_f64(&a),vld1q_dup_f64(&a));
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation double,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,4>::register_type
    _mm_load1<double,cyme::neon,4>(const simd_trait<double,cyme::neon,4>::value_type &a){
	return simd_trait<double,cyme::neon,4>::register_type(vld1q_dup_f64(&a),vld1q_dup_f64(&a),
							      vld1q_dup_f64(&a),vld1q_dup_f64(&a));
    }

    /**
      Loads a vector from the given cyme address.
       specialisation double,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,1>::register_type
    _mm_load<double,cyme::neon,1>(simd_trait<double,cyme::neon,1>::const_pointer a){
	return vld1q_f64(a);
    }

    /**
      Loads a vector from the given cyme address.
       specialisation double,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,2>::register_type
    _mm_load<double,cyme::neon,2>(simd_trait<double,cyme::neon,2>::const_pointer a){
	return simd_trait<double,cyme::neon,2>::register_type(vld1q_f64(a),
							      vld1q_f64(a+2));
    }

    /**
      Loads a vector from the given cyme address.
       specialisation double,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,4>::register_type
    _mm_load<double,cyme::neon,4>(simd_trait<double,cyme::neon,4>::const_pointer a){
	return simd_trait<double,cyme::neon,4>::register_type(vld1q_f64(a),
							      vld1q_f64(a+2),
							      vld1q_f64(a+4),
							      vld1q_f64(a+6));
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation double,cyme::neon,1 regs
     */
    template<>
    forceinline void
    _mm_store<double,cyme::neon,1>(simd_trait<double,cyme::neon,1>::register_type xmm0,
                                   simd_trait<double,cyme::neon,1>::pointer a){
	vst1q_f64(a,xmm0);
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation double,cyme::neon,2 regs
     */
    template<>
    forceinline void
    _mm_store<double,cyme::neon,2>(simd_trait<double,cyme::neon,2>::register_type xmm0,
                                   simd_trait<double,cyme::neon,2>::pointer a){
	vst1q_f64(a,xmm0.r0);
	vst1q_f64((a+2),xmm0.r1);
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation double,cyme::neon,4 regs
     */
    template<>
    forceinline void
    _mm_store<double,cyme::neon,4>(simd_trait<double,cyme::neon,4>::register_type xmm0,
                                   simd_trait<double,cyme::neon,4>::pointer a){
	vst1q_f64(a,xmm0.r0);
	vst1q_f64((a+2),xmm0.r1);
	vst1q_f64((a+4),xmm0.r2);
	vst1q_f64((a+6),xmm0.r3);
    }

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation double,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,1>::register_type
    _mm_mul<double,cyme::neon,1>(simd_trait<double,cyme::neon,1>::register_type xmm0,
                                 simd_trait<double,cyme::neon,1>::register_type xmm1){
	return vmulq_f64(xmm0,xmm1);
    }

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation double,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,2>::register_type
    _mm_mul<double,cyme::neon,2>(simd_trait<double,cyme::neon,2>::register_type xmm0,
                                 simd_trait<double,cyme::neon,2>::register_type xmm1){
	return simd_trait<double,cyme::neon,2>::register_type(vmulq_f64(xmm0.r0,xmm1.r0),
							      vmulq_f64(xmm0.r1,xmm1.r1));
    }

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation double,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,4>::register_type
    _mm_mul<double,cyme::neon,4>(simd_trait<double,cyme::neon,4>::register_type xmm0,
                                 simd_trait<double,cyme::neon,4>::register_type xmm1){
	return simd_trait<double,cyme::neon,4>::register_type(vmulq_f64(xmm0.r0,xmm1.r0),
							      vmulq_f64(xmm0.r1,xmm1.r1),
							      vmulq_f64(xmm0.r2,xmm1.r2),
							      vmulq_f64(xmm0.r3,xmm1.r3));
    }

    /**
      Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation double,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,1>::register_type
    _mm_div<double,cyme::neon,1>(simd_trait<double,cyme::neon,1>::register_type xmm0,
                                 simd_trait<double,cyme::neon,1>::register_type xmm1){
	return vdivq_f64(xmm0,xmm1);
    }

    /**
      Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation double,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,2>::register_type
    _mm_div<double,cyme::neon,2>(simd_trait<double,cyme::neon,2>::register_type xmm0,
                                 simd_trait<double,cyme::neon,2>::register_type xmm1){
	return simd_trait<double,cyme::neon,2>::register_type(vdivq_f64(xmm0.r0,xmm1.r0),
							      vdivq_f64(xmm0.r1,xmm1.r1));
    }

    /**
      Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation double,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,4>::register_type
    _mm_div<double,cyme::neon,4>(simd_trait<double,cyme::neon,4>::register_type xmm0,
                                 simd_trait<double,cyme::neon,4>::register_type xmm1){
	return simd_trait<double,cyme::neon,4>::register_type(vdivq_f64(xmm0.r0,xmm1.r0),
							      vdivq_f64(xmm0.r1,xmm1.r1),
							      vdivq_f64(xmm0.r2,xmm1.r2),
							      vdivq_f64(xmm0.r3,xmm1.r3));
    }

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation double,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,1>::register_type
    _mm_add<double,cyme::neon,1>(simd_trait<double,cyme::neon,1>::register_type xmm0,
                                 simd_trait<double,cyme::neon,1>::register_type xmm1){
	return vaddq_f64(xmm0,xmm1);
    }

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation double,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,2>::register_type
    _mm_add<double,cyme::neon,2>(simd_trait<double,cyme::neon,2>::register_type xmm0,
                                 simd_trait<double,cyme::neon,2>::register_type xmm1){
	return simd_trait<double,cyme::neon,2>::register_type(vaddq_f64(xmm0.r0,xmm1.r0),
							      vaddq_f64(xmm0.r1,xmm1.r1));
    }

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation double,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,4>::register_type
    _mm_add<double,cyme::neon,4>(simd_trait<double,cyme::neon,4>::register_type xmm0,
                                 simd_trait<double,cyme::neon,4>::register_type xmm1){
	return simd_trait<double,cyme::neon,4>::register_type(vaddq_f64(xmm0.r0,xmm1.r0),
							      vaddq_f64(xmm0.r1,xmm1.r1),
							      vaddq_f64(xmm0.r2,xmm1.r2),
							      vaddq_f64(xmm0.r3,xmm1.r3));
    }

    /**
      Returns a vector containing the result of subtracting each element of b from the corresponding element of a.
       specialisation double,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,1>::register_type
    _mm_sub<double,cyme::neon,1>(simd_trait<double,cyme::neon,1>::register_type xmm0,
                                 simd_trait<double,cyme::neon,1>::register_type xmm1){
	return vsubq_f64(xmm0,xmm1);
    }

    /**
      Returns a vector containing the result of subtracting each element of b from the corresponding element of a.
       specialisation double,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,2>::register_type
    _mm_sub<double,cyme::neon,2>(simd_trait<double,cyme::neon,2>::register_type xmm0,
                                 simd_trait<double,cyme::neon,2>::register_type xmm1){
	return simd_trait<double,cyme::neon,2>::register_type(vsubq_f64(xmm0.r0,xmm1.r0),
							      vsubq_f64(xmm0.r1,xmm1.r1));
    }

    /**
      Returns a vector containing the result of subtracting each element of b from the corresponding element of a.
       specialisation double,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,4>::register_type
    _mm_sub<double,cyme::neon,4>(simd_trait<double,cyme::neon,4>::register_type xmm0,
                                 simd_trait<double,cyme::neon,4>::register_type xmm1){
	return simd_trait<double,cyme::neon,4>::register_type(vsubq_f64(xmm0.r0,xmm1.r0),
							      vsubq_f64(xmm0.r1,xmm1.r1),
							      vsubq_f64(xmm0.r2,xmm1.r2),
							      vsubq_f64(xmm0.r3,xmm1.r3));
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation double,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,1>::register_type
    _mm_exp<double,cyme::neon,1>(simd_trait<double,cyme::neon,1>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation double,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,2>::register_type
    _mm_exp<double,cyme::neon,2>(simd_trait<double,cyme::neon,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation double,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,4>::register_type
    _mm_exp<double,cyme::neon,4>(simd_trait<double,cyme::neon,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation double,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,1>::register_type
    _mm_log<double,cyme::neon,1>(simd_trait<double,cyme::neon,1>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation double,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,2>::register_type
    _mm_log<double,cyme::neon,2>(simd_trait<double,cyme::neon,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation double,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,4>::register_type
    _mm_log<double,cyme::neon,4>(simd_trait<double,cyme::neon,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Returns a vector containing estimates of the reciprocals of the corresponding elements of the given vector.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x) / (1/x) | ≤ 1/256
       specialisation double,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,1>::register_type
    _mm_rec<double,cyme::neon,1>(simd_trait<double,cyme::neon,1>::register_type xmm0){
	return vrecpeq_f64(xmm0);
    }

    /**
      Returns a vector containing estimates of the reciprocals of the corresponding elements of the given vector.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x) / (1/x) | ≤ 1/256
       specialisation double,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,2>::register_type
    _mm_rec<double,cyme::neon,2>(simd_trait<double,cyme::neon,2>::register_type xmm0){
        return simd_trait<double,cyme::neon,2>::register_type(vrecpeq_f64(xmm0.r0),
							      vrecpeq_f64(xmm0.r1));
    }

    /**
      Returns a vector containing estimates of the reciprocals of the corresponding elements of the given vector.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x) / (1/x) | ≤ 1/256
       specialisation double,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,4>::register_type
    _mm_rec<double,cyme::neon,4>(simd_trait<double,cyme::neon,4>::register_type xmm0){
        return simd_trait<double,cyme::neon,4>::register_type(vrecpeq_f64(xmm0.r0),
							      vrecpeq_f64(xmm0.r1),
							      vrecpeq_f64(xmm0.r2),
							      vrecpeq_f64(xmm0.r3));
    }

    /**
      Compute 1/recsqrt (64-bit) floating point elements in xmm0 to packed double-precision (64-bit)
     floating-point elements, and store the results in dst.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x^0,5) / (1/x^0.5) | ≤ 1/256
       specialisation double,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,1>::register_type
    _mm_rsqrt<double,cyme::neon,1>(simd_trait<double,cyme::neon,1>::register_type xmm0){
	return vrsqrteq_f64(xmm0);
    }

    /**
      Compute 1/recsqrt (64-bit) floating point elements in xmm0 to packed double-precision (64-bit)
     floating-point elements, and store the results in dst.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x^0,5) / (1/x^0.5) | ≤ 1/256
       specialisation double,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,2>::register_type
    _mm_rsqrt<double,cyme::neon,2>(simd_trait<double,cyme::neon,2>::register_type xmm0){
	return simd_trait<double,cyme::neon,2>::register_type(vrsqrteq_f64(xmm0.r0),
							      vrsqrteq_f64(xmm0.r1));
    }

    /**
      Compute 1/recsqrt (64-bit) floating point elements in xmm0 to packed double-precision (64-bit)
     floating-point elements, and store the results in dst.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x^0,5) / (1/x^0.5) | ≤ 1/256
       specialisation double,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,4>::register_type
    _mm_rsqrt<double,cyme::neon,4>(simd_trait<double,cyme::neon,4>::register_type xmm0){
	return simd_trait<double,cyme::neon,4>::register_type(vrsqrteq_f64(xmm0.r0),
							      vrsqrteq_f64(xmm0.r1),
							      vrsqrteq_f64(xmm0.r2),
							      vrsqrteq_f64(xmm0.r3));
    }


    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation double,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,1>::register_type
    _mm_neg<double,cyme::neon,1>(simd_trait<double,cyme::neon,1>::register_type xmm0){
	return vnegq_f64(xmm0);
}

    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation double,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,2>::register_type
    _mm_neg<double,cyme::neon,2>(simd_trait<double,cyme::neon,2>::register_type xmm0){
	return simd_trait<double,cyme::neon,2>::register_type(vnegq_f64(xmm0.r0),
							      vnegq_f64(xmm0.r1));
    }

    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation double,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,4>::register_type
    _mm_neg<double,cyme::neon,4>(simd_trait<double,cyme::neon,4>::register_type xmm0){
	return simd_trait<double,cyme::neon,4>::register_type(vnegq_f64(xmm0.r0),
							      vnegq_f64(xmm0.r1),
							      vnegq_f64(xmm0.r2),
							      vnegq_f64(xmm0.r3));
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation double,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,1>::register_type
    _mm_cast<double,cyme::neon,1>(simd_trait<int,cyme::neon,1>::register_type xmm0){
	return vcvt_high_f64_f32(vcvtq_f32_s32(xmm0));
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation double,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,2>::register_type
    _mm_cast<double,cyme::neon,2>(simd_trait<int,cyme::neon,2>::register_type xmm0){
	return simd_trait<double,cyme::neon,2>::register_type(vcvt_high_f64_f32(vcvtq_f32_s32(xmm0.r0)),
							      vcvt_high_f64_f32(vcvtq_f32_s32(xmm0.r1)));
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation double,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,4>::register_type
    _mm_cast<double,cyme::neon,4>(simd_trait<int,cyme::neon,4>::register_type xmm0){
	return simd_trait<double,cyme::neon,4>::register_type(vcvt_high_f64_f32(vcvtq_f32_s32(xmm0.r0)),
							      vcvt_high_f64_f32(vcvtq_f32_s32(xmm0.r1)),
							      vcvt_high_f64_f32(vcvtq_f32_s32(xmm0.r2)),
							      vcvt_high_f64_f32(vcvtq_f32_s32(xmm0.r3)));
    }

    /**
      Returns a vector containing the largest representable floating-point integral values less than or equal
     to the values of the corresponding elements of the given vector.
       specialisation double,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<int,cyme::neon,1>::register_type
    _mm_floor<double,cyme::neon,1>(simd_trait<double,cyme::neon,1>::register_type xmm0){
	float32x2_t temp = vcvt_f32_f64(xmm0);
	return vcvtq_s32_f32(vcombine_f32(temp,temp));
    }

    /**
      Returns a vector containing the largest representable floating-point integral values less than or equal
     to the values of the corresponding elements of the given vector.
       specialisation double,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<int,cyme::neon,2>::register_type
    _mm_floor<double,cyme::neon,2>(simd_trait<double,cyme::neon,2>::register_type xmm0){
	float32x2_t temp1 = vcvt_f32_f64(xmm0.r0);
	float32x2_t temp2 = vcvt_f32_f64(xmm0.r1);
	return simd_trait<int,cyme::neon,2>::register_type(vcvtq_s32_f32(vcombine_f32(temp1,temp1)),
							   vcvtq_s32_f32(vcombine_f32(temp2,temp2)));
    }

    /**
      Returns a vector containing the largest representable floating-point integral values less than or equal
     to the values of the corresponding elements of the given vector.
       specialisation double,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<int,cyme::neon,4>::register_type
    _mm_floor<double,cyme::neon,4>(simd_trait<double,cyme::neon,4>::register_type xmm0){
	//convert 64-bit to 32-bit registers
	float32x2_t temp1 = vcvt_f32_f64(xmm0.r0);
	float32x2_t temp2 = vcvt_f32_f64(xmm0.r1);
	float32x2_t temp3 = vcvt_f32_f64(xmm0.r2);
	float32x2_t temp4 = vcvt_f32_f64(xmm0.r3);
	//convert 2x(float32x2_t) -> int32x4_t 
	return simd_trait<int,cyme::neon,4>::register_type(vcvtq_s32_f32(vcombine_f32(temp1,temp1)),
							   vcvtq_s32_f32(vcombine_f32(temp2,temp2)),
							   vcvtq_s32_f32(vcombine_f32(temp3,temp3)),
							   vcvtq_s32_f32(vcombine_f32(temp4,temp4)));
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer, because there is no builtin function
      for 2^k in double, the computation is done using a C trick.
       specialisation double,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,1>::register_type
    _mm_twok<double,cyme::neon,1>(simd_trait<int,cyme::neon,1>::register_type xmm0){
	xmm0 = vaddq_s32(xmm0,vmovq_n_s32(1023));
	xmm0 = vshlq_s32(xmm0,vmovq_n_s32(20));
	return (float64x2_t)xmm0; 
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer, because there is no builtin function
      for 2^k in double, the computation is done using a C trick.
       specialisation double,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,2>::register_type
    _mm_twok<double,cyme::neon,2>(simd_trait<int,cyme::neon,2>::register_type xmm0){
	xmm0.r0 = vaddq_s32(xmm0.r0,vmovq_n_s32(1023));
	xmm0.r1 = vaddq_s32(xmm0.r1,vmovq_n_s32(1023));
	xmm0.r0 = vshlq_s32(xmm0.r0,vmovq_n_s32(20));
	xmm0.r1 = vshlq_s32(xmm0.r1,vmovq_n_s32(20));
	return simd_trait<double,cyme::neon,2>::register_type((float64x2_t)xmm0.r0,
							      (float64x2_t)xmm0.r1);
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer, because there is no builtin function
      for 2^k in double, the computation is done using a C trick.
       specialisation double,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,4>::register_type
    _mm_twok<double,cyme::neon,4>(simd_trait<int,cyme::neon,4>::register_type xmm0){
	xmm0.r0 = vaddq_s32(xmm0.r0,vmovq_n_s32(1023));
	xmm0.r1 = vaddq_s32(xmm0.r1,vmovq_n_s32(1023));
	xmm0.r2 = vaddq_s32(xmm0.r2,vmovq_n_s32(1023));
	xmm0.r3 = vaddq_s32(xmm0.r3,vmovq_n_s32(1023));
	xmm0.r0 = vshlq_s32(xmm0.r0,vmovq_n_s32(20));
	xmm0.r1 = vshlq_s32(xmm0.r1,vmovq_n_s32(20));
	xmm0.r2 = vshlq_s32(xmm0.r2,vmovq_n_s32(20));
	xmm0.r3 = vshlq_s32(xmm0.r3,vmovq_n_s32(20));
	return simd_trait<double,cyme::neon,4>::register_type((float64x2_t)xmm0.r0,
							      (float64x2_t)xmm0.r1,
							      (float64x2_t)xmm0.r2,
							      (float64x2_t)xmm0.r3);
    }

   /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
      Because we are casting from vector2double -> vector4int, must use specific mask and tmp_sub vectors.
       specialisation double,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,1>::register_type
    _mm_ge<double,cyme::neon,1>(simd_trait<double,cyme::neon,1>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

   /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
      Because we are casting from vector2double -> vector4int, must use specific mask and tmp_sub vectors.
       specialisation double,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,2>::register_type
    _mm_ge<double,cyme::neon,2>(simd_trait<double,cyme::neon,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

   /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
      Because we are casting from vector2double -> vector4int, must use specific mask and tmp_sub vectors.
       specialisation double,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,4>::register_type
    _mm_ge<double,cyme::neon,4>(simd_trait<double,cyme::neon,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
      Because we are casting from vector2double -> vector4int, must use specific mask and tmp_add vectors.
       specialisation double,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,1>::register_type
    _mm_gf<double,cyme::neon,1>(simd_trait<double,cyme::neon,1>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
      Because we are casting from vector2double -> vector4int, must use specific mask and tmp_add vectors.
       specialisation double,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,2>::register_type
    _mm_gf<double,cyme::neon,2>(simd_trait<double,cyme::neon,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
      Because we are casting from vector2double -> vector4int, must use specific mask and tmp_add vectors.
       specialisation double,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,4>::register_type
    _mm_gf<double,cyme::neon,4>(simd_trait<double,cyme::neon,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

#ifdef __FMA__
    /**
      Returns a vector containing the results of performing a fused multiply/add for each corresponding
     set of elements of the given vectors.
     Given arguments a,b, and c,
     result = a*b+c
       specialisation double,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,1>::register_type
    _mm_fma<double,cyme::neon,1>(simd_trait<double,cyme::neon,1>::register_type xmm0,
                                 simd_trait<double,cyme::neon,1>::register_type xmm1,
                                 simd_trait<double,cyme::neon,1>::register_type xmm2){
	return vfmaq_f64(xmm2,xmm0,xmm1);
    }

    /**
      Returns a vector containing the results of performing a fused multiply/add for each corresponding
     set of elements of the given vectors.
     Given arguments a,b, and c,
     result = a*b+c
       specialisation double,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,2>::register_type
    _mm_fma<double,cyme::neon,2>(simd_trait<double,cyme::neon,2>::register_type xmm0,
                                 simd_trait<double,cyme::neon,2>::register_type xmm1,
                                 simd_trait<double,cyme::neon,2>::register_type xmm2){
	return simd_trait<double,cyme::neon,2>::register_type(vfmaq_f64(xmm2.r0,xmm0.r0,xmm1.r0),
							      vfmaq_f64(xmm2.r1,xmm0.r1,xmm1.r1));
    }

    /**
      Returns a vector containing the results of performing a fused multiply/add for each corresponding
     set of elements of the given vectors.
     Given arguments a,b, and c,
     result = a*b+c
       specialisation double,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,4>::register_type
    _mm_fma<double,cyme::neon,4>(simd_trait<double,cyme::neon,4>::register_type xmm0,
                                 simd_trait<double,cyme::neon,4>::register_type xmm1,
                                 simd_trait<double,cyme::neon,4>::register_type xmm2){
	return simd_trait<double,cyme::neon,4>::register_type(vfmaq_f64(xmm2.r0,xmm0.r0,xmm1.r0),
							      vfmaq_f64(xmm2.r1,xmm0.r1,xmm1.r1),
							      vfmaq_f64(xmm2.r2,xmm0.r2,xmm1.r2),
							      vfmaq_f64(xmm2.r3,xmm0.r3,xmm1.r3));
    }

    /**
      Returns a vector containing the results of performing a negative multiply-subtract
      operation on the given vectors. Given arguments a, b, and c,
      result = -(a*b-c),
      result = c-a*b.
       specialisation double,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,1>::register_type
    _mm_nfma<double,cyme::neon,1>(simd_trait<double,cyme::neon,1>::register_type xmm0,
                                  simd_trait<double,cyme::neon,1>::register_type xmm1,
                                  simd_trait<double,cyme::neon,1>::register_type xmm2){
	return vfmsq_f64(xmm2,xmm0,xmm1);
    }

    /**
      Returns a vector containing the results of performing a negative multiply-subtract
      operation on the given vectors. Given arguments a, b, and c,
      result = -(a*b-c),
      result = c-a*b.
       specialisation double,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,2>::register_type
    _mm_nfma<double,cyme::neon,2>(simd_trait<double,cyme::neon,2>::register_type xmm0,
                                  simd_trait<double,cyme::neon,2>::register_type xmm1,
                                  simd_trait<double,cyme::neon,2>::register_type xmm2){
	return simd_trait<double,cyme::neon,2>::register_type(vfmsq_f64(xmm2.r0,xmm0.r0,xmm1.r0),
							      vfmsq_f64(xmm2.r1,xmm0.r1,xmm1.r1));
    }

    /**
      Returns a vector containing the results of performing a negative multiply-subtract
      operation on the given vectors. Given arguments a, b, and c,
      result = -(a*b-c),
      result = c-a*b.
       specialisation double,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,4>::register_type
    _mm_nfma<double,cyme::neon,4>(simd_trait<double,cyme::neon,4>::register_type xmm0,
                                  simd_trait<double,cyme::neon,4>::register_type xmm1,
                                  simd_trait<double,cyme::neon,4>::register_type xmm2){
	return simd_trait<double,cyme::neon,4>::register_type(vfmsq_f64(xmm2.r0,xmm0.r0,xmm1.r0),
							      vfmsq_f64(xmm2.r1,xmm0.r1,xmm1.r1),
							      vfmsq_f64(xmm2.r2,xmm0.r2,xmm1.r2),
							      vfmsq_f64(xmm2.r3,xmm0.r3,xmm1.r3));
    }

    /**
      Returns a vector containing the results of performing a multiply-substract
      operation on the given vectors. Given arguments a, b, and c,
      result = a*b-c.
       specialisation double,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,1>::register_type
    _mm_fms<double,cyme::neon,1>(simd_trait<double,cyme::neon,1>::register_type xmm0,
                                 simd_trait<double,cyme::neon,1>::register_type xmm1,
                                 simd_trait<double,cyme::neon,1>::register_type xmm2){
	float64x2_t temp = vfmsq_f64(xmm2,xmm0,xmm1);
	return vnegq_f64(temp);
    }

    /**
      Returns a vector containing the results of performing a multiply-substract 
      operation on the given vectors. Given arguments a, b, and c,
      result = a*b-c.
       specialisation double,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,2>::register_type
    _mm_fms<double,cyme::neon,2>(simd_trait<double,cyme::neon,2>::register_type xmm0,
                                 simd_trait<double,cyme::neon,2>::register_type xmm1,
                                 simd_trait<double,cyme::neon,2>::register_type xmm2){
	float64x2_t temp1 = vfmsq_f64(xmm2.r0,xmm0.r0,xmm1.r0);
	float64x2_t temp2 = vfmsq_f64(xmm2.r1,xmm0.r1,xmm1.r1);
	return simd_trait<double,cyme::neon,2>::register_type(vnegq_f64(temp1),
							      vnegq_f64(temp2));
    }

    /**
      Returns a vector containing the results of performing a multiply-substract
      operation on the given vectors. Given arguments a, b, and c,
      result = a*b-c.
       specialisation double,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,4>::register_type
    _mm_fms<double,cyme::neon,4>(simd_trait<double,cyme::neon,4>::register_type xmm0,
                                 simd_trait<double,cyme::neon,4>::register_type xmm1,
                                 simd_trait<double,cyme::neon,4>::register_type xmm2){
	float64x2_t temp1 = vfmsq_f64(xmm2.r0,xmm0.r0,xmm1.r0);
	float64x2_t temp2 = vfmsq_f64(xmm2.r1,xmm0.r1,xmm1.r1);
	float64x2_t temp3 = vfmsq_f64(xmm2.r2,xmm0.r2,xmm1.r2);
	float64x2_t temp4 = vfmsq_f64(xmm2.r3,xmm0.r3,xmm1.r3);
	return simd_trait<double,cyme::neon,4>::register_type(vnegq_f64(temp1),
							      vnegq_f64(temp2),
							      vnegq_f64(temp3),
							      vnegq_f64(temp4));
    }

    /**
     Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
     Given arguments a,b, and c,
     result = -(a*b+c
       specialisation double,cyme::neon,1 regs
    */
    template<>
    forceinline simd_trait<double,cyme::neon,1>::register_type
    _mm_nfms<double,cyme::neon,1>(simd_trait<double,cyme::neon,1>::register_type xmm0,
                                  simd_trait<double,cyme::neon,1>::register_type xmm1,
                                  simd_trait<double,cyme::neon,1>::register_type xmm2){
	float64x2_t temp = vfmaq_f64(xmm2,xmm0,xmm1);
	return vnegq_f64(temp);
    }

    /**
     Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
     Given arguments a,b, and c,
     result = -(a*b+c
       specialisation double,cyme::neon,2 regs
    */
    template<>
    forceinline simd_trait<double,cyme::neon,2>::register_type
    _mm_nfms<double,cyme::neon,2>(simd_trait<double,cyme::neon,2>::register_type xmm0,
                                  simd_trait<double,cyme::neon,2>::register_type xmm1,
                                  simd_trait<double,cyme::neon,2>::register_type xmm2){
	float64x2_t temp1 = vfmaq_f64(xmm2.r0,xmm0.r0,xmm1.r0);
	float64x2_t temp2 = vfmaq_f64(xmm2.r0,xmm0.r0,xmm1.r0);
	return simd_trait<double,cyme::neon,2>::register_type(vnegq_f64(temp1),
							      vnegq_f64(temp2));
    }

    /**
     Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
     Given arguments a,b, and c,
     result = -(a*b+c
       specialisation double,cyme::neon,4 regs
    */
    template<>
    forceinline simd_trait<double,cyme::neon,4>::register_type
    _mm_nfms<double,cyme::neon,4>(simd_trait<double,cyme::neon,4>::register_type xmm0,
                                  simd_trait<double,cyme::neon,4>::register_type xmm1,
                                  simd_trait<double,cyme::neon,4>::register_type xmm2){
	float64x2_t temp1 = vfmaq_f64(xmm2.r0,xmm0.r0,xmm1.r0);
	float64x2_t temp2 = vfmaq_f64(xmm2.r1,xmm0.r1,xmm1.r1);
	float64x2_t temp3 = vfmaq_f64(xmm2.r2,xmm0.r2,xmm1.r2);
	float64x2_t temp4 = vfmaq_f64(xmm2.r3,xmm0.r3,xmm1.r3);
	return simd_trait<double,cyme::neon,4>::register_type(vnegq_f64(temp1),
							      vnegq_f64(temp2),
							      vnegq_f64(temp3),
							      vnegq_f64(temp4));
    }
#endif
} //end namespace

#endif
