/*
* Cyme - simd_wrapper_sse.ipp, Copyright (c), 2014,
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
* @file cyme/core/simd_vector/detail/x86/simd_wrapper_sse.ipp
* Final specialisation for math functions and sse technology
*/
#ifndef CYME_SIMD_WRAPPER_SSE_IPP
#define CYME_SIMD_WRAPPER_SSE_IPP

namespace cyme{

    /**  Load a double-precision (64-bit) floating-point element from cyme into
     lower element of dst . */
    template<> forceinline simd_trait<double,cyme::sse,1>::register_type
    _mm_single_load<double,cyme::sse,1>(const
    simd_trait<double,cyme::sse,1>::value_type b){ return _mm_load_sd(&b); }

    /** store a double-precision (64-bit) floating-point element from register
    lower element to cyme.  */
    template<>
    forceinline simd_trait<double,cyme::sse,1>::value_type
    _mm_single_store<double,cyme::sse,1>(simd_trait<double,cyme::sse,1>::register_type xmm0,
                                         simd_trait<double,cyme::sse,1>::pointer b){
        _mm_storel_pd(b,xmm0);
        return *b;
    }

    /**
       Load a double-precision (64-bit) floating-point element from cyme into both elements of dst.
       specialisation double,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,1>::register_type
    _mm_load1<double,cyme::sse,1>(const simd_trait<double,cyme::sse,1>::value_type& a){
        return _mm_set1_pd(a);
    }

    /**
       Load a double-precision (64-bit) floating-point element from cyme into both elements of dst.
       specialisation double,cyme::sse,2 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::sse,2>::register_type
    _mm_load1<double,cyme::sse,2>(const simd_trait<double,cyme::sse,2>::value_type& a){
        return simd_trait<double,cyme::sse,2>::register_type(_mm_set1_pd(a),_mm_set1_pd(a));
    }

    /**
       Load a double-precision (64-bit) floating-point element from cyme into both elements of dst.
       specialisation double,cyme::sse,4 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::sse,4>::register_type
    _mm_load1<double,cyme::sse,4>(const simd_trait<double,cyme::sse,4>::value_type& a){
        return simd_trait<double,cyme::sse,4>::register_type(_mm_set1_pd(a),_mm_set1_pd(a),
                                                             _mm_set1_pd(a),_mm_set1_pd(a));
    }

    /**
       Load 128-bits (composed of 2 packed double-precision (64-bit) floating-point elements) from cyme
     into dst. mem_addr must be aligned on a 16-byte boundary or a general-protection exception will be generated.
       specialisation double,cyme::sse,1 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::sse,1>::register_type
    _mm_load<double,cyme::sse,1>(simd_trait<double,cyme::sse,1>::const_pointer a){
        return _mm_load_pd(a);
    }

    /**
       Load 128-bits (composed of 2 packed double-precision (64-bit) floating-point elements) from cyme
     into dst. mem_addr must be aligned on a 16-byte boundary or a general-protection exception will be generated.
       specialisation double,cyme::sse,2 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::sse,2>::register_type
    _mm_load<double,cyme::sse,2>(simd_trait<double,cyme::sse,2>::const_pointer a){
        return simd_trait<double,cyme::sse,2>::register_type(_mm_load_pd(a),_mm_load_pd(a+2));
    }

    /**
       Load 128-bits (composed of 2 packed double-precision (64-bit) floating-point elements) from cyme
     into dst. mem_addr must be aligned on a 16-byte boundary or a general-protection exception will be generated.
       specialisation double,cyme::sse,4 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::sse,4>::register_type
    _mm_load<double,cyme::sse,4>(simd_trait<double,cyme::sse,4>::const_pointer a){
        return simd_trait<double,cyme::sse,4>::register_type(_mm_load_pd(a),_mm_load_pd(a+2),
                                                             _mm_load_pd(a+4),_mm_load_pd(a+6));
    }

    /**
       Store 128-bits (composed of 2 packed double-precision (64-bit) floating-point elements) from a into cyme.
     mem_addr must be aligned on a 16-byte boundary or a general-protection exception will be generated.
       specialisation double,cyme::sse,1 regs
     */
    template<>
    void _mm_store<double,cyme::sse,1>(simd_trait<double,cyme::sse,1>::register_type xmm0,
                                       simd_trait<double,cyme::sse,1>::pointer a){
        _mm_store_pd(a,xmm0);
    }

    /**
       Store 128-bits (composed of 2 packed double-precision (64-bit) floating-point elements) from a into cyme.
     mem_addr must be aligned on a 16-byte boundary or a general-protection exception will be generated.
       specialisation double,cyme::sse,2 regs
     */
    template<>
    void _mm_store<double,cyme::sse,2>(simd_trait<double,cyme::sse,2>::register_type xmm0,
                                       simd_trait<double,cyme::sse,2>::pointer a){
        _mm_store_pd(a,xmm0.r0);
        _mm_store_pd(a+2,xmm0.r1);
    }

    /**
       Store 128-bits (composed of 2 packed double-precision (64-bit) floating-point elements) from a into cyme.
     mem_addr must be aligned on a 16-byte boundary or a general-protection exception will be generated.
       specialisation double,cyme::sse,4 regs
     */
    template<>
    void _mm_store<double,cyme::sse,4>(simd_trait<double,cyme::sse,4>::register_type xmm0,
                                       simd_trait<double,cyme::sse,4>::pointer a){
        _mm_store_pd(a,xmm0.r0);
        _mm_store_pd(a+2,xmm0.r1);
        _mm_store_pd(a+4,xmm0.r2);
        _mm_store_pd(a+6,xmm0.r3);

    }

