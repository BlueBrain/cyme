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
#include <iostream>
#include <assert.h>
// extern "C" vector float expf4(vector float vx);// link to the fortran one
// extern "C" vector float logf4(vector float vx);// link to the fortran one
// extern "C" vector double expd4(vector double vx);// link to the fortran one
// extern "C" vector double logd4(vector double vx);// link to the fortran one

namespace cyme {

/**
  Rounds xmm0 up to the next even integer.
  Specialisation int, cyme::neon, 1 reg
*/
template <>
forceinline simd_trait<int, cyme::neon, 1>::register_type
_mm_round_up_even<cyme::neon, 1>(simd_trait<int, cyme::neon, 1>::register_type xmm0) {
    xmm0 = vaddq_s32(xmm0, vmovq_n_s32(1));
    xmm0 = vandq_s32(xmm0, vmovq_n_s32(~1));
    return xmm0;
}

/**
  Rounds xmm0 up to the next even integer.
  Specialisation int, cyme::neon, 2 reg
*/
template <>
forceinline simd_trait<int, cyme::neon, 2>::register_type
_mm_round_up_even<cyme::neon, 2>(simd_trait<int, cyme::neon, 2>::register_type xmm0) {
    int32x4_t one = vmovq_n_s32(1);
    int32x4_t inv_one = vmovq_n_s32(~1);
    xmm0.r0 = vaddq_s32(xmm0.r0, one);
    xmm0.r1 = vaddq_s32(xmm0.r1, one);
    xmm0.r0 = vandq_s32(xmm0.r0, inv_one);
    xmm0.r1 = vandq_s32(xmm0.r1, inv_one);
    return simd_trait<int, cyme::neon, 2>::register_type(xmm0.r0, xmm0.r1);
}

/**
  Rounds xmm0 up to the next even integer.
  Specialisation int, cyme::neon, 4 reg
*/
template <>
forceinline simd_trait<int, cyme::neon, 4>::register_type
_mm_round_up_even<cyme::neon, 4>(simd_trait<int, cyme::neon, 4>::register_type xmm0) {
    int32x4_t one = vmovq_n_s32(1);
    int32x4_t inv_one = vmovq_n_s32(~1);
    xmm0.r0 = vaddq_s32(xmm0.r0, one);
    xmm0.r1 = vaddq_s32(xmm0.r1, one);
    xmm0.r2 = vaddq_s32(xmm0.r2, one);
    xmm0.r3 = vaddq_s32(xmm0.r3, one);
    xmm0.r0 = vandq_s32(xmm0.r0, inv_one);
    xmm0.r1 = vandq_s32(xmm0.r1, inv_one);
    xmm0.r2 = vandq_s32(xmm0.r2, inv_one);
    xmm0.r3 = vandq_s32(xmm0.r3, inv_one);
    return simd_trait<int, cyme::neon, 4>::register_type(xmm0.r0, xmm0.r1, xmm0.r2, xmm0.r3);
}

/**
   Load a single-precision (32-bit) floating-point element from cyme into lower element of dst.
 */
template <>
forceinline simd_trait<float, cyme::neon, 1>::register_type
_mm_single_load<float, cyme::neon, 1>(const simd_trait<float, cyme::neon, 1>::value_type b) {
    return vld1q_f32(&b);
}

/**
   store a single-precision (32-bit) floating-point element from register lower element to cyme.
 */
template <>
forceinline simd_trait<float, cyme::neon, 1>::value_type
_mm_single_store<float, cyme::neon, 1>(simd_trait<float, cyme::neon, 1>::register_type xmm0,
                                       simd_trait<float, cyme::neon, 1>::pointer b) {
    vst1q_f32(b, xmm0);
    return *b;
}

/**
  Returns a vector of which the value of each element is set to a.
   specialisation float,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 1>::register_type
_mm_load1<float, cyme::neon, 1>(const simd_trait<float, cyme::neon, 1>::value_type &a) {
    return vld1q_dup_f32(&a);
}

/**
  Returns a vector of which the value of each element is set to a.
   specialisation float,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 2>::register_type
_mm_load1<float, cyme::neon, 2>(const simd_trait<float, cyme::neon, 2>::value_type &a) {
    return simd_trait<float, cyme::neon, 2>::register_type(vld1q_dup_f32(&a), vld1q_dup_f32(&a));
}

/**
  Returns a vector of which the value of each element is set to a.
   specialisation float,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 4>::register_type
_mm_load1<float, cyme::neon, 4>(const simd_trait<float, cyme::neon, 4>::value_type &a) {
    return simd_trait<float, cyme::neon, 4>::register_type(vld1q_dup_f32(&a), vld1q_dup_f32(&a), vld1q_dup_f32(&a),
                                                           vld1q_dup_f32(&a));
}

/**
  Loads a vector from the given cyme address.
   specialisation float,cyme::neon,1 regs
*/
template <>
forceinline simd_trait<float, cyme::neon, 1>::register_type
_mm_load<float, cyme::neon, 1>(simd_trait<float, cyme::neon, 1>::const_pointer a) {
    return vld1q_f32(a);
}

/**
  Loads a vector from the given cyme address.
   specialisation float,cyme::neon,2 regs
*/
template <>
forceinline simd_trait<float, cyme::neon, 2>::register_type
_mm_load<float, cyme::neon, 2>(simd_trait<float, cyme::neon, 2>::const_pointer a) {
    return simd_trait<float, cyme::neon, 2>::register_type(vld1q_f32(a), vld1q_f32(a + 4));
}

/**
  Loads a vector from the given cyme address.
   specialisation float,cyme::neon,4 regs
*/
template <>
forceinline simd_trait<float, cyme::neon, 4>::register_type
_mm_load<float, cyme::neon, 4>(simd_trait<float, cyme::neon, 4>::const_pointer a) {
    return simd_trait<float, cyme::neon, 4>::register_type(vld1q_f32(a), vld1q_f32(a + 4), vld1q_f32(a + 8),
                                                           vld1q_f32(a + 12));
}

/**
  Stores a vector to cyme at the given address.
   specialisation float,cyme::neon,1 regs
*/
template <>
forceinline void _mm_store<float, cyme::neon, 1>(simd_trait<float, cyme::neon, 1>::register_type xmm0,
                                                 simd_trait<float, cyme::neon, 1>::pointer a) {
    vst1q_f32(a, xmm0);
}

/**
  Stores a vector to cyme at the given address.
   specialisation float,cyme::neon,2 regs
*/
template <>
forceinline void _mm_store<float, cyme::neon, 2>(simd_trait<float, cyme::neon, 2>::register_type xmm0,
                                                 simd_trait<float, cyme::neon, 2>::pointer a) {
    vst1q_f32(a, xmm0.r0);
    vst1q_f32((a + 4), xmm0.r1);
}

/**
  Stores a vector to cyme at the given address.
   specialisation float,cyme::neon,4 regs
*/
template <>
forceinline void _mm_store<float, cyme::neon, 4>(simd_trait<float, cyme::neon, 4>::register_type xmm0,
                                                 simd_trait<float, cyme::neon, 4>::pointer a) {
    vst1q_f32(a, xmm0.r0);
    vst1q_f32((a + 4), xmm0.r1);
    vst1q_f32((a + 8), xmm0.r2);
    vst1q_f32((a + 12), xmm0.r3);
}

/**
  Returns a vector containing the results of performing a multiply operation using the given vectors.
   specialisation float,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 1>::register_type
_mm_mul<float, cyme::neon, 1>(simd_trait<float, cyme::neon, 1>::register_type xmm0,
                              simd_trait<float, cyme::neon, 1>::register_type xmm1) {
    return vmulq_f32(xmm0, xmm1);
}

/**
  Returns a vector containing the results of performing a multiply operation using the given vectors.
   specialisation float,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 2>::register_type
_mm_mul<float, cyme::neon, 2>(simd_trait<float, cyme::neon, 2>::register_type xmm0,
                              simd_trait<float, cyme::neon, 2>::register_type xmm1) {
    return simd_trait<float, cyme::neon, 2>::register_type(vmulq_f32(xmm0.r0, xmm1.r0), vmulq_f32(xmm0.r1, xmm1.r1));
}

/**
  Returns a vector containing the results of performing a multiply operation using the given vectors.
   specialisation float,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 4>::register_type
_mm_mul<float, cyme::neon, 4>(simd_trait<float, cyme::neon, 4>::register_type xmm0,
                              simd_trait<float, cyme::neon, 4>::register_type xmm1) {
    return simd_trait<float, cyme::neon, 4>::register_type(vmulq_f32(xmm0.r0, xmm1.r0), vmulq_f32(xmm0.r1, xmm1.r1),
                                                           vmulq_f32(xmm0.r2, xmm1.r2), vmulq_f32(xmm0.r3, xmm1.r3));
}

/**
   Returns a vector containing the result of dividing each element of a by the corresponding element of b.
   specialisation float,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 1>::register_type
_mm_div<float, cyme::neon, 1>(simd_trait<float, cyme::neon, 1>::register_type xmm0,
                              simd_trait<float, cyme::neon, 1>::register_type xmm1) {
    return vdivq_f32(xmm0, xmm1);
}

/**
   Returns a vector containing the result of dividing each element of a by the corresponding element of b.
   specialisation float,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 2>::register_type
_mm_div<float, cyme::neon, 2>(simd_trait<float, cyme::neon, 2>::register_type xmm0,
                              simd_trait<float, cyme::neon, 2>::register_type xmm1) {
    return simd_trait<float, cyme::neon, 2>::register_type(vdivq_f32(xmm0.r0, xmm1.r0), vdivq_f32(xmm0.r1, xmm1.r1));
}

/**
   Returns a vector containing the result of dividing each element of a by the corresponding element of b.
   specialisation float,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 4>::register_type
_mm_div<float, cyme::neon, 4>(simd_trait<float, cyme::neon, 4>::register_type xmm0,
                              simd_trait<float, cyme::neon, 4>::register_type xmm1) {
    return simd_trait<float, cyme::neon, 4>::register_type(vdivq_f32(xmm0.r0, xmm1.r0), vdivq_f32(xmm0.r1, xmm1.r1),
                                                           vdivq_f32(xmm0.r2, xmm1.r2), vdivq_f32(xmm0.r3, xmm1.r3));
}

/**
  Returns a vector containing the sums of each set of corresponding elements of the given vectors.
   specialisation float,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 1>::register_type
_mm_add<float, cyme::neon, 1>(simd_trait<float, cyme::neon, 1>::register_type xmm0,
                              simd_trait<float, cyme::neon, 1>::register_type xmm1) {
    return vaddq_f32(xmm0, xmm1);
}

/**
  Returns a vector containing the sums of each set of corresponding elements of the given vectors.
   specialisation float,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 2>::register_type
_mm_add<float, cyme::neon, 2>(simd_trait<float, cyme::neon, 2>::register_type xmm0,
                              simd_trait<float, cyme::neon, 2>::register_type xmm1) {
    return simd_trait<float, cyme::neon, 2>::register_type(vaddq_f32(xmm0.r0, xmm1.r0), vaddq_f32(xmm0.r1, xmm1.r1));
}

/**
  Returns a vector containing the sums of each set of corresponding elements of the given vectors.
   specialisation float,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 4>::register_type
_mm_add<float, cyme::neon, 4>(simd_trait<float, cyme::neon, 4>::register_type xmm0,
                              simd_trait<float, cyme::neon, 4>::register_type xmm1) {
    return simd_trait<float, cyme::neon, 4>::register_type(vaddq_f32(xmm0.r0, xmm1.r0), vaddq_f32(xmm0.r1, xmm1.r1),
                                                           vaddq_f32(xmm0.r2, xmm1.r2), vaddq_f32(xmm0.r3, xmm1.r3));
}

/**
  Returns a vector containing the result of subtracting each element of b
 from the corresponding element of a.
   specialisation float,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 1>::register_type
_mm_sub<float, cyme::neon, 1>(simd_trait<float, cyme::neon, 1>::register_type xmm0,
                              simd_trait<float, cyme::neon, 1>::register_type xmm1) {
    return vsubq_f32(xmm0, xmm1);
}

/**
  Returns a vector containing the result of subtracting each element of b
 from the corresponding element of a.
   specialisation float,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 2>::register_type
_mm_sub<float, cyme::neon, 2>(simd_trait<float, cyme::neon, 2>::register_type xmm0,
                              simd_trait<float, cyme::neon, 2>::register_type xmm1) {
    return simd_trait<float, cyme::neon, 2>::register_type(vsubq_f32(xmm0.r0, xmm1.r0), vsubq_f32(xmm0.r1, xmm1.r1));
}

/**
  Returns a vector containing the result of subtracting each element of b
 from the corresponding element of a.
   specialisation float,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 4>::register_type
_mm_sub<float, cyme::neon, 4>(simd_trait<float, cyme::neon, 4>::register_type xmm0,
                              simd_trait<float, cyme::neon, 4>::register_type xmm1) {
    return simd_trait<float, cyme::neon, 4>::register_type(vsubq_f32(xmm0.r0, xmm1.r0), vsubq_f32(xmm0.r1, xmm1.r1),
                                                           vsubq_f32(xmm0.r2, xmm1.r2), vsubq_f32(xmm0.r3, xmm1.r3));
}

/**
  Computes the exponential function of each element of vx.
   specialisation float,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 1>::register_type
_mm_exp<float, cyme::neon, 1>(simd_trait<float, cyme::neon, 1>::register_type xmm0) {
    std::cout << "Vendor EXP not yet implemented for float." << std::endl;
    assert(false);
    return xmm0;
}

/**
  Computes the exponential function of each element of vx.
   specialisation float,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 2>::register_type
_mm_exp<float, cyme::neon, 2>(simd_trait<float, cyme::neon, 2>::register_type xmm0) {
    std::cout << "Vendor EXP not yet implemented for float." << std::endl;
    assert(false);
    return xmm0;
}

/**
  Computes the exponential function of each element of vx.
   specialisation float,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 4>::register_type
_mm_exp<float, cyme::neon, 4>(simd_trait<float, cyme::neon, 4>::register_type xmm0) {
    std::cout << "Vendor EXP not yet implemented for float." << std::endl;
    assert(false);
    return xmm0;
}

/**
  Computes the logarithm function of each element of vx.
   specialisation float,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 1>::register_type
_mm_log<float, cyme::neon, 1>(simd_trait<float, cyme::neon, 1>::register_type xmm0) {
    std::cout << "Vendor LOG not yet implemented for float." << std::endl;
    assert(false);
    return xmm0;
}

/**
  Computes the logarithm function of each element of vx.
   specialisation float,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 2>::register_type
_mm_log<float, cyme::neon, 2>(simd_trait<float, cyme::neon, 2>::register_type xmm0) {
    std::cout << "Vendor LOG not yet implemented for float." << std::endl;
    assert(false);
    return xmm0;
}

/**
  Computes the logarithm function of each element of vx.
   specialisation float,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 4>::register_type
_mm_log<float, cyme::neon, 4>(simd_trait<float, cyme::neon, 4>::register_type xmm0) {
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
template <>
forceinline simd_trait<float, cyme::neon, 1>::register_type
_mm_rec<float, cyme::neon, 1>(simd_trait<float, cyme::neon, 1>::register_type xmm0) {
    return vrecpeq_f32(xmm0);
}

/**
  Returns a vector containing estimates of the reciprocals of the corresponding elements of the given vector.
 \warning The precision guarantee is specified by the following expression, where x is the value of each element
 of a and r is the value of the corresponding element of the result value:
 | (r-1/x) / (1/x) | ≤ 1/256
   specialisation float,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 2>::register_type
_mm_rec<float, cyme::neon, 2>(simd_trait<float, cyme::neon, 2>::register_type xmm0) {
    return simd_trait<float, cyme::neon, 2>::register_type(vrecpeq_f32(xmm0.r0), vrecpeq_f32(xmm0.r1));
}

/**
  Returns a vector containing estimates of the reciprocals of the corresponding elements of the given vector.
 \warning The precision guarantee is specified by the following expression, where x is the value of each element
 of a and r is the value of the corresponding element of the result value:
 | (r-1/x) / (1/x) | ≤ 1/256
   specialisation float,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 4>::register_type
_mm_rec<float, cyme::neon, 4>(simd_trait<float, cyme::neon, 4>::register_type xmm0) {
    return simd_trait<float, cyme::neon, 4>::register_type(vrecpeq_f32(xmm0.r0), vrecpeq_f32(xmm0.r1),
                                                           vrecpeq_f32(xmm0.r2), vrecpeq_f32(xmm0.r3));
}

/**
  Compute 1/recsqrt (32-bit) floating point elements in xmm0 to packed single-precision
 (32-bit) floating-point elements, and store the results in dst.
 \warning The precision guarantee is specified by the following expression, where x is the value of each element
   of a and r is the value of the corresponding element of the result value:
 | (r-1/x^0.5) / (1/x^0.5) | ≤ 1/256
   specialisation float,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 1>::register_type
_mm_rsqrt<float, cyme::neon, 1>(simd_trait<float, cyme::neon, 1>::register_type xmm0) {
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
template <>
forceinline simd_trait<float, cyme::neon, 2>::register_type
_mm_rsqrt<float, cyme::neon, 2>(simd_trait<float, cyme::neon, 2>::register_type xmm0) {
    return simd_trait<float, cyme::neon, 2>::register_type(vrsqrteq_f32(xmm0.r0), vrsqrteq_f32(xmm0.r1));
}

/**
  Compute 1/recsqrt (32-bit) floating point elements in xmm0 to packed single-precision
 (32-bit) floating-point elements, and store the results in dst.
 \warning The precision guarantee is specified by the following expression, where x is the value of each element
   of a and r is the value of the corresponding element of the result value:
 | (r-1/x^0.5) / (1/x^0.5) | ≤ 1/256
   specialisation float,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 4>::register_type
_mm_rsqrt<float, cyme::neon, 4>(simd_trait<float, cyme::neon, 4>::register_type xmm0) {
    return simd_trait<float, cyme::neon, 4>::register_type(vrsqrteq_f32(xmm0.r0), vrsqrteq_f32(xmm0.r1),
                                                           vrsqrteq_f32(xmm0.r2), vrsqrteq_f32(xmm0.r3));
}

/**
  Returns a vector containing the negated value of the corresponding elements in the given vector.
   specialisation float,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 1>::register_type
_mm_neg<float, cyme::neon, 1>(simd_trait<float, cyme::neon, 1>::register_type xmm0) {
    return vnegq_f32(xmm0);
}

/**
  Returns a vector containing the negated value of the corresponding elements in the given vector.
   specialisation float,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 2>::register_type
_mm_neg<float, cyme::neon, 2>(simd_trait<float, cyme::neon, 2>::register_type xmm0) {
    return simd_trait<float, cyme::neon, 2>::register_type(vnegq_f32(xmm0.r0), vnegq_f32(xmm0.r1));
}

/**
  Returns a vector containing the negated value of the corresponding elements in the given vector.
   specialisation float,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 4>::register_type
_mm_neg<float, cyme::neon, 4>(simd_trait<float, cyme::neon, 4>::register_type xmm0) {
    return simd_trait<float, cyme::neon, 4>::register_type(vnegq_f32(xmm0.r0), vnegq_f32(xmm0.r1), vnegq_f32(xmm0.r2),
                                                           vnegq_f32(xmm0.r3));
}

/**
  Convert packed 32-bit integers in xmm0 to packed single-precision (32-bit) floating-point elements,
 and store the results in dst.
   specialisation float,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 1>::register_type
_mm_cast<float, cyme::neon, 1>(simd_trait<int, cyme::neon, 1>::register_type xmm0) {
    return vcvtq_f32_s32(xmm0);
}

/**
  Convert packed 32-bit integers in xmm0 to packed single-precision (32-bit) floating-point elements,
 and store the results in dst.
   specialisation float,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 2>::register_type
_mm_cast<float, cyme::neon, 2>(simd_trait<int, cyme::neon, 2>::register_type xmm0) {
    return simd_trait<float, cyme::neon, 2>::register_type(vcvtq_f32_s32(xmm0.r0), vcvtq_f32_s32(xmm0.r1));
}

/**
  Convert packed 32-bit integers in xmm0 to packed single-precision (32-bit) floating-point elements,
 and store the results in dst.
   specialisation float,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 4>::register_type
_mm_cast<float, cyme::neon, 4>(simd_trait<int, cyme::neon, 4>::register_type xmm0) {
    return simd_trait<float, cyme::neon, 4>::register_type(vcvtq_f32_s32(xmm0.r0), vcvtq_f32_s32(xmm0.r1),
                                                           vcvtq_f32_s32(xmm0.r2), vcvtq_f32_s32(xmm0.r3));
}

/**
  Returns a vector containing the largest representable floating-point integral
 values less than or equal to the values of the corresponding elements of the given vector.
   specialisation float,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<int, cyme::neon, 1>::register_type
_mm_floor<float, cyme::neon, 1>(simd_trait<float, cyme::neon, 1>::register_type xmm0) {
    int32x4_t temp = vcvtq_s32_f32(xmm0);    // value cast to int32x4
    float32x4_t comp = vcvtq_f32_s32(temp);  // cast back for comparison
    uint32x4_t corr = vcltq_f32(xmm0, comp); // temp -1 if xmm0 < comp
    return vaddq_s32(temp, (int32x4_t)corr); // adjust temp
}

/**
  Returns a vector containing the largest representable floating-point integral
 values less than or equal to the values of the corresponding elements of the given vector.
   specialisation float,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<int, cyme::neon, 2>::register_type
_mm_floor<float, cyme::neon, 2>(simd_trait<float, cyme::neon, 2>::register_type xmm0) {
    int32x4_t temp1 = vcvtq_s32_f32(xmm0.r0);                    // value cast to int32x4
    int32x4_t temp2 = vcvtq_s32_f32(xmm0.r1);                    // value cast to int32x4
    uint32x4_t corr1 = vcltq_f32(xmm0.r0, vcvtq_f32_s32(temp1)); // temp -1 if xmm0 < temp
    uint32x4_t corr2 = vcltq_f32(xmm0.r1, vcvtq_f32_s32(temp2)); // temp -1 if xmm0 < temp
    return simd_trait<int, cyme::neon, 2>::register_type(vaddq_s32(temp1, (int32x4_t)corr1),
                                                         vaddq_s32(temp2, (int32x4_t)corr2));
}

/**
  Returns a vector containing the largest representable floating-point integral
 values less than or equal to the values of the corresponding elements of the given vector.
   specialisation float,cyme::neon,4 regs
 */

template <>
forceinline simd_trait<int, cyme::neon, 4>::register_type
_mm_floor<float, cyme::neon, 4>(simd_trait<float, cyme::neon, 4>::register_type xmm0) {
    int32x4_t temp1 = vcvtq_s32_f32(xmm0.r0); // value cast to int32x4
    int32x4_t temp2 = vcvtq_s32_f32(xmm0.r1);
    int32x4_t temp3 = vcvtq_s32_f32(xmm0.r2);
    int32x4_t temp4 = vcvtq_s32_f32(xmm0.r3);
    uint32x4_t corr1 = vcltq_f32(xmm0.r0, vcvtq_f32_s32(temp1)); // temp -1 if xmm0 < temp
    uint32x4_t corr2 = vcltq_f32(xmm0.r1, vcvtq_f32_s32(temp2));
    uint32x4_t corr3 = vcltq_f32(xmm0.r2, vcvtq_f32_s32(temp3));
    uint32x4_t corr4 = vcltq_f32(xmm0.r3, vcvtq_f32_s32(temp4));
    return simd_trait<int, cyme::neon, 4>::register_type(
        vaddq_s32(temp1, (int32x4_t)corr1), // adjust temp
        vaddq_s32(temp2, (int32x4_t)corr2), vaddq_s32(temp3, (int32x4_t)corr3), vaddq_s32(temp4, (int32x4_t)corr4));
}

/**
  Returns a vector containing 2^k where k is a vector of integer
   specialisation float,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 1>::register_type
_mm_twok<float, cyme::neon, 1>(simd_trait<int, cyme::neon, 1>::register_type xmm0) {
    xmm0 = vaddq_s32(xmm0, vmovq_n_s32(127));
    xmm0 = vshlq_s32(xmm0, vmovq_n_s32(23));
    return (float32x4_t)xmm0;
}

/**
  Returns a vector containing 2^k where k is a vector of integer
   specialisation float,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 2>::register_type
_mm_twok<float, cyme::neon, 2>(simd_trait<int, cyme::neon, 2>::register_type xmm0) {
    xmm0.r0 = vaddq_s32(xmm0.r0, vmovq_n_s32(127));
    xmm0.r1 = vaddq_s32(xmm0.r1, vmovq_n_s32(127));
    xmm0.r0 = vshlq_s32(xmm0.r0, vmovq_n_s32(23));
    xmm0.r1 = vshlq_s32(xmm0.r1, vmovq_n_s32(23));
    return simd_trait<float, cyme::neon, 2>::register_type((float32x4_t)xmm0.r0, (float32x4_t)xmm0.r1);
}

/**
  Returns a vector containing 2^k where k is a vector of integer
   specialisation float,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 4>::register_type
_mm_twok<float, cyme::neon, 4>(simd_trait<int, cyme::neon, 4>::register_type xmm0) {
    xmm0.r0 = vaddq_s32(xmm0.r0, vmovq_n_s32(127));
    xmm0.r1 = vaddq_s32(xmm0.r1, vmovq_n_s32(127));
    xmm0.r2 = vaddq_s32(xmm0.r2, vmovq_n_s32(127));
    xmm0.r3 = vaddq_s32(xmm0.r3, vmovq_n_s32(127));
    xmm0.r0 = vshlq_s32(xmm0.r0, vmovq_n_s32(23));
    xmm0.r1 = vshlq_s32(xmm0.r1, vmovq_n_s32(23));
    xmm0.r2 = vshlq_s32(xmm0.r2, vmovq_n_s32(23));
    xmm0.r3 = vshlq_s32(xmm0.r3, vmovq_n_s32(23));
    return simd_trait<float, cyme::neon, 4>::register_type((float32x4_t)xmm0.r0, (float32x4_t)xmm0.r1,
                                                           (float32x4_t)xmm0.r2, (float32x4_t)xmm0.r3);
}

/**
  Extract the exponent of floating-point exponent (32-bit) elements and store the results in dst.
   specialisation float,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 1>::register_type
_mm_ge<float, cyme::neon, 1>(simd_trait<float, cyme::neon, 1>::register_type xmm0) {
    int32x4_t tmp = (int32x4_t)xmm0;
    tmp = vshrq_n_s32(tmp, 23);
    tmp = vsubq_s32(tmp, vmovq_n_s32(127));
    return vcvtq_f32_s32(tmp);
}

/**
  Extract the exponent of floating-point exponent (32-bit) elements and store the results in dst.
   specialisation float,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 2>::register_type
_mm_ge<float, cyme::neon, 2>(simd_trait<float, cyme::neon, 2>::register_type xmm0) {
    int32x4_t tmp1 = (int32x4_t)xmm0.r0;
    int32x4_t tmp2 = (int32x4_t)xmm0.r1;
    tmp1 = vshrq_n_s32(tmp1, 23);
    tmp2 = vshrq_n_s32(tmp2, 23);
    tmp1 = vsubq_s32(tmp1, vmovq_n_s32(127));
    tmp2 = vsubq_s32(tmp2, vmovq_n_s32(127));
    return simd_trait<float, cyme::neon, 2>::register_type(vcvtq_f32_s32(tmp1), vcvtq_f32_s32(tmp2));
}

/**
  Extract the exponent of floating-point exponent (32-bit) elements and store the results in dst.
   specialisation float,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 4>::register_type
_mm_ge<float, cyme::neon, 4>(simd_trait<float, cyme::neon, 4>::register_type xmm0) {
    int32x4_t tmp1 = (int32x4_t)xmm0.r0;
    int32x4_t tmp2 = (int32x4_t)xmm0.r1;
    int32x4_t tmp3 = (int32x4_t)xmm0.r2;
    int32x4_t tmp4 = (int32x4_t)xmm0.r3;
    tmp1 = vshrq_n_s32(tmp1, 23);
    tmp2 = vshrq_n_s32(tmp2, 23);
    tmp3 = vshrq_n_s32(tmp3, 23);
    tmp4 = vshrq_n_s32(tmp4, 23);
    tmp1 = vsubq_s32(tmp1, vmovq_n_s32(127));
    tmp2 = vsubq_s32(tmp2, vmovq_n_s32(127));
    tmp3 = vsubq_s32(tmp3, vmovq_n_s32(127));
    tmp4 = vsubq_s32(tmp4, vmovq_n_s32(127));
    return simd_trait<float, cyme::neon, 4>::register_type(vcvtq_f32_s32(tmp1), vcvtq_f32_s32(tmp2),
                                                           vcvtq_f32_s32(tmp3), vcvtq_f32_s32(tmp4));
}

/**
  Extract the fraction of floating-point exponent (32-bit) elements and store the results in dst.
   specialisation float,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 1>::register_type
_mm_gf<float, cyme::neon, 1>(simd_trait<float, cyme::neon, 1>::register_type xmm0) {
    int32x4_t tmp = (int32x4_t)xmm0;
    tmp = vandq_s32(tmp, vmovq_n_s32((signed int)0x7fffff));
    tmp = vaddq_s32(tmp, vmovq_n_s32((signed int)0x3f800000));
    return (float32x4_t)tmp;
}

/**
  Extract the fraction of floating-point exponent (32-bit) elements and store the results in dst.
   specialisation float,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 2>::register_type
_mm_gf<float, cyme::neon, 2>(simd_trait<float, cyme::neon, 2>::register_type xmm0) {
    int32x4_t tmp1 = (int32x4_t)xmm0.r0;
    int32x4_t tmp2 = (int32x4_t)xmm0.r1;
    tmp1 = vandq_s32(tmp1, vmovq_n_s32((signed int)0x7fffff));
    tmp2 = vandq_s32(tmp2, vmovq_n_s32((signed int)0x7fffff));
    tmp1 = vaddq_s32(tmp1, vmovq_n_s32((signed int)0x3f800000));
    tmp2 = vaddq_s32(tmp2, vmovq_n_s32((signed int)0x3f800000));
    return simd_trait<float, cyme::neon, 2>::register_type((float32x4_t)tmp1, (float32x4_t)tmp2);
}

/**
  Extract the fraction of floating-point exponent (32-bit) elements and store the results in dst.
   specialisation float,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 4>::register_type
_mm_gf<float, cyme::neon, 4>(simd_trait<float, cyme::neon, 4>::register_type xmm0) {
    int32x4_t tmp1 = (int32x4_t)xmm0.r0;
    int32x4_t tmp2 = (int32x4_t)xmm0.r1;
    int32x4_t tmp3 = (int32x4_t)xmm0.r2;
    int32x4_t tmp4 = (int32x4_t)xmm0.r3;
    tmp1 = vandq_s32(tmp1, vmovq_n_s32((signed int)0x7fffff));
    tmp2 = vandq_s32(tmp2, vmovq_n_s32((signed int)0x7fffff));
    tmp3 = vandq_s32(tmp3, vmovq_n_s32((signed int)0x7fffff));
    tmp4 = vandq_s32(tmp4, vmovq_n_s32((signed int)0x7fffff));
    tmp1 = vaddq_s32(tmp1, vmovq_n_s32((signed int)0x3f800000));
    tmp2 = vaddq_s32(tmp2, vmovq_n_s32((signed int)0x3f800000));
    tmp3 = vaddq_s32(tmp3, vmovq_n_s32((signed int)0x3f800000));
    tmp4 = vaddq_s32(tmp4, vmovq_n_s32((signed int)0x3f800000));
    return simd_trait<float, cyme::neon, 4>::register_type((float32x4_t)tmp1, (float32x4_t)tmp2, (float32x4_t)tmp3,
                                                           (float32x4_t)tmp4);
}

/**
  Computes the absolute value for single-precision (32-bit) floating point elements and stores
  the result in dst.
  specialisation float,cyme::neon,1 reg
 */
template <>
forceinline simd_trait<float, cyme::neon, 1>::register_type
_mm_fabs<float, cyme::neon, 1>(simd_trait<float, cyme::neon, 1>::register_type xmm0) {
    return vabsq_f32(xmm0);
}

/**
  Computes the absolute value for single-precision (32-bit) floating point elements and stores
  the result in dst.
  specialisation float,cyme::neon,2 reg
 */
template <>
forceinline simd_trait<float, cyme::neon, 2>::register_type
_mm_fabs<float, cyme::neon, 2>(simd_trait<float, cyme::neon, 2>::register_type xmm0) {
    return simd_trait<float, cyme::neon, 2>::register_type(vabsq_f32(xmm0.r0), vabsq_f32(xmm0.r1));
}

/**
  Computes the absolute value for single-precision (32-bit) floating point elements and stores
  the result in dst.
  specialisation float,cyme::neon,4 reg
 */
template <>
forceinline simd_trait<float, cyme::neon, 4>::register_type
_mm_fabs<float, cyme::neon, 4>(simd_trait<float, cyme::neon, 4>::register_type xmm0) {
    return simd_trait<float, cyme::neon, 4>::register_type(vabsq_f32(xmm0.r0), vabsq_f32(xmm0.r1), vabsq_f32(xmm0.r2),
                                                           vabsq_f32(xmm0.r3));
}

/**
  Selects the polynomial for sin function. Inputs are:
    - Selector int
    - Option one
    - Option two
  specialisation float,cyme::neon, 1 reg
 */
template <>
forceinline simd_trait<float, cyme::neon, 1>::register_type
_mm_select_poly<float, cyme::neon, 1>(simd_trait<int, cyme::neon, 1>::register_type sel,
                                      simd_trait<float, cyme::neon, 1>::register_type xmm0,
                                      simd_trait<float, cyme::neon, 1>::register_type xmm1) {
    int32x4_t mask = vmovq_n_s32(2);
    int32x4_t zero = vmovq_n_s32(0);
    sel = vandq_s32(sel, mask);
    sel = (int32x4_t)vceqq_s32(sel, zero);

    xmm0 = (float32x4_t)vbicq_s32((int32x4_t)xmm0, sel);
    xmm1 = (float32x4_t)vandq_s32((int32x4_t)xmm1, sel);
    return vaddq_f32(xmm0, xmm1);
}

/**
  Selects the polynomial for sin function. Inputs are:
    - Selector int
    - Option one
    - Option two
  specialisation float,cyme::neon, 2 reg
 */
template <>
forceinline simd_trait<float, cyme::neon, 2>::register_type
_mm_select_poly<float, cyme::neon, 2>(simd_trait<int, cyme::neon, 2>::register_type sel,
                                      simd_trait<float, cyme::neon, 2>::register_type xmm0,
                                      simd_trait<float, cyme::neon, 2>::register_type xmm1) {
    int32x4_t mask = vmovq_n_s32(2);
    int32x4_t zero = vmovq_n_s32(0);
    sel.r0 = vandq_s32(sel.r0, mask);
    sel.r1 = vandq_s32(sel.r1, mask);
    sel.r0 = (int32x4_t)vceqq_s32(sel.r0, zero);
    sel.r1 = (int32x4_t)vceqq_s32(sel.r1, zero);

    xmm0.r0 = (float32x4_t)vbicq_s32((int32x4_t)xmm0.r0, sel.r0);
    xmm0.r1 = (float32x4_t)vbicq_s32((int32x4_t)xmm0.r1, sel.r1);
    xmm1.r0 = (float32x4_t)vandq_s32((int32x4_t)xmm1.r0, sel.r0);
    xmm1.r1 = (float32x4_t)vandq_s32((int32x4_t)xmm1.r1, sel.r1);
    return simd_trait<float, cyme::neon, 2>::register_type(vaddq_f32(xmm0.r0, xmm1.r0), vaddq_f32(xmm0.r1, xmm1.r1));
}

/**
  Selects the polynomial for sin function. Inputs are:
    - Selector int
    - Option one
    - Option two
  specialisation float,cyme::neon, 4 reg
 */
template <>
forceinline simd_trait<float, cyme::neon, 4>::register_type
_mm_select_poly<float, cyme::neon, 4>(simd_trait<int, cyme::neon, 4>::register_type sel,
                                      simd_trait<float, cyme::neon, 4>::register_type xmm0,
                                      simd_trait<float, cyme::neon, 4>::register_type xmm1) {
    int32x4_t mask = vmovq_n_s32(2);
    int32x4_t zero = vmovq_n_s32(0);
    sel.r0 = vandq_s32(sel.r0, mask);
    sel.r1 = vandq_s32(sel.r1, mask);
    sel.r2 = vandq_s32(sel.r2, mask);
    sel.r3 = vandq_s32(sel.r3, mask);
    sel.r0 = (int32x4_t)vceqq_s32(sel.r0, zero);
    sel.r1 = (int32x4_t)vceqq_s32(sel.r1, zero);
    sel.r2 = (int32x4_t)vceqq_s32(sel.r2, zero);
    sel.r3 = (int32x4_t)vceqq_s32(sel.r3, zero);

    xmm0.r0 = (float32x4_t)vbicq_s32((int32x4_t)xmm0.r0, sel.r0);
    xmm0.r1 = (float32x4_t)vbicq_s32((int32x4_t)xmm0.r1, sel.r1);
    xmm0.r2 = (float32x4_t)vbicq_s32((int32x4_t)xmm0.r2, sel.r2);
    xmm0.r3 = (float32x4_t)vbicq_s32((int32x4_t)xmm0.r3, sel.r3);
    xmm1.r0 = (float32x4_t)vandq_s32((int32x4_t)xmm1.r0, sel.r0);
    xmm1.r0 = (float32x4_t)vandq_s32((int32x4_t)xmm1.r0, sel.r0);
    xmm1.r1 = (float32x4_t)vandq_s32((int32x4_t)xmm1.r1, sel.r1);
    xmm1.r2 = (float32x4_t)vandq_s32((int32x4_t)xmm1.r2, sel.r2);
    xmm1.r3 = (float32x4_t)vandq_s32((int32x4_t)xmm1.r3, sel.r3);
    return simd_trait<float, cyme::neon, 4>::register_type(vaddq_f32(xmm0.r0, xmm1.r0), vaddq_f32(xmm0.r1, xmm1.r1),
                                                           vaddq_f32(xmm0.r2, xmm1.r2), vaddq_f32(xmm0.r3, xmm1.r3));
}

/**
  Selects the sign (+/-) for sin function. Inputs are:
    - swap int
    - Original input
    - Final calculated sin value
  specialisation float,cyme::neon,1 reg
 */
template <>
forceinline simd_trait<float, cyme::neon, 1>::register_type
_mm_select_sign_sin<float, cyme::neon, 1>(simd_trait<int, cyme::neon, 1>::register_type swap,
                                          simd_trait<float, cyme::neon, 1>::register_type xmm0,
                                          simd_trait<float, cyme::neon, 1>::register_type xmm1) {
    int32x4_t mask = vmovq_n_s32(0x80000000);
    int32x4_t four = vmovq_n_s32(4);
    /* extract the sign bit (upper one) from original val */
    int32x4_t imm0 = vandq_s32((int32x4_t)xmm0, mask);

    /* get the swap sign flag */
    swap = vandq_s32(swap, four);
    swap = vshlq_s32(swap, vmovq_n_s32(29));

    /* update the sign of the final value*/
    imm0 = veorq_s32(imm0, swap);
    xmm1 = (float32x4_t)veorq_s32((int32x4_t)xmm1, imm0);
    return xmm1;
}

/**
  Selects the sign (+/-) for sin function. Inputs are:
    - swap int
    - Original input
    - Final calculated sin value
  specialisation float,cyme::neon,2 reg
 */
template <>
forceinline simd_trait<float, cyme::neon, 2>::register_type
_mm_select_sign_sin<float, cyme::neon, 2>(simd_trait<int, cyme::neon, 2>::register_type swap,
                                          simd_trait<float, cyme::neon, 2>::register_type xmm0,
                                          simd_trait<float, cyme::neon, 2>::register_type xmm1) {
    int32x4_t mask = vmovq_n_s32(0x80000000);
    int32x4_t four = vmovq_n_s32(4);
    /* extract the sign bit (upper one) from original val */
    int32x4_t imm0_0 = vandq_s32((int32x4_t)xmm0.r0, mask);
    int32x4_t imm0_1 = vandq_s32((int32x4_t)xmm0.r1, mask);

    /* get the swap sign flag */
    swap.r0 = vandq_s32(swap.r0, four);
    swap.r1 = vandq_s32(swap.r1, four);
    swap.r0 = vshlq_s32(swap.r0, vmovq_n_s32(29));
    swap.r1 = vshlq_s32(swap.r1, vmovq_n_s32(29));

    /* update the sign of the final value*/
    imm0_0 = veorq_s32(imm0_0, swap.r0);
    imm0_1 = veorq_s32(imm0_1, swap.r1);
    xmm1.r0 = (float32x4_t)veorq_s32((int32x4_t)xmm1.r0, imm0_0);
    xmm1.r1 = (float32x4_t)veorq_s32((int32x4_t)xmm1.r1, imm0_1);
    return simd_trait<float, cyme::neon, 2>::register_type(xmm1.r0, xmm1.r1);
}

/**
  Selects the sign (+/-) for sin function. Inputs are:
    - swap int
    - Original input
    - Final calculated sin value
  specialisation float,cyme::neon,4 reg
 */
template <>
forceinline simd_trait<float, cyme::neon, 4>::register_type
_mm_select_sign_sin<float, cyme::neon, 4>(simd_trait<int, cyme::neon, 4>::register_type swap,
                                          simd_trait<float, cyme::neon, 4>::register_type xmm0,
                                          simd_trait<float, cyme::neon, 4>::register_type xmm1) {
    int32x4_t mask = vmovq_n_s32(0x80000000);
    int32x4_t four = vmovq_n_s32(4);
    /* extract the sign bit (upper one) from original val */
    int32x4_t imm0_0 = vandq_s32((int32x4_t)xmm0.r0, mask);
    int32x4_t imm0_1 = vandq_s32((int32x4_t)xmm0.r1, mask);
    int32x4_t imm0_2 = vandq_s32((int32x4_t)xmm0.r2, mask);
    int32x4_t imm0_3 = vandq_s32((int32x4_t)xmm0.r3, mask);

    /* get the swap sign flag */
    swap.r0 = vandq_s32(swap.r0, four);
    swap.r1 = vandq_s32(swap.r1, four);
    swap.r2 = vandq_s32(swap.r2, four);
    swap.r3 = vandq_s32(swap.r3, four);
    swap.r0 = vshlq_s32(swap.r0, vmovq_n_s32(29));
    swap.r1 = vshlq_s32(swap.r1, vmovq_n_s32(29));
    swap.r2 = vshlq_s32(swap.r2, vmovq_n_s32(29));
    swap.r3 = vshlq_s32(swap.r3, vmovq_n_s32(29));

    /* update the sign of the final value*/
    imm0_0 = veorq_s32(imm0_0, swap.r0);
    imm0_1 = veorq_s32(imm0_1, swap.r1);
    imm0_2 = veorq_s32(imm0_2, swap.r2);
    imm0_3 = veorq_s32(imm0_3, swap.r3);
    xmm1.r0 = (float32x4_t)veorq_s32((int32x4_t)xmm1.r0, imm0_0);
    xmm1.r1 = (float32x4_t)veorq_s32((int32x4_t)xmm1.r1, imm0_1);
    xmm1.r2 = (float32x4_t)veorq_s32((int32x4_t)xmm1.r2, imm0_2);
    xmm1.r3 = (float32x4_t)veorq_s32((int32x4_t)xmm1.r3, imm0_3);
    return simd_trait<float, cyme::neon, 4>::register_type(xmm1.r0, xmm1.r1, xmm1.r2, xmm1.r3);
}

/**
  Selects the sign (+/-) for cos function. Inputs are:
    - swap int
    - Final calculated cos value
  specialisation float,cyme::neon,1 reg
 */
template <>
forceinline simd_trait<float, cyme::neon, 1>::register_type
_mm_select_sign_cos<float, cyme::neon, 1>(simd_trait<int, cyme::neon, 1>::register_type swap,
                                          simd_trait<float, cyme::neon, 1>::register_type xmm0) {
    int32x4_t four = vmovq_n_s32(4);

    /* get the swap sign flag */
    swap = vbicq_s32(four, swap);
    swap = vshlq_s32(swap, vmovq_n_s32(29));

    /* update the sign of the final value*/
    xmm0 = (float32x4_t)veorq_s32((int32x4_t)xmm0, swap);
    return xmm0;
}

/**
  Selects the sign (+/-) for cos function. Inputs are:
    - swap int
    - Final calculated cos value
  specialisation float,cyme::neon,2 reg
 */
template <>
forceinline simd_trait<float, cyme::neon, 2>::register_type
_mm_select_sign_cos<float, cyme::neon, 2>(simd_trait<int, cyme::neon, 2>::register_type swap,
                                          simd_trait<float, cyme::neon, 2>::register_type xmm0) {
    int32x4_t four = vmovq_n_s32(4);

    /* get the swap sign flag */
    swap.r0 = vbicq_s32(four, swap.r0);
    swap.r1 = vbicq_s32(four, swap.r1);
    swap.r0 = vshlq_s32(swap.r0, vmovq_n_s32(29));
    swap.r1 = vshlq_s32(swap.r1, vmovq_n_s32(29));

    /* update the sign of the final value*/
    xmm0.r0 = (float32x4_t)veorq_s32((int32x4_t)xmm0.r0, swap.r0);
    xmm0.r1 = (float32x4_t)veorq_s32((int32x4_t)xmm0.r1, swap.r1);
    return simd_trait<float, cyme::neon, 2>::register_type(xmm0.r0, xmm0.r1);
}

/**
  Selects the sign (+/-) for cos function. Inputs are:
    - swap int
    - Final calculated cos value
  specialisation float,cyme::neon,4 reg
 */
template <>
forceinline simd_trait<float, cyme::neon, 4>::register_type
_mm_select_sign_cos<float, cyme::neon, 4>(simd_trait<int, cyme::neon, 4>::register_type swap,
                                          simd_trait<float, cyme::neon, 4>::register_type xmm0) {
    int32x4_t four = vmovq_n_s32(4);

    /* get the swap sign flag */
    swap.r0 = vbicq_s32(four, swap.r0);
    swap.r1 = vbicq_s32(four, swap.r1);
    swap.r2 = vbicq_s32(four, swap.r2);
    swap.r3 = vbicq_s32(four, swap.r3);
    swap.r0 = vshlq_s32(swap.r0, vmovq_n_s32(29));
    swap.r1 = vshlq_s32(swap.r1, vmovq_n_s32(29));
    swap.r2 = vshlq_s32(swap.r2, vmovq_n_s32(29));
    swap.r3 = vshlq_s32(swap.r3, vmovq_n_s32(29));

    /* update the sign of the final value*/
    xmm0.r0 = (float32x4_t)veorq_s32((int32x4_t)xmm0.r0, swap.r0);
    xmm0.r1 = (float32x4_t)veorq_s32((int32x4_t)xmm0.r1, swap.r1);
    xmm0.r2 = (float32x4_t)veorq_s32((int32x4_t)xmm0.r2, swap.r2);
    xmm0.r3 = (float32x4_t)veorq_s32((int32x4_t)xmm0.r3, swap.r3);
    return simd_trait<float, cyme::neon, 4>::register_type(xmm0.r0, xmm0.r1, xmm0.r2, xmm0.r3);
}

#ifdef __FMA__
/**
  Returns a vector containing the results of performing a fused multiply/add
 for each corresponding of a set of elements of the given vectors.
 Given arguments a,b, and c,
 result = a*b+c
   specialisation float,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 1>::register_type
_mm_fma<float, cyme::neon, 1>(simd_trait<float, cyme::neon, 1>::register_type xmm0,
                              simd_trait<float, cyme::neon, 1>::register_type xmm1,
                              simd_trait<float, cyme::neon, 1>::register_type xmm2) {
    return vfmaq_f32(xmm2, xmm0, xmm1);
}

/**
  Returns a vector containing the results of performing a fused multiply/add
 for each corresponding of a set of elements of the given vectors.
 Given arguments a,b, and c,
 result = a*b+c
   specialisation float,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 2>::register_type
_mm_fma<float, cyme::neon, 2>(simd_trait<float, cyme::neon, 2>::register_type xmm0,
                              simd_trait<float, cyme::neon, 2>::register_type xmm1,
                              simd_trait<float, cyme::neon, 2>::register_type xmm2) {
    return simd_trait<float, cyme::neon, 2>::register_type(vfmaq_f32(xmm2.r0, xmm0.r0, xmm1.r0),
                                                           vfmaq_f32(xmm2.r1, xmm0.r1, xmm1.r1));
}

/**
  Returns a vector containing the results of performing a fused multiply/add
 for each corresponding of a set of elements of the given vectors.
 Given arguments a,b, and c,
 result = a*b+c
   specialisation float,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 4>::register_type
_mm_fma<float, cyme::neon, 4>(simd_trait<float, cyme::neon, 4>::register_type xmm0,
                              simd_trait<float, cyme::neon, 4>::register_type xmm1,
                              simd_trait<float, cyme::neon, 4>::register_type xmm2) {
    return simd_trait<float, cyme::neon, 4>::register_type(
        vfmaq_f32(xmm2.r0, xmm0.r0, xmm1.r0), vfmaq_f32(xmm2.r1, xmm0.r1, xmm1.r1),
        vfmaq_f32(xmm2.r2, xmm0.r2, xmm1.r2), vfmaq_f32(xmm2.r3, xmm0.r3, xmm1.r3));
}

/**
  Returns a vector containing the results of performing a negative
  multiply-subtract operation on the given vectors. Given arguments a, b, and c,
  result = -(a*b-c)
  result = c - a*b.
   specialisation float,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 1>::register_type
_mm_nfma<float, cyme::neon, 1>(simd_trait<float, cyme::neon, 1>::register_type xmm0,
                               simd_trait<float, cyme::neon, 1>::register_type xmm1,
                               simd_trait<float, cyme::neon, 1>::register_type xmm2) {
    return vfmsq_f32(xmm2, xmm0, xmm1);
}

/**
  Returns a vector containing the results of performing a negative
  multiply-subtract operation on the given vectors. Given arguments a, b, and c,
  result = -(a*b-c)
  result = c - a*b.
   specialisation float,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 2>::register_type
_mm_nfma<float, cyme::neon, 2>(simd_trait<float, cyme::neon, 2>::register_type xmm0,
                               simd_trait<float, cyme::neon, 2>::register_type xmm1,
                               simd_trait<float, cyme::neon, 2>::register_type xmm2) {
    return simd_trait<float, cyme::neon, 2>::register_type(vfmsq_f32(xmm2.r0, xmm0.r0, xmm1.r0),
                                                           vfmsq_f32(xmm2.r1, xmm0.r1, xmm1.r1));
}

/**
  Returns a vector containing the results of performing a negative
  multiply-subtract operation on the given vectors. Given arguments a, b, and c,
  result = -(a*b-c)
  result = c - a*b.
   specialisation float,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 4>::register_type
_mm_nfma<float, cyme::neon, 4>(simd_trait<float, cyme::neon, 4>::register_type xmm0,
                               simd_trait<float, cyme::neon, 4>::register_type xmm1,
                               simd_trait<float, cyme::neon, 4>::register_type xmm2) {
    return simd_trait<float, cyme::neon, 4>::register_type(
        vfmsq_f32(xmm2.r0, xmm0.r0, xmm1.r0), vfmsq_f32(xmm2.r1, xmm0.r1, xmm1.r1),
        vfmsq_f32(xmm2.r2, xmm0.r2, xmm1.r2), vfmsq_f32(xmm2.r3, xmm0.r3, xmm1.r3));
}

/**
  Returns a vector containing the results of performing a multiply-substract
  operation on the given vectors. Given arguments a, b, and c,
  result = a*b-c.
   specialisation float,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 1>::register_type
_mm_fms<float, cyme::neon, 1>(simd_trait<float, cyme::neon, 1>::register_type xmm0,
                              simd_trait<float, cyme::neon, 1>::register_type xmm1,
                              simd_trait<float, cyme::neon, 1>::register_type xmm2) {
    float32x4_t temp = vfmsq_f32(xmm2, xmm0, xmm1);
    return vnegq_f32(temp);
}

/**
  Returns a vector containing the results of performing a multiply-substract
  operation on the given vectors. Given arguments a, b, and c,
  result = a*b-c.
   specialisation float,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 2>::register_type
_mm_fms<float, cyme::neon, 2>(simd_trait<float, cyme::neon, 2>::register_type xmm0,
                              simd_trait<float, cyme::neon, 2>::register_type xmm1,
                              simd_trait<float, cyme::neon, 2>::register_type xmm2) {
    float32x4_t temp1 = vfmsq_f32(xmm2.r0, xmm0.r0, xmm1.r0);
    float32x4_t temp2 = vfmsq_f32(xmm2.r1, xmm0.r1, xmm1.r1);
    return simd_trait<float, cyme::neon, 2>::register_type(vnegq_f32(temp1), vnegq_f32(temp2));
}

/**
  Returns a vector containing the results of performing a multiply-substract
  operation on the given vectors. Given arguments a, b, and c,
  result = a*b-c.
   specialisation float,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<float, cyme::neon, 4>::register_type
_mm_fms<float, cyme::neon, 4>(simd_trait<float, cyme::neon, 4>::register_type xmm0,
                              simd_trait<float, cyme::neon, 4>::register_type xmm1,
                              simd_trait<float, cyme::neon, 4>::register_type xmm2) {
    float32x4_t temp1 = vfmsq_f32(xmm2.r0, xmm0.r0, xmm1.r0);
    float32x4_t temp2 = vfmsq_f32(xmm2.r1, xmm0.r1, xmm1.r1);
    float32x4_t temp3 = vfmsq_f32(xmm2.r2, xmm0.r2, xmm1.r2);
    float32x4_t temp4 = vfmsq_f32(xmm2.r3, xmm0.r3, xmm1.r3);
    return simd_trait<float, cyme::neon, 4>::register_type(vnegq_f32(temp1), vnegq_f32(temp2), vnegq_f32(temp3),
                                                           vnegq_f32(temp4));
}

/**
 Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
 Given arguments a,b, and c,
 result = -(a*b+c)
   specialisation float,cyme::neon,1 regs
*/
template <>
forceinline simd_trait<float, cyme::neon, 1>::register_type
_mm_nfms<float, cyme::neon, 1>(simd_trait<float, cyme::neon, 1>::register_type xmm0,
                               simd_trait<float, cyme::neon, 1>::register_type xmm1,
                               simd_trait<float, cyme::neon, 1>::register_type xmm2) {
    float32x4_t temp = vfmaq_f32(xmm2, xmm0, xmm1);
    return vnegq_f32(temp);
}

/**
 Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
 Given arguments a,b, and c,
 result = -(a*b+c)
   specialisation float,cyme::neon,2 regs
*/
template <>
forceinline simd_trait<float, cyme::neon, 2>::register_type
_mm_nfms<float, cyme::neon, 2>(simd_trait<float, cyme::neon, 2>::register_type xmm0,
                               simd_trait<float, cyme::neon, 2>::register_type xmm1,
                               simd_trait<float, cyme::neon, 2>::register_type xmm2) {
    float32x4_t temp1 = vfmaq_f32(xmm2.r0, xmm0.r0, xmm1.r0);
    float32x4_t temp2 = vfmaq_f32(xmm2.r1, xmm0.r1, xmm1.r1);
    return simd_trait<float, cyme::neon, 2>::register_type(vnegq_f32(temp1), vnegq_f32(temp2));
}

/**
 Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
 Given arguments a,b, and c,
 result = -(a*b+c)
   specialisation float,cyme::neon,4 regs
*/
template <>
forceinline simd_trait<float, cyme::neon, 4>::register_type
_mm_nfms<float, cyme::neon, 4>(simd_trait<float, cyme::neon, 4>::register_type xmm0,
                               simd_trait<float, cyme::neon, 4>::register_type xmm1,
                               simd_trait<float, cyme::neon, 4>::register_type xmm2) {
    float32x4_t temp1 = vfmaq_f32(xmm2.r0, xmm0.r0, xmm1.r0);
    float32x4_t temp2 = vfmaq_f32(xmm2.r1, xmm0.r1, xmm1.r1);
    float32x4_t temp3 = vfmaq_f32(xmm2.r2, xmm0.r2, xmm1.r2);
    float32x4_t temp4 = vfmaq_f32(xmm2.r3, xmm0.r3, xmm1.r3);
    return simd_trait<float, cyme::neon, 4>::register_type(vnegq_f32(temp1), vnegq_f32(temp2), vnegq_f32(temp3),
                                                           vnegq_f32(temp4));
}
#endif
/*--------------------------------------------------------------------- double ---------------*/
/**
   Single load a double-precision (64-bit) floating-point element from cyme into lower element of dst.
 */
template <>
forceinline simd_trait<double, cyme::neon, 1>::register_type
_mm_single_load<double, cyme::neon, 1>(const simd_trait<double, cyme::neon, 1>::value_type b) {
    return vld1q_f64(&b);
}

/**
   Single store a double-precision (64-bit) floating-point element from register lower element to cyme.
 */
template <>
forceinline simd_trait<double, cyme::neon, 1>::value_type
_mm_single_store<double, cyme::neon, 1>(simd_trait<double, cyme::neon, 1>::register_type xmm0,
                                        simd_trait<double, cyme::neon, 1>::pointer b) {
    vst1q_f64(b, xmm0);
    return *b;
}

/**
  Returns a vector of which the value of each element is set to a.
   specialisation double,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 1>::register_type
_mm_load1<double, cyme::neon, 1>(const simd_trait<double, cyme::neon, 1>::value_type &a) {
    return vld1q_dup_f64(&a);
}

/**
  Returns a vector of which the value of each element is set to a.
   specialisation double,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 2>::register_type
_mm_load1<double, cyme::neon, 2>(const simd_trait<double, cyme::neon, 2>::value_type &a) {
    return simd_trait<double, cyme::neon, 2>::register_type(vld1q_dup_f64(&a), vld1q_dup_f64(&a));
}

/**
  Returns a vector of which the value of each element is set to a.
   specialisation double,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 4>::register_type
_mm_load1<double, cyme::neon, 4>(const simd_trait<double, cyme::neon, 4>::value_type &a) {
    return simd_trait<double, cyme::neon, 4>::register_type(vld1q_dup_f64(&a), vld1q_dup_f64(&a), vld1q_dup_f64(&a),
                                                            vld1q_dup_f64(&a));
}

/**
  Loads a vector from the given cyme address.
   specialisation double,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 1>::register_type
_mm_load<double, cyme::neon, 1>(simd_trait<double, cyme::neon, 1>::const_pointer a) {
    return vld1q_f64(a);
}

/**
  Loads a vector from the given cyme address.
   specialisation double,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 2>::register_type
_mm_load<double, cyme::neon, 2>(simd_trait<double, cyme::neon, 2>::const_pointer a) {
    return simd_trait<double, cyme::neon, 2>::register_type(vld1q_f64(a), vld1q_f64(a + 2));
}

/**
  Loads a vector from the given cyme address.
   specialisation double,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 4>::register_type
_mm_load<double, cyme::neon, 4>(simd_trait<double, cyme::neon, 4>::const_pointer a) {
    return simd_trait<double, cyme::neon, 4>::register_type(vld1q_f64(a), vld1q_f64(a + 2), vld1q_f64(a + 4),
                                                            vld1q_f64(a + 6));
}

/**
  Stores a vector to cyme at the given address.
   specialisation double,cyme::neon,1 regs
 */
template <>
forceinline void _mm_store<double, cyme::neon, 1>(simd_trait<double, cyme::neon, 1>::register_type xmm0,
                                                  simd_trait<double, cyme::neon, 1>::pointer a) {
    vst1q_f64(a, xmm0);
}

/**
  Stores a vector to cyme at the given address.
   specialisation double,cyme::neon,2 regs
 */
template <>
forceinline void _mm_store<double, cyme::neon, 2>(simd_trait<double, cyme::neon, 2>::register_type xmm0,
                                                  simd_trait<double, cyme::neon, 2>::pointer a) {
    vst1q_f64(a, xmm0.r0);
    vst1q_f64((a + 2), xmm0.r1);
}

/**
  Stores a vector to cyme at the given address.
   specialisation double,cyme::neon,4 regs
 */
template <>
forceinline void _mm_store<double, cyme::neon, 4>(simd_trait<double, cyme::neon, 4>::register_type xmm0,
                                                  simd_trait<double, cyme::neon, 4>::pointer a) {
    vst1q_f64(a, xmm0.r0);
    vst1q_f64((a + 2), xmm0.r1);
    vst1q_f64((a + 4), xmm0.r2);
    vst1q_f64((a + 6), xmm0.r3);
}

/**
  Returns a vector containing the results of performing a multiply operation using the given vectors.
   specialisation double,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 1>::register_type
_mm_mul<double, cyme::neon, 1>(simd_trait<double, cyme::neon, 1>::register_type xmm0,
                               simd_trait<double, cyme::neon, 1>::register_type xmm1) {
    return vmulq_f64(xmm0, xmm1);
}

/**
  Returns a vector containing the results of performing a multiply operation using the given vectors.
   specialisation double,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 2>::register_type
_mm_mul<double, cyme::neon, 2>(simd_trait<double, cyme::neon, 2>::register_type xmm0,
                               simd_trait<double, cyme::neon, 2>::register_type xmm1) {
    return simd_trait<double, cyme::neon, 2>::register_type(vmulq_f64(xmm0.r0, xmm1.r0), vmulq_f64(xmm0.r1, xmm1.r1));
}

/**
  Returns a vector containing the results of performing a multiply operation using the given vectors.
   specialisation double,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 4>::register_type
_mm_mul<double, cyme::neon, 4>(simd_trait<double, cyme::neon, 4>::register_type xmm0,
                               simd_trait<double, cyme::neon, 4>::register_type xmm1) {
    return simd_trait<double, cyme::neon, 4>::register_type(vmulq_f64(xmm0.r0, xmm1.r0), vmulq_f64(xmm0.r1, xmm1.r1),
                                                            vmulq_f64(xmm0.r2, xmm1.r2), vmulq_f64(xmm0.r3, xmm1.r3));
}

/**
  Returns a vector containing the result of dividing each element of a by the corresponding element of b.
   specialisation double,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 1>::register_type
_mm_div<double, cyme::neon, 1>(simd_trait<double, cyme::neon, 1>::register_type xmm0,
                               simd_trait<double, cyme::neon, 1>::register_type xmm1) {
    return vdivq_f64(xmm0, xmm1);
}

/**
  Returns a vector containing the result of dividing each element of a by the corresponding element of b.
   specialisation double,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 2>::register_type
_mm_div<double, cyme::neon, 2>(simd_trait<double, cyme::neon, 2>::register_type xmm0,
                               simd_trait<double, cyme::neon, 2>::register_type xmm1) {
    return simd_trait<double, cyme::neon, 2>::register_type(vdivq_f64(xmm0.r0, xmm1.r0), vdivq_f64(xmm0.r1, xmm1.r1));
}

/**
  Returns a vector containing the result of dividing each element of a by the corresponding element of b.
   specialisation double,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 4>::register_type
_mm_div<double, cyme::neon, 4>(simd_trait<double, cyme::neon, 4>::register_type xmm0,
                               simd_trait<double, cyme::neon, 4>::register_type xmm1) {
    return simd_trait<double, cyme::neon, 4>::register_type(vdivq_f64(xmm0.r0, xmm1.r0), vdivq_f64(xmm0.r1, xmm1.r1),
                                                            vdivq_f64(xmm0.r2, xmm1.r2), vdivq_f64(xmm0.r3, xmm1.r3));
}

/**
  Returns a vector containing the sums of each set of corresponding elements of the given vectors.
   specialisation double,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 1>::register_type
_mm_add<double, cyme::neon, 1>(simd_trait<double, cyme::neon, 1>::register_type xmm0,
                               simd_trait<double, cyme::neon, 1>::register_type xmm1) {
    return vaddq_f64(xmm0, xmm1);
}

/**
  Returns a vector containing the sums of each set of corresponding elements of the given vectors.
   specialisation double,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 2>::register_type
_mm_add<double, cyme::neon, 2>(simd_trait<double, cyme::neon, 2>::register_type xmm0,
                               simd_trait<double, cyme::neon, 2>::register_type xmm1) {
    return simd_trait<double, cyme::neon, 2>::register_type(vaddq_f64(xmm0.r0, xmm1.r0), vaddq_f64(xmm0.r1, xmm1.r1));
}

/**
  Returns a vector containing the sums of each set of corresponding elements of the given vectors.
   specialisation double,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 4>::register_type
_mm_add<double, cyme::neon, 4>(simd_trait<double, cyme::neon, 4>::register_type xmm0,
                               simd_trait<double, cyme::neon, 4>::register_type xmm1) {
    return simd_trait<double, cyme::neon, 4>::register_type(vaddq_f64(xmm0.r0, xmm1.r0), vaddq_f64(xmm0.r1, xmm1.r1),
                                                            vaddq_f64(xmm0.r2, xmm1.r2), vaddq_f64(xmm0.r3, xmm1.r3));
}

/**
  Returns a vector containing the result of subtracting each element of b from the corresponding element of a.
   specialisation double,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 1>::register_type
_mm_sub<double, cyme::neon, 1>(simd_trait<double, cyme::neon, 1>::register_type xmm0,
                               simd_trait<double, cyme::neon, 1>::register_type xmm1) {
    return vsubq_f64(xmm0, xmm1);
}

/**
  Returns a vector containing the result of subtracting each element of b from the corresponding element of a.
   specialisation double,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 2>::register_type
_mm_sub<double, cyme::neon, 2>(simd_trait<double, cyme::neon, 2>::register_type xmm0,
                               simd_trait<double, cyme::neon, 2>::register_type xmm1) {
    return simd_trait<double, cyme::neon, 2>::register_type(vsubq_f64(xmm0.r0, xmm1.r0), vsubq_f64(xmm0.r1, xmm1.r1));
}

/**
  Returns a vector containing the result of subtracting each element of b from the corresponding element of a.
   specialisation double,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 4>::register_type
_mm_sub<double, cyme::neon, 4>(simd_trait<double, cyme::neon, 4>::register_type xmm0,
                               simd_trait<double, cyme::neon, 4>::register_type xmm1) {
    return simd_trait<double, cyme::neon, 4>::register_type(vsubq_f64(xmm0.r0, xmm1.r0), vsubq_f64(xmm0.r1, xmm1.r1),
                                                            vsubq_f64(xmm0.r2, xmm1.r2), vsubq_f64(xmm0.r3, xmm1.r3));
}

/**
  Computes the exponential function of each element of vx.
   specialisation double,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 1>::register_type
_mm_exp<double, cyme::neon, 1>(simd_trait<double, cyme::neon, 1>::register_type xmm0) {
    std::cout << "Vendor EXP not yet implemented for double." << std::endl;
    assert(false);
    return xmm0;
}

/**
  Computes the exponential function of each element of vx.
   specialisation double,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 2>::register_type
_mm_exp<double, cyme::neon, 2>(simd_trait<double, cyme::neon, 2>::register_type xmm0) {
    std::cout << "Vendor EXP not yet implemented for double." << std::endl;
    assert(false);
    return xmm0;
}

/**
  Computes the exponential function of each element of vx.
   specialisation double,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 4>::register_type
_mm_exp<double, cyme::neon, 4>(simd_trait<double, cyme::neon, 4>::register_type xmm0) {
    std::cout << "Vendor EXP not yet implemented for double." << std::endl;
    assert(false);
    return xmm0;
}

/**
  Computes the logarithm function of each element of vx.
   specialisation double,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 1>::register_type
_mm_log<double, cyme::neon, 1>(simd_trait<double, cyme::neon, 1>::register_type xmm0) {
    std::cout << "Vendor LOG not yet implemented for double." << std::endl;
    assert(false);
    return xmm0;
}

/**
  Computes the logarithm function of each element of vx.
   specialisation double,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 2>::register_type
_mm_log<double, cyme::neon, 2>(simd_trait<double, cyme::neon, 2>::register_type xmm0) {
    std::cout << "Vendor LOG not yet implemented for double." << std::endl;
    assert(false);
    return xmm0;
}

/**
  Computes the logarithm function of each element of vx.
   specialisation double,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 4>::register_type
_mm_log<double, cyme::neon, 4>(simd_trait<double, cyme::neon, 4>::register_type xmm0) {
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
template <>
forceinline simd_trait<double, cyme::neon, 1>::register_type
_mm_rec<double, cyme::neon, 1>(simd_trait<double, cyme::neon, 1>::register_type xmm0) {
    return vrecpeq_f64(xmm0);
}

/**
  Returns a vector containing estimates of the reciprocals of the corresponding elements of the given vector.
 \warning The precision guarantee is specified by the following expression, where x is the value of each element
 of a and r is the value of the corresponding element of the result value:
 | (r-1/x) / (1/x) | ≤ 1/256
   specialisation double,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 2>::register_type
_mm_rec<double, cyme::neon, 2>(simd_trait<double, cyme::neon, 2>::register_type xmm0) {
    return simd_trait<double, cyme::neon, 2>::register_type(vrecpeq_f64(xmm0.r0), vrecpeq_f64(xmm0.r1));
}

/**
  Returns a vector containing estimates of the reciprocals of the corresponding elements of the given vector.
 \warning The precision guarantee is specified by the following expression, where x is the value of each element
 of a and r is the value of the corresponding element of the result value:
 | (r-1/x) / (1/x) | ≤ 1/256
   specialisation double,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 4>::register_type
_mm_rec<double, cyme::neon, 4>(simd_trait<double, cyme::neon, 4>::register_type xmm0) {
    return simd_trait<double, cyme::neon, 4>::register_type(vrecpeq_f64(xmm0.r0), vrecpeq_f64(xmm0.r1),
                                                            vrecpeq_f64(xmm0.r2), vrecpeq_f64(xmm0.r3));
}

/**
  Compute 1/recsqrt (64-bit) floating point elements in xmm0 to packed double-precision (64-bit)
 floating-point elements, and store the results in dst.
 \warning The precision guarantee is specified by the following expression, where x is the value of each element
 of a and r is the value of the corresponding element of the result value:
 | (r-1/x^0,5) / (1/x^0.5) | ≤ 1/256
   specialisation double,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 1>::register_type
_mm_rsqrt<double, cyme::neon, 1>(simd_trait<double, cyme::neon, 1>::register_type xmm0) {
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
template <>
forceinline simd_trait<double, cyme::neon, 2>::register_type
_mm_rsqrt<double, cyme::neon, 2>(simd_trait<double, cyme::neon, 2>::register_type xmm0) {
    return simd_trait<double, cyme::neon, 2>::register_type(vrsqrteq_f64(xmm0.r0), vrsqrteq_f64(xmm0.r1));
}

/**
  Compute 1/recsqrt (64-bit) floating point elements in xmm0 to packed double-precision (64-bit)
 floating-point elements, and store the results in dst.
 \warning The precision guarantee is specified by the following expression, where x is the value of each element
 of a and r is the value of the corresponding element of the result value:
 | (r-1/x^0,5) / (1/x^0.5) | ≤ 1/256
   specialisation double,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 4>::register_type
_mm_rsqrt<double, cyme::neon, 4>(simd_trait<double, cyme::neon, 4>::register_type xmm0) {
    return simd_trait<double, cyme::neon, 4>::register_type(vrsqrteq_f64(xmm0.r0), vrsqrteq_f64(xmm0.r1),
                                                            vrsqrteq_f64(xmm0.r2), vrsqrteq_f64(xmm0.r3));
}

/**
  Returns a vector containing the negated value of the corresponding elements in the given vector.
   specialisation double,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 1>::register_type
_mm_neg<double, cyme::neon, 1>(simd_trait<double, cyme::neon, 1>::register_type xmm0) {
    return vnegq_f64(xmm0);
}

/**
  Returns a vector containing the negated value of the corresponding elements in the given vector.
   specialisation double,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 2>::register_type
_mm_neg<double, cyme::neon, 2>(simd_trait<double, cyme::neon, 2>::register_type xmm0) {
    return simd_trait<double, cyme::neon, 2>::register_type(vnegq_f64(xmm0.r0), vnegq_f64(xmm0.r1));
}

/**
  Returns a vector containing the negated value of the corresponding elements in the given vector.
   specialisation double,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 4>::register_type
_mm_neg<double, cyme::neon, 4>(simd_trait<double, cyme::neon, 4>::register_type xmm0) {
    return simd_trait<double, cyme::neon, 4>::register_type(vnegq_f64(xmm0.r0), vnegq_f64(xmm0.r1), vnegq_f64(xmm0.r2),
                                                            vnegq_f64(xmm0.r3));
}

/**
  Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
 and store the results in dst.
   specialisation double,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 1>::register_type
_mm_cast<double, cyme::neon, 1>(simd_trait<int, cyme::neon, 1>::register_type xmm0) {
    return vcvtq_f64_s64(vshrq_n_s64((int64x2_t)xmm0, 32));
}

/**
  Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
 and store the results in dst.
   specialisation double,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 2>::register_type
_mm_cast<double, cyme::neon, 2>(simd_trait<int, cyme::neon, 2>::register_type xmm0) {
    return simd_trait<double, cyme::neon, 2>::register_type(vcvtq_f64_s64(vshrq_n_s64((int64x2_t)xmm0.r0, 32)),
                                                            vcvtq_f64_s64(vshrq_n_s64((int64x2_t)xmm0.r1, 32)));
}

/**
  Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
 and store the results in dst.
   specialisation double,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 4>::register_type
_mm_cast<double, cyme::neon, 4>(simd_trait<int, cyme::neon, 4>::register_type xmm0) {
    return simd_trait<double, cyme::neon, 4>::register_type(
        vcvtq_f64_s64(vshrq_n_s64((int64x2_t)xmm0.r0, 32)), vcvtq_f64_s64(vshrq_n_s64((int64x2_t)xmm0.r1, 32)),
        vcvtq_f64_s64(vshrq_n_s64((int64x2_t)xmm0.r2, 32)), vcvtq_f64_s64(vshrq_n_s64((int64x2_t)xmm0.r3, 32)));
}

/**
  Returns a vector containing the largest representable floating-point integral values less than or equal
 to the values of the corresponding elements of the given vector.
   specialisation double,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<int, cyme::neon, 1>::register_type
_mm_floor<double, cyme::neon, 1>(simd_trait<double, cyme::neon, 1>::register_type xmm0) {
    int64x2_t temp = vcvtq_s64_f64(xmm0);    // value cast to int64
    float64x2_t comp = vcvtq_f64_s64(temp);  // convert back for comparison
    uint64x2_t corr = vcltq_f64(xmm0, comp); // temp -1 if xmm0 < comp
    temp = vaddq_s64(temp, (int64x2_t)corr); // adjust temp

    // create int pointer and use to create two seperate intx2 vectors
    int32_t scalar32[4];
    vst1q_s32(scalar32, (int32x4_t)temp);
    int32x2_t result1 = vmov_n_s32(scalar32[0]);
    int32x2_t result2 = vmov_n_s32(scalar32[2]);
    return vcombine_s32(result1, result2);
}

/**
  Returns a vector containing the largest representable floating-point integral values less than or equal
 to the values of the corresponding elements of the given vector.
   specialisation double,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<int, cyme::neon, 2>::register_type
_mm_floor<double, cyme::neon, 2>(simd_trait<double, cyme::neon, 2>::register_type xmm0) {
    int64x2_t temp1 = vcvtq_s64_f64(xmm0.r0);                    // value cast to int64
    int64x2_t temp2 = vcvtq_s64_f64(xmm0.r1);                    // value cast to int64
    uint64x2_t corr1 = vcltq_f64(xmm0.r0, vcvtq_f64_s64(temp1)); // temp1 -1 if xmm0 < temp
    uint64x2_t corr2 = vcltq_f64(xmm0.r1, vcvtq_f64_s64(temp2)); // temp2 -1 if xmm0 < temp
    temp1 = vaddq_s64(temp1, (int64x2_t)corr1);                  // adjust temp1
    temp2 = vaddq_s64(temp2, (int64x2_t)corr2);                  // adjust temp2

    int32_t scalar32[4];
    // vec[0]
    vst1q_s32(scalar32, (int32x4_t)temp1);
    int32x2_t resultn_1 = vmov_n_s32(scalar32[0]);
    int32x2_t resultn_2 = vmov_n_s32(scalar32[2]);
    int32x4_t result1 = vcombine_s32(resultn_1, resultn_2);
    // vec[1]
    vst1q_s32(scalar32, (int32x4_t)temp2);
    resultn_1 = vmov_n_s32(scalar32[0]);
    resultn_2 = vmov_n_s32(scalar32[2]);
    int32x4_t result2 = vcombine_s32(resultn_1, resultn_2);
    return simd_trait<int, cyme::neon, 2>::register_type(result1, result2);
}

/**
  Returns a vector containing the largest representable floating-point integral values less than or equal
 to the values of the corresponding elements of the given vector.
   specialisation double,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<int, cyme::neon, 4>::register_type
_mm_floor<double, cyme::neon, 4>(simd_trait<double, cyme::neon, 4>::register_type xmm0) {
    int64x2_t temp1 = vcvtq_s64_f64(xmm0.r0); // value cast to int64x2
    int64x2_t temp2 = vcvtq_s64_f64(xmm0.r1);
    int64x2_t temp3 = vcvtq_s64_f64(xmm0.r2);
    int64x2_t temp4 = vcvtq_s64_f64(xmm0.r3);
    uint64x2_t corr1 = vcltq_f64(xmm0.r0, vcvtq_f64_s64(temp1)); // temp -1 if xmm0 < temp
    uint64x2_t corr2 = vcltq_f64(xmm0.r1, vcvtq_f64_s64(temp2));
    uint64x2_t corr3 = vcltq_f64(xmm0.r2, vcvtq_f64_s64(temp3));
    uint64x2_t corr4 = vcltq_f64(xmm0.r3, vcvtq_f64_s64(temp4));
    temp1 = vaddq_s64(temp1, (int64x2_t)corr1); // add correction to temp
    temp2 = vaddq_s64(temp2, (int64x2_t)corr2);
    temp3 = vaddq_s64(temp3, (int64x2_t)corr3);
    temp4 = vaddq_s64(temp4, (int64x2_t)corr4);

    int32_t scalar32[4];
    // vec[0]
    vst1q_s32(scalar32, (int32x4_t)temp1);
    int32x2_t resultn_1 = vmov_n_s32(scalar32[0]);
    int32x2_t resultn_2 = vmov_n_s32(scalar32[2]);
    int32x4_t result1 = vcombine_s32(resultn_1, resultn_2);
    // vec[1]
    vst1q_s32(scalar32, (int32x4_t)temp2);
    resultn_1 = vmov_n_s32(scalar32[0]);
    resultn_2 = vmov_n_s32(scalar32[2]);
    int32x4_t result2 = vcombine_s32(resultn_1, resultn_2);
    // vec[2]
    vst1q_s32(scalar32, (int32x4_t)temp3);
    resultn_1 = vmov_n_s32(scalar32[0]);
    resultn_2 = vmov_n_s32(scalar32[2]);
    int32x4_t result3 = vcombine_s32(resultn_1, resultn_2);
    // vec[3]
    vst1q_s32(scalar32, (int32x4_t)temp4);
    resultn_1 = vmov_n_s32(scalar32[0]);
    resultn_2 = vmov_n_s32(scalar32[2]);
    int32x4_t result4 = vcombine_s32(resultn_1, resultn_2);
    return simd_trait<int, cyme::neon, 4>::register_type(result1, result2, result3, result4);
}

/**
  Returns a vector containing 2^k where k is a vector of integer, because there is no builtin function
  for 2^k in double, the computation is done using a C trick.
   specialisation double,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 1>::register_type
_mm_twok<double, cyme::neon, 1>(simd_trait<int, cyme::neon, 1>::register_type xmm0) {
    xmm0 = vaddq_s32(xmm0, vmovq_n_s32(1023));
    xmm0 = vshlq_s32(xmm0, vmovq_n_s32(20));
    return (float64x2_t)xmm0;
}

/**
  Returns a vector containing 2^k where k is a vector of integer, because there is no builtin function
  for 2^k in double, the computation is done using a C trick.
   specialisation double,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 2>::register_type
_mm_twok<double, cyme::neon, 2>(simd_trait<int, cyme::neon, 2>::register_type xmm0) {
    xmm0.r0 = vaddq_s32(xmm0.r0, vmovq_n_s32(1023));
    xmm0.r1 = vaddq_s32(xmm0.r1, vmovq_n_s32(1023));
    xmm0.r0 = vshlq_s32(xmm0.r0, vmovq_n_s32(20));
    xmm0.r1 = vshlq_s32(xmm0.r1, vmovq_n_s32(20));
    return simd_trait<double, cyme::neon, 2>::register_type((float64x2_t)xmm0.r0, (float64x2_t)xmm0.r1);
}

/**
  Returns a vector containing 2^k where k is a vector of integer, because there is no builtin function
  for 2^k in double, the computation is done using a C trick.
   specialisation double,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 4>::register_type
_mm_twok<double, cyme::neon, 4>(simd_trait<int, cyme::neon, 4>::register_type xmm0) {
    xmm0.r0 = vaddq_s32(xmm0.r0, vmovq_n_s32(1023));
    xmm0.r1 = vaddq_s32(xmm0.r1, vmovq_n_s32(1023));
    xmm0.r2 = vaddq_s32(xmm0.r2, vmovq_n_s32(1023));
    xmm0.r3 = vaddq_s32(xmm0.r3, vmovq_n_s32(1023));
    xmm0.r0 = vshlq_s32(xmm0.r0, vmovq_n_s32(20));
    xmm0.r1 = vshlq_s32(xmm0.r1, vmovq_n_s32(20));
    xmm0.r2 = vshlq_s32(xmm0.r2, vmovq_n_s32(20));
    xmm0.r3 = vshlq_s32(xmm0.r3, vmovq_n_s32(20));
    return simd_trait<double, cyme::neon, 4>::register_type((float64x2_t)xmm0.r0, (float64x2_t)xmm0.r1,
                                                            (float64x2_t)xmm0.r2, (float64x2_t)xmm0.r3);
}

/**
   Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
   Because we are casting from vector2double -> vector4int, must use specific mask and tmp_sub vectors.
    specialisation double,cyme::neon,1 regs
  */
template <>
forceinline simd_trait<double, cyme::neon, 1>::register_type
_mm_ge<double, cyme::neon, 1>(simd_trait<double, cyme::neon, 1>::register_type xmm0) {
    int64x2_t tmp = (int64x2_t)xmm0;
    tmp = vshrq_n_s64(tmp, 52);
    tmp = vsubq_s64(tmp, vmovq_n_s64(1023));
    return vcvtq_f64_s64(tmp);
}

/**
   Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
   Because we are casting from vector2double -> vector4int, must use specific mask and tmp_sub vectors.
    specialisation double,cyme::neon,2 regs
  */
template <>
forceinline simd_trait<double, cyme::neon, 2>::register_type
_mm_ge<double, cyme::neon, 2>(simd_trait<double, cyme::neon, 2>::register_type xmm0) {
    int64x2_t tmp1 = (int64x2_t)xmm0.r0;
    int64x2_t tmp2 = (int64x2_t)xmm0.r1;
    tmp1 = vshrq_n_s64(tmp1, 52);
    tmp2 = vshrq_n_s64(tmp2, 52);
    tmp1 = vsubq_s64(tmp1, vmovq_n_s64(1023));
    tmp2 = vsubq_s64(tmp2, vmovq_n_s64(1023));
    return simd_trait<double, cyme::neon, 2>::register_type(vcvtq_f64_s64(tmp1), vcvtq_f64_s64(tmp2));
}

/**
   Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
   Because we are casting from vector2double -> vector4int, must use specific mask and tmp_sub vectors.
    specialisation double,cyme::neon,4 regs
  */
template <>
forceinline simd_trait<double, cyme::neon, 4>::register_type
_mm_ge<double, cyme::neon, 4>(simd_trait<double, cyme::neon, 4>::register_type xmm0) {
    int64x2_t tmp1 = (int64x2_t)xmm0.r0;
    int64x2_t tmp2 = (int64x2_t)xmm0.r1;
    int64x2_t tmp3 = (int64x2_t)xmm0.r2;
    int64x2_t tmp4 = (int64x2_t)xmm0.r3;
    tmp1 = vshrq_n_s64(tmp1, 52);
    tmp2 = vshrq_n_s64(tmp2, 52);
    tmp3 = vshrq_n_s64(tmp3, 52);
    tmp4 = vshrq_n_s64(tmp4, 52);
    tmp1 = vsubq_s64(tmp1, vmovq_n_s64(1023));
    tmp2 = vsubq_s64(tmp2, vmovq_n_s64(1023));
    tmp3 = vsubq_s64(tmp3, vmovq_n_s64(1023));
    tmp4 = vsubq_s64(tmp4, vmovq_n_s64(1023));
    return simd_trait<double, cyme::neon, 4>::register_type(vcvtq_f64_s64(tmp1), vcvtq_f64_s64(tmp2),
                                                            vcvtq_f64_s64(tmp3), vcvtq_f64_s64(tmp4));
}

/**
  Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
  Because we are casting from vector2double -> vector4int, must use specific mask and tmp_add vectors.
   specialisation double,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 1>::register_type
_mm_gf<double, cyme::neon, 1>(simd_trait<double, cyme::neon, 1>::register_type xmm0) {
    int64x2_t tmp = (int64x2_t)xmm0;
    tmp = vandq_s64(tmp, vmovq_n_s64((signed long)0xfffffffffffff));
    tmp = vaddq_s64(tmp, vmovq_n_s64((signed long)0x3ff0000000000000));
    return (float64x2_t)tmp;
}

/**
  Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
  Because we are casting from vector2double -> vector4int, must use specific mask and tmp_add vectors.
   specialisation double,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 2>::register_type
_mm_gf<double, cyme::neon, 2>(simd_trait<double, cyme::neon, 2>::register_type xmm0) {
    int64x2_t tmp1 = (int64x2_t)xmm0.r0;
    int64x2_t tmp2 = (int64x2_t)xmm0.r1;
    tmp1 = vandq_s64(tmp1, vmovq_n_s64((signed long)0xfffffffffffff));
    tmp2 = vandq_s64(tmp2, vmovq_n_s64((signed long)0xfffffffffffff));
    tmp1 = vaddq_s64(tmp1, vmovq_n_s64((signed long)0x3ff0000000000000));
    tmp2 = vaddq_s64(tmp2, vmovq_n_s64((signed long)0x3ff0000000000000));
    return simd_trait<double, cyme::neon, 2>::register_type((float64x2_t)tmp1, (float64x2_t)tmp2);
}

/**
  Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
  Because we are casting from vector2double -> vector4int, must use specific mask and tmp_add vectors.
   specialisation double,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 4>::register_type
_mm_gf<double, cyme::neon, 4>(simd_trait<double, cyme::neon, 4>::register_type xmm0) {
    int64x2_t tmp1 = (int64x2_t)xmm0.r0;
    int64x2_t tmp2 = (int64x2_t)xmm0.r1;
    int64x2_t tmp3 = (int64x2_t)xmm0.r2;
    int64x2_t tmp4 = (int64x2_t)xmm0.r3;
    tmp1 = vandq_s64(tmp1, vmovq_n_s64((signed long)0xfffffffffffff));
    tmp2 = vandq_s64(tmp2, vmovq_n_s64((signed long)0xfffffffffffff));
    tmp3 = vandq_s64(tmp3, vmovq_n_s64((signed long)0xfffffffffffff));
    tmp4 = vandq_s64(tmp4, vmovq_n_s64((signed long)0xfffffffffffff));
    tmp1 = vaddq_s64(tmp1, vmovq_n_s64((signed long)0x3ff0000000000000));
    tmp2 = vaddq_s64(tmp2, vmovq_n_s64((signed long)0x3ff0000000000000));
    tmp3 = vaddq_s64(tmp3, vmovq_n_s64((signed long)0x3ff0000000000000));
    tmp4 = vaddq_s64(tmp4, vmovq_n_s64((signed long)0x3ff0000000000000));
    return simd_trait<double, cyme::neon, 4>::register_type((float64x2_t)tmp1, (float64x2_t)tmp2, (float64x2_t)tmp3,
                                                            (float64x2_t)tmp4);
}

/**
  Computes the absolute value for double-precision (64-bit) floating point elements and stores
  the result in dst.
  specialisation double,cyme::neon, 1 reg
 */
template <>
forceinline simd_trait<double, cyme::neon, 1>::register_type
_mm_fabs<double, cyme::neon, 1>(simd_trait<double, cyme::neon, 1>::register_type xmm0) {
    return vabsq_f64(xmm0);
}

/**
  Computes the absolute value for double-precision (64-bit) floating point elements and stores
  the result in dst.
  specialisation double,cyme::neon, 2 reg
 */
template <>
forceinline simd_trait<double, cyme::neon, 2>::register_type
_mm_fabs<double, cyme::neon, 2>(simd_trait<double, cyme::neon, 2>::register_type xmm0) {
    return simd_trait<double, cyme::neon, 2>::register_type(vabsq_f64(xmm0.r0), vabsq_f64(xmm0.r1));
}

/**
  Computes the absolute value for double-precision (64-bit) floating point elements and stores
  the result in dst.
  specialisation double,cyme::neon, 4 reg
 */
template <>
forceinline simd_trait<double, cyme::neon, 4>::register_type
_mm_fabs<double, cyme::neon, 4>(simd_trait<double, cyme::neon, 4>::register_type xmm0) {
    return simd_trait<double, cyme::neon, 4>::register_type(vabsq_f64(xmm0.r0), vabsq_f64(xmm0.r1), vabsq_f64(xmm0.r2),
                                                            vabsq_f64(xmm0.r3));
}

/**
  Selects the polynomial for sin function. Inputs are:
    - Selector int
    - Option one
    - Option two
  specialisation double,cyme::neon, 1 reg
 */
template <>
forceinline simd_trait<double, cyme::neon, 1>::register_type
_mm_select_poly<double, cyme::neon, 1>(simd_trait<int, cyme::neon, 1>::register_type sel,
                                       simd_trait<double, cyme::neon, 1>::register_type xmm0,
                                       simd_trait<double, cyme::neon, 1>::register_type xmm1) {
    int64x2_t mask = vmovq_n_s64(2);
    int64x2_t zero = vmovq_n_s64(0);
    int64x2_t imm0 = vandq_s64((int64x2_t)sel, mask);
    imm0 = (int64x2_t)vceqq_s64(imm0, zero);

    xmm0 = (float64x2_t)vbicq_s64((int64x2_t)xmm0, imm0);
    xmm1 = (float64x2_t)vandq_s64((int64x2_t)xmm1, imm0);
    return vaddq_f64(xmm0, xmm1);
}

/**
  Selects the polynomial for sin function. Inputs are:
    - Selector int
    - Option one
    - Option two
  specialisation double,cyme::neon, 2 reg
 */
template <>
forceinline simd_trait<double, cyme::neon, 2>::register_type
_mm_select_poly<double, cyme::neon, 2>(simd_trait<int, cyme::neon, 2>::register_type sel,
                                       simd_trait<double, cyme::neon, 2>::register_type xmm0,
                                       simd_trait<double, cyme::neon, 2>::register_type xmm1) {
    int64x2_t mask = vmovq_n_s64(2);
    int64x2_t zero = vmovq_n_s64(0);
    int64x2_t imm0_0 = vandq_s64((int64x2_t)sel.r0, mask);
    int64x2_t imm0_1 = vandq_s64((int64x2_t)sel.r1, mask);
    imm0_0 = (int64x2_t)vceqq_s64(imm0_0, zero);
    imm0_1 = (int64x2_t)vceqq_s64(imm0_1, zero);

    xmm0.r0 = (float64x2_t)vbicq_s64((int64x2_t)xmm0.r0, imm0_0);
    xmm0.r1 = (float64x2_t)vbicq_s64((int64x2_t)xmm0.r1, imm0_1);
    xmm1.r0 = (float64x2_t)vandq_s64((int64x2_t)xmm1.r0, imm0_0);
    xmm1.r1 = (float64x2_t)vandq_s64((int64x2_t)xmm1.r1, imm0_1);
    return simd_trait<double, cyme::neon, 2>::register_type(vaddq_f64(xmm0.r0, xmm1.r0), vaddq_f64(xmm0.r1, xmm1.r1));
}

/**
  Selects the polynomial for sin function. Inputs are:
    - Selector int
    - Option one
    - Option two
  specialisation double,cyme::neon, 4 reg
 */
template <>
forceinline simd_trait<double, cyme::neon, 4>::register_type
_mm_select_poly<double, cyme::neon, 4>(simd_trait<int, cyme::neon, 4>::register_type sel,
                                       simd_trait<double, cyme::neon, 4>::register_type xmm0,
                                       simd_trait<double, cyme::neon, 4>::register_type xmm1) {
    int64x2_t mask = vmovq_n_s64(2);
    int64x2_t zero = vmovq_n_s64(0);
    int64x2_t imm0_0 = vandq_s64((int64x2_t)sel.r0, mask);
    int64x2_t imm0_1 = vandq_s64((int64x2_t)sel.r1, mask);
    int64x2_t imm0_2 = vandq_s64((int64x2_t)sel.r2, mask);
    int64x2_t imm0_3 = vandq_s64((int64x2_t)sel.r3, mask);
    imm0_0 = (int64x2_t)vceqq_s64(imm0_0, zero);
    imm0_1 = (int64x2_t)vceqq_s64(imm0_1, zero);
    imm0_2 = (int64x2_t)vceqq_s64(imm0_2, zero);
    imm0_3 = (int64x2_t)vceqq_s64(imm0_3, zero);

    xmm0.r0 = (float64x2_t)vbicq_s64((int64x2_t)xmm0.r0, imm0_0);
    xmm0.r1 = (float64x2_t)vbicq_s64((int64x2_t)xmm0.r1, imm0_1);
    xmm0.r2 = (float64x2_t)vbicq_s64((int64x2_t)xmm0.r2, imm0_2);
    xmm0.r3 = (float64x2_t)vbicq_s64((int64x2_t)xmm0.r3, imm0_3);
    xmm1.r0 = (float64x2_t)vandq_s64((int64x2_t)xmm1.r0, imm0_0);
    xmm1.r1 = (float64x2_t)vandq_s64((int64x2_t)xmm1.r1, imm0_1);
    xmm1.r2 = (float64x2_t)vandq_s64((int64x2_t)xmm1.r2, imm0_2);
    xmm1.r3 = (float64x2_t)vandq_s64((int64x2_t)xmm1.r3, imm0_3);
    return simd_trait<double, cyme::neon, 4>::register_type(vaddq_f64(xmm0.r0, xmm1.r0), vaddq_f64(xmm0.r1, xmm1.r1),
                                                            vaddq_f64(xmm0.r2, xmm1.r2), vaddq_f64(xmm0.r3, xmm1.r3));
}

/**
  Selects the sign (+/-) for sin function. Inputs are:
    - swap int
    - Original input
    - Final calculated sin value
  specialisation double,cyme::neon, 1 reg
 */
template <>
forceinline simd_trait<double, cyme::neon, 1>::register_type
_mm_select_sign_sin<double, cyme::neon, 1>(simd_trait<int, cyme::neon, 1>::register_type swap,
                                           simd_trait<double, cyme::neon, 1>::register_type xmm0,
                                           simd_trait<double, cyme::neon, 1>::register_type xmm1) {
    int64x2_t mask = vmovq_n_s64(0x8000000000000000);
    int64x2_t four = vmovq_n_s64(4);
    /* extract the sign bit (upper one) from original val */
    int64x2_t imm0 = vandq_s64((int64x2_t)xmm0, mask);

    /* get the swap sign flag */
    int64x2_t imm1 = vandq_s64((int64x2_t)swap, four);
    imm1 = vshlq_s64(imm1, vmovq_n_s64(61));

    /* update the sign of the final value*/
    imm0 = veorq_s64(imm0, imm1);
    xmm1 = (float64x2_t)veorq_s64((int64x2_t)xmm1, imm0);
    return xmm1;
}

/**
  Selects the sign (+/-) for sin function. Inputs are:
    - swap int
    - Original input
    - Final calculated sin value
  specialisation double,cyme::neon, 2 reg
 */
template <>
forceinline simd_trait<double, cyme::neon, 2>::register_type
_mm_select_sign_sin<double, cyme::neon, 2>(simd_trait<int, cyme::neon, 2>::register_type swap,
                                           simd_trait<double, cyme::neon, 2>::register_type xmm0,
                                           simd_trait<double, cyme::neon, 2>::register_type xmm1) {
    int64x2_t mask = vmovq_n_s64(0x8000000000000000);
    int64x2_t four = vmovq_n_s64(4);
    /* extract the sign bit (upper one) from original val */
    int64x2_t imm0_0 = vandq_s64((int64x2_t)xmm0.r0, mask);
    int64x2_t imm0_1 = vandq_s64((int64x2_t)xmm0.r1, mask);

    /* get the swap sign flag */
    int64x2_t imm1_0 = vandq_s64((int64x2_t)swap.r0, four);
    int64x2_t imm1_1 = vandq_s64((int64x2_t)swap.r1, four);
    imm1_0 = vshlq_s64(imm1_0, vmovq_n_s64(61));
    imm1_1 = vshlq_s64(imm1_1, vmovq_n_s64(61));

    /* update the sign of the final value*/
    imm0_0 = veorq_s64(imm0_0, imm1_0);
    imm0_1 = veorq_s64(imm0_1, imm1_1);
    xmm1.r0 = (float64x2_t)veorq_s64((int64x2_t)xmm1.r0, imm0_0);
    xmm1.r1 = (float64x2_t)veorq_s64((int64x2_t)xmm1.r1, imm0_1);
    return simd_trait<double, cyme::neon, 2>::register_type(xmm1.r0, xmm1.r1);
}

/**
  Selects the sign (+/-) for sin function. Inputs are:
    - swap int
    - Original input
    - Final calculated sin value
  specialisation double,cyme::neon, 4 reg
 */
template <>
forceinline simd_trait<double, cyme::neon, 4>::register_type
_mm_select_sign_sin<double, cyme::neon, 4>(simd_trait<int, cyme::neon, 4>::register_type swap,
                                           simd_trait<double, cyme::neon, 4>::register_type xmm0,
                                           simd_trait<double, cyme::neon, 4>::register_type xmm1) {
    int64x2_t mask = vmovq_n_s64(0x8000000000000000);
    int64x2_t four = vmovq_n_s64(4);
    /* extract the sign bit (upper one) from original val */
    int64x2_t imm0_0 = vandq_s64((int64x2_t)xmm0.r0, mask);
    int64x2_t imm0_1 = vandq_s64((int64x2_t)xmm0.r1, mask);
    int64x2_t imm0_2 = vandq_s64((int64x2_t)xmm0.r2, mask);
    int64x2_t imm0_3 = vandq_s64((int64x2_t)xmm0.r3, mask);

    /* get the swap sign flag */
    int64x2_t imm1_0 = vandq_s64((int64x2_t)swap.r0, four);
    int64x2_t imm1_1 = vandq_s64((int64x2_t)swap.r1, four);
    int64x2_t imm1_2 = vandq_s64((int64x2_t)swap.r2, four);
    int64x2_t imm1_3 = vandq_s64((int64x2_t)swap.r3, four);
    imm1_0 = vshlq_s64(imm1_0, vmovq_n_s64(61));
    imm1_1 = vshlq_s64(imm1_1, vmovq_n_s64(61));
    imm1_2 = vshlq_s64(imm1_2, vmovq_n_s64(61));
    imm1_3 = vshlq_s64(imm1_3, vmovq_n_s64(61));

    /* update the sign of the final value*/
    imm0_0 = veorq_s64(imm0_0, imm1_0);
    imm0_1 = veorq_s64(imm0_1, imm1_1);
    imm0_2 = veorq_s64(imm0_2, imm1_2);
    imm0_3 = veorq_s64(imm0_3, imm1_3);
    xmm1.r0 = (float64x2_t)veorq_s64((int64x2_t)xmm1.r0, imm0_0);
    xmm1.r1 = (float64x2_t)veorq_s64((int64x2_t)xmm1.r1, imm0_1);
    xmm1.r2 = (float64x2_t)veorq_s64((int64x2_t)xmm1.r2, imm0_2);
    xmm1.r3 = (float64x2_t)veorq_s64((int64x2_t)xmm1.r3, imm0_3);
    return simd_trait<double, cyme::neon, 4>::register_type(xmm1.r0, xmm1.r1, xmm1.r2, xmm1.r3);
}

/**
  Selects the sign (+/-) for cos function. Inputs are:
    - swap int
    - Final calculated cos value
  specialisation double,cyme::neon,1 reg
 */
template <>
forceinline simd_trait<double, cyme::neon, 1>::register_type
_mm_select_sign_cos<double, cyme::neon, 1>(simd_trait<int, cyme::neon, 1>::register_type swap,
                                           simd_trait<double, cyme::neon, 1>::register_type xmm0) {
    int64x2_t four = vmovq_n_s64(4);

    /* get the swap sign flag */
    int64x2_t imm0 = vbicq_s64(four, (int64x2_t)swap);
    imm0 = vshlq_s64(imm0, vmovq_n_s64(61));

    /* update the sign of the final value*/
    xmm0 = (float64x2_t)veorq_s64((int64x2_t)xmm0, imm0);
    return xmm0;
}

/**
  Selects the sign (+/-) for cos function. Inputs are:
    - swap int
    - Final calculated cos value
  specialisation double,cyme::neon,2 reg
 */
template <>
forceinline simd_trait<double, cyme::neon, 2>::register_type
_mm_select_sign_cos<double, cyme::neon, 2>(simd_trait<int, cyme::neon, 2>::register_type swap,
                                           simd_trait<double, cyme::neon, 2>::register_type xmm0) {
    int64x2_t four = vmovq_n_s64(4);

    /* get the swap sign flag */
    int64x2_t imm0_0 = vbicq_s64(four, (int64x2_t)swap.r0);
    int64x2_t imm0_1 = vbicq_s64(four, (int64x2_t)swap.r1);
    imm0_0 = vshlq_s64(imm0_0, vmovq_n_s64(61));
    imm0_1 = vshlq_s64(imm0_1, vmovq_n_s64(61));

    /* update the sign of the final value*/
    xmm0.r0 = (float64x2_t)veorq_s64((int64x2_t)xmm0.r0, imm0_0);
    xmm0.r1 = (float64x2_t)veorq_s64((int64x2_t)xmm0.r1, imm0_1);
    return simd_trait<double, cyme::neon, 2>::register_type(xmm0.r0, xmm0.r1);
}

/**
  Selects the sign (+/-) for cos function. Inputs are:
    - swap int
    - Final calculated cos value
  specialisation double,cyme::neon,4 reg
 */
template <>
forceinline simd_trait<double, cyme::neon, 4>::register_type
_mm_select_sign_cos<double, cyme::neon, 4>(simd_trait<int, cyme::neon, 4>::register_type swap,
                                           simd_trait<double, cyme::neon, 4>::register_type xmm0) {
    int64x2_t four = vmovq_n_s64(4);

    /* get the swap sign flag */
    int64x2_t imm0_0 = vbicq_s64(four, (int64x2_t)swap.r0);
    int64x2_t imm0_1 = vbicq_s64(four, (int64x2_t)swap.r1);
    int64x2_t imm0_2 = vbicq_s64(four, (int64x2_t)swap.r2);
    int64x2_t imm0_3 = vbicq_s64(four, (int64x2_t)swap.r3);
    imm0_0 = vshlq_s64(imm0_0, vmovq_n_s64(61));
    imm0_1 = vshlq_s64(imm0_1, vmovq_n_s64(61));
    imm0_2 = vshlq_s64(imm0_2, vmovq_n_s64(61));
    imm0_3 = vshlq_s64(imm0_3, vmovq_n_s64(61));

    /* update the sign of the final value*/
    xmm0.r0 = (float64x2_t)veorq_s64((int64x2_t)xmm0.r0, imm0_0);
    xmm0.r1 = (float64x2_t)veorq_s64((int64x2_t)xmm0.r1, imm0_1);
    xmm0.r2 = (float64x2_t)veorq_s64((int64x2_t)xmm0.r2, imm0_2);
    xmm0.r3 = (float64x2_t)veorq_s64((int64x2_t)xmm0.r3, imm0_3);
    return simd_trait<double, cyme::neon, 4>::register_type(xmm0.r0, xmm0.r1, xmm0.r2, xmm0.r3);
}

#ifdef __FMA__
/**
  Returns a vector containing the results of performing a fused multiply/add for each corresponding
 set of elements of the given vectors.
 Given arguments a,b, and c,
 result = a*b+c
   specialisation double,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 1>::register_type
_mm_fma<double, cyme::neon, 1>(simd_trait<double, cyme::neon, 1>::register_type xmm0,
                               simd_trait<double, cyme::neon, 1>::register_type xmm1,
                               simd_trait<double, cyme::neon, 1>::register_type xmm2) {
    return vfmaq_f64(xmm2, xmm0, xmm1);
}

/**
  Returns a vector containing the results of performing a fused multiply/add for each corresponding
 set of elements of the given vectors.
 Given arguments a,b, and c,
 result = a*b+c
   specialisation double,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 2>::register_type
_mm_fma<double, cyme::neon, 2>(simd_trait<double, cyme::neon, 2>::register_type xmm0,
                               simd_trait<double, cyme::neon, 2>::register_type xmm1,
                               simd_trait<double, cyme::neon, 2>::register_type xmm2) {
    return simd_trait<double, cyme::neon, 2>::register_type(vfmaq_f64(xmm2.r0, xmm0.r0, xmm1.r0),
                                                            vfmaq_f64(xmm2.r1, xmm0.r1, xmm1.r1));
}

/**
  Returns a vector containing the results of performing a fused multiply/add for each corresponding
 set of elements of the given vectors.
 Given arguments a,b, and c,
 result = a*b+c
   specialisation double,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 4>::register_type
_mm_fma<double, cyme::neon, 4>(simd_trait<double, cyme::neon, 4>::register_type xmm0,
                               simd_trait<double, cyme::neon, 4>::register_type xmm1,
                               simd_trait<double, cyme::neon, 4>::register_type xmm2) {
    return simd_trait<double, cyme::neon, 4>::register_type(
        vfmaq_f64(xmm2.r0, xmm0.r0, xmm1.r0), vfmaq_f64(xmm2.r1, xmm0.r1, xmm1.r1),
        vfmaq_f64(xmm2.r2, xmm0.r2, xmm1.r2), vfmaq_f64(xmm2.r3, xmm0.r3, xmm1.r3));
}

/**
  Returns a vector containing the results of performing a negative multiply-subtract
  operation on the given vectors. Given arguments a, b, and c,
  result = -(a*b-c),
  result = c-a*b.
   specialisation double,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 1>::register_type
_mm_nfma<double, cyme::neon, 1>(simd_trait<double, cyme::neon, 1>::register_type xmm0,
                                simd_trait<double, cyme::neon, 1>::register_type xmm1,
                                simd_trait<double, cyme::neon, 1>::register_type xmm2) {
    return vfmsq_f64(xmm2, xmm0, xmm1);
}

/**
  Returns a vector containing the results of performing a negative multiply-subtract
  operation on the given vectors. Given arguments a, b, and c,
  result = -(a*b-c),
  result = c-a*b.
   specialisation double,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 2>::register_type
_mm_nfma<double, cyme::neon, 2>(simd_trait<double, cyme::neon, 2>::register_type xmm0,
                                simd_trait<double, cyme::neon, 2>::register_type xmm1,
                                simd_trait<double, cyme::neon, 2>::register_type xmm2) {
    return simd_trait<double, cyme::neon, 2>::register_type(vfmsq_f64(xmm2.r0, xmm0.r0, xmm1.r0),
                                                            vfmsq_f64(xmm2.r1, xmm0.r1, xmm1.r1));
}

/**
  Returns a vector containing the results of performing a negative multiply-subtract
  operation on the given vectors. Given arguments a, b, and c,
  result = -(a*b-c),
  result = c-a*b.
   specialisation double,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 4>::register_type
_mm_nfma<double, cyme::neon, 4>(simd_trait<double, cyme::neon, 4>::register_type xmm0,
                                simd_trait<double, cyme::neon, 4>::register_type xmm1,
                                simd_trait<double, cyme::neon, 4>::register_type xmm2) {
    return simd_trait<double, cyme::neon, 4>::register_type(
        vfmsq_f64(xmm2.r0, xmm0.r0, xmm1.r0), vfmsq_f64(xmm2.r1, xmm0.r1, xmm1.r1),
        vfmsq_f64(xmm2.r2, xmm0.r2, xmm1.r2), vfmsq_f64(xmm2.r3, xmm0.r3, xmm1.r3));
}

/**
  Returns a vector containing the results of performing a multiply-substract
  operation on the given vectors. Given arguments a, b, and c,
  result = a*b-c.
   specialisation double,cyme::neon,1 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 1>::register_type
_mm_fms<double, cyme::neon, 1>(simd_trait<double, cyme::neon, 1>::register_type xmm0,
                               simd_trait<double, cyme::neon, 1>::register_type xmm1,
                               simd_trait<double, cyme::neon, 1>::register_type xmm2) {
    float64x2_t temp = vfmsq_f64(xmm2, xmm0, xmm1);
    return vnegq_f64(temp);
}

/**
  Returns a vector containing the results of performing a multiply-substract
  operation on the given vectors. Given arguments a, b, and c,
  result = a*b-c.
   specialisation double,cyme::neon,2 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 2>::register_type
_mm_fms<double, cyme::neon, 2>(simd_trait<double, cyme::neon, 2>::register_type xmm0,
                               simd_trait<double, cyme::neon, 2>::register_type xmm1,
                               simd_trait<double, cyme::neon, 2>::register_type xmm2) {
    float64x2_t temp1 = vfmsq_f64(xmm2.r0, xmm0.r0, xmm1.r0);
    float64x2_t temp2 = vfmsq_f64(xmm2.r1, xmm0.r1, xmm1.r1);
    return simd_trait<double, cyme::neon, 2>::register_type(vnegq_f64(temp1), vnegq_f64(temp2));
}

/**
  Returns a vector containing the results of performing a multiply-substract
  operation on the given vectors. Given arguments a, b, and c,
  result = a*b-c.
   specialisation double,cyme::neon,4 regs
 */
template <>
forceinline simd_trait<double, cyme::neon, 4>::register_type
_mm_fms<double, cyme::neon, 4>(simd_trait<double, cyme::neon, 4>::register_type xmm0,
                               simd_trait<double, cyme::neon, 4>::register_type xmm1,
                               simd_trait<double, cyme::neon, 4>::register_type xmm2) {
    float64x2_t temp1 = vfmsq_f64(xmm2.r0, xmm0.r0, xmm1.r0);
    float64x2_t temp2 = vfmsq_f64(xmm2.r1, xmm0.r1, xmm1.r1);
    float64x2_t temp3 = vfmsq_f64(xmm2.r2, xmm0.r2, xmm1.r2);
    float64x2_t temp4 = vfmsq_f64(xmm2.r3, xmm0.r3, xmm1.r3);
    return simd_trait<double, cyme::neon, 4>::register_type(vnegq_f64(temp1), vnegq_f64(temp2), vnegq_f64(temp3),
                                                            vnegq_f64(temp4));
}

/**
 Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
 Given arguments a,b, and c,
 result = -(a*b+c
   specialisation double,cyme::neon,1 regs
*/
template <>
forceinline simd_trait<double, cyme::neon, 1>::register_type
_mm_nfms<double, cyme::neon, 1>(simd_trait<double, cyme::neon, 1>::register_type xmm0,
                                simd_trait<double, cyme::neon, 1>::register_type xmm1,
                                simd_trait<double, cyme::neon, 1>::register_type xmm2) {
    float64x2_t temp = vfmaq_f64(xmm2, xmm0, xmm1);
    return vnegq_f64(temp);
}

/**
 Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
 Given arguments a,b, and c,
 result = -(a*b+c
   specialisation double,cyme::neon,2 regs
*/
template <>
forceinline simd_trait<double, cyme::neon, 2>::register_type
_mm_nfms<double, cyme::neon, 2>(simd_trait<double, cyme::neon, 2>::register_type xmm0,
                                simd_trait<double, cyme::neon, 2>::register_type xmm1,
                                simd_trait<double, cyme::neon, 2>::register_type xmm2) {
    float64x2_t temp1 = vfmaq_f64(xmm2.r0, xmm0.r0, xmm1.r0);
    float64x2_t temp2 = vfmaq_f64(xmm2.r1, xmm0.r1, xmm1.r1);
    return simd_trait<double, cyme::neon, 2>::register_type(vnegq_f64(temp1), vnegq_f64(temp2));
}

/**
 Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
 Given arguments a,b, and c,
 result = -(a*b+c
   specialisation double,cyme::neon,4 regs
*/
template <>
forceinline simd_trait<double, cyme::neon, 4>::register_type
_mm_nfms<double, cyme::neon, 4>(simd_trait<double, cyme::neon, 4>::register_type xmm0,
                                simd_trait<double, cyme::neon, 4>::register_type xmm1,
                                simd_trait<double, cyme::neon, 4>::register_type xmm2) {
    float64x2_t temp1 = vfmaq_f64(xmm2.r0, xmm0.r0, xmm1.r0);
    float64x2_t temp2 = vfmaq_f64(xmm2.r1, xmm0.r1, xmm1.r1);
    float64x2_t temp3 = vfmaq_f64(xmm2.r2, xmm0.r2, xmm1.r2);
    float64x2_t temp4 = vfmaq_f64(xmm2.r3, xmm0.r3, xmm1.r3);
    return simd_trait<double, cyme::neon, 4>::register_type(vnegq_f64(temp1), vnegq_f64(temp2), vnegq_f64(temp3),
                                                            vnegq_f64(temp4));
}
#endif
} // end namespace

#endif
