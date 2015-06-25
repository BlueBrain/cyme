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

//extern "C" vector float expf4(vector float vx);// link to the fortran one
//extern "C" vector float logf4(vector float vx);// link to the fortran one
//extern "C" vector double expd4(vector double vx);// link to the fortran one
//extern "C" vector double logd4(vector double vx);// link to the fortran one

namespace cyme{
    /**
       Load a single-precision (32-bit) floating-point element from cyme into lower element of dst.
     */
    template<>
    forceinline simd_trait<float,cyme::arm,1>::register_type
    _mm_single_load<float,cyme::arm,1>(const simd_trait<float,cyme::arm,1>::value_type __attribute__((unused))b){
	assert(false);
    }

    /**
       store a single-precision (32-bit) floating-point element from register lower element to cyme.
     */
    template<>
    forceinline simd_trait<float,cyme::arm,1>::value_type
    _mm_single_store<float,cyme::arm,1>(simd_trait<float,cyme::arm,1>::register_type __attribute__((unused))xmm0,
                                        simd_trait<float,cyme::arm,1>::pointer __attribute__((unused))b){
	assert(false);
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation float,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,1>::register_type
    _mm_load1<float,cyme::arm,1>(const simd_trait<float,cyme::arm,1>::value_type __attribute__((unused))&a){
	assert(false);
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation float,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,2>::register_type
    _mm_load1<float,cyme::arm,2>(const simd_trait<float,cyme::arm,2>::value_type __attribute__((unused))&a){
	assert(false);
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation float,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,4>::register_type
    _mm_load1<float,cyme::arm,4>(const simd_trait<float,cyme::arm,4>::value_type __attribute__((unused))&a){
	assert(false);
    }

    /**
      Loads a vector from the given cyme address.
       specialisation float,cyme::arm,1 regs
    */
    template<>
    forceinline simd_trait<float,cyme::arm,1>::register_type
    _mm_load<float,cyme::arm,1>(simd_trait<float,cyme::arm,1>::const_pointer __attribute__((unused))a){
	assert(false);
    }

    /**
      Loads a vector from the given cyme address.
       specialisation float,cyme::arm,2 regs
    */
    template<>
    forceinline simd_trait<float,cyme::arm,2>::register_type
    _mm_load<float,cyme::arm,2>(simd_trait<float,cyme::arm,2>::const_pointer __attribute__((unused))a){
	assert(false);
    }

    /**
      Loads a vector from the given cyme address.
       specialisation float,cyme::arm,4 regs
    */
    template<>
    forceinline simd_trait<float,cyme::arm,4>::register_type
    _mm_load<float,cyme::arm,4>(simd_trait<float,cyme::arm,4>::const_pointer __attribute__((unused))a){
	assert(false);
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation float,cyme::arm,1 regs
    */
    template<>
    forceinline void
    _mm_store<float,cyme::arm,1>(simd_trait<float,cyme::arm,1>::register_type __attribute__((unused))xmm0,
                                 simd_trait<float,cyme::arm,1>::pointer __attribute__((unused))a){
	assert(false);
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation float,cyme::arm,2 regs
    */
    template<>
    forceinline void
    _mm_store<float,cyme::arm,2>(simd_trait<float,cyme::arm,2>::register_type __attribute__((unused))xmm0,
                                 simd_trait<float,cyme::arm,2>::pointer __attribute__((unused))a){
	assert(false);
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation float,cyme::arm,4 regs
    */
    template<>
    forceinline void
    _mm_store<float,cyme::arm,4>(simd_trait<float,cyme::arm,4>::register_type __attribute__((unused))xmm0,
                                 simd_trait<float,cyme::arm,4>::pointer __attribute__((unused))a){
	assert(false);
    }

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation float,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,1>::register_type
    _mm_mul<float,cyme::arm,1>(simd_trait<float,cyme::arm,1>::register_type __attribute__((unused))xmm0,
                               simd_trait<float,cyme::arm,1>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation float,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,2>::register_type
    _mm_mul<float,cyme::arm,2>(simd_trait<float,cyme::arm,2>::register_type __attribute__((unused))xmm0,
                               simd_trait<float,cyme::arm,2>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation float,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,4>::register_type
    _mm_mul<float,cyme::arm,4>(simd_trait<float,cyme::arm,4>::register_type __attribute__((unused))xmm0,
                               simd_trait<float,cyme::arm,4>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
       Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation float,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,1>::register_type
    _mm_div<float,cyme::arm,1>(simd_trait<float,cyme::arm,1>::register_type __attribute__((unused))xmm0,
                               simd_trait<float,cyme::arm,1>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
       Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation float,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,2>::register_type
    _mm_div<float,cyme::arm,2>(simd_trait<float,cyme::arm,2>::register_type __attribute__((unused))xmm0,
                               simd_trait<float,cyme::arm,2>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
       Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation float,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,4>::register_type
    _mm_div<float,cyme::arm,4>(simd_trait<float,cyme::arm,4>::register_type __attribute__((unused))xmm0,
                               simd_trait<float,cyme::arm,4>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation float,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,1>::register_type
    _mm_add<float,cyme::arm,1>(simd_trait<float,cyme::arm,1>::register_type __attribute__((unused))xmm0,
                               simd_trait<float,cyme::arm,1>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation float,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,2>::register_type
    _mm_add<float,cyme::arm,2>(simd_trait<float,cyme::arm,2>::register_type __attribute__((unused))xmm0,
                               simd_trait<float,cyme::arm,2>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation float,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,4>::register_type
    _mm_add<float,cyme::arm,4>(simd_trait<float,cyme::arm,4>::register_type __attribute__((unused))xmm0,
                               simd_trait<float,cyme::arm,4>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Returns a vector containing the result of subtracting each element of b
     from the corresponding element of a.
       specialisation float,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,1>::register_type
    _mm_sub<float,cyme::arm,1>(simd_trait<float,cyme::arm,1>::register_type __attribute__((unused))xmm0,
                               simd_trait<float,cyme::arm,1>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Returns a vector containing the result of subtracting each element of b
     from the corresponding element of a.
       specialisation float,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,2>::register_type
    _mm_sub<float,cyme::arm,2>(simd_trait<float,cyme::arm,2>::register_type __attribute__((unused))xmm0,
                               simd_trait<float,cyme::arm,2>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Returns a vector containing the result of subtracting each element of b
     from the corresponding element of a.
       specialisation float,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,4>::register_type
    _mm_sub<float,cyme::arm,4>(simd_trait<float,cyme::arm,4>::register_type __attribute__((unused))xmm0,
                               simd_trait<float,cyme::arm,4>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation float,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,1>::register_type
    _mm_exp<float,cyme::arm,1>(simd_trait<float,cyme::arm,1>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation float,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,2>::register_type
    _mm_exp<float,cyme::arm,2>(simd_trait<float,cyme::arm,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation float,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,4>::register_type
    _mm_exp<float,cyme::arm,4>(simd_trait<float,cyme::arm,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation float,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,1>::register_type
    _mm_log<float,cyme::arm,1>(simd_trait<float,cyme::arm,1>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation float,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,2>::register_type
    _mm_log<float,cyme::arm,2>(simd_trait<float,cyme::arm,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation float,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,4>::register_type
    _mm_log<float,cyme::arm,4>(simd_trait<float,cyme::arm,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Returns a vector containing estimates of the reciprocals of the corresponding elements of the given vector.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x) / (1/x) | ≤ 1/256
       specialisation float,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,1>::register_type
    _mm_rec<float,cyme::arm,1>(simd_trait<float,cyme::arm,1>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Returns a vector containing estimates of the reciprocals of the corresponding elements of the given vector.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x) / (1/x) | ≤ 1/256
       specialisation float,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,2>::register_type
    _mm_rec<float,cyme::arm,2>(simd_trait<float,cyme::arm,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Returns a vector containing estimates of the reciprocals of the corresponding elements of the given vector.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x) / (1/x) | ≤ 1/256
       specialisation float,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,4>::register_type
    _mm_rec<float,cyme::arm,4>(simd_trait<float,cyme::arm,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Compute 1/recsqrt (32-bit) floating point elements in xmm0 to packed single-precision
     (32-bit) floating-point elements, and store the results in dst.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
       of a and r is the value of the corresponding element of the result value:
     | (r-1/x^0.5) / (1/x^0.5) | ≤ 1/256
       specialisation float,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,1>::register_type
    _mm_rsqrt<float,cyme::arm,1>(simd_trait<float,cyme::arm,1>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Compute 1/recsqrt (32-bit) floating point elements in xmm0 to packed single-precision
     (32-bit) floating-point elements, and store the results in dst.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
       of a and r is the value of the corresponding element of the result value:
     | (r-1/x^0.5) / (1/x^0.5) | ≤ 1/256
       specialisation float,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,2>::register_type
    _mm_rsqrt<float,cyme::arm,2>(simd_trait<float,cyme::arm,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Compute 1/recsqrt (32-bit) floating point elements in xmm0 to packed single-precision
     (32-bit) floating-point elements, and store the results in dst.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
       of a and r is the value of the corresponding element of the result value:
     | (r-1/x^0.5) / (1/x^0.5) | ≤ 1/256
       specialisation float,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,4>::register_type
    _mm_rsqrt<float,cyme::arm,4>(simd_trait<float,cyme::arm,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation float,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,1>::register_type
    _mm_neg<float,cyme::arm,1>(simd_trait<float,cyme::arm,1>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation float,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,2>::register_type
    _mm_neg<float,cyme::arm,2>(simd_trait<float,cyme::arm,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation float,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,4>::register_type
    _mm_neg<float,cyme::arm,4>(simd_trait<float,cyme::arm,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed single-precision (32-bit) floating-point elements,
     and store the results in dst.
       specialisation float,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,1>::register_type
    _mm_cast<float,cyme::arm,1>(simd_trait<int,cyme::arm,1>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed single-precision (32-bit) floating-point elements,
     and store the results in dst.
       specialisation float,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,2>::register_type
    _mm_cast<float,cyme::arm,2>(simd_trait<int,cyme::arm,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed single-precision (32-bit) floating-point elements,
     and store the results in dst.
       specialisation float,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,4>::register_type
    _mm_cast<float,cyme::arm,4>(simd_trait<int,cyme::arm,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Returns a vector containing the largest representable floating-point integral
     values less than or equal to the values of the corresponding elements of the given vector.
       specialisation float,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<int,cyme::arm,1>::register_type
    _mm_floor<float,cyme::arm,1>(simd_trait<float,cyme::arm,1>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Returns a vector containing the largest representable floating-point integral
     values less than or equal to the values of the corresponding elements of the given vector.
       specialisation float,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<int,cyme::arm,2>::register_type
    _mm_floor<float,cyme::arm,2>(simd_trait<float,cyme::arm,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Returns a vector containing the largest representable floating-point integral
     values less than or equal to the values of the corresponding elements of the given vector.
       specialisation float,cyme::arm,4 regs
     */

    template<>
    forceinline simd_trait<int,cyme::arm,4>::register_type
    _mm_floor<float,cyme::arm,4>(simd_trait<float,cyme::arm,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer
       specialisation float,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,1>::register_type
    _mm_twok<float,cyme::arm,1>(simd_trait<int,cyme::arm,1>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer
       specialisation float,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,2>::register_type
    _mm_twok<float,cyme::arm,2>(simd_trait<int,cyme::arm,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer
       specialisation float,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,4>::register_type
    _mm_twok<float,cyme::arm,4>(simd_trait<int,cyme::arm,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Extract the exponent of floating-point exponent (32-bit) elements and store the results in dst.
       specialisation float,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,1>::register_type
    _mm_ge<float,cyme::arm,1>(simd_trait<float,cyme::arm,1>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Extract the exponent of floating-point exponent (32-bit) elements and store the results in dst.
       specialisation float,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,2>::register_type
    _mm_ge<float,cyme::arm,2>(simd_trait<float,cyme::arm,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Extract the exponent of floating-point exponent (32-bit) elements and store the results in dst.
       specialisation float,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,4>::register_type
    _mm_ge<float,cyme::arm,4>(simd_trait<float,cyme::arm,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Extract the fraction of floating-point exponent (32-bit) elements and store the results in dst.
       specialisation float,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,1>::register_type
    _mm_gf<float,cyme::arm,1>(simd_trait<float,cyme::arm,1>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Extract the fraction of floating-point exponent (32-bit) elements and store the results in dst.
       specialisation float,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,2>::register_type
    _mm_gf<float,cyme::arm,2>(simd_trait<float,cyme::arm,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Extract the fraction of floating-point exponent (32-bit) elements and store the results in dst.
       specialisation float,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,4>::register_type
    _mm_gf<float,cyme::arm,4>(simd_trait<float,cyme::arm,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

#ifdef __FMA__
    /**
      Returns a vector containing the results of performing a fused multiply/add
     for each corresponding of a set of elements of the given vectors.
       specialisation float,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,1>::register_type
    _mm_fma<float,cyme::arm,1>(simd_trait<float,cyme::arm,1>::register_type __attribute__((unused))xmm0,
                               simd_trait<float,cyme::arm,1>::register_type __attribute__((unused))xmm1,
                               simd_trait<float,cyme::arm,1>::register_type __attribute__((unused))xmm2){
	assert(false);
    }

    /**
      Returns a vector containing the results of performing a fused multiply/add
     for each corresponding of a set of elements of the given vectors.
       specialisation float,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,2>::register_type
    _mm_fma<float,cyme::arm,2>(simd_trait<float,cyme::arm,2>::register_type __attribute__((unused))xmm0,
                               simd_trait<float,cyme::arm,2>::register_type __attribute__((unused))xmm1,
                               simd_trait<float,cyme::arm,2>::register_type __attribute__((unused))xmm2){
	assert(false);
    }

    /**
      Returns a vector containing the results of performing a fused multiply/add
     for each corresponding of a set of elements of the given vectors.
       specialisation float,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,4>::register_type
    _mm_fma<float,cyme::arm,4>(simd_trait<float,cyme::arm,4>::register_type __attribute__((unused))xmm0,
                               simd_trait<float,cyme::arm,4>::register_type __attribute__((unused))xmm1,
                               simd_trait<float,cyme::arm,4>::register_type __attribute__((unused))xmm2){
	assert(false);
    }

    /**
      Returns a vector containing the results of performing a negative
      multiply-subtract operation on the given vectors.
       specialisation float,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,1>::register_type
    _mm_nfma<float,cyme::arm,1>(simd_trait<float,cyme::arm,1>::register_type __attribute__((unused))xmm0,
                                simd_trait<float,cyme::arm,1>::register_type __attribute__((unused))xmm1,
                                simd_trait<float,cyme::arm,1>::register_type __attribute__((unused))xmm2){
	assert(false);
    }

    /**
      Returns a vector containing the results of performing a negative
      multiply-subtract operation on the given vectors.
       specialisation float,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,2>::register_type
    _mm_nfma<float,cyme::arm,2>(simd_trait<float,cyme::arm,2>::register_type __attribute__((unused))xmm0,
                                simd_trait<float,cyme::arm,2>::register_type __attribute__((unused))xmm1,
                                simd_trait<float,cyme::arm,2>::register_type __attribute__((unused))xmm2){
	assert(false);
    }

    /**
      Returns a vector containing the results of performing a negative
      multiply-subtract operation on the given vectors.
       specialisation float,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,4>::register_type
    _mm_nfma<float,cyme::arm,4>(simd_trait<float,cyme::arm,4>::register_type __attribute__((unused))xmm0,
                                simd_trait<float,cyme::arm,4>::register_type __attribute__((unused))xmm1,
                                simd_trait<float,cyme::arm,4>::register_type __attribute__((unused))xmm2){
	assert(false);
    }

    /**
      Returns a vector containing the results of performing a multiply-substract
      operation using the given vectors.
       specialisation float,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,1>::register_type
    _mm_fms<float,cyme::arm,1>(simd_trait<float,cyme::arm,1>::register_type __attribute__((unused))xmm0,
                               simd_trait<float,cyme::arm,1>::register_type__attribute__((unused)) xmm1,
                               simd_trait<float,cyme::arm,1>::register_type __attribute__((unused))xmm2){
	assert(false);
    }

    /**
      Returns a vector containing the results of performing a multiply-substract
      operation using the given vectors.
       specialisation float,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,2>::register_type
    _mm_fms<float,cyme::arm,2>(simd_trait<float,cyme::arm,2>::register_type __attribute__((unused))xmm0,
                               simd_trait<float,cyme::arm,2>::register_type __attribute__((unused))xmm1,
                               simd_trait<float,cyme::arm,2>::register_type __attribute__((unused))xmm2){
	assert(false);
    }

    /**
      Returns a vector containing the results of performing a multiply-substract
      operation using the given vectors.
       specialisation float,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::arm,4>::register_type
    _mm_fms<float,cyme::arm,4>(simd_trait<float,cyme::arm,4>::register_type __attribute__((unused))xmm0,
                               simd_trait<float,cyme::arm,4>::register_type __attribute__((unused))xmm1,
                               simd_trait<float,cyme::arm,4>::register_type __attribute__((unused))xmm2){
	assert(false);
    }

    /**
     Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
       specialisation float,cyme::arm,1 regs
    */
    template<>
    forceinline simd_trait<float,cyme::arm,1>::register_type
    _mm_nfms<float,cyme::arm,1>(simd_trait<float,cyme::arm,1>::register_type __attribute__((unused))xmm0,
                                simd_trait<float,cyme::arm,1>::register_type __attribute__((unused))xmm1,
                                simd_trait<float,cyme::arm,1>::register_type __attribute__((unused))xmm2){
	assert(false);
    }

    /**
     Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
       specialisation float,cyme::arm,2 regs
    */
    template<>
    forceinline simd_trait<float,cyme::arm,2>::register_type
    _mm_nfms<float,cyme::arm,2>(simd_trait<float,cyme::arm,2>::register_type __attribute__((unused))xmm0,
                                simd_trait<float,cyme::arm,2>::register_type __attribute__((unused))xmm1,
                                simd_trait<float,cyme::arm,2>::register_type __attribute__((unused))xmm2){
	assert(false);
    }

    /**
     Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
       specialisation float,cyme::arm,4 regs
    */
    template<>
    forceinline simd_trait<float,cyme::arm,4>::register_type
    _mm_nfms<float,cyme::arm,4>(simd_trait<float,cyme::arm,4>::register_type __attribute__((unused))xmm0,
                                simd_trait<float,cyme::arm,4>::register_type __attribute__((unused))xmm1,
                                simd_trait<float,cyme::arm,4>::register_type __attribute__((unused))xmm2){
	assert(false);
    }
#endif
/*--------------------------------------------------------------------- double ---------------*/
    /**
       Single load a double-precision (64-bit) floating-point element from cyme into lower element of dst.
     */
    template<>
    forceinline simd_trait<double,cyme::arm,1>::register_type
    _mm_single_load<double,cyme::arm,1>(const simd_trait<double,cyme::arm,1>::value_type __attribute__((unused))b){
	assert(false);
    }

    /**
       Single store a double-precision (64-bit) floating-point element from register lower element to cyme.
     */
    template<>
    forceinline simd_trait<double,cyme::arm,1>::value_type
    _mm_single_store<double,cyme::arm,1>(simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm0,
                                           simd_trait<double,cyme::arm,1>::pointer __attribute__((unused))b){
	assert(false);
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation double,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,1>::register_type
    _mm_load1<double,cyme::arm,1>(const simd_trait<double,cyme::arm,1>::value_type __attribute__((unused))&a){
	assert(false);
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation double,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,2>::register_type
    _mm_load1<double,cyme::arm,2>(const simd_trait<double,cyme::arm,2>::value_type __attribute__((unused))&a){
	assert(false);
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation double,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,4>::register_type
    _mm_load1<double,cyme::arm,4>(const simd_trait<double,cyme::arm,4>::value_type __attribute__((unused))&a){
	assert(false);
    }

    /**
      Loads a vector from the given cyme address.
       specialisation double,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,1>::register_type
    _mm_load<double,cyme::arm,1>(simd_trait<double,cyme::arm,1>::const_pointer __attribute__((unused))a){
	assert(false);
    }

    /**
      Loads a vector from the given cyme address.
       specialisation double,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,2>::register_type
    _mm_load<double,cyme::arm,2>(simd_trait<double,cyme::arm,2>::const_pointer __attribute__((unused))a){
	assert(false);
    }

    /**
      Loads a vector from the given cyme address.
       specialisation double,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,4>::register_type
    _mm_load<double,cyme::arm,4>(simd_trait<double,cyme::arm,4>::const_pointer __attribute__((unused))a){
	assert(false);
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation double,cyme::arm,1 regs
     */
    template<>
    forceinline void
    _mm_store<double,cyme::arm,1>(simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm0,
                                  simd_trait<double,cyme::arm,1>::pointer __attribute__((unused))a){
	assert(false);
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation double,cyme::arm,2 regs
     */
    template<>
    forceinline void
    _mm_store<double,cyme::arm,2>(simd_trait<double,cyme::arm,2>::register_type __attribute__((unused))xmm0,
                                  simd_trait<double,cyme::arm,2>::pointer __attribute__((unused))a){
	assert(false);
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation double,cyme::arm,4 regs
     */
    template<>
    forceinline void
    _mm_store<double,cyme::arm,4>(simd_trait<double,cyme::arm,4>::register_type __attribute__((unused))xmm0,
                                  simd_trait<double,cyme::arm,4>::pointer __attribute__((unused))a){
	assert(false);
    }

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation double,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,1>::register_type
    _mm_mul<double,cyme::arm,1>(simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm0,
                                simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation double,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,2>::register_type
    _mm_mul<double,cyme::arm,2>(simd_trait<double,cyme::arm,2>::register_type __attribute__((unused))xmm0,
                                simd_trait<double,cyme::arm,2>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation double,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,4>::register_type
    _mm_mul<double,cyme::arm,4>(simd_trait<double,cyme::arm,4>::register_type __attribute__((unused))xmm0,
                                simd_trait<double,cyme::arm,4>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation double,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,1>::register_type
    _mm_div<double,cyme::arm,1>(simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm0,
                                simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation double,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,2>::register_type
    _mm_div<double,cyme::arm,2>(simd_trait<double,cyme::arm,2>::register_type __attribute__((unused))xmm0,
                                simd_trait<double,cyme::arm,2>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation double,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,4>::register_type
    _mm_div<double,cyme::arm,4>(simd_trait<double,cyme::arm,4>::register_type __attribute__((unused))xmm0,
	assert(false);
    }

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation double,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,1>::register_type
    _mm_add<double,cyme::arm,1>(simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm0,
                                simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation double,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,2>::register_type
    _mm_add<double,cyme::arm,2>(simd_trait<double,cyme::arm,2>::register_type __attribute__((unused))xmm0,
                                simd_trait<double,cyme::arm,2>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation double,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,4>::register_type
    _mm_add<double,cyme::arm,4>(simd_trait<double,cyme::arm,4>::register_type __attribute__((unused))xmm0,
                                simd_trait<double,cyme::arm,4>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Returns a vector containing the result of subtracting each element of b from the corresponding element of a.
       specialisation double,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,1>::register_type
    _mm_sub<double,cyme::arm,1>(simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm0,
                                simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Returns a vector containing the result of subtracting each element of b from the corresponding element of a.
       specialisation double,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,2>::register_type
    _mm_sub<double,cyme::arm,2>(simd_trait<double,cyme::arm,2>::register_type __attribute__((unused))xmm0,
                                simd_trait<double,cyme::arm,2>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Returns a vector containing the result of subtracting each element of b from the corresponding element of a.
       specialisation double,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,4>::register_type
    _mm_sub<double,cyme::arm,4>(simd_trait<double,cyme::arm,4>::register_type __attribute__((unused))xmm0,
                                simd_trait<double,cyme::arm,4>::register_type __attribute__((unused))xmm1){
	assert(false);
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation double,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,1>::register_type
    _mm_exp<double,cyme::arm,1>(simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation double,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,2>::register_type
    _mm_exp<double,cyme::arm,2>(simd_trait<double,cyme::arm,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation double,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,4>::register_type
    _mm_exp<double,cyme::arm,4>(simd_trait<double,cyme::arm,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation double,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,1>::register_type
    _mm_log<double,cyme::arm,1>(simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation double,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,2>::register_type
    _mm_log<double,cyme::arm,2>(simd_trait<double,cyme::arm,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation double,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,4>::register_type
    _mm_log<double,cyme::arm,4>(simd_trait<double,cyme::arm,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Returns a vector containing estimates of the reciprocals of the corresponding elements of the given vector.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x) / (1/x) | ≤ 1/256
       specialisation double,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,1>::register_type
    _mm_rec<double,cyme::arm,1>(simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Returns a vector containing estimates of the reciprocals of the corresponding elements of the given vector.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x) / (1/x) | ≤ 1/256
       specialisation double,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,2>::register_type
    _mm_rec<double,cyme::arm,2>(simd_trait<double,cyme::arm,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Returns a vector containing estimates of the reciprocals of the corresponding elements of the given vector.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x) / (1/x) | ≤ 1/256
       specialisation double,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,4>::register_type
    _mm_rec<double,cyme::arm,4>(simd_trait<double,cyme::arm,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Compute 1/recsqrt (64-bit) floating point elements in xmm0 to packed double-precision (64-bit)
     floating-point elements, and store the results in dst.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x^0,5) / (1/x^0.5) | ≤ 1/256
       specialisation double,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,1>::register_type
    _mm_rsqrt<double,cyme::arm,1>(simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Compute 1/recsqrt (64-bit) floating point elements in xmm0 to packed double-precision (64-bit)
     floating-point elements, and store the results in dst.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x^0,5) / (1/x^0.5) | ≤ 1/256
       specialisation double,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,2>::register_type
    _mm_rsqrt<double,cyme::arm,2>(simd_trait<double,cyme::arm,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Compute 1/recsqrt (64-bit) floating point elements in xmm0 to packed double-precision (64-bit)
     floating-point elements, and store the results in dst.
     \warning The precision guarantee is specified by the following expression, where x is the value of each element
     of a and r is the value of the corresponding element of the result value:
     | (r-1/x^0,5) / (1/x^0.5) | ≤ 1/256
       specialisation double,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,4>::register_type
    _mm_rsqrt<double,cyme::arm,4>(simd_trait<double,cyme::arm,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }


    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation double,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,1>::register_type
    _mm_neg<double,cyme::arm,1>(simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm0){
	assert(false);
}

    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation double,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,2>::register_type
    _mm_neg<double,cyme::arm,2>(simd_trait<double,cyme::arm,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation double,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,4>::register_type
    _mm_neg<double,cyme::arm,4>(simd_trait<double,cyme::arm,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation double,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,1>::register_type
    _mm_cast<double,cyme::arm,1>(simd_trait<int,cyme::arm,1>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation double,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,2>::register_type
    _mm_cast<double,cyme::arm,2>(simd_trait<int,cyme::arm,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation double,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,4>::register_type
    _mm_cast<double,cyme::arm,4>(simd_trait<int,cyme::arm,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Returns a vector containing the largest representable floating-point integral values less than or equal
     to the values of the corresponding elements of the given vector.
       specialisation double,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<int,cyme::arm,1>::register_type
    _mm_floor<double,cyme::arm,1>(simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Returns a vector containing the largest representable floating-point integral values less than or equal
     to the values of the corresponding elements of the given vector.
       specialisation double,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<int,cyme::arm,2>::register_type
    _mm_floor<double,cyme::arm,2>(simd_trait<double,cyme::arm,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Returns a vector containing the largest representable floating-point integral values less than or equal
     to the values of the corresponding elements of the given vector.
       specialisation double,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<int,cyme::arm,4>::register_type
    _mm_floor<double,cyme::arm,4>(simd_trait<double,cyme::arm,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer, because there is no builtin function
      for 2^k in double, the computation is done using a C trick.
       specialisation double,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,1>::register_type
    _mm_twok<double,cyme::arm,1>(simd_trait<int,cyme::arm,1>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer, because there is no builtin function
      for 2^k in double, the computation is done using a C trick.
       specialisation double,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,2>::register_type
    _mm_twok<double,cyme::arm,2>(simd_trait<int,cyme::arm,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer, because there is no builtin function
      for 2^k in double, the computation is done using a C trick.
       specialisation double,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,4>::register_type
    _mm_twok<double,cyme::arm,4>(simd_trait<int,cyme::arm,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

   /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
      Because we are casting from vector2double -> vector4int, must use specific mask and tmp_sub vectors.
       specialisation double,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,1>::register_type
    _mm_ge<double,cyme::arm,1>(simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

   /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
      Because we are casting from vector2double -> vector4int, must use specific mask and tmp_sub vectors.
       specialisation double,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,2>::register_type
    _mm_ge<double,cyme::arm,2>(simd_trait<double,cyme::arm,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

   /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
      Because we are casting from vector2double -> vector4int, must use specific mask and tmp_sub vectors.
       specialisation double,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,4>::register_type
    _mm_ge<double,cyme::arm,4>(simd_trait<double,cyme::arm,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
      Because we are casting from vector2double -> vector4int, must use specific mask and tmp_add vectors.
       specialisation double,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,1>::register_type
    _mm_gf<double,cyme::arm,1>(simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
      Because we are casting from vector2double -> vector4int, must use specific mask and tmp_add vectors.
       specialisation double,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,2>::register_type
    _mm_gf<double,cyme::arm,2>(simd_trait<double,cyme::arm,2>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
      Because we are casting from vector2double -> vector4int, must use specific mask and tmp_add vectors.
       specialisation double,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,4>::register_type
    _mm_gf<double,cyme::arm,4>(simd_trait<double,cyme::arm,4>::register_type __attribute__((unused))xmm0){
	assert(false);
    }

#ifdef __FMA__
    /**
      Returns a vector containing the results of performing a fused multiply/add for each corresponding
     set of elements of the given vectors.
       specialisation double,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,1>::register_type
    _mm_fma<double,cyme::arm,1>(simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm0,
                                simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm1,
                                simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm2){
	assert(false);
    }

    /**
      Returns a vector containing the results of performing a fused multiply/add for each corresponding
     set of elements of the given vectors.
       specialisation double,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,2>::register_type
    _mm_fma<double,cyme::arm,2>(simd_trait<double,cyme::arm,2>::register_type __attribute__((unused))xmm0,
                                simd_trait<double,cyme::arm,2>::register_type __attribute__((unused))xmm1,
                                simd_trait<double,cyme::arm,2>::register_type __attribute__((unused))xmm2){
	assert(false);
    }

    /**
      Returns a vector containing the results of performing a fused multiply/add for each corresponding
     set of elements of the given vectors.
       specialisation double,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,4>::register_type
    _mm_fma<double,cyme::arm,4>(simd_trait<double,cyme::arm,4>::register_type __attribute__((unused))xmm0,
                                simd_trait<double,cyme::arm,4>::register_type __attribute__((unused))xmm1,
                                simd_trait<double,cyme::arm,4>::register_type __attribute__((unused))xmm2){
	assert(false);
    }

    /**
      Returns a vector containing the results of performing a negative multiply-subtract
     operation on the given vectors.
       specialisation double,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,1>::register_type
    _mm_nfma<double,cyme::arm,1>(simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm0,
                                 simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm1,
                                 simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm2){
	assert(false);
    }

    /**
      Returns a vector containing the results of performing a negative multiply-subtract
     operation on the given vectors.
       specialisation double,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,2>::register_type
    _mm_nfma<double,cyme::arm,2>(simd_trait<double,cyme::arm,2>::register_type __attribute__((unused))xmm0,
                                 simd_trait<double,cyme::arm,2>::register_type __attribute__((unused))xmm1,
                                 simd_trait<double,cyme::arm,2>::register_type __attribute__((unused))xmm2){
	assert(false);
    }

    /**
      Returns a vector containing the results of performing a negative multiply-subtract
     operation on the given vectors.
       specialisation double,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,4>::register_type
    _mm_nfma<double,cyme::arm,4>(simd_trait<double,cyme::arm,4>::register_type __attribute__((unused))xmm0,
                                 simd_trait<double,cyme::arm,4>::register_type __attribute__((unused))xmm1,
                                 simd_trait<double,cyme::arm,4>::register_type __attribute__((unused))xmm2){
	assert(false);
    }

    /**
      Returns a vector containing the results of performing a multiply-substract operation using the given vectors.
       specialisation double,cyme::arm,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,1>::register_type
    _mm_fms<double,cyme::arm,1>(simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm0,
                                simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm1,
                                simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm2){
	assert(false);
    }

    /**
      Returns a vector containing the results of performing a multiply-substract operation using the given vectors.
       specialisation double,cyme::arm,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,2>::register_type
    _mm_fms<double,cyme::arm,2>(simd_trait<double,cyme::arm,2>::register_type __attribute__((unused))xmm0,
                                simd_trait<double,cyme::arm,2>::register_type __attribute__((unused))xmm1,
                                simd_trait<double,cyme::arm,2>::register_type __attribute__((unused))xmm2){
	assert(false);
    }

    /**
      Returns a vector containing the results of performing a multiply-substract operation using the given vectors.
       specialisation double,cyme::arm,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::arm,4>::register_type
    _mm_fms<double,cyme::arm,4>(simd_trait<double,cyme::arm,4>::register_type __attribute__((unused))xmm0,
                                simd_trait<double,cyme::arm,4>::register_type __attribute__((unused))xmm1,
                                simd_trait<double,cyme::arm,4>::register_type __attribute__((unused))xmm2){
	assert(false);
    }

    /**
     Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
       specialisation double,cyme::arm,1 regs
    */
    template<>
    forceinline simd_trait<double,cyme::arm,1>::register_type
    _mm_nfms<double,cyme::arm,1>(simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm0,
                                 simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm1,
                                 simd_trait<double,cyme::arm,1>::register_type __attribute__((unused))xmm2){
	assert(false);
    }

    /**
     Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
       specialisation double,cyme::arm,2 regs
    */
    template<>
    forceinline simd_trait<double,cyme::arm,2>::register_type
    _mm_nfms<double,cyme::arm,2>(simd_trait<double,cyme::arm,2>::register_type __attribute__((unused))xmm0,
                                 simd_trait<double,cyme::arm,2>::register_type __attribute__((unused))xmm1,
                                 simd_trait<double,cyme::arm,2>::register_type __attribute__((unused))xmm2){
	assert(false);
    }

    /**
     Returns a vector containing the results of performing a negative multiply-sum operation on the given vectors.
       specialisation double,cyme::arm,4 regs
    */
    template<>
    forceinline simd_trait<double,cyme::arm,4>::register_type
    _mm_nfms<double,cyme::arm,4>(simd_trait<double,cyme::arm,4>::register_type __attribute__((unused))xmm0,
                                 simd_trait<double,cyme::arm,4>::register_type __attribute__((unused))xmm1,
                                 simd_trait<double,cyme::arm,4>::register_type __attribute__((unused))xmm2){
	assert(false);
    }
#endif
} //end namespace

#endif