    /**
       Multiply packed double-precision (64-bit) floating-point elements in xmm0 and xmm1,
     and store the results in dst.
       specialisation double,cyme::sse,1 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::sse,1>::register_type
    _mm_mul<double,cyme::sse,1>(simd_trait<double,cyme::sse,1>::register_type xmm0,
                                simd_trait<double,cyme::sse,1>::register_type xmm1){
        return _mm_mul_pd(xmm0, xmm1);
    }

    /**
       Multiply packed double-precision (64-bit) floating-point elements in xmm0 and xmm1,
     and store the results in dst.
       specialisation double,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,2>::register_type
    _mm_mul<double,cyme::sse,2>(simd_trait<double,cyme::sse,2>::register_type xmm0,
                                simd_trait<double,cyme::sse,2>::register_type xmm1){
        return simd_trait<double,cyme::sse,2>::register_type(_mm_mul_pd(xmm0.r0, xmm1.r0),
                                                             _mm_mul_pd(xmm0.r1, xmm1.r1));
    }

    /**
       Multiply packed double-precision (64-bit) floating-point elements in xmm0 and xmm1,
     and store the results in dst.
       specialisation double,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,4>::register_type
    _mm_mul<double,cyme::sse,4>(simd_trait<double,cyme::sse,4>::register_type xmm0,
                                simd_trait<double,cyme::sse,4>::register_type xmm1){
        return simd_trait<double,cyme::sse,4>::register_type(_mm_mul_pd(xmm0.r0, xmm1.r0),
                                                             _mm_mul_pd(xmm0.r1, xmm1.r1),
                                                             _mm_mul_pd(xmm0.r2, xmm1.r2),
                                                             _mm_mul_pd(xmm0.r3, xmm1.r3));
    }

    /**
       Divide packed double-precision (64-bit) floating-point elements in xmm0 by packed elements in xmm1,
     and store the results in dst.
       specialisation double,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,1>::register_type
    _mm_div<double,cyme::sse,1>(simd_trait<double,cyme::sse,1>::register_type xmm0,
                                simd_trait<double,cyme::sse,1>::register_type xmm1){
        return _mm_div_pd(xmm0, xmm1);
    }

    /**
       Divide packed double-precision (64-bit) floating-point elements in xmm0 by packed elements in xmm1,
     and store the results in dst.
       specialisation double,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,2>::register_type
    _mm_div<double,cyme::sse,2>(simd_trait<double,cyme::sse,2>::register_type xmm0,
                                simd_trait<double,cyme::sse,2>::register_type xmm1){
        return simd_trait<double,cyme::sse,2>::register_type(_mm_div_pd(xmm0.r0, xmm1.r0),
                                                             _mm_div_pd(xmm0.r1, xmm1.r1));
    }

    /**
       Divide packed double-precision (64-bit) floating-point elements in xmm0 by packed elements in xmm1,
     and store the results in dst.
       specialisation double,cyme::sse,4 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::sse,4>::register_type
    _mm_div<double,cyme::sse,4>(simd_trait<double,cyme::sse,4>::register_type xmm0,
                                simd_trait<double,cyme::sse,4>::register_type xmm1){
        return simd_trait<double,cyme::sse,4>::register_type(_mm_div_pd(xmm0.r0, xmm1.r0),
                                                             _mm_div_pd(xmm0.r1, xmm1.r1),
                                                             _mm_div_pd(xmm0.r2, xmm1.r2),
                                                             _mm_div_pd(xmm0.r3, xmm1.r3));
    }

    /**
       Add packed double-precision (64-bit) floating-point elements in xmm0 by packed elements in xmm1,
     and store the results in dst.
       specialisation double,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,1>::register_type
    _mm_add<double,cyme::sse,1>(simd_trait<double,cyme::sse,1>::register_type xmm0,
                                simd_trait<double,cyme::sse,1>::register_type xmm1){
        return _mm_add_pd(xmm0, xmm1);
    }

    /**
       Add packed double-precision (64-bit) floating-point elements in xmm0 by packed elements in xmm1,
     and store the results in dst.
       specialisation double,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,2>::register_type
    _mm_add<double,cyme::sse,2>(simd_trait<double,cyme::sse,2>::register_type xmm0,
                                simd_trait<double,cyme::sse,2>::register_type xmm1){
        return simd_trait<double,cyme::sse,2>::register_type(_mm_add_pd(xmm0.r0, xmm1.r0),
                                                             _mm_add_pd(xmm0.r1, xmm1.r1));
    }

    /**
       Add packed double-precision (64-bit) floating-point elements in xmm0 by packed elements in xmm1,
     and store the results in dst.
       specialisation double,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,4>::register_type
    _mm_add<double,cyme::sse,4>(simd_trait<double,cyme::sse,4>::register_type xmm0,
                                simd_trait<double,cyme::sse,4>::register_type xmm1){
        return simd_trait<double,cyme::sse,4>::register_type(_mm_add_pd(xmm0.r0, xmm1.r0),
                                                             _mm_add_pd(xmm0.r1, xmm1.r1),
                                                             _mm_add_pd(xmm0.r2, xmm1.r2),
                                                             _mm_add_pd(xmm0.r3, xmm1.r3));
    }

    /**
       Sub packed double-precision (64-bit) floating-point elements in xmm0 by packed elements in xmm1,
     and store the results in dst.
       specialisation double,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,1>::register_type
    _mm_sub<double,cyme::sse,1>(simd_trait<double,cyme::sse,1>::register_type xmm0,
                                simd_trait<double,cyme::sse,1>::register_type xmm1){
        return _mm_sub_pd(xmm0, xmm1);
    }

    /**
       Sub packed double-precision (64-bit) floating-point elements in xmm0 by packed elements in xmm1,
     and store the results in dst.
       specialisation double,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,2>::register_type
    _mm_sub<double,cyme::sse,2>(simd_trait<double,cyme::sse,2>::register_type xmm0,
                                simd_trait<double,cyme::sse,2>::register_type xmm1){
        return simd_trait<double,cyme::sse,2>::register_type(_mm_sub_pd(xmm0.r0, xmm1.r0),
                                                             _mm_sub_pd(xmm0.r1, xmm1.r1));
    }

    /**
       Sub packed double-precision (64-bit) floating-point elements in xmm0 by packed elements in xmm1,
     and store the results in dst.
       specialisation double,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,4>::register_type
    _mm_sub<double,cyme::sse,4>(simd_trait<double,cyme::sse,4>::register_type xmm0,
                                simd_trait<double,cyme::sse,4>::register_type xmm1){
        return simd_trait<double,cyme::sse,4>::register_type(_mm_sub_pd(xmm0.r0, xmm1.r0),
                                                             _mm_sub_pd(xmm0.r1, xmm1.r1),
                                                             _mm_sub_pd(xmm0.r2, xmm1.r2),
                                                             _mm_sub_pd(xmm0.r3, xmm1.r3));
    }

    /**
      Convert packed single-precision (32-bit) floating-point elements in xmm0
     to packed double-precision (64-bit) floating-point elements, and store the results in dst.
       specialisation double,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,1>::register_type
    _mm_rec<double,cyme::sse,1>(simd_trait<double,cyme::sse,1>::register_type xmm0){
        return _mm_cvtps_pd(_mm_rcp_ps(_mm_cvtpd_ps(xmm0)));
    }

    /**
      Convert packed single-precision (32-bit) floating-point elements in xmm0
     to packed double-precision (64-bit) floating-point elements, and store the results in dst.
       specialisation double,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,2>::register_type
    _mm_rec<double,cyme::sse,2>(simd_trait<double,cyme::sse,2>::register_type xmm0){
        return simd_trait<double,cyme::sse,2>::register_type(_mm_cvtps_pd(_mm_rcp_ps(_mm_cvtpd_ps(xmm0.r0))),
                                                             _mm_cvtps_pd(_mm_rcp_ps(_mm_cvtpd_ps(xmm0.r1))));
    }

    /**
      Convert packed single-precision (32-bit) floating-point elements in xmm0
     to packed double-precision (64-bit) floating-point elements, and store the results in dst.
       specialisation double,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,4>::register_type
    _mm_rec<double,cyme::sse,4>(simd_trait<double,cyme::sse,4>::register_type xmm0){
        return simd_trait<double,cyme::sse,4>::register_type(_mm_cvtps_pd(_mm_rcp_ps(_mm_cvtpd_ps(xmm0.r0))),
                                                             _mm_cvtps_pd(_mm_rcp_ps(_mm_cvtpd_ps(xmm0.r1))),
                                                             _mm_cvtps_pd(_mm_rcp_ps(_mm_cvtpd_ps(xmm0.r2))),
                                                             _mm_cvtps_pd(_mm_rcp_ps(_mm_cvtpd_ps(xmm0.r3))));
    }

    /**
      Negate packed double-precision (64-bit) floating-point elements in xmm0 to packed double-precision (64-bit)
     floating-point elements, and store the results in dst.
       specialisation double,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,1>::register_type
    _mm_neg<double,cyme::sse,1>(simd_trait<double,cyme::sse,1>::register_type xmm0){
        simd_trait<double,cyme::sse,1>::register_type mask =  _mm_castsi128_pd(_mm_set1_epi64x(0x8000000000000000));
        return _mm_xor_pd(xmm0, mask);
    }

    /**
      Negate packed double-precision (64-bit) floating-point elements in xmm0 to packed double-precision (64-bit)
     floating-point elements, and store the results in dst.
       specialisation double,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,2>::register_type
    _mm_neg<double,cyme::sse,2>(simd_trait<double,cyme::sse,2>::register_type xmm0){
        simd_trait<double,cyme::sse,1>::register_type mask(_mm_castsi128_pd(_mm_set1_epi64x(0x8000000000000000)));
        return simd_trait<double,cyme::sse,2>::register_type(_mm_xor_pd(xmm0.r0, mask),
                                                             _mm_xor_pd(xmm0.r1, mask));
    }

    /**
      Negate packed double-precision (64-bit) floating-point elements in xmm0 to packed double-precision (64-bit)
     floating-point elements, and store the results in dst.
       specialisation double,cyme::sse,4 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::sse,4>::register_type
    _mm_neg<double,cyme::sse,4>(simd_trait<double,cyme::sse,4>::register_type xmm0){
        simd_trait<double,cyme::sse,1>::register_type mask(_mm_castsi128_pd(_mm_set1_epi64x(0x8000000000000000)));
        return simd_trait<double,cyme::sse,4>::register_type(_mm_xor_pd(xmm0.r0, mask),
                                                             _mm_xor_pd(xmm0.r1, mask),
                                                             _mm_xor_pd(xmm0.r2, mask),
                                                             _mm_xor_pd(xmm0.r3, mask));
    }

    /**
      Convert packed double-precision (64-bit) floating-point elements in xmm0 to packed 32-bit integers with
     truncation, and store the results in dst.
       specialisation double,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<int,cyme::sse,1>::register_type
    _mm_floor<double,cyme::sse,1>(simd_trait<double,cyme::sse,1>::register_type xmm0){
        return _mm_cvttpd_epi32(_mm_floor_pd(xmm0));
    }

    /**
      Convert packed double-precision (64-bit) floating-point elements in xmm0 to packed 32-bit integers with
     truncation, and store the results in dst.
       specialisation double,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<int,cyme::sse,2>::register_type
    _mm_floor<double,cyme::sse,2>(simd_trait<double,cyme::sse,2>::register_type xmm0){
        return simd_trait<int,cyme::sse,2>::register_type(_mm_cvttpd_epi32(_mm_floor_pd(xmm0.r0)),
                                                          _mm_cvttpd_epi32(_mm_floor_pd(xmm0.r1)));
    }

    /**
      Convert packed double-precision (64-bit) floating-point elements in xmm0 to packed 32-bit integers with
     truncation, and store the results in dst.
       specialisation double,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<int,cyme::sse,4>::register_type
    _mm_floor<double,cyme::sse,4>(simd_trait<double,cyme::sse,4>::register_type xmm0){
        return simd_trait<int,cyme::sse,4>::register_type(_mm_cvttpd_epi32(_mm_floor_pd(xmm0.r0)),
                                                          _mm_cvttpd_epi32(_mm_floor_pd(xmm0.r1)),
                                                          _mm_cvttpd_epi32(_mm_floor_pd(xmm0.r2)),
                                                          _mm_cvttpd_epi32(_mm_floor_pd(xmm0.r3)));
    }


    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation double,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,1>::register_type
    _mm_cast<double,cyme::sse,1>(simd_trait<int,cyme::sse,1>::register_type xmm0){
        return  _mm_cvtepi32_pd(xmm0);
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation double,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,2>::register_type
    _mm_cast<double,cyme::sse,2>(simd_trait<int,cyme::sse,2>::register_type xmm0){
        return simd_trait<double,cyme::sse,2>::register_type(_mm_cvtepi32_pd(xmm0.r0),
                                                             _mm_cvtepi32_pd(xmm0.r1));
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed double-precision (64-bit) floating-point elements,
     and store the results in dst.
       specialisation double,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,4>::register_type
    _mm_cast<double,cyme::sse,4>(simd_trait<int,cyme::sse,4>::register_type xmm0){
        return simd_trait<double,cyme::sse,4>::register_type(_mm_cvtepi32_pd(xmm0.r0),
                                                             _mm_cvtepi32_pd(xmm0.r1),
                                                             _mm_cvtepi32_pd(xmm0.r2),
                                                             _mm_cvtepi32_pd(xmm0.r3));
    }


    /**
      Compute 2^k packed integer (64-bit) elements in xmm0 to packed double-precision (64-bit) floating-point
     elements, and store the results in dst.
       specialisation double,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,1>::register_type
    _mm_twok<double,cyme::sse,1>(simd_trait<int,cyme::sse,1>::register_type xmm0){
        // OK it is more than a basic wrapper
         //       xmm0 = _mm_add_epi32(xmm0,  _mm_setr_epi32(1023, 1023, 0, 0));
         //       xmm0 = _mm_slli_epi32(xmm0, 20);
         //       xmm0 = _mm_shuffle_epi32(xmm0, _MM_SHUFFLE(1,3,0,2));
        return  _mm_castsi128_pd(_mm_shuffle_epi32(_mm_slli_epi32(_mm_add_epi32(xmm0, _mm_setr_epi32(1023, 1023, 0, 0)), 20),
                                                   _MM_SHUFFLE(1,3,0,2)));
    }

    /**
      Compute 2^k packed integer (64-bit) elements in xmm0 to packed double-precision (64-bit) floating-point
     elements, and store the results in dst.
       specialisation double,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,2>::register_type
    _mm_twok<double,cyme::sse,2>(simd_trait<int,cyme::sse,2>::register_type xmm0){
        // OK it is more than a basic wrapper
        xmm0.r0 = _mm_add_epi32(xmm0.r0,  _mm_setr_epi32(1023, 1023, 0, 0));
        xmm0.r1 = _mm_add_epi32(xmm0.r1,  _mm_setr_epi32(1023, 1023, 0, 0));
        xmm0.r0 = _mm_slli_epi32(xmm0.r0, 20);
        xmm0.r1 = _mm_slli_epi32(xmm0.r1, 20);
        xmm0.r0 = _mm_shuffle_epi32(xmm0.r0, _MM_SHUFFLE(1,3,0,2));
        xmm0.r1 = _mm_shuffle_epi32(xmm0.r1, _MM_SHUFFLE(1,3,0,2));
        return simd_trait<double,cyme::sse,2>::register_type(_mm_castsi128_pd(xmm0.r0),
                                                               _mm_castsi128_pd(xmm0.r1));
    }

    /**
      Compute 2^k packed integer (64-bit) elements in xmm0 to packed double-precision (64-bit) floating-point
     elements, and store the results in dst.
       specialisation double,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,4>::register_type
    _mm_twok<double,cyme::sse,4>(simd_trait<int,cyme::sse,4>::register_type xmm0){
        // OK it is more than a basic wrapper
        xmm0.r0 = _mm_add_epi32(xmm0.r0,  _mm_setr_epi32(1023, 1023, 0, 0));
        xmm0.r1 = _mm_add_epi32(xmm0.r1,  _mm_setr_epi32(1023, 1023, 0, 0));
        xmm0.r2 = _mm_add_epi32(xmm0.r2,  _mm_setr_epi32(1023, 1023, 0, 0));
        xmm0.r3 = _mm_add_epi32(xmm0.r3,  _mm_setr_epi32(1023, 1023, 0, 0));
        xmm0.r0 = _mm_slli_epi32(xmm0.r0, 20);
        xmm0.r1 = _mm_slli_epi32(xmm0.r1, 20);
        xmm0.r2 = _mm_slli_epi32(xmm0.r2, 20);
        xmm0.r3 = _mm_slli_epi32(xmm0.r3, 20);
        xmm0.r0 = _mm_shuffle_epi32(xmm0.r0, _MM_SHUFFLE(1,3,0,2));
        xmm0.r1 = _mm_shuffle_epi32(xmm0.r1, _MM_SHUFFLE(1,3,0,2));
        xmm0.r2 = _mm_shuffle_epi32(xmm0.r2, _MM_SHUFFLE(1,3,0,2));
        xmm0.r3 = _mm_shuffle_epi32(xmm0.r3, _MM_SHUFFLE(1,3,0,2));
        return simd_trait<double,cyme::sse,4>::register_type(_mm_castsi128_pd(xmm0.r0),
                                                               _mm_castsi128_pd(xmm0.r1),
                                                               _mm_castsi128_pd(xmm0.r2),
                                                               _mm_castsi128_pd(xmm0.r3));
    }

    /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
       specialisation double,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,1>::register_type
    _mm_ge<double,cyme::sse,1>(simd_trait<double,cyme::sse,1>::register_type xmm0){
        __m128i tmp =  _mm_castpd_si128(xmm0);
        tmp = _mm_srli_epi64(tmp,52);
        tmp = _mm_sub_epi64(tmp, _mm_set1_epi64x(1023));
         // _mm_shuffle_epi32(a, <1, 3, 2, 0>) {a.1, a.2, a.2, a.3} → {a.1, a.3, a.2, a.0}
        tmp = _mm_shuffle_epi32(tmp, _MM_SHUFFLE(1,3,2,0));
        return _mm_cvtepi32_pd(tmp);
    }

    /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
       specialisation double,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,2>::register_type
    _mm_ge<double,cyme::sse,2>(simd_trait<double,cyme::sse,2>::register_type xmm0){
        __m128i tmp0 =  _mm_castpd_si128(xmm0.r0);
        __m128i tmp1 =  _mm_castpd_si128(xmm0.r1);
        tmp0 = _mm_srli_epi64(tmp0,52);
        tmp1 = _mm_srli_epi64(tmp1,52);
        tmp0 = _mm_sub_epi64(tmp0, _mm_set1_epi64x(1023));
        tmp1 = _mm_sub_epi64(tmp1, _mm_set1_epi64x(1023));
        tmp0 = _mm_shuffle_epi32(tmp0, _MM_SHUFFLE(1,3,2,0));
        tmp1 = _mm_shuffle_epi32(tmp1, _MM_SHUFFLE(1,3,2,0));
        return simd_trait<double,cyme::sse,2>::register_type(_mm_cvtepi32_pd(tmp0),
                                                               _mm_cvtepi32_pd(tmp1));
    }

    /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
       specialisation double,cyme::sse,4 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::sse,4>::register_type
    _mm_ge<double,cyme::sse,4>(simd_trait<double,cyme::sse,4>::register_type xmm0){
        __m128i tmp0 =  _mm_castpd_si128(xmm0.r0);
        __m128i tmp1 =  _mm_castpd_si128(xmm0.r1);
        __m128i tmp2 =  _mm_castpd_si128(xmm0.r2);
        __m128i tmp3 =  _mm_castpd_si128(xmm0.r3);
        tmp0 = _mm_srli_epi64(tmp0,52);
        tmp1 = _mm_srli_epi64(tmp1,52);
        tmp2 = _mm_srli_epi64(tmp2,52);
        tmp3 = _mm_srli_epi64(tmp3,52);
        tmp0 = _mm_sub_epi64(tmp0, _mm_set1_epi64x(1023));
        tmp1 = _mm_sub_epi64(tmp1, _mm_set1_epi64x(1023));
        tmp2 = _mm_sub_epi64(tmp2, _mm_set1_epi64x(1023));
        tmp3 = _mm_sub_epi64(tmp3, _mm_set1_epi64x(1023));
        tmp0 = _mm_shuffle_epi32(tmp0, _MM_SHUFFLE(1,3,2,0));
        tmp1 = _mm_shuffle_epi32(tmp1, _MM_SHUFFLE(1,3,2,0));
        tmp2 = _mm_shuffle_epi32(tmp2, _MM_SHUFFLE(1,3,2,0));
        tmp3 = _mm_shuffle_epi32(tmp3, _MM_SHUFFLE(1,3,2,0));
        return simd_trait<double,cyme::sse,4>::register_type(_mm_cvtepi32_pd(tmp0),
                                                             _mm_cvtepi32_pd(tmp1),
                                                             _mm_cvtepi32_pd(tmp2),
                                                             _mm_cvtepi32_pd(tmp3));
    }


    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
       specialisation double,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,1>::register_type
    _mm_gf<double,cyme::sse,1>(simd_trait<double,cyme::sse,1>::register_type xmm0){
        __m128i tmp =  _mm_castpd_si128(xmm0);
        tmp = _mm_and_si128(tmp,_mm_set1_epi64x(0xfffffffffffff));
        tmp = _mm_add_epi64(tmp,_mm_set1_epi64x(0x3ff0000000000000));
        return _mm_castsi128_pd(tmp);
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
       specialisation double,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,2>::register_type
    _mm_gf<double,cyme::sse,2>(simd_trait<double,cyme::sse,2>::register_type xmm0){
        __m128i tmp0 =  _mm_castpd_si128(xmm0.r0);
        __m128i tmp1 =  _mm_castpd_si128(xmm0.r1);
        tmp0 = _mm_and_si128(tmp0,_mm_set1_epi64x(0xfffffffffffff));
        tmp1 = _mm_and_si128(tmp1,_mm_set1_epi64x(0xfffffffffffff));
        tmp0 = _mm_add_epi64(tmp0,_mm_set1_epi64x(0x3ff0000000000000));
        tmp1 = _mm_add_epi64(tmp1,_mm_set1_epi64x(0x3ff0000000000000));
        return simd_trait<double,cyme::sse,2>::register_type(_mm_castsi128_pd(tmp0),
                                                             _mm_castsi128_pd(tmp1));
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
       specialisation double,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,4>::register_type
    _mm_gf<double,cyme::sse,4>(simd_trait<double,cyme::sse,4>::register_type xmm0){
        __m128i tmp0 =  _mm_castpd_si128(xmm0.r0);
        __m128i tmp1 =  _mm_castpd_si128(xmm0.r1);
        __m128i tmp2 =  _mm_castpd_si128(xmm0.r2);
        __m128i tmp3 =  _mm_castpd_si128(xmm0.r3);
        tmp0 = _mm_and_si128(tmp0,_mm_set1_epi64x(0xfffffffffffff));
        tmp1 = _mm_and_si128(tmp1,_mm_set1_epi64x(0xfffffffffffff));
        tmp2 = _mm_and_si128(tmp2,_mm_set1_epi64x(0xfffffffffffff));
        tmp3 = _mm_and_si128(tmp3,_mm_set1_epi64x(0xfffffffffffff));
        tmp0 = _mm_add_epi64(tmp0,_mm_set1_epi64x(0x3ff0000000000000));
        tmp1 = _mm_add_epi64(tmp1,_mm_set1_epi64x(0x3ff0000000000000));
        tmp2 = _mm_add_epi64(tmp2,_mm_set1_epi64x(0x3ff0000000000000));
        tmp3 = _mm_add_epi64(tmp3,_mm_set1_epi64x(0x3ff0000000000000));
        return simd_trait<double,cyme::sse,4>::register_type(_mm_castsi128_pd(tmp0),
                                                             _mm_castsi128_pd(tmp1),
                                                             _mm_castsi128_pd(tmp2),
                                                             _mm_castsi128_pd(tmp3));
    }


    /**
      Compute sqrt (64-bit) floating point elements in xmm0 to packed double-precision (64-bit)
     floating-point elements, and store the results in dst.
       specialisation double,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,1>::register_type
    _mm_sqrt<double,cyme::sse,1>(simd_trait<double,cyme::sse,1>::register_type xmm0){
        return _mm_sqrt_pd(xmm0);
    }

    /**
      Compute sqrt (64-bit) floating point elements in xmm0 to packed double-precision (64-bit)
     floating-point elements, and store the results in dst.
       specialisation double,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,2>::register_type
    _mm_sqrt<double,cyme::sse,2>(simd_trait<double,cyme::sse,2>::register_type xmm0){
        return simd_trait<double,cyme::sse,2>::register_type(_mm_sqrt_pd(xmm0.r0),
                                                             _mm_sqrt_pd(xmm0.r1));
    }

    /**
      Compute sqrt (64-bit) floating point elements in xmm0 to packed double-precision (64-bit)
     floating-point elements, and store the results in dst.
       specialisation double,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,4>::register_type
    _mm_sqrt<double,cyme::sse,4>(simd_trait<double,cyme::sse,4>::register_type xmm0){
        return simd_trait<double,cyme::sse,4>::register_type(_mm_sqrt_pd(xmm0.r0),
                                                             _mm_sqrt_pd(xmm0.r1),
                                                             _mm_sqrt_pd(xmm0.r2),
                                                             _mm_sqrt_pd(xmm0.r3));
    }

    /**
      Compute 1/recsqrt (64-bit) floating point elements in xmm0 to packed double-precision (64-bit)
     floating-point elements, and store the results in dst. precision 12 bits
       specialisation double,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,1>::register_type
    _mm_rsqrt<double,cyme::sse,1>(simd_trait<double,cyme::sse,1>::register_type xmm0){
        return _mm_cvtps_pd(_mm_rsqrt_ps(_mm_cvtpd_ps(xmm0)));
    }

    /**
      Compute 1/recsqrt (64-bit) floating point elements in xmm0 to packed double-precision (64-bit)
     floating-point elements, and store the results in dst. precision 12 bits
       specialisation double,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,2>::register_type
    _mm_rsqrt<double,cyme::sse,2>(simd_trait<double,cyme::sse,2>::register_type xmm0){
        return simd_trait<double,cyme::sse,2>::register_type(_mm_cvtps_pd(_mm_rsqrt_ps(_mm_cvtpd_ps(xmm0.r0))),
                                                             _mm_cvtps_pd(_mm_rsqrt_ps(_mm_cvtpd_ps(xmm0.r1))));
    }

    /**
      Compute 1/recsqrt (64-bit) floating point elements in xmm0 to packed double-precision (64-bit)
     floating-point elements, and store the results in dst. precision 12 bits
       specialisation double,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,4>::register_type
    _mm_rsqrt<double,cyme::sse,4>(simd_trait<double,cyme::sse,4>::register_type xmm0){
        return simd_trait<double,cyme::sse,4>::register_type(_mm_cvtps_pd(_mm_rsqrt_ps(_mm_cvtpd_ps(xmm0.r0))),
                                                             _mm_cvtps_pd(_mm_rsqrt_ps(_mm_cvtpd_ps(xmm0.r1))),
                                                             _mm_cvtps_pd(_mm_rsqrt_ps(_mm_cvtpd_ps(xmm0.r2))),
                                                             _mm_cvtps_pd(_mm_rsqrt_ps(_mm_cvtpd_ps(xmm0.r3))));
    }

#ifdef __INTEL_COMPILER
    /**
      Compute the exponential value of e raised to the power of packed double-precision (64-bit) f
     loating-point elements in xmm0, and store the results in dst.
     \warning Intel compiler only
       specialisation double,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,1>::register_type
    _mm_exp<double,cyme::sse,1>(simd_trait<double,cyme::sse,1>::register_type xmm0){
        return _mm_exp_pd(xmm0);
    }

    /**
      Compute the exponential value of e raised to the power of packed double-precision (64-bit) f
     loating-point elements in xmm0, and store the results in dst.
     \warning Intel compiler only
       specialisation double,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,2>::register_type
    _mm_exp<double,cyme::sse,2>(simd_trait<double,cyme::sse,2>::register_type xmm0){
        return simd_trait<double,cyme::sse,2>::register_type(_mm_exp_pd(xmm0.r0),
                                                             _mm_exp_pd(xmm0.r1));
    }

    /**
      Compute the exponential value of e raised to the power of packed double-precision (64-bit) f
     loating-point elements in xmm0, and store the results in dst.
     \warning Intel compiler only
       specialisation double,cyme::sse,4 regs
     */
    template<>
    forceinline  simd_trait<double,cyme::sse,4>::register_type
    _mm_exp<double,cyme::sse,4>(simd_trait<double,cyme::sse,4>::register_type xmm0){
        return simd_trait<double,cyme::sse,4>::register_type(_mm_exp_pd(xmm0.r0),
                                                             _mm_exp_pd(xmm0.r1),
                                                             _mm_exp_pd(xmm0.r2),
                                                             _mm_exp_pd(xmm0.r3));
    }
    /**
      Compute the natural logarithm of packed double-precision (64-bit) floating-point elements in xmm0,
     and store the results in dst.
     \warning Intel compiler only
       specialisation double,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,1>::register_type
    _mm_log<double,cyme::sse,1>(simd_trait<double,cyme::sse,1>::register_type xmm0){
        return _mm_log_pd(xmm0);
    }

    /**
      Compute the natural logarithm of packed double-precision (64-bit) floating-point elements in xmm0,
     and store the results in dst.
     \warning Intel compiler only
       specialisation double,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,2>::register_type
    _mm_log<double,cyme::sse,2>(simd_trait<double,cyme::sse,2>::register_type xmm0){
        return simd_trait<double,cyme::sse,2>::register_type(_mm_log_pd(xmm0.r0),
                                                             _mm_log_pd(xmm0.r1));
    }

    /**
      Compute the natural logarithm of packed double-precision (64-bit) floating-point elements in xmm0,
     and store the results in dst.
     \warning Intel compiler only
       specialisation double,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,4>::register_type
    _mm_log<double,cyme::sse,4>(simd_trait<double,cyme::sse,4>::register_type xmm0){
        return simd_trait<double,cyme::sse,4>::register_type(_mm_log_pd(xmm0.r0),
                                                             _mm_log_pd(xmm0.r1),
                                                             _mm_log_pd(xmm0.r2),
                                                             _mm_log_pd(xmm0.r3));
    }
#else
    /**
      Compute the exponential value of e raised to the power of packed double-precision (64-bit) floating-point
     elements in xmm0, and store the results in dst.
     \warning Intel compiler only
       specialisation double,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,1>::register_type
    _mm_exp<double,cyme::sse,1>(simd_trait<double,cyme::sse,1>::register_type xmm0){
        return __svml_exp2(xmm0);
    }

    /**
      Compute the exponential value of e raised to the power of packed double-precision (64-bit) floating-point
     elements in xmm0, and store the results in dst.
     \warning Intel compiler only
       specialisation double,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,2>::register_type
    _mm_exp<double,cyme::sse,2>(simd_trait<double,cyme::sse,2>::register_type xmm0){
        return simd_trait<double,cyme::sse,2>::register_type(__svml_exp2(xmm0.r0),
                                                             __svml_exp2(xmm0.r1));
    }

    /**
      Compute the exponential value of e raised to the power of packed double-precision (64-bit) floating-point
     elements in xmm0, and store the results in dst.
     \warning Intel compiler only
       specialisation double,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,4>::register_type
    _mm_exp<double,cyme::sse,4>(simd_trait<double,cyme::sse,4>::register_type xmm0){
        return simd_trait<double,cyme::sse,4>::register_type(__svml_exp2(xmm0.r0),
                                                             __svml_exp2(xmm0.r1),
                                                             __svml_exp2(xmm0.r2),
                                                             __svml_exp2(xmm0.r3));
    }
    /**
      Compute the natural logarithm of packed double-precision (64-bit) floating-point elements in xmm0,
     and store the results in dst.
     \warning Intel compiler only
       specialisation double,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,1>::register_type
    _mm_log<double,cyme::sse,1>(simd_trait<double,cyme::sse,1>::register_type xmm0){
        return __svml_log2(xmm0);
    }

    /**
      Compute the natural logarithm of packed double-precision (64-bit) floating-point elements in xmm0,
     and store the results in dst.
     \warning Intel compiler only
       specialisation double,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,2>::register_type
    _mm_log<double,cyme::sse,2>(simd_trait<double,cyme::sse,2>::register_type xmm0){
        return simd_trait<double,cyme::sse,2>::register_type(__svml_log2(xmm0.r0),
                                                             __svml_log2(xmm0.r1));
    }

    /**
      Compute the natural logarithm of packed double-precision (64-bit) floating-point elements in xmm0,
     and store the results in dst.
     \warning Intel compiler only
       specialisation double,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,4>::register_type
    _mm_log<double,cyme::sse,4>(simd_trait<double,cyme::sse,4>::register_type xmm0){
        return simd_trait<double,cyme::sse,4>::register_type(__svml_log2(xmm0.r0),
                                                             __svml_log2(xmm0.r1),
                                                             __svml_log2(xmm0.r2),
                                                             __svml_log2(xmm0.r3));
    }

#endif

#ifdef __FMA__
    /**
      Multiply packed double-precision (64-bit) floating-point elements in xmm0 and xmm2, add the intermediate
     result to packed elements in xmm2, and store the results in dst.
       specialisation double,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,1>::register_type
    _mm_fma<double,cyme::sse,1>(simd_trait<double,cyme::sse,1>::register_type xmm0,
                                simd_trait<double,cyme::sse,1>::register_type xmm1,
                                simd_trait<double,cyme::sse,1>::register_type xmm2){
        return _mm_fmadd_pd(xmm0, xmm1, xmm2);
    }

    /**
      Multiply packed double-precision (64-bit) floating-point elements in xmm0 and xmm2, add the intermediate
     result to packed elements in xmm2, and store the results in dst.
       specialisation double,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,2>::register_type
    _mm_fma<double,cyme::sse,2>(simd_trait<double,cyme::sse,2>::register_type xmm0,
                                simd_trait<double,cyme::sse,2>::register_type xmm1,
                                simd_trait<double,cyme::sse,2>::register_type xmm2){
        return simd_trait<double,cyme::sse,2>::register_type(_mm_fmadd_pd(xmm0.r0, xmm1.r0, xmm2.r0),
                                                             _mm_fmadd_pd(xmm0.r1, xmm1.r1, xmm2.r1));
    }

    /**
      Multiply packed double-precision (64-bit) floating-point elements in xmm0 and xmm2, add the intermediate
     result to packed elements in xmm2, and store the results in dst.
       specialisation double,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,4>::register_type
    _mm_fma<double,cyme::sse,4>(simd_trait<double,cyme::sse,4>::register_type xmm0,
                                simd_trait<double,cyme::sse,4>::register_type xmm1,
                                simd_trait<double,cyme::sse,4>::register_type xmm2){
        return simd_trait<double,cyme::sse,4>::register_type(_mm_fmadd_pd(xmm0.r0, xmm1.r0, xmm2.r0),
                                                             _mm_fmadd_pd(xmm0.r1, xmm1.r1, xmm2.r1),
                                                             _mm_fmadd_pd(xmm0.r2, xmm1.r2, xmm2.r2),
                                                             _mm_fmadd_pd(xmm0.r3, xmm1.r3, xmm2.r3));
    }

    /**
      Multiply packed double-precision (64-bit) floating-point elements in xmm0 and xmm1, add the negated
     intermediate result to packed elements in xmm1, and store the results in dst.
       specialisation double,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,1>::register_type
    _mm_nfma<double,cyme::sse,1>(simd_trait<double,cyme::sse,1>::register_type xmm0,
                                 simd_trait<double,cyme::sse,1>::register_type xmm1,
                                 simd_trait<double,cyme::sse,1>::register_type xmm2){
        return _mm_fnmadd_pd(xmm0, xmm1, xmm2);
    }

    /**
      Multiply packed double-precision (64-bit) floating-point elements in xmm0 and xmm1, add the negated
     intermediate result to packed elements in xmm1, and store the results in dst.
       specialisation double,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,2>::register_type
    _mm_nfma<double,cyme::sse,2>(simd_trait<double,cyme::sse,2>::register_type xmm0,
                                 simd_trait<double,cyme::sse,2>::register_type xmm1,
                                 simd_trait<double,cyme::sse,2>::register_type xmm2){
        return simd_trait<double,cyme::sse,2>::register_type(_mm_fnmadd_pd(xmm0.r0, xmm1.r0, xmm2.r0),
                                                             _mm_fnmadd_pd(xmm0.r1, xmm1.r1, xmm2.r1));
    }

    /**
      Multiply packed double-precision (64-bit) floating-point elements in xmm0 and xmm1, add the negated
     intermediate result to packed elements in xmm1, and store the results in dst.
       specialisation double,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,4>::register_type
    _mm_nfma<double,cyme::sse,4>(simd_trait<double,cyme::sse,4>::register_type xmm0,
                                 simd_trait<double,cyme::sse,4>::register_type xmm1,
                                 simd_trait<double,cyme::sse,4>::register_type xmm2){
        return simd_trait<double,cyme::sse,4>::register_type(_mm_fnmadd_pd(xmm0.r0, xmm1.r0, xmm2.r0),
                                                             _mm_fnmadd_pd(xmm0.r1, xmm1.r1, xmm2.r1),
                                                             _mm_fnmadd_pd(xmm0.r2, xmm1.r2, xmm2.r2),
                                                             _mm_fnmadd_pd(xmm0.r3, xmm1.r3, xmm2.r3));
    }

    /**
      Multiply packed double-precision (64-bit) floating-point elements in xmm0 and xmm1,
     subtract packed elements in xmm2 from the intermediate result, and store the results in dst.
       specialisation double,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,1>::register_type
    _mm_fms<double,cyme::sse,1>(simd_trait<double,cyme::sse,1>::register_type xmm0,
                                simd_trait<double,cyme::sse,1>::register_type xmm1,
                                simd_trait<double,cyme::sse,1>::register_type xmm2){
        return _mm_fmsub_pd(xmm0, xmm1, xmm2);
    }

    /**
      Multiply packed double-precision (64-bit) floating-point elements in xmm0 and xmm1,
     subtract packed elements in xmm2 from the intermediate result, and store the results in dst.
       specialisation double,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,2>::register_type
    _mm_fms<double,cyme::sse,2>(simd_trait<double,cyme::sse,2>::register_type xmm0,
                                simd_trait<double,cyme::sse,2>::register_type xmm1,
                                simd_trait<double,cyme::sse,2>::register_type xmm2){
        return simd_trait<double,cyme::sse,2>::register_type(_mm_fmsub_pd(xmm0.r0, xmm1.r0, xmm2.r0),
                                                             _mm_fmsub_pd(xmm0.r1, xmm1.r1, xmm2.r1));
    }

    /**
      Multiply packed double-precision (64-bit) floating-point elements in xmm0 and xmm1,
     subtract packed elements in xmm2 from the intermediate result, and store the results in dst.
       specialisation double,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,4>::register_type
    _mm_fms<double,cyme::sse,4>(simd_trait<double,cyme::sse,4>::register_type xmm0,
                                simd_trait<double,cyme::sse,4>::register_type xmm1,
                                simd_trait<double,cyme::sse,4>::register_type xmm2){
        return simd_trait<double,cyme::sse,4>::register_type(_mm_fmsub_pd(xmm0.r0, xmm1.r0, xmm2.r0),
                                                             _mm_fmsub_pd(xmm0.r1, xmm1.r1, xmm2.r1),
                                                             _mm_fmsub_pd(xmm0.r2, xmm1.r2, xmm2.r2),
                                                             _mm_fmsub_pd(xmm0.r3, xmm1.r3, xmm2.r3));
    }



    /**
      Multiply packed double-precision (64-bit) floating-point elements in xmm0 and xmm1, subtract packed elements
     in xmm2 from the negated intermediate result, and store the results in dst.
       specialisation double,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,1>::register_type
    _mm_nfms<double,cyme::sse,1>(simd_trait<double,cyme::sse,1>::register_type xmm0,
                                 simd_trait<double,cyme::sse,1>::register_type xmm1,
                                 simd_trait<double,cyme::sse,1>::register_type xmm2){
        return _mm_fnmsub_pd(xmm0, xmm1, xmm2);
    }

    /**
      Multiply packed double-precision (64-bit) floating-point elements in xmm0 and xmm1, subtract packed elements
     in xmm2 from the negated intermediate result, and store the results in dst.
       specialisation double,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,2>::register_type
    _mm_nfms<double,cyme::sse,2>(simd_trait<double,cyme::sse,2>::register_type xmm0,
                                 simd_trait<double,cyme::sse,2>::register_type xmm1,
                                 simd_trait<double,cyme::sse,2>::register_type xmm2){
        return simd_trait<double,cyme::sse,2>::register_type(_mm_fnmsub_pd(xmm0.r0, xmm1.r0, xmm2.r0),
                                                             _mm_fnmsub_pd(xmm0.r1, xmm1.r1, xmm2.r1));
    }

    /**
      Multiply packed double-precision (64-bit) floating-point elements in xmm0 and xmm1, subtract packed elements
     in xmm2 from the negated intermediate result, and store the results in dst.
       specialisation double,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<double,cyme::sse,4>::register_type
    _mm_nfms<double,cyme::sse,4>(simd_trait<double,cyme::sse,4>::register_type xmm0,
                                 simd_trait<double,cyme::sse,4>::register_type xmm1,
                                 simd_trait<double,cyme::sse,4>::register_type xmm2){
        return simd_trait<double,cyme::sse,4>::register_type(_mm_fnmsub_pd(xmm0.r0, xmm1.r0, xmm2.r0),
                                                             _mm_fnmsub_pd(xmm0.r1, xmm1.r1, xmm2.r1),
                                                             _mm_fnmsub_pd(xmm0.r2, xmm1.r2, xmm2.r2),
                                                               _mm_fnmsub_pd(xmm0.r3, xmm1.r3, xmm2.r3));
    }
#endif //end FMA

    /**
       Single load a single-precision (32-bit) floating-point element from cyme into lower element of dst.
     */
    template<>
    forceinline simd_trait<float,cyme::sse,1>::register_type
    _mm_single_load<float,cyme::sse,1>(const simd_trait<float,cyme::sse,1>::value_type b){
        return _mm_load_ss(&b);
    }

