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
    _mm_exp<float,cyme::neon,1>(simd_trait<float,cyme::neon,1>::register_type xmm0){
	std::cout << "Vendor EXP not yet implemented for float." << std::endl;
	assert(false);
	return xmm0;
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation float,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,2>::register_type
    _mm_exp<float,cyme::neon,2>(simd_trait<float,cyme::neon,2>::register_type xmm0){
	std::cout << "Vendor EXP not yet implemented for float." << std::endl;
	assert(false);
	return xmm0;
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation float,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,4>::register_type
    _mm_exp<float,cyme::neon,4>(simd_trait<float,cyme::neon,4>::register_type xmm0){
	std::cout << "Vendor EXP not yet implemented for float." << std::endl;
	assert(false);
	return xmm0;
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation float,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,1>::register_type
    _mm_log<float,cyme::neon,1>(simd_trait<float,cyme::neon,1>::register_type xmm0){
	std::cout << "Vendor LOG not yet implemented for float." << std::endl;
	assert(false);
	return xmm0;
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation float,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,2>::register_type
    _mm_log<float,cyme::neon,2>(simd_trait<float,cyme::neon,2>::register_type xmm0){
	std::cout << "Vendor LOG not yet implemented for float." << std::endl;
	assert(false);
	return xmm0;
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation float,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,4>::register_type
    _mm_log<float,cyme::neon,4>(simd_trait<float,cyme::neon,4>::register_type xmm0){
	std::cout << "Vendor LOG not yet implemented for float." << std::endl;
	assert(false);
	return xmm0;
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
	xmm0.r2 = vaddq_s32(xmm0.r2,vmovq_n_s32(127));
	xmm0.r3 = vaddq_s32(xmm0.r3,vmovq_n_s32(127));
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
    _mm_ge<float,cyme::neon,1>(simd_trait<float,cyme::neon,1>::register_type xmm0){
	int32x4_t tmp = (int32x4_t)xmm0;
	tmp = vshrq_n_s32(tmp,23);
	tmp = vsubq_s32(tmp,vmovq_n_s32(127));
	return vcvtq_f32_s32(tmp);
    }

    /**
      Extract the exponent of floating-point exponent (32-bit) elements and store the results in dst.
       specialisation float,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,2>::register_type
    _mm_ge<float,cyme::neon,2>(simd_trait<float,cyme::neon,2>::register_type xmm0){
	int32x4_t tmp1 = (int32x4_t)xmm0.r0;
	int32x4_t tmp2 = (int32x4_t)xmm0.r1;
	tmp1 = vshrq_n_s32(tmp1,23);
	tmp2 = vshrq_n_s32(tmp2,23);
	tmp1 = vsubq_s32(tmp1,vmovq_n_s32(127));
	tmp2 = vsubq_s32(tmp2,vmovq_n_s32(127));
	return simd_trait<float,cyme::neon,2>::register_type(vcvtq_f32_s32(tmp1),
							     vcvtq_f32_s32(tmp2));
    }

    /**
      Extract the exponent of floating-point exponent (32-bit) elements and store the results in dst.
       specialisation float,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,4>::register_type
    _mm_ge<float,cyme::neon,4>(simd_trait<float,cyme::neon,4>::register_type xmm0){
	int32x4_t tmp1 = (int32x4_t)xmm0.r0;
	int32x4_t tmp2 = (int32x4_t)xmm0.r1;
	int32x4_t tmp3 = (int32x4_t)xmm0.r2;
	int32x4_t tmp4 = (int32x4_t)xmm0.r3;
	tmp1 = vshrq_n_s32(tmp1,23);
	tmp2 = vshrq_n_s32(tmp2,23);
	tmp3 = vshrq_n_s32(tmp3,23);
	tmp4 = vshrq_n_s32(tmp4,23);
	tmp1 = vsubq_s32(tmp1,vmovq_n_s32(127));
	tmp2 = vsubq_s32(tmp2,vmovq_n_s32(127));
	tmp3 = vsubq_s32(tmp3,vmovq_n_s32(127));
	tmp4 = vsubq_s32(tmp4,vmovq_n_s32(127));
	return simd_trait<float,cyme::neon,4>::register_type(vcvtq_f32_s32(tmp1),
							     vcvtq_f32_s32(tmp2),
							     vcvtq_f32_s32(tmp3),
							     vcvtq_f32_s32(tmp4));
    }

    /**
      Extract the fraction of floating-point exponent (32-bit) elements and store the results in dst.
       specialisation float,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,1>::register_type
    _mm_gf<float,cyme::neon,1>(simd_trait<float,cyme::neon,1>::register_type xmm0){
	int32x4_t tmp = (int32x4_t)xmm0;
	tmp = vandq_s32(tmp,vmovq_n_s32((signed int)0x7fffff));
	tmp = vaddq_s32(tmp,vmovq_n_s32((signed int)0x3f800000));
	return (float32x4_t)tmp;
    }

    /**
      Extract the fraction of floating-point exponent (32-bit) elements and store the results in dst.
       specialisation float,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,2>::register_type
    _mm_gf<float,cyme::neon,2>(simd_trait<float,cyme::neon,2>::register_type xmm0){
	int32x4_t tmp1 = (int32x4_t)xmm0.r0;
	int32x4_t tmp2 = (int32x4_t)xmm0.r1;
	tmp1 = vandq_s32(tmp1,vmovq_n_s32((signed int)0x7fffff));
	tmp2 = vandq_s32(tmp2,vmovq_n_s32((signed int)0x7fffff));
	tmp1 = vaddq_s32(tmp1,vmovq_n_s32((signed int)0x3f800000));
	tmp2 = vaddq_s32(tmp2,vmovq_n_s32((signed int)0x3f800000));
	return simd_trait<float,cyme::neon,2>::register_type((float32x4_t)tmp1,
							     (float32x4_t)tmp2);
    }

    /**
      Extract the fraction of floating-point exponent (32-bit) elements and store the results in dst.
       specialisation float,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::neon,4>::register_type
    _mm_gf<float,cyme::neon,4>(simd_trait<float,cyme::neon,4>::register_type xmm0){
	int32x4_t tmp1 = (int32x4_t)xmm0.r0;
	int32x4_t tmp2 = (int32x4_t)xmm0.r1;
	int32x4_t tmp3 = (int32x4_t)xmm0.r2;
	int32x4_t tmp4 = (int32x4_t)xmm0.r3;
	tmp1 = vandq_s32(tmp1,vmovq_n_s32((signed int)0x7fffff));
	tmp2 = vandq_s32(tmp2,vmovq_n_s32((signed int)0x7fffff));
	tmp3 = vandq_s32(tmp3,vmovq_n_s32((signed int)0x7fffff));
	tmp4 = vandq_s32(tmp4,vmovq_n_s32((signed int)0x7fffff));
	tmp1 = vaddq_s32(tmp1,vmovq_n_s32((signed int)0x3f800000));
	tmp2 = vaddq_s32(tmp2,vmovq_n_s32((signed int)0x3f800000));
	tmp3 = vaddq_s32(tmp3,vmovq_n_s32((signed int)0x3f800000));
	tmp4 = vaddq_s32(tmp4,vmovq_n_s32((signed int)0x3f800000));
	return simd_trait<float,cyme::neon,4>::register_type((float32x4_t)tmp1,
							     (float32x4_t)tmp2,
							     (float32x4_t)tmp3,
							     (float32x4_t)tmp4);
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
    _mm_exp<double,cyme::neon,1>(simd_trait<double,cyme::neon,1>::register_type xmm0){
	std::cout << "Vendor EXP not yet implemented for double." << std::endl;
	assert(false);
	return xmm0;
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation double,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,2>::register_type
    _mm_exp<double,cyme::neon,2>(simd_trait<double,cyme::neon,2>::register_type xmm0){
	std::cout << "Vendor EXP not yet implemented for double." << std::endl;
	assert(false);
	return xmm0;
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation double,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,4>::register_type
    _mm_exp<double,cyme::neon,4>(simd_trait<double,cyme::neon,4>::register_type xmm0){
	std::cout << "Vendor EXP not yet implemented for double." << std::endl;
	assert(false);
	return xmm0;
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation double,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,1>::register_type
    _mm_log<double,cyme::neon,1>(simd_trait<double,cyme::neon,1>::register_type xmm0){
	std::cout << "Vendor LOG not yet implemented for double." << std::endl;
	assert(false);
	return xmm0;
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation double,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,2>::register_type
    _mm_log<double,cyme::neon,2>(simd_trait<double,cyme::neon,2>::register_type xmm0){
	std::cout << "Vendor LOG not yet implemented for double." << std::endl;
	assert(false);
	return xmm0;
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation double,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,4>::register_type
    _mm_log<double,cyme::neon,4>(simd_trait<double,cyme::neon,4>::register_type xmm0){
	std::cout << "Vendor LOG not yet implemented for double." << std::endl;
	assert(false);
	return xmm0;
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
	return vcvtq_f64_s64(vshrq_n_s64((int64x2_t)xmm0,32));
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation double,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,2>::register_type
    _mm_cast<double,cyme::neon,2>(simd_trait<int,cyme::neon,2>::register_type xmm0){
	return simd_trait<double,cyme::neon,2>::register_type(vcvtq_f64_s64(vshrq_n_s64((int64x2_t)xmm0.r0,32)),
							      vcvtq_f64_s64(vshrq_n_s64((int64x2_t)xmm0.r1,32)));
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation double,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,4>::register_type
    _mm_cast<double,cyme::neon,4>(simd_trait<int,cyme::neon,4>::register_type xmm0){
	return simd_trait<double,cyme::neon,4>::register_type(vcvtq_f64_s64(vshrq_n_s64((int64x2_t)xmm0.r0,32)),
							      vcvtq_f64_s64(vshrq_n_s64((int64x2_t)xmm0.r1,32)),
							      vcvtq_f64_s64(vshrq_n_s64((int64x2_t)xmm0.r2,32)),
							      vcvtq_f64_s64(vshrq_n_s64((int64x2_t)xmm0.r3,32)));
    }

    /**
      Returns a vector containing the largest representable floating-point integral values less than or equal
     to the values of the corresponding elements of the given vector.
       specialisation double,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<int,cyme::neon,1>::register_type
    _mm_floor<double,cyme::neon,1>(simd_trait<double,cyme::neon,1>::register_type xmm0){
	//value cast to int64
	int64x2_t temp = vcvtq_s64_f64(xmm0);

	//create int pointer and use to create two seperate intx2 vectors
	int32_t scalar32[4];
	vst1q_s32(scalar32, (int32x4_t)temp);
	int32x2_t result1 = vmov_n_s32(scalar32[0]);
	int32x2_t result2 = vmov_n_s32(scalar32[2]);
	//combine two intx2 vectors into one intx4
	int32x4_t result = vcombine_s32(result1,result2);
	//if result is greater than original value
	//(i.e original is non-integer -ve), add -1,
	//otherwise, value stays the same
	int32x4_t corr = (int32x4_t)vcgtq_f64(vcvtq_f64_s64(temp),xmm0);
	return vaddq_s32(result,corr);
   }

    /**
      Returns a vector containing the largest representable floating-point integral values less than or equal
     to the values of the corresponding elements of the given vector.
       specialisation double,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<int,cyme::neon,2>::register_type
    _mm_floor<double,cyme::neon,2>(simd_trait<double,cyme::neon,2>::register_type xmm0){
	int32_t scalar32[4];
	int64x2_t temp1 = vcvtq_s64_f64(xmm0.r0);
	int64x2_t temp2 = vcvtq_s64_f64(xmm0.r1);
	//vec[0]
	vst1q_s32(scalar32, (int32x4_t)temp1);
	int32x2_t resultn_1 = vmov_n_s32(scalar32[0]);
	int32x2_t resultn_2 = vmov_n_s32(scalar32[2]);
	int32x4_t result1 = vcombine_s32(resultn_1,resultn_2);
	//vec[1]
	vst1q_s32(scalar32, (int32x4_t)temp2);
	resultn_1 = vmov_n_s32(scalar32[0]);
	resultn_2 = vmov_n_s32(scalar32[2]);
	int32x4_t result2 = vcombine_s32(resultn_1,resultn_2);
	//if result is greater than original value
	//(i.e original is non-integer -ve), add -1,
	//otherwise, value stays the same
	int32x4_t corr1 = (int32x4_t)vcgtq_f64(vcvtq_f64_s64(temp1),xmm0.r0);
	int32x4_t corr2 = (int32x4_t)vcgtq_f64(vcvtq_f64_s64(temp2),xmm0.r1);
	return simd_trait<int,cyme::neon,2>::register_type(vaddq_s32(result1,corr1),
							   vaddq_s32(result2,corr2));
    }

    /**
      Returns a vector containing the largest representable floating-point integral values less than or equal
     to the values of the corresponding elements of the given vector.
       specialisation double,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<int,cyme::neon,4>::register_type
    _mm_floor<double,cyme::neon,4>(simd_trait<double,cyme::neon,4>::register_type xmm0){
	int32_t scalar32[4];
	int64x2_t temp1 = vcvtq_s64_f64(xmm0.r0);
	int64x2_t temp2 = vcvtq_s64_f64(xmm0.r1);
	int64x2_t temp3 = vcvtq_s64_f64(xmm0.r2);
	int64x2_t temp4 = vcvtq_s64_f64(xmm0.r3);
	//vec[0]
	vst1q_s32(scalar32, (int32x4_t)temp1);
	int32x2_t resultn_1 = vmov_n_s32(scalar32[0]);
	int32x2_t resultn_2 = vmov_n_s32(scalar32[2]);
	int32x4_t result1 = vcombine_s32(resultn_1,resultn_2);
	//vec[1]
	vst1q_s32(scalar32, (int32x4_t)temp2);
	resultn_1 = vmov_n_s32(scalar32[0]);
	resultn_2 = vmov_n_s32(scalar32[2]);
	int32x4_t result2 = vcombine_s32(resultn_1,resultn_2);
	//vec[2]
	vst1q_s32(scalar32, (int32x4_t)temp3);
	resultn_1 = vmov_n_s32(scalar32[0]);
	resultn_2 = vmov_n_s32(scalar32[2]);
	int32x4_t result3 = vcombine_s32(resultn_1,resultn_2);
	//vec[3]
	vst1q_s32(scalar32, (int32x4_t)temp4);
	resultn_1 = vmov_n_s32(scalar32[0]);
	resultn_2 = vmov_n_s32(scalar32[2]);
	int32x4_t result4 = vcombine_s32(resultn_1,resultn_2);
	//if result is greater than original value
	//(i.e original is non-integer -ve), add -1,
	//otherwise, value stays the same
	int32x4_t corr1 = (int32x4_t)vcgtq_f64(vcvtq_f64_s64(temp1),xmm0.r0);
	int32x4_t corr2 = (int32x4_t)vcgtq_f64(vcvtq_f64_s64(temp2),xmm0.r1);
	int32x4_t corr3 = (int32x4_t)vcgtq_f64(vcvtq_f64_s64(temp3),xmm0.r2);
	int32x4_t corr4 = (int32x4_t)vcgtq_f64(vcvtq_f64_s64(temp4),xmm0.r3);
	return simd_trait<int,cyme::neon,4>::register_type(vaddq_s32(result1,corr1),
							   vaddq_s32(result2,corr2),
							   vaddq_s32(result3,corr3),
							   vaddq_s32(result4,corr4));
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
    _mm_ge<double,cyme::neon,1>(simd_trait<double,cyme::neon,1>::register_type xmm0){
	int64x2_t tmp = (int64x2_t)xmm0;
	tmp = vshrq_n_s64(tmp,52);
	tmp = vsubq_s64(tmp,vmovq_n_s64(1023));
	return vcvtq_f64_s64(tmp);
    }

   /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
      Because we are casting from vector2double -> vector4int, must use specific mask and tmp_sub vectors.
       specialisation double,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,2>::register_type
    _mm_ge<double,cyme::neon,2>(simd_trait<double,cyme::neon,2>::register_type xmm0){
	int64x2_t tmp1 = (int64x2_t)xmm0.r0;
	int64x2_t tmp2 = (int64x2_t)xmm0.r1;
	tmp1 = vshrq_n_s64(tmp1,52);
	tmp2 = vshrq_n_s64(tmp2,52);
	tmp1 = vsubq_s64(tmp1,vmovq_n_s64(1023));
	tmp2 = vsubq_s64(tmp2,vmovq_n_s64(1023));
	return simd_trait<double,cyme::neon,2>::register_type(vcvtq_f64_s64(tmp1),
							      vcvtq_f64_s64(tmp2));
    }

   /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
      Because we are casting from vector2double -> vector4int, must use specific mask and tmp_sub vectors.
       specialisation double,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,4>::register_type
    _mm_ge<double,cyme::neon,4>(simd_trait<double,cyme::neon,4>::register_type xmm0){
	int64x2_t tmp1 = (int64x2_t)xmm0.r0;
	int64x2_t tmp2 = (int64x2_t)xmm0.r1;
	int64x2_t tmp3 = (int64x2_t)xmm0.r2;
	int64x2_t tmp4 = (int64x2_t)xmm0.r3;
	tmp1 = vshrq_n_s64(tmp1,52);
	tmp2 = vshrq_n_s64(tmp2,52);
	tmp3 = vshrq_n_s64(tmp3,52);
	tmp4 = vshrq_n_s64(tmp4,52);
	tmp1 = vsubq_s64(tmp1,vmovq_n_s64(1023));
	tmp2 = vsubq_s64(tmp2,vmovq_n_s64(1023));
	tmp3 = vsubq_s64(tmp3,vmovq_n_s64(1023));
	tmp4 = vsubq_s64(tmp4,vmovq_n_s64(1023));
	return simd_trait<double,cyme::neon,4>::register_type(vcvtq_f64_s64(tmp1),
							      vcvtq_f64_s64(tmp2),
							      vcvtq_f64_s64(tmp3),
							      vcvtq_f64_s64(tmp4));
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
      Because we are casting from vector2double -> vector4int, must use specific mask and tmp_add vectors.
       specialisation double,cyme::neon,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,1>::register_type
    _mm_gf<double,cyme::neon,1>(simd_trait<double,cyme::neon,1>::register_type xmm0){
	int64x2_t tmp = (int64x2_t)xmm0;
	tmp = vandq_s64(tmp,vmovq_n_s64((signed long)0xfffffffffffff));
	tmp = vaddq_s64(tmp,vmovq_n_s64((signed long)0x3ff0000000000000));
	return (float64x2_t)tmp;
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
      Because we are casting from vector2double -> vector4int, must use specific mask and tmp_add vectors.
       specialisation double,cyme::neon,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,2>::register_type
    _mm_gf<double,cyme::neon,2>(simd_trait<double,cyme::neon,2>::register_type xmm0){
	int64x2_t tmp1 = (int64x2_t)xmm0.r0;
	int64x2_t tmp2 = (int64x2_t)xmm0.r1;
	tmp1 = vandq_s64(tmp1,vmovq_n_s64((signed long)0xfffffffffffff));
	tmp2 = vandq_s64(tmp2,vmovq_n_s64((signed long)0xfffffffffffff));
	tmp1 = vaddq_s64(tmp1,vmovq_n_s64((signed long)0x3ff0000000000000));
	tmp2 = vaddq_s64(tmp2,vmovq_n_s64((signed long)0x3ff0000000000000));
	return simd_trait<double,cyme::neon,2>::register_type((float64x2_t)tmp1,
							      (float64x2_t)tmp2);
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
      Because we are casting from vector2double -> vector4int, must use specific mask and tmp_add vectors.
       specialisation double,cyme::neon,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::neon,4>::register_type
    _mm_gf<double,cyme::neon,4>(simd_trait<double,cyme::neon,4>::register_type xmm0){
	int64x2_t tmp1 = (int64x2_t)xmm0.r0;
	int64x2_t tmp2 = (int64x2_t)xmm0.r1;
	int64x2_t tmp3 = (int64x2_t)xmm0.r2;
	int64x2_t tmp4 = (int64x2_t)xmm0.r3;
	tmp1 = vandq_s64(tmp1,vmovq_n_s64((signed long)0xfffffffffffff));
	tmp2 = vandq_s64(tmp2,vmovq_n_s64((signed long)0xfffffffffffff));
	tmp3 = vandq_s64(tmp3,vmovq_n_s64((signed long)0xfffffffffffff));
	tmp4 = vandq_s64(tmp4,vmovq_n_s64((signed long)0xfffffffffffff));
	tmp1 = vaddq_s64(tmp1,vmovq_n_s64((signed long)0x3ff0000000000000));
	tmp2 = vaddq_s64(tmp2,vmovq_n_s64((signed long)0x3ff0000000000000));
	tmp3 = vaddq_s64(tmp3,vmovq_n_s64((signed long)0x3ff0000000000000));
	tmp4 = vaddq_s64(tmp4,vmovq_n_s64((signed long)0x3ff0000000000000));
	return simd_trait<double,cyme::neon,4>::register_type((float64x2_t)tmp1,
							      (float64x2_t)tmp2,
							      (float64x2_t)tmp3,
							      (float64x2_t)tmp4);
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
	float64x2_t temp2 = vfmaq_f64(xmm2.r1,xmm0.r1,xmm1.r1);
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
