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
        assert(false);
    }

    /**
       store a double-precision (32-bit) floating-point element from register lower element to cyme.
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::value_type
    _mm_single_store<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0,
                                        simd_trait<float,cyme::vmx,1>::pointer b){
        assert(false);
    }


    /**
      Returns a vector of which the value of each element is set to a.
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_load1<float,cyme::vmx,1>(const simd_trait<float,cyme::vmx,1>::value_type& a){
        assert(false);
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_load1<float,cyme::vmx,2>(const simd_trait<float,cyme::vmx,2>::value_type& a){
        assert(false);
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_load1<float,cyme::vmx,4>(const simd_trait<float,cyme::vmx,4>::value_type& a){
        assert(false);
    }

    /**
      Loads a vector from the given cyme address.
       specialisation float,cyme::vmx,1 regs
    */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_load<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::const_pointer a){
        assert(false);
    }

    /**
      Loads a vector from the given cyme address.
       specialisation float,cyme::vmx,2 regs
    */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_load<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::const_pointer a){
        assert(false);
    }

    /**
      Loads a vector from the given cyme address.
       specialisation float,cyme::vmx,4 regs
    */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_load<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::const_pointer a){
        assert(false);
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation float,cyme::vmx,1 regs
    */
    template<>
    forceinline void
    _mm_store<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0,
                                 simd_trait<float,cyme::vmx,1>::pointer a){
        assert(false);
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation float,cyme::vmx,2 regs
    */
    template<>
    forceinline void
    _mm_store<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0,
                                 simd_trait<float,cyme::vmx,2>::pointer a){
        assert(false);
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation float,cyme::vmx,4 regs
    */
    template<>
    forceinline void
    _mm_store<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0,
                                 simd_trait<float,cyme::vmx,4>::pointer a){
        assert(false);
    }

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_mul<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0,
                               simd_trait<float,cyme::vmx,1>::register_type xmm1){
        assert(false);
    }

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_mul<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0,
                               simd_trait<float,cyme::vmx,2>::register_type xmm1){
        assert(false);
    }

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_mul<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0,
                               simd_trait<float,cyme::vmx,4>::register_type xmm1){
        assert(false);
    }

    /**
       Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_div<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0,
                               simd_trait<float,cyme::vmx,1>::register_type xmm1){
        assert(false);
    }

    /**
       Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_div<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0,
                               simd_trait<float,cyme::vmx,2>::register_type xmm1){
        assert(false);
    }

    /**
       Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_div<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0,
                               simd_trait<float,cyme::vmx,4>::register_type xmm1){
        assert(false);
    }

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_add<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0,
                               simd_trait<float,cyme::vmx,1>::register_type xmm1){
        assert(false);
    }

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_add<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0,
                               simd_trait<float,cyme::vmx,2>::register_type xmm1){
        assert(false);
    }

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_add<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0,
                               simd_trait<float,cyme::vmx,4>::register_type xmm1){
        assert(false);
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
        assert(false);
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
        assert(false);
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
        assert(false);
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_exp<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0){
        assert(false);
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_exp<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0){
        assert(false);
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_exp<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0){
        assert(false);
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_log<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0){
        assert(false);
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_log<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0){
        assert(false);
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_log<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0){
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
        assert(false);
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
         assert(false);
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
         assert(false);
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
    forceinline  simd_trait<float,cyme::vmx,1>::register_type
    _mm_rsqrt<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0){
        assert(false);
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
    forceinline  simd_trait<float,cyme::vmx,2>::register_type
    _mm_rsqrt<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0){
        assert(false);
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
    forceinline  simd_trait<float,cyme::vmx,4>::register_type
    _mm_rsqrt<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0){
        assert(false);
    }

    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_neg<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0){
        assert(false);
    };

    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_neg<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0){
         assert(false);
    };

    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_neg<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0){
         assert(false);
    };

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::vmx,1>::register_type
    _mm_cast<float,cyme::vmx,1>(simd_trait<int,cyme::vmx,1>::register_type xmm0){
        assert(false);
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::vmx,2>::register_type
    _mm_cast<float,cyme::vmx,2>(simd_trait<int,cyme::vmx,2>::register_type xmm0){
        assert(false);
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::vmx,4>::register_type
    _mm_cast<float,cyme::vmx,4>(simd_trait<int,cyme::vmx,4>::register_type xmm0){
        assert(false);
    }

    /**
      Returns a vector containing the largest representable floating-point integral
     values less than or equal to the values of the corresponding elements of the given vector.
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_floor<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0){
        assert(false);
    }

    /**
      Returns a vector containing the largest representable floating-point integral
     values less than or equal to the values of the corresponding elements of the given vector.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,2>::register_type
    _mm_floor<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0){
         assert(false);
    };

    /**
      Returns a vector containing the largest representable floating-point integral
     values less than or equal to the values of the corresponding elements of the given vector.
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,4>::register_type
    _mm_floor<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0){
         assert(false);
    };

    /**
      Returns a vector containing 2^k where k is a vector of integer, as the BG/Q does not
     support vmx integer the computation is done serialy using C trick
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::vmx,1>::register_type
    _mm_twok<float,cyme::vmx,1>(simd_trait<int,cyme::vmx,1>::register_type xmm0){
        assert(false);
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer, as the BG/Q does not
     support vmx integer the computation is done serialy using C trick
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::vmx,2>::register_type
    _mm_twok<float,cyme::vmx,2>(simd_trait<int,cyme::vmx,2>::register_type xmm0){
        assert(false);
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer, as the BG/Q does not
     support vmx integer the computation is done serialy using C trick
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::vmx,4>::register_type
    _mm_twok<float,cyme::vmx,4>(simd_trait<int,cyme::vmx,4>::register_type xmm0){
        assert(false);
    }

    /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
      arithmetic are very badly supported with AVX, I am presently glue I so do the compuation in SSE;
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::vmx,1>::register_type
    _mm_ge<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0){
        assert(false);
    }

    /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
      arithmetic are very badly supported with AVX, I am presently glue I so do the compuation in SSE;
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::vmx,2>::register_type
    _mm_ge<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0){
        assert(false);
    }

    /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
      arithmetic are very badly supported with AVX, I am presently glue I so do the compuation in SSE;
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::vmx,4>::register_type
    _mm_ge<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0){
        assert(false);
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
       specialisation float,cyme::vmx,1 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::vmx,1>::register_type
    _mm_gf<float,cyme::vmx,1>(simd_trait<float,cyme::vmx,1>::register_type xmm0){
        assert(false);
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
       specialisation float,cyme::vmx,2 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::vmx,2>::register_type
    _mm_gf<float,cyme::vmx,2>(simd_trait<float,cyme::vmx,2>::register_type xmm0){
        assert(false);
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
       specialisation float,cyme::vmx,4 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::vmx,4>::register_type
    _mm_gf<float,cyme::vmx,4>(simd_trait<float,cyme::vmx,4>::register_type xmm0){
        assert(false);
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
        assert(false);
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
         assert(false);
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
         assert(false);
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
        assert(false);
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
         assert(false);
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
         assert(false);
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
        assert(false);
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
         assert(false);
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
         assert(false);
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
        assert(false);
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
         assert(false);
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
         assert(false);
    }
#endif
/*--------------------------------------------------------------------- double ---------------*/
    /**
       Single load a double-precision (64-bit) floating-point element from cyme into lower element of dst.
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_single_load<double,cyme::vmx,1>(const simd_trait<double,cyme::vmx,1>::value_type b){
        assert(false);
    }

    /**
       Single store a double-precision (64-bit) floating-point element from register lower element to cyme.
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::value_type
    _mm_single_store<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0,
                                           simd_trait<double,cyme::vmx,1>::pointer b){
        assert(false);
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_load1<double,cyme::vmx,1>(const simd_trait<double,cyme::vmx,1>::value_type& a){
        assert(false);
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_load1<double,cyme::vmx,2>(const simd_trait<double,cyme::vmx,2>::value_type& a){
        assert(false);
    }

    /**
      Returns a vector of which the value of each element is set to a.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_load1<double,cyme::vmx,4>(const simd_trait<double,cyme::vmx,4>::value_type& a){
        assert(false);
    }

    /**
      Loads a vector from the given cyme address.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_load<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::const_pointer a){
        assert(false);
    }

    /**
      Loads a vector from the given cyme address.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_load<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::const_pointer a){
        assert(false);
    }

    /**
      Loads a vector from the given cyme address.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_load<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::const_pointer a){
        assert(false);
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline void
    _mm_store<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0,
                                  simd_trait<double,cyme::vmx,1>::pointer a){
        assert(false);
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline void
    _mm_store<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0,
                                  simd_trait<double,cyme::vmx,2>::pointer a){
        assert(false);
    }

    /**
      Stores a vector to cyme at the given address.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline void
    _mm_store<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0,
                                  simd_trait<double,cyme::vmx,4>::pointer a){
        assert(false);
    }

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_mul<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0,
                                simd_trait<double,cyme::vmx,1>::register_type xmm1){
        assert(false);
    }

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_mul<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0,
                                simd_trait<double,cyme::vmx,2>::register_type xmm1){
         assert(false);
    }

    /**
      Returns a vector containing the results of performing a multiply operation using the given vectors.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_mul<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0,
                                simd_trait<double,cyme::vmx,4>::register_type xmm1){
         assert(false);
    }

    /**
      Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_div<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0,
                                simd_trait<double,cyme::vmx,1>::register_type xmm1){
        assert(false);
    }

    /**
      Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_div<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0,
                                simd_trait<double,cyme::vmx,2>::register_type xmm1){
         assert(false);
    }

    /**
      Returns a vector containing the result of dividing each element of a by the corresponding element of b.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_div<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0,
                                simd_trait<double,cyme::vmx,4>::register_type xmm1){
         assert(false);
    }

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_add<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0,
                                simd_trait<double,cyme::vmx,1>::register_type xmm1){
        assert(false);
    }

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_add<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0,
                                simd_trait<double,cyme::vmx,2>::register_type xmm1){
         assert(false);
    }

    /**
      Returns a vector containing the sums of each set of corresponding elements of the given vectors.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_add<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0,
                                simd_trait<double,cyme::vmx,4>::register_type xmm1){
         assert(false);
    }

    /**
      Returns a vector containing the result of subtracting each element of b from the corresponding element of a.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_sub<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0,
                                simd_trait<double,cyme::vmx,1>::register_type xmm1){
        assert(false);
    }

    /**
      Returns a vector containing the result of subtracting each element of b from the corresponding element of a.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_sub<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0,
                                simd_trait<double,cyme::vmx,2>::register_type xmm1){
         assert(false);
    }

    /**
      Returns a vector containing the result of subtracting each element of b from the corresponding element of a.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_sub<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0,
                                simd_trait<double,cyme::vmx,4>::register_type xmm1){
         assert(false);
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_exp<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0){
        assert(false);
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_exp<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0){
         assert(false);
    }

    /**
      Computes the exponential function of each element of vx.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_exp<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0){
         assert(false);
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_log<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0){
        assert(false);
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_log<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0){
         assert(false);
    }

    /**
      Computes the logarithm function of each element of vx.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_log<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0){
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
        assert(false);
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
         assert(false);
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
         assert(false);
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
    forceinline  simd_trait<double,cyme::vmx,1>::register_type
    _mm_rsqrt<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0){
        assert(false);
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
    forceinline  simd_trait<double,cyme::vmx,2>::register_type
    _mm_rsqrt<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0){
        assert(false);
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
    forceinline  simd_trait<double,cyme::vmx,4>::register_type
    _mm_rsqrt<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0){
        assert(false);
    }


    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_neg<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0){
        assert(false);
    }

    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_neg<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0){
         assert(false);
    }

    /**
      Returns a vector containing the negated value of the corresponding elements in the given vector.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_neg<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0){
         assert(false);
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::vmx,1>::register_type
    _mm_cast<double,cyme::vmx,1>(simd_trait<int,cyme::vmx,1>::register_type xmm0){
        assert(false);
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::vmx,2>::register_type
    _mm_cast<double,cyme::vmx,2>(simd_trait<int,cyme::vmx,2>::register_type xmm0){
        assert(false);
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::vmx,4>::register_type
    _mm_cast<double,cyme::vmx,4>(simd_trait<int,cyme::vmx,4>::register_type xmm0){
        assert(false);
    }


    /**
      Returns a vector containing the largest representable floating-point integral values less than or equal
     to the values of the corresponding elements of the given vector.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,1>::register_type
    _mm_floor<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0){
        assert(false);
    }

    /**
      Returns a vector containing the largest representable floating-point integral values less than or equal
     to the values of the corresponding elements of the given vector.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,2>::register_type
    _mm_floor<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0){
         assert(false);
    }

    /**
      Returns a vector containing the largest representable floating-point integral values less than or equal
     to the values of the corresponding elements of the given vector.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::vmx,4>::register_type
    _mm_floor<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0){
         assert(false);
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer, as the BG/Q does not support vmx integer
     the computation is done serialy using C trick
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::vmx,1>::register_type
    _mm_twok<double,cyme::vmx,1>(simd_trait<int,cyme::vmx,1>::register_type xmm0){
        assert(false);
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer, as the BG/Q does not support vmx integer
     the computation is done serialy using C trick
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::vmx,2>::register_type
    _mm_twok<double,cyme::vmx,2>(simd_trait<int,cyme::vmx,2>::register_type xmm0){
        assert(false);
    }

    /**
      Returns a vector containing 2^k where k is a vector of integer, as the BG/Q does not support vmx integer
     the computation is done serialy using C trick
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::vmx,4>::register_type
    _mm_twok<double,cyme::vmx,4>(simd_trait<int,cyme::vmx,4>::register_type xmm0){
        assert(false);
    }

   /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
      arithmetic are very badly supported with AVX, I am presently glue I so do the compuation in SSE;
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::vmx,1>::register_type
    _mm_ge<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0){
        assert(false);
    }

   /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
      arithmetic are very badly supported with AVX, I am presently glue I so do the compuation in SSE;
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::vmx,2>::register_type
    _mm_ge<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0){
        assert(false);
    }

   /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
      arithmetic are very badly supported with AVX, I am presently glue I so do the compuation in SSE;
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::vmx,4>::register_type
    _mm_ge<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0){
        assert(false);
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::vmx,1>::register_type
    _mm_gf<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0){
        assert(false);
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
       specialisation double,cyme::vmx,2 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::vmx,2>::register_type
    _mm_gf<double,cyme::vmx,2>(simd_trait<double,cyme::vmx,2>::register_type xmm0){
        assert(false);
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
       specialisation double,cyme::vmx,4 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::vmx,4>::register_type
    _mm_gf<double,cyme::vmx,4>(simd_trait<double,cyme::vmx,4>::register_type xmm0){
        assert(false);
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
        assert(false);
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
         assert(false);
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
         assert(false);
    }

    /**
      Returns a vector containing the results of performing a negative multiply-subtract
     operation on the given vectors.
       specialisation double,cyme::vmx,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::vmx,1>::register_type
    _mm_nfma<double,cyme::vmx,1>(simd_trait<double,cyme::vmx,1>::register_type xmm0,
                                 simd_trait<double,cyme::vmx,1>::register_type xmm1,
                                 simd_trait<double,cyme::vmx,1>::register_type xmm2){
        assert(false);
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
         assert(false);
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
         assert(false);
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
        assert(false);
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
         assert(false);
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
         assert(false);
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
        assert(false);
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
         assert(false);
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
         assert(false);
    }
#endif
} //end namespace

#endif