    /**
       Single store a single-precision (32-bit) floating-point element from register lower element to cyme.
     */
    template<>
    forceinline simd_trait<float,cyme::sse,1>::value_type
    _mm_single_store<float,cyme::sse,1>(simd_trait<float,cyme::sse,1>::register_type xmm0,
                                        simd_trait<float,cyme::sse,1>::pointer b){
        _mm_store_ss(b,xmm0);
        return *b;
    }

    /**
      Load a single-precision (32-bit) floating-point element from cyme into all elements of dst.
       specialisation float,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,1>::register_type
    _mm_load1<float,cyme::sse,1>(const simd_trait<float,cyme::sse,1>::value_type& a){
        return _mm_load1_ps(&a);
    }

    /**
      Load a single-precision (32-bit) floating-point element from cyme into all elements of dst.
       specialisation float,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,2>::register_type
    _mm_load1<float,cyme::sse,2>(const simd_trait<float,cyme::sse,2>::value_type& a){
        return simd_trait<float,cyme::sse,2>::register_type(_mm_set1_ps(a),_mm_set1_ps(a));
    }

    /**
      Load a single-precision (32-bit) floating-point element from cyme into all elements of dst.
       specialisation float,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,4>::register_type
    _mm_load1<float,cyme::sse,4>(const simd_trait<float,cyme::sse,4>::value_type& a){
        return simd_trait<float,cyme::sse,4>::register_type(_mm_set1_ps(a),_mm_set1_ps(a),
                                                            _mm_set1_ps(a),_mm_set1_ps(a));
    }

    /**
      Load 128-bits (composed of 4 packed single-precision (32-bit) floating-point elements) from cyme
     into dst. mem_addr must be aligned on a 16-byte boundary or a general-protection exception will be generated.
     specialisation float,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,1>::register_type
    _mm_load<float,cyme::sse,1>(simd_trait<float,cyme::sse,1>::const_pointer a){
        return _mm_load_ps(a);
    }

    /**
      Load 128-bits (composed of 4 packed single-precision (32-bit) floating-point elements) from cyme
     into dst. mem_addr must be aligned on a 16-byte boundary or a general-protection exception will be generated.
     specialisation float,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,2>::register_type
    _mm_load<float,cyme::sse,2>(simd_trait<float,cyme::sse,2>::const_pointer a){
        return simd_trait<float,cyme::sse,2>::register_type(_mm_load_ps(a),_mm_load_ps(a+4));
    }

    /**
      Load 128-bits (composed of 4 packed single-precision (32-bit) floating-point elements) from cyme
     into dst. mem_addr must be aligned on a 16-byte boundary or a general-protection exception will be generated.
     specialisation float,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,4>::register_type
    _mm_load<float,cyme::sse,4>(simd_trait<float,cyme::sse,4>::const_pointer a){
        return simd_trait<float,cyme::sse,4>::register_type(_mm_load_ps(a),_mm_load_ps(a+4),
                                                            _mm_load_ps(a+8),_mm_load_ps(a+12));
    }

    /**
       Store 128-bits (composed of 4 packed double-precision (32-bit) floating-point elements) from a into cyme.
     mem_addr must be aligned on a 16-byte boundary or a general-protection exception will be generated.
     specialisation float,cyme::sse,1 regs
     */
    template<>
    void _mm_store<float,cyme::sse,1>(simd_trait<float,cyme::sse,1>::register_type xmm0,
                                      simd_trait<float,cyme::sse,1>::pointer a){
        _mm_store_ps(a,xmm0);
    }

    /**
       Store 128-bits (composed of 4 packed double-precision (32-bit) floating-point elements) from a into cyme.
     mem_addr must be aligned on a 16-byte boundary or a general-protection exception will be generated.
     specialisation float,cyme::sse,2 regs
     */
    template<>
    void _mm_store<float,cyme::sse,2>(simd_trait<float,cyme::sse,2>::register_type xmm0,
                                      simd_trait<float,cyme::sse,2>::pointer a){
        _mm_store_ps(a,xmm0.r0);
        _mm_store_ps(a+4,xmm0.r1);
    }

    /**
       Store 128-bits (composed of 4 packed double-precision (32-bit) floating-point elements) from a into cyme.
     mem_addr must be aligned on a 16-byte boundary or a general-protection exception will be generated.
     specialisation float,cyme::sse,4 regs
     */
    template<>
    void _mm_store<float,cyme::sse,4>(simd_trait<float,cyme::sse,4>::register_type xmm0,
                                      simd_trait<float,cyme::sse,4>::pointer a){
        _mm_store_ps(a,xmm0.r0);
        _mm_store_ps(a+4,xmm0.r1);
        _mm_store_ps(a+8,xmm0.r2);
        _mm_store_ps(a+12,xmm0.r3);
    }

    /**
      Multiply packed single-precision (32-bit) floating-point elements in xmm0 and xmm1,
     and store the results in dst.
     specialisation float,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,1>::register_type
    _mm_mul<float,cyme::sse,1>(simd_trait<float,cyme::sse,1>::register_type xmm0,
                               simd_trait<float,cyme::sse,1>::register_type xmm1){
        return _mm_mul_ps(xmm0, xmm1);
    }

    /**
      Multiply packed single-precision (32-bit) floating-point elements in xmm0 and xmm1,
     and store the results in dst.
     specialisation float,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,2>::register_type
    _mm_mul<float,cyme::sse,2>(simd_trait<float,cyme::sse,2>::register_type xmm0,
                               simd_trait<float,cyme::sse,2>::register_type xmm1){
        return simd_trait<float,cyme::sse,2>::register_type(_mm_mul_ps(xmm0.r0, xmm1.r0),
                                                            _mm_mul_ps(xmm0.r1, xmm1.r1));
    }

    /**
      Multiply packed single-precision (32-bit) floating-point elements in xmm0 and xmm1,
     and store the results in dst.
     specialisation float,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,4>::register_type
    _mm_mul<float,cyme::sse,4>(simd_trait<float,cyme::sse,4>::register_type xmm0,
                               simd_trait<float,cyme::sse,4>::register_type xmm1){
        return simd_trait<float,cyme::sse,4>::register_type(_mm_mul_ps(xmm0.r0, xmm1.r0),
                                                            _mm_mul_ps(xmm0.r1, xmm1.r1),
                                                            _mm_mul_ps(xmm0.r2, xmm1.r2),
                                                            _mm_mul_ps(xmm0.r3, xmm1.r3));
    }

    /**
      Divide packed single-precision (32-bit) floating-point elements in xmm0 and xmm1,
     and store the results in dst.
     specialisation float,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,1>::register_type
    _mm_div<float,cyme::sse,1>(simd_trait<float,cyme::sse,1>::register_type xmm0,
                               simd_trait<float,cyme::sse,1>::register_type xmm1){
        return _mm_div_ps(xmm0, xmm1);
    }

    /**
      Divide packed single-precision (32-bit) floating-point elements in xmm0 and xmm1,
     and store the results in dst.
     specialisation float,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,2>::register_type
    _mm_div<float,cyme::sse,2>(simd_trait<float,cyme::sse,2>::register_type xmm0,
                               simd_trait<float,cyme::sse,2>::register_type xmm1){
        return simd_trait<float,cyme::sse,2>::register_type(_mm_div_ps(xmm0.r0, xmm1.r0),
                                                            _mm_div_ps(xmm0.r1, xmm1.r1));
    }

    /**
      Divide packed single-precision (32-bit) floating-point elements in xmm0 and xmm1,
     and store the results in dst.
     specialisation float,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,4>::register_type
    _mm_div<float,cyme::sse,4>(simd_trait<float,cyme::sse,4>::register_type xmm0,
                                 simd_trait<float,cyme::sse,4>::register_type xmm1){
        return simd_trait<float,cyme::sse,4>::register_type(_mm_div_ps(xmm0.r0, xmm1.r0),
                                                            _mm_div_ps(xmm0.r1, xmm1.r1),
                                                            _mm_div_ps(xmm0.r2, xmm1.r2),
                                                            _mm_div_ps(xmm0.r3, xmm1.r3));
    }

    /**
      Add packed single-precision (32-bit) floating-point elements in xmm0 and xmm1,
      and store the results in dst.
     specialisation float,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,1>::register_type
    _mm_add<float,cyme::sse,1>(simd_trait<float,cyme::sse,1>::register_type xmm0,
                               simd_trait<float,cyme::sse,1>::register_type xmm1){
        return _mm_add_ps(xmm0, xmm1);
    }

    /**
      Add packed single-precision (32-bit) floating-point elements in xmm0 and xmm1,
      and store the results in dst.
     specialisation float,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,2>::register_type
    _mm_add<float,cyme::sse,2>(simd_trait<float,cyme::sse,2>::register_type xmm0,
                               simd_trait<float,cyme::sse,2>::register_type xmm1){
        return simd_trait<float,cyme::sse,2>::register_type(_mm_add_ps(xmm0.r0, xmm1.r0),
                                                            _mm_add_ps(xmm0.r1, xmm1.r1));
    }

    /**
      Add packed single-precision (32-bit) floating-point elements in xmm0 and xmm1,
      and store the results in dst.
     specialisation float,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,4>::register_type
    _mm_add<float,cyme::sse,4>(simd_trait<float,cyme::sse,4>::register_type xmm0,
                               simd_trait<float,cyme::sse,4>::register_type xmm1){
        return simd_trait<float,cyme::sse,4>::register_type(_mm_add_ps(xmm0.r0, xmm1.r0),
                                                            _mm_add_ps(xmm0.r1, xmm1.r1),
                                                            _mm_add_ps(xmm0.r2, xmm1.r2),
                                                            _mm_add_ps(xmm0.r3, xmm1.r3));
    }

    /**
      Subtract packed single-precision (32-bit) floating-point elements in xmm0 and xmm1,
     and store the results in dst.
     specialisation float,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,1>::register_type
    _mm_sub<float,cyme::sse,1>(simd_trait<float,cyme::sse,1>::register_type xmm0,
                               simd_trait<float,cyme::sse,1>::register_type xmm1){
        return _mm_sub_ps(xmm0, xmm1);
    }

    /**
      Subtract packed single-precision (32-bit) floating-point elements in xmm0 and xmm1,
     and store the results in dst.
     specialisation float,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,2>::register_type
    _mm_sub<float,cyme::sse,2>(simd_trait<float,cyme::sse,2>::register_type xmm0,
                               simd_trait<float,cyme::sse,2>::register_type xmm1){
        return simd_trait<float,cyme::sse,2>::register_type(_mm_sub_ps(xmm0.r0, xmm1.r0),
                                                            _mm_sub_ps(xmm0.r1, xmm1.r1));
    }

    /**
      Subtract packed single-precision (32-bit) floating-point elements in xmm0 and xmm1,
     and store the results in dst.
     specialisation float,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,4>::register_type
    _mm_sub<float,cyme::sse,4>(simd_trait<float,cyme::sse,4>::register_type xmm0,
                               simd_trait<float,cyme::sse,4>::register_type xmm1){
        return simd_trait<float,cyme::sse,4>::register_type(_mm_sub_ps(xmm0.r0, xmm1.r0),
                                                            _mm_sub_ps(xmm0.r1, xmm1.r1),
                                                            _mm_sub_ps(xmm0.r2, xmm1.r2),
                                                            _mm_sub_ps(xmm0.r3, xmm1.r3));
    }

    /**
      Compute the approximate reciprocal of packed single-precision (32-bit) floating-point elements in xmm0,
     and store the results in dst. The maximum relative error for this approximation is less than 1.5*2^-12.
     specialisation float,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,1>::register_type
    _mm_rec<float,cyme::sse,1>(simd_trait<float,cyme::sse,1>::register_type xmm0){
        return _mm_rcp_ps(xmm0);
    }

    /**
      Compute the approximate reciprocal of packed single-precision (32-bit) floating-point elements in xmm0,
     and store the results in dst. The maximum relative error for this approximation is less than 1.5*2^-12.
     specialisation float,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,2>::register_type
    _mm_rec<float,cyme::sse,2>(simd_trait<float,cyme::sse,2>::register_type xmm0){
        return simd_trait<float,cyme::sse,2>::register_type(_mm_rcp_ps(xmm0.r0),
                                                            _mm_rcp_ps(xmm0.r1));
    }

    /**
      Compute the approximate reciprocal of packed single-precision (32-bit) floating-point elements in xmm0,
     and store the results in dst. The maximum relative error for this approximation is less than 1.5*2^-12.
     specialisation float,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,4>::register_type
    _mm_rec<float,cyme::sse,4>(simd_trait<float,cyme::sse,4>::register_type xmm0){
        return simd_trait<float,cyme::sse,4>::register_type(_mm_rcp_ps(xmm0.r0),
                                                            _mm_rcp_ps(xmm0.r1),
                                                            _mm_rcp_ps(xmm0.r2),
                                                            _mm_rcp_ps(xmm0.r3));
    }

    /**
      Negate packed single-precision (re-bit) floating-point elements in xmm0 to packed single-precision (63-bit)
     floating-point elements, and store the results in dst.
     specialisation float,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,1>::register_type
    _mm_neg<float,cyme::sse,1>(simd_trait<float,cyme::sse,1>::register_type xmm0){
        simd_trait<float,cyme::sse,1>::register_type mask(_mm_castsi128_ps(_mm_set1_epi32(0x80000000)));
        return _mm_xor_ps(xmm0, mask);
    }

    /**
      Negate packed single-precision (re-bit) floating-point elements in xmm0 to packed single-precision (63-bit)
     floating-point elements, and store the results in dst.
     specialisation float,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,2>::register_type
    _mm_neg<float,cyme::sse,2>(simd_trait<float,cyme::sse,2>::register_type xmm0){
        simd_trait<float,cyme::sse,1>::register_type mask(_mm_castsi128_ps(_mm_set1_epi32(0x80000000)));
        return simd_trait<float,cyme::sse,2>::register_type(_mm_xor_ps(xmm0.r0, mask),
                                                            _mm_xor_ps(xmm0.r1, mask));
    }

    /**
      Negate packed single-precision (re-bit) floating-point elements in xmm0 to packed single-precision (63-bit)
     floating-point elements, and store the results in dst.
     specialisation float,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,4>::register_type
    _mm_neg<float,cyme::sse,4>(simd_trait<float,cyme::sse,4>::register_type xmm0){
        simd_trait<float,cyme::sse,1>::register_type mask(_mm_castsi128_ps(_mm_set1_epi32(0x80000000)));
        return simd_trait<float,cyme::sse,4>::register_type(_mm_xor_ps(xmm0.r0, mask),
                                                            _mm_xor_ps(xmm0.r1, mask),
                                                            _mm_xor_ps(xmm0.r2, mask),
                                                            _mm_xor_ps(xmm0.r3, mask));
    }

    /**
      Convert packed single-precision (32-bit) floating-point elements in xmm0 to packed 32-bit integers with
     truncation, and store the results in dst.
     specialisation float,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<int,cyme::sse,1>::register_type
    _mm_floor<float,cyme::sse,1>(simd_trait<float,cyme::sse,1>::register_type xmm0){
        return _mm_cvttps_epi32(_mm_floor_ps(xmm0));
    }

    /**
      Convert packed single-precision (32-bit) floating-point elements in xmm0 to packed 32-bit integers with
     truncation, and store the results in dst.
     specialisation float,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<int,cyme::sse,2>::register_type
    _mm_floor<float,cyme::sse,2>(simd_trait<float,cyme::sse,2>::register_type xmm0){
        return simd_trait<int,cyme::sse,2>::register_type(_mm_cvttps_epi32(_mm_floor_ps(xmm0.r0)),
                                                          _mm_cvttps_epi32(_mm_floor_ps(xmm0.r1)));
    }

    /**
      Convert packed single-precision (32-bit) floating-point elements in xmm0 to packed 32-bit integers with
     truncation, and store the results in dst.
     specialisation float,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<int,cyme::sse,4>::register_type
    _mm_floor<float,cyme::sse,4>(simd_trait<float,cyme::sse,4>::register_type xmm0){
        return simd_trait<int,cyme::sse,4>::register_type(_mm_cvttps_epi32(_mm_floor_ps(xmm0.r0)),
                                                          _mm_cvttps_epi32(_mm_floor_ps(xmm0.r1)),
                                                          _mm_cvttps_epi32(_mm_floor_ps(xmm0.r2)),
                                                          _mm_cvttps_epi32(_mm_floor_ps(xmm0.r3)));
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed single-precision (32-bit) floating-point elements,
     and store the results in dst.
     specialisation float,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,1>::register_type
    _mm_cast<float,cyme::sse,1>(simd_trait<int,cyme::sse,1>::register_type xmm0){
        return  _mm_cvtepi32_ps(xmm0);
    }

    /**
      Convert packed 32-bit integers in xmm0 to packed single-precision (32-bit) floating-point elements,
     and store the results in dst.
     specialisation float,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,2>::register_type
    _mm_cast<float,cyme::sse,2>(simd_trait<int,cyme::sse,2>::register_type xmm0){
        return simd_trait<float,cyme::sse,2>::register_type(_mm_cvtepi32_ps(xmm0.r0),
                                                            _mm_cvtepi32_ps(xmm0.r1));
    }


    /**
      Convert packed 32-bit integers in xmm0 to packed single-precision (32-bit) floating-point elements,
     and store the results in dst.
     specialisation float,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,4>::register_type
    _mm_cast<float,cyme::sse,4>(simd_trait<int,cyme::sse,4>::register_type xmm0){
        return simd_trait<float,cyme::sse,4>::register_type(_mm_cvtepi32_ps(xmm0.r0),
                                                            _mm_cvtepi32_ps(xmm0.r1),
                                                            _mm_cvtepi32_ps(xmm0.r2),
                                                            _mm_cvtepi32_ps(xmm0.r3));
    }

    /**
      Compute 2^k packed integer (32-bit) elements in xmm0 to packed single-precision (32-bit)
     floating-point elements, and store the results in dst.
     specialisation float,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,1>::register_type
    _mm_twok<float,cyme::sse,1>(simd_trait<int,cyme::sse,1>::register_type xmm0){
        // ((int + 127) << 23) <=> int to float
        return  _mm_castsi128_ps(_mm_slli_epi32(_mm_add_epi32(xmm0, _mm_set1_epi32(127)), 23));
    }

    /**
      Compute 2^k packed integer (32-bit) elements in xmm0 to packed single-precision (32-bit)
     floating-point elements, and store the results in dst.
     specialisation float,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,2>::register_type
    _mm_twok<float,cyme::sse,2>(simd_trait<int,cyme::sse,2>::register_type xmm0){
        // ((int + 127) << 23) <=> int to float
        xmm0.r0 = _mm_add_epi32(xmm0.r0, _mm_set1_epi32(127));
        xmm0.r1 = _mm_add_epi32(xmm0.r1, _mm_set1_epi32(127));
        xmm0.r0 = _mm_slli_epi32(xmm0.r0, 23);
        xmm0.r1 = _mm_slli_epi32(xmm0.r1, 23);
        return simd_trait<float,cyme::sse,2>::register_type(_mm_castsi128_ps(xmm0.r0),
                                                            _mm_castsi128_ps(xmm0.r1));
    }

    /**
      Compute 2^k packed integer (32-bit) elements in xmm0 to packed single-precision (32-bit)
     floating-point elements, and store the results in dst.
     specialisation float,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,4>::register_type
    _mm_twok<float,cyme::sse,4>(simd_trait<int,cyme::sse,4>::register_type xmm0){
        xmm0.r0 = _mm_add_epi32(xmm0.r0, _mm_set1_epi32(127));
        xmm0.r1 = _mm_add_epi32(xmm0.r1, _mm_set1_epi32(127));
        xmm0.r2 = _mm_add_epi32(xmm0.r2, _mm_set1_epi32(127));
        xmm0.r3 = _mm_add_epi32(xmm0.r3, _mm_set1_epi32(127));
        xmm0.r0 = _mm_slli_epi32(xmm0.r0, 23);
        xmm0.r1 = _mm_slli_epi32(xmm0.r1, 23);
        xmm0.r2 = _mm_slli_epi32(xmm0.r2, 23);
        xmm0.r3 = _mm_slli_epi32(xmm0.r3, 23);
        return simd_trait<float,cyme::sse,4>::register_type(_mm_castsi128_ps(xmm0.r0),
                                                            _mm_castsi128_ps(xmm0.r1),
                                                            _mm_castsi128_ps(xmm0.r2),
                                                            _mm_castsi128_ps(xmm0.r3));
    }

    /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
     specialisation float,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,1>::register_type
    _mm_ge<float,cyme::sse,1>(simd_trait<float,cyme::sse,1>::register_type xmm0){
        __m128i tmp =  _mm_castps_si128(xmm0);
        tmp = _mm_srli_epi32(tmp,23);
        tmp = _mm_sub_epi32(tmp, _mm_set1_epi32(127));
        return _mm_cvtepi32_ps(tmp);
    }

    /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
     specialisation float,cyme::sse,2 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::sse,2>::register_type
    _mm_ge<float,cyme::sse,2>(simd_trait<float,cyme::sse,2>::register_type xmm0){
        __m128i tmp0 =  _mm_castps_si128(xmm0.r0);
        __m128i tmp1 =  _mm_castps_si128(xmm0.r1);
        tmp0 = _mm_srli_epi32(tmp0,23);
        tmp1 = _mm_srli_epi32(tmp1,23);
        tmp0 = _mm_sub_epi32(tmp0, _mm_set1_epi32(127));
        tmp1 = _mm_sub_epi32(tmp1, _mm_set1_epi32(127));
        return simd_trait<float,cyme::sse,2>::register_type(_mm_cvtepi32_ps(tmp0),
                                                            _mm_cvtepi32_ps(tmp1));
    }

    /**
      Extract the exponent of floating-point exponent (64-bit) elements and store the results in dst.
     specialisation float,cyme::sse,4 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::sse,4>::register_type
    _mm_ge<float,cyme::sse,4>(simd_trait<float,cyme::sse,4>::register_type xmm0){
        __m128i tmp0 =  _mm_castps_si128(xmm0.r0);
        __m128i tmp1 =  _mm_castps_si128(xmm0.r1);
        __m128i tmp2 =  _mm_castps_si128(xmm0.r2);
        __m128i tmp3 =  _mm_castps_si128(xmm0.r3);
        tmp0 = _mm_srli_epi32(tmp0,23);
        tmp1 = _mm_srli_epi32(tmp1,23);
        tmp2 = _mm_srli_epi32(tmp2,23);
        tmp3 = _mm_srli_epi32(tmp3,23);
        tmp0 = _mm_sub_epi32(tmp0, _mm_set1_epi32(127));
        tmp1 = _mm_sub_epi32(tmp1, _mm_set1_epi32(127));
        tmp2 = _mm_sub_epi32(tmp2, _mm_set1_epi32(127));
        tmp3 = _mm_sub_epi32(tmp3, _mm_set1_epi32(127));
        return simd_trait<float,cyme::sse,4>::register_type(_mm_cvtepi32_ps(tmp0),
                                                            _mm_cvtepi32_ps(tmp1),
                                                            _mm_cvtepi32_ps(tmp2),
                                                            _mm_cvtepi32_ps(tmp3));
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
     specialisation float,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,1>::register_type
    _mm_gf<float,cyme::sse,1>(simd_trait<float,cyme::sse,1>::register_type xmm0){
        __m128i tmp =  _mm_castps_si128(xmm0);
        tmp = _mm_and_si128(tmp,_mm_set1_epi32(0x7fffff));
        tmp = _mm_add_epi32(tmp,_mm_set1_epi32(0x3f800000));
        return _mm_castsi128_ps(tmp);
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
     specialisation float,cyme::sse,2 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::sse,2>::register_type
    _mm_gf<float,cyme::sse,2>(simd_trait<float,cyme::sse,2>::register_type xmm0){
        __m128i tmp0 =  _mm_castps_si128(xmm0.r0);
        __m128i tmp1 =  _mm_castps_si128(xmm0.r1);
        tmp0 = _mm_and_si128(tmp0,_mm_set1_epi32(0x7fffff));
        tmp1 = _mm_and_si128(tmp1,_mm_set1_epi32(0x7fffff));
        tmp0 = _mm_add_epi32(tmp0,_mm_set1_epi32(0x3f800000));
        tmp1 = _mm_add_epi32(tmp1,_mm_set1_epi32(0x3f800000));
        return simd_trait<float,cyme::sse,2>::register_type(_mm_castsi128_ps(tmp0),
                                                            _mm_castsi128_ps(tmp1));
    }

    /**
      Extract the fraction of floating-point exponent (64-bit) elements and store the results in dst.
     specialisation float,cyme::sse,4 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::sse,4>::register_type
    _mm_gf<float,cyme::sse,4>(simd_trait<float,cyme::sse,4>::register_type xmm0){
        __m128i tmp0 =  _mm_castps_si128(xmm0.r0);
        __m128i tmp1 =  _mm_castps_si128(xmm0.r1);
        __m128i tmp2 =  _mm_castps_si128(xmm0.r2);
        __m128i tmp3 =  _mm_castps_si128(xmm0.r3);
        tmp0 = _mm_and_si128(tmp0,_mm_set1_epi32(0x7fffff));
        tmp1 = _mm_and_si128(tmp1,_mm_set1_epi32(0x7fffff));
        tmp2 = _mm_and_si128(tmp2,_mm_set1_epi32(0x7fffff));
        tmp3 = _mm_and_si128(tmp3,_mm_set1_epi32(0x7fffff));
        tmp0 = _mm_add_epi32(tmp0,_mm_set1_epi32(0x3f800000));
        tmp1 = _mm_add_epi32(tmp1,_mm_set1_epi32(0x3f800000));
        tmp2 = _mm_add_epi32(tmp2,_mm_set1_epi32(0x3f800000));
        tmp3 = _mm_add_epi32(tmp3,_mm_set1_epi32(0x3f800000));
        return simd_trait<float,cyme::sse,4>::register_type(_mm_castsi128_ps(tmp0),
                                                            _mm_castsi128_ps(tmp1),
                                                            _mm_castsi128_ps(tmp2),
                                                            _mm_castsi128_ps(tmp3));
    }

    /**
      Compute 1/recsqrt (32-bit) floating point elements in xmm0 to packed double-precision (64-bit)
     floating-point elements, and store the results in dst.
     precision 12 bits
     specialisation float,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,1>::register_type
    _mm_rsqrt<float,cyme::sse,1>(simd_trait<float,cyme::sse,1>::register_type xmm0){
        return _mm_rsqrt_ps(xmm0);
    }

    /**
      Compute 1/recsqrt (32-bit) floating point elements in xmm0 to packed double-precision (64-bit)
     floating-point elements, and store the results in dst.
     precision 12 bits
     specialisation float,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,2>::register_type
    _mm_rsqrt<float,cyme::sse,2>(simd_trait<float,cyme::sse,2>::register_type xmm0){
        return simd_trait<float,cyme::sse,2>::register_type(_mm_rsqrt_ps(xmm0.r0),
                                                            _mm_rsqrt_ps(xmm0.r1));
    }

    /**
      Compute 1/recsqrt (32-bit) floating point elements in xmm0 to packed double-precision (64-bit)
     floating-point elements, and store the results in dst.
     precision 12 bits
     specialisation float,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,4>::register_type
    _mm_rsqrt<float,cyme::sse,4>(simd_trait<float,cyme::sse,4>::register_type xmm0){
        return simd_trait<float,cyme::sse,4>::register_type(_mm_rsqrt_ps(xmm0.r0),
                                                            _mm_rsqrt_ps(xmm0.r1),
                                                            _mm_rsqrt_ps(xmm0.r2),
                                                            _mm_rsqrt_ps(xmm0.r3));
    }

    /**
      Compute sqrt (32-bit) floating point elements in xmm0 to packed double-precision (64-bit)
     floating-point elements, and store the results in dst.
     specialisation float,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,1>::register_type
    _mm_sqrt<float,cyme::sse,1>(simd_trait<float,cyme::sse,1>::register_type xmm0){
        return _mm_sqrt_ps(xmm0);
    }


    /**
      Compute sqrt (32-bit) floating point elements in xmm0 to packed double-precision (64-bit)
     floating-point elements, and store the results in dst.
     specialisation float,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,2>::register_type
    _mm_sqrt<float,cyme::sse,2>(simd_trait<float,cyme::sse,2>::register_type xmm0){
        return simd_trait<float,cyme::sse,2>::register_type(_mm_sqrt_ps(xmm0.r0),
                                                            _mm_sqrt_ps(xmm0.r1));
    }

    /**
      Compute sqrt (32-bit) floating point elements in xmm0 to packed double-precision (64-bit)
     floating-point elements, and store the results in dst.
     specialisation float,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,4>::register_type
    _mm_sqrt<float,cyme::sse,4>(simd_trait<float,cyme::sse,4>::register_type xmm0){
        return simd_trait<float,cyme::sse,4>::register_type(_mm_sqrt_ps(xmm0.r0),
                                                            _mm_sqrt_ps(xmm0.r1),
                                                            _mm_sqrt_ps(xmm0.r2),
                                                            _mm_sqrt_ps(xmm0.r3));
    }

#ifdef __INTEL_COMPILER
    /**
        Compute the exponential value of e raised to the power of packed single-precision (32-bit)
     floating-point elements in xmm0, and store the results in dst.
     specialisation float,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,1>::register_type
    _mm_exp<float,cyme::sse,1>(simd_trait<float,cyme::sse,1>::register_type xmm0){
        return _mm_exp_ps(xmm0);
    }

    /**
        Compute the exponential value of e raised to the power of packed single-precision (32-bit)
     floating-point elements in xmm0, and store the results in dst.
     specialisation float,cyme::sse,2 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::sse,2>::register_type
    _mm_exp<float,cyme::sse,2>(simd_trait<float,cyme::sse,2>::register_type xmm0){
        return simd_trait<float,cyme::sse,2>::register_type(_mm_exp_ps(xmm0.r0),
                                                            _mm_exp_ps(xmm0.r1));
    }

    /**
        Compute the exponential value of e raised to the power of packed single-precision (32-bit)
     floating-point elements in xmm0, and store the results in dst.
     specialisation float,cyme::sse,4 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::sse,4>::register_type
    _mm_exp<float,cyme::sse,4>(simd_trait<float,cyme::sse,4>::register_type xmm0){
        return simd_trait<float,cyme::sse,4>::register_type(_mm_exp_ps(xmm0.r0),
                                                            _mm_exp_ps(xmm0.r1),
                                                            _mm_exp_ps(xmm0.r2),
                                                            _mm_exp_ps(xmm0.r3));
    }

    /**
        Compute the logarithm value of e raised to the power of packed single-precision (32-bit)
     floating-point elements in xmm0, and store the results in dst.
     specialisation float,cyme::sse,1 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::sse,1>::register_type
    _mm_log<float,cyme::sse,1>(simd_trait<float,cyme::sse,1>::register_type xmm0){
        return _mm_log_ps(xmm0);
    }

    /**
        Compute the logarithm value of e raised to the power of packed single-precision (32-bit)
     floating-point elements in xmm0, and store the results in dst.
     specialisation float,cyme::sse,2 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::sse,2>::register_type
    _mm_log<float,cyme::sse,2>(simd_trait<float,cyme::sse,2>::register_type xmm0){
        return simd_trait<float,cyme::sse,2>::register_type(_mm_log_ps(xmm0.r0),
                                                            _mm_log_ps(xmm0.r1));
    }

    /**
        Compute the logarithm value of e raised to the power of packed single-precision (32-bit)
     floating-point elements in xmm0, and store the results in dst.
     specialisation float,cyme::sse,4 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::sse,4>::register_type
    _mm_log<float,cyme::sse,4>(simd_trait<float,cyme::sse,4>::register_type xmm0){
        return simd_trait<float,cyme::sse,4>::register_type(_mm_log_ps(xmm0.r0),
                                                            _mm_log_ps(xmm0.r1),
                                                            _mm_log_ps(xmm0.r2),
                                                            _mm_log_ps(xmm0.r3));
    }
#else
    /**
        Compute the exponential value of e raised to the power of packed single-precision (32-bit)
     floating-point elements in xmm0, and store the results in dst.
     specialisation float,cyme::sse,1 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,1>::register_type
    _mm_exp<float,cyme::sse,1>(simd_trait<float,cyme::sse,1>::register_type xmm0){
        return __svml_expf4(xmm0);
    }

    /**
        Compute the exponential value of e raised to the power of packed single-precision (32-bit)
     floating-point elements in xmm0, and store the results in dst.
     specialisation float,cyme::sse,2 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,2>::register_type
    _mm_exp<float,cyme::sse,2>(simd_trait<float,cyme::sse,2>::register_type xmm0){
        return simd_trait<float,cyme::sse,2>::register_type(__svml_expf4(xmm0.r0),
                                                            __svml_expf4(xmm0.r1));
    }

    /**
        Compute the exponential value of e raised to the power of packed single-precision (32-bit)
     floating-point elements in xmm0, and store the results in dst.
     specialisation float,cyme::sse,4 regs
     */
    template<>
    forceinline simd_trait<float,cyme::sse,4>::register_type
    _mm_exp<float,cyme::sse,4>(simd_trait<float,cyme::sse,4>::register_type xmm0){
        return simd_trait<float,cyme::sse,4>::register_type(__svml_expf4(xmm0.r0),
                                                            __svml_expf4(xmm0.r1),
                                                            __svml_expf4(xmm0.r2),
                                                            __svml_expf4(xmm0.r3));
    }

    /**
        Compute the logarithm value of e raised to the power of packed single-precision (32-bit)
     floating-point elements in xmm0, and store the results in dst.
     specialisation float,cyme::sse,1 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::sse,1>::register_type
    _mm_log<float,cyme::sse,1>(simd_trait<float,cyme::sse,1>::register_type xmm0){
        return __svml_logf4(xmm0);
    }

    /**
        Compute the logarithm value of e raised to the power of packed single-precision (32-bit)
     floating-point elements in xmm0, and store the results in dst.
     specialisation float,cyme::sse,2 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::sse,2>::register_type
    _mm_log<float,cyme::sse,2>(simd_trait<float,cyme::sse,2>::register_type xmm0){
        return simd_trait<float,cyme::sse,2>::register_type(__svml_logf4(xmm0.r0),
                                                            __svml_logf4(xmm0.r1));
    }

    /**
        Compute the logarithm value of e raised to the power of packed single-precision (32-bit)
     floating-point elements in xmm0, and store the results in dst.
     specialisation float,cyme::sse,4 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::sse,4>::register_type
    _mm_log<float,cyme::sse,4>(simd_trait<float,cyme::sse,4>::register_type xmm0){
        return simd_trait<float,cyme::sse,4>::register_type(__svml_logf4(xmm0.r0),
                                                            __svml_logf4(xmm0.r1),
                                                            __svml_logf4(xmm0.r2),
                                                            __svml_logf4(xmm0.r3));
    }
#endif

#ifdef __FMA__
    /**
      Multiply packed single-precision (32-bit) floating-point elements in xmm0 and xmm1,
     add the intermediate result to packed elements in xmm2, and store the results in dst.
     specialisation float,cyme::sse,1 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::sse,1>::register_type
    _mm_fma<float,cyme::sse,1>(simd_trait<float,cyme::sse,1>::register_type xmm0,
                                 simd_trait<float,cyme::sse,1>::register_type xmm1,
                                 simd_trait<float,cyme::sse,1>::register_type xmm2){
        return _mm_fmadd_ps(xmm0, xmm1, xmm2);
    }

    /**
      Multiply packed single-precision (32-bit) floating-point elements in xmm0 and xmm1,
     add the intermediate result to packed elements in xmm2, and store the results in dst.
     specialisation float,cyme::sse,2 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::sse,2>::register_type
    _mm_fma<float,cyme::sse,2>(simd_trait<float,cyme::sse,2>::register_type xmm0,
                                 simd_trait<float,cyme::sse,2>::register_type xmm1,
                                 simd_trait<float,cyme::sse,2>::register_type xmm2){
        return simd_trait<float,cyme::sse,2>::register_type(_mm_fmadd_ps(xmm0.r0, xmm1.r0, xmm2.r0),
                                                            _mm_fmadd_ps(xmm0.r1, xmm1.r1, xmm2.r1));
    }

    /**
      Multiply packed single-precision (32-bit) floating-point elements in xmm0 and xmm1,
     add the intermediate result to packed elements in xmm2, and store the results in dst.
     specialisation float,cyme::sse,4 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::sse,4>::register_type
    _mm_fma<float,cyme::sse,4>(simd_trait<float,cyme::sse,4>::register_type xmm0,
                                 simd_trait<float,cyme::sse,4>::register_type xmm1,
                                 simd_trait<float,cyme::sse,4>::register_type xmm2){
        return simd_trait<float,cyme::sse,4>::register_type(_mm_fmadd_ps(xmm0.r0, xmm1.r0, xmm2.r0),
                                                            _mm_fmadd_ps(xmm0.r1, xmm1.r1, xmm2.r1),
                                                            _mm_fmadd_ps(xmm0.r2, xmm1.r2, xmm2.r2),
                                                            _mm_fmadd_ps(xmm0.r3, xmm1.r3, xmm2.r3));
    }

    /**
      Multiply packed single-precision (32-bit) floating-point elements in xmm0 and xmm1,
     add the negated intermediate result to packed elements in xmm2, and store the results in dst.
     specialisation float,cyme::sse,1 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::sse,1>::register_type
    _mm_nfma<float,cyme::sse,1>(simd_trait<float,cyme::sse,1>::register_type xmm0,
                                  simd_trait<float,cyme::sse,1>::register_type xmm1,
                                  simd_trait<float,cyme::sse,1>::register_type xmm2){
        return _mm_fnmadd_ps(xmm0, xmm1, xmm2);
    }

    /**
      Multiply packed single-precision (32-bit) floating-point elements in xmm0 and xmm1,
     add the negated intermediate result to packed elements in xmm2, and store the results in dst.
     specialisation float,cyme::sse,2 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::sse,2>::register_type
    _mm_nfma<float,cyme::sse,2>(simd_trait<float,cyme::sse,2>::register_type xmm0,
                                  simd_trait<float,cyme::sse,2>::register_type xmm1,
                                  simd_trait<float,cyme::sse,2>::register_type xmm2){
        return simd_trait<float,cyme::sse,2>::register_type(_mm_fnmadd_ps(xmm0.r0, xmm1.r0, xmm2.r0),
                                                            _mm_fnmadd_ps(xmm0.r1, xmm1.r1, xmm2.r1));
    }

    /**
      Multiply packed single-precision (32-bit) floating-point elements in xmm0 and xmm1,
     add the negated intermediate result to packed elements in xmm2, and store the results in dst.
     specialisation float,cyme::sse,4 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::sse,4>::register_type
    _mm_nfma<float,cyme::sse,4>(simd_trait<float,cyme::sse,4>::register_type xmm0,
                                  simd_trait<float,cyme::sse,4>::register_type xmm1,
                                  simd_trait<float,cyme::sse,4>::register_type xmm2){
        return simd_trait<float,cyme::sse,4>::register_type(_mm_fnmadd_ps(xmm0.r0, xmm1.r0, xmm2.r0),
                                                            _mm_fnmadd_ps(xmm0.r1, xmm1.r1, xmm2.r1),
                                                            _mm_fnmadd_ps(xmm0.r2, xmm1.r2, xmm2.r2),
                                                            _mm_fnmadd_ps(xmm0.r3, xmm1.r3, xmm2.r3));
    }

    /**
      Multiply packed single-precision (32-bit) floating-point elements in xmm0 and xmm1,
     subtract packed elements in xmm2 from the intermediate result, and store the results in dst.
     specialisation float,cyme::sse,1 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::sse,1>::register_type
    _mm_fms<float,cyme::sse,1>(simd_trait<float,cyme::sse,1>::register_type xmm0,
                                 simd_trait<float,cyme::sse,1>::register_type xmm1,
                                 simd_trait<float,cyme::sse,1>::register_type xmm2){
        return _mm_fmsub_ps(xmm0, xmm1, xmm2);
    }

    /**
      Multiply packed single-precision (32-bit) floating-point elements in xmm0 and xmm1,
     subtract packed elements in xmm2 from the intermediate result, and store the results in dst.
     specialisation float,cyme::sse,2 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::sse,2>::register_type
    _mm_fms<float,cyme::sse,2>(simd_trait<float,cyme::sse,2>::register_type xmm0,
                                 simd_trait<float,cyme::sse,2>::register_type xmm1,
                                  simd_trait<float,cyme::sse,2>::register_type xmm2){
        return simd_trait<float,cyme::sse,2>::register_type(_mm_fmsub_ps(xmm0.r0, xmm1.r0, xmm2.r0),
                                                            _mm_fmsub_ps(xmm0.r1, xmm1.r1, xmm2.r1));
    }

    /**
      Multiply packed single-precision (32-bit) floating-point elements in xmm0 and xmm1,
     subtract packed elements in xmm2 from the intermediate result, and store the results in dst.
     specialisation float,cyme::sse,4 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::sse,4>::register_type
    _mm_fms<float,cyme::sse,4>(simd_trait<float,cyme::sse,4>::register_type xmm0,
                                 simd_trait<float,cyme::sse,4>::register_type xmm1,
                                 simd_trait<float,cyme::sse,4>::register_type xmm2){
        return simd_trait<float,cyme::sse,4>::register_type(_mm_fmsub_ps(xmm0.r0, xmm1.r0, xmm2.r0),
                                                            _mm_fmsub_ps(xmm0.r1, xmm1.r1, xmm2.r1),
                                                            _mm_fmsub_ps(xmm0.r2, xmm1.r2, xmm2.r2),
                                                            _mm_fmsub_ps(xmm0.r3, xmm1.r3, xmm2.r3));
    }

    /**
     Multiply packed single-precision (32-bit) floating-point elements in xmm0 and xmm1,
     subtract packed elements in xmm2 from the negated intermediate result, and store the results in dst.
     specialisation float,cyme::sse,1 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::sse,1>::register_type
    _mm_nfms<float,cyme::sse,1>(simd_trait<float,cyme::sse,1>::register_type xmm0,
                                  simd_trait<float,cyme::sse,1>::register_type xmm1,
                                  simd_trait<float,cyme::sse,1>::register_type xmm2){
        return _mm_fnmsub_ps(xmm0, xmm1, xmm2);
    }

    /**
     Multiply packed single-precision (32-bit) floating-point elements in xmm0 and xmm1,
     subtract packed elements in xmm2 from the negated intermediate result, and store the results in dst.
     specialisation float,cyme::sse,2 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::sse,2>::register_type
    _mm_nfms<float,cyme::sse,2>(simd_trait<float,cyme::sse,2>::register_type xmm0,
                                  simd_trait<float,cyme::sse,2>::register_type xmm1,
                                  simd_trait<float,cyme::sse,2>::register_type xmm2){
        return simd_trait<float,cyme::sse,2>::register_type(_mm_fnmsub_ps(xmm0.r0, xmm1.r0, xmm2.r0),
                                                             _mm_fnmsub_ps(xmm0.r1, xmm1.r1, xmm2.r1));
    }

    /**
     Multiply packed single-precision (32-bit) floating-point elements in xmm0 and xmm1,
     subtract packed elements in xmm2 from the negated intermediate result, and store the results in dst.
     specialisation float,cyme::sse,4 regs
     */
    template<>
    forceinline  simd_trait<float,cyme::sse,4>::register_type
    _mm_nfms<float,cyme::sse,4>(simd_trait<float,cyme::sse,4>::register_type xmm0,
                                  simd_trait<float,cyme::sse,4>::register_type xmm1,
                                  simd_trait<float,cyme::sse,4>::register_type xmm2){
        return simd_trait<float,cyme::sse,4>::register_type(_mm_fnmsub_ps(xmm0.r0, xmm1.r0, xmm2.r0),
                                                            _mm_fnmsub_ps(xmm0.r1, xmm1.r1, xmm2.r1),
                                                            _mm_fnmsub_ps(xmm0.r2, xmm1.r2, xmm2.r2),
                                                            _mm_fnmsub_ps(xmm0.r3, xmm1.r3, xmm2.r3));
    }

#endif //end FMA

} //end namespace

#endif
