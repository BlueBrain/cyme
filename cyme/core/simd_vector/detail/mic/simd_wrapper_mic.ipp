/*
* Cyme - simd_wrapper_mic.ipp, Copyright (c), 2014,
* Timothee Ewart - Swiss Federal Institute of technology in Lausanne,
* timothee.ewart@epfl.ch,
* All rights reserved.
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

#ifndef CYME_SIMD_WRAPPER_MIC_IPP
#define CYME_SIMD_WRAPPER_MIC_IPP

namespace numeric{

    /**
     \brief Broadcast double-precision (64-bit) floating-point value a to all elements of dst.
     */
    template<>
    forceinline  simd_trait<double,memory::mic,1>::register_type _mm_load1<double,memory::mic,1>(const simd_trait<double,memory::mic,1>::value_type& a){
        return _mm512_set1_pd(a);
    }

    template<>
    forceinline  simd_trait<double,memory::mic,2>::register_type _mm_load1<double,memory::mic,2>(const simd_trait<double,memory::mic,2>::value_type& a){
        return simd_trait<double,memory::mic,2>::register_type(_mm512_set1_pd(a),_mm512_set1_pd(a));
    }

    template<>
    forceinline  simd_trait<double,memory::mic,4>::register_type _mm_load1<double,memory::mic,4>(const simd_trait<double,memory::mic,4>::value_type& a){
        return simd_trait<double,memory::mic,4>::register_type(_mm512_set1_pd(a),_mm512_set1_pd(a),_mm512_set1_pd(a),_mm512_set1_pd(a));
    }
    /**
     \brief Load 512-bits (composed of 8 packed double-precision (64-bit) floating-point elements) from memory into dst. mem_addr must be aligned on a 64-byte boundary or a general-protection exception will be generated.
     */
    template<>
    forceinline  simd_trait<double,memory::mic,1>::register_type _mm_load<double,memory::mic,1>(simd_trait<double,memory::mic,1>::const_pointer a){
        return _mm512_load_pd(a);
    }

    template<>
    forceinline  simd_trait<double,memory::mic,2>::register_type _mm_load<double,memory::mic,2>(simd_trait<double,memory::mic,2>::const_pointer a){
        return simd_trait<double,memory::mic,2>::register_type(_mm512_load_pd(a),_mm512_load_pd(a+8));
    }

    template<>
    forceinline  simd_trait<double,memory::mic,4>::register_type _mm_load<double,memory::mic,4>(simd_trait<double,memory::mic,4>::const_pointer a){
        return simd_trait<double,memory::mic,4>::register_type(_mm512_load_pd(a),_mm512_load_pd(a+8),_mm512_load_pd(a+16),_mm512_load_pd(a+24));
    }
    /**
      \brief   Store 512-bits (composed of 8 packed double-precision (64-bit) floating-point elements) from a into memory. mem_addr must be aligned on a 64-byte boundary or a general-protection exception will be generated.
     */
    template<>
    void _mm_store<double,memory::mic,1>( simd_trait<double,memory::mic,1>::register_type xmm0,  simd_trait<double,memory::mic,1>::pointer a){
        _mm512_store_pd(a,xmm0);
    }

    template<>
    forceinline void _mm_store<double,memory::mic,2>( simd_trait<double,memory::mic,2>::register_type xmm0,  simd_trait<double,memory::mic,2>::pointer a){
        _mm512_store_pd(a,xmm0.r0);
        _mm512_store_pd(a+8,xmm0.r1);
    }

    template<>
    forceinline void _mm_store<double,memory::mic,4>( simd_trait<double,memory::mic,4>::register_type xmm0,  simd_trait<double,memory::mic,4>::pointer a){
        _mm512_store_pd(a,xmm0.r0);
        _mm512_store_pd(a+8,xmm0.r1);
        _mm512_store_pd(a+16,xmm0.r2);
        _mm512_store_pd(a+24,xmm0.r3);
    }
    /**
     \brief Multiply packed double-precision (64-bit) floating-point elements in xmm0 and xmm1, and store the results in dst.
     */
    template<>
    forceinline  simd_trait<double,memory::mic,1>::register_type _mm_mul<double,memory::mic,1>( simd_trait<double,memory::mic,1>::register_type xmm0,  simd_trait<double,memory::mic,1>::register_type xmm1){
        return _mm512_mul_pd(xmm0, xmm1);
    }

    template<>
    forceinline  simd_trait<double,memory::mic,2>::register_type _mm_mul<double,memory::mic,2>( simd_trait<double,memory::mic,2>::register_type xmm0,  simd_trait<double,memory::mic,2>::register_type xmm1){
        return simd_trait<double,memory::mic,2>::register_type(
                        _mm512_mul_pd(xmm0.r0, xmm1.r0),
                        _mm512_mul_pd(xmm0.r1, xmm1.r1)
                      );
    }

    template<>
    forceinline  simd_trait<double,memory::mic,4>::register_type _mm_mul<double,memory::mic,4>( simd_trait<double,memory::mic,4>::register_type xmm0,  simd_trait<double,memory::mic,4>::register_type xmm1){
        return simd_trait<double,memory::mic,4>::register_type(
                        _mm512_mul_pd(xmm0.r0, xmm1.r0),
                        _mm512_mul_pd(xmm0.r1, xmm1.r1),
                        _mm512_mul_pd(xmm0.r2, xmm1.r2),
                        _mm512_mul_pd(xmm0.r3, xmm1.r3)
                      );
    }
    /**
     \brief Divide packed double-precision (64-bit) floating-point elements in xmm0 and xmm1, and store the results in dst.
     */
    template<>
    forceinline  simd_trait<double,memory::mic,1>::register_type _mm_div<double,memory::mic,1>( simd_trait<double,memory::mic,1>::register_type xmm0,  simd_trait<double,memory::mic,1>::register_type xmm1){
        return _mm512_div_pd(xmm0, xmm1);
    }

    template<>
    forceinline  simd_trait<double,memory::mic,2>::register_type _mm_div<double,memory::mic,2>( simd_trait<double,memory::mic,2>::register_type xmm0,  simd_trait<double,memory::mic,2>::register_type xmm1){
        return simd_trait<double,memory::mic,2>::register_type(
                        _mm512_div_pd(xmm0.r0, xmm1.r0),
                        _mm512_div_pd(xmm0.r1, xmm1.r1)
                      );
    }

    template<>
    forceinline  simd_trait<double,memory::mic,4>::register_type _mm_div<double,memory::mic,4>( simd_trait<double,memory::mic,4>::register_type xmm0,  simd_trait<double,memory::mic,4>::register_type xmm1){
        return simd_trait<double,memory::mic,4>::register_type(
                        _mm512_div_pd(xmm0.r0, xmm1.r0),
                        _mm512_div_pd(xmm0.r1, xmm1.r1),
                        _mm512_div_pd(xmm0.r2, xmm1.r2),
                        _mm512_div_pd(xmm0.r3, xmm1.r3)
                      );
    }
    /**
     \brief Add packed double-precision (64-bit) floating-point elements in xmm0 and xmm1, and store the results in dst.
     */
    template<>
    forceinline  simd_trait<double,memory::mic,1>::register_type _mm_add<double,memory::mic,1>( simd_trait<double,memory::mic,1>::register_type xmm0,  simd_trait<double,memory::mic,1>::register_type xmm1){
        return _mm512_add_pd(xmm0, xmm1);
    }

    template<>
    forceinline  simd_trait<double,memory::mic,2>::register_type _mm_add<double,memory::mic,2>( simd_trait<double,memory::mic,2>::register_type xmm0,  simd_trait<double,memory::mic,2>::register_type xmm1){
        return simd_trait<double,memory::mic,2>::register_type(
                        _mm512_add_pd(xmm0.r0, xmm1.r0),
                        _mm512_add_pd(xmm0.r1, xmm1.r1)
                      );
    }

    template<>
    forceinline  simd_trait<double,memory::mic,4>::register_type _mm_add<double,memory::mic,4>( simd_trait<double,memory::mic,4>::register_type xmm0,  simd_trait<double,memory::mic,4>::register_type xmm1){
        return simd_trait<double,memory::mic,4>::register_type(
                        _mm512_add_pd(xmm0.r0, xmm1.r0),
                        _mm512_add_pd(xmm0.r1, xmm1.r1),
                        _mm512_add_pd(xmm0.r2, xmm1.r2),
                        _mm512_add_pd(xmm0.r3, xmm1.r3)
                      );
    }
    /**
     \brief Substract packed double-precision (64-bit) floating-point elements in xmm0 and xmm1, and store the results in dst.
     */
    template<>
    forceinline  simd_trait<double,memory::mic,1>::register_type _mm_sub<double,memory::mic,1>( simd_trait<double,memory::mic,1>::register_type xmm0,  simd_trait<double,memory::mic,1>::register_type xmm1){
        return _mm512_sub_pd(xmm0, xmm1);
    }

    template<>
    forceinline  simd_trait<double,memory::mic,2>::register_type _mm_sub<double,memory::mic,2>( simd_trait<double,memory::mic,2>::register_type xmm0,  simd_trait<double,memory::mic,2>::register_type xmm1){
        return simd_trait<double,memory::mic,2>::register_type(
                        _mm512_sub_pd(xmm0.r0, xmm1.r0),
                        _mm512_sub_pd(xmm0.r1, xmm1.r1)
                      );
    }

    template<>
    forceinline  simd_trait<double,memory::mic,4>::register_type _mm_sub<double,memory::mic,4>( simd_trait<double,memory::mic,4>::register_type xmm0,  simd_trait<double,memory::mic,4>::register_type xmm1){
        return simd_trait<double,memory::mic,4>::register_type(
                        _mm512_sub_pd(xmm0.r0, xmm1.r0),
                        _mm512_sub_pd(xmm0.r1, xmm1.r1),
                        _mm512_sub_pd(xmm0.r2, xmm1.r2),
                        _mm512_sub_pd(xmm0.r3, xmm1.r3)
                      );
    }

    /**
        \brief Negate packed double-precision (64-bit) floating-point elements in xmm0 to packed double-precision (64-bit) floating-point elements, and store the results in dst.
    */
    template<>
    forceinline  simd_trait<double,memory::mic,1>::register_type _mm_neg<double,memory::mic,1>(simd_trait<double,memory::mic,1>::register_type xmm0){
        return _mm512_castsi512_pd(_mm512_xor_si512(_mm512_castpd_si512(xmm0),_mm512_set1_epi64(0x8000000000000000)));
    }

    template<>
    forceinline  simd_trait<double,memory::mic,2>::register_type _mm_neg<double,memory::mic,2>(simd_trait<double,memory::mic,2>::register_type xmm0){
        simd_trait<int,memory::mic,1>::register_type mask =  _mm512_set1_epi64(0x8000000000000000);
        return simd_trait<double,memory::mic,2>::register_type(
            _mm512_castsi512_pd(_mm512_xor_si512(_mm512_castpd_si512(xmm0.r0), mask)),
            _mm512_castsi512_pd(_mm512_xor_si512(_mm512_castpd_si512(xmm0.r1), mask))
        );
    }

    template<>
    forceinline  simd_trait<double,memory::mic,4>::register_type _mm_neg<double,memory::mic,4>(simd_trait<double,memory::mic,4>::register_type xmm0){
        simd_trait<int,memory::mic,1>::register_type mask =  _mm512_set1_epi64(0x8000000000000000);
        return simd_trait<double,memory::mic,4>::register_type(
            _mm512_castsi512_pd(_mm512_xor_si512(_mm512_castpd_si512(xmm0.r0), mask)),
            _mm512_castsi512_pd(_mm512_xor_si512(_mm512_castpd_si512(xmm0.r1), mask)),
            _mm512_castsi512_pd(_mm512_xor_si512(_mm512_castpd_si512(xmm0.r2), mask)),
            _mm512_castsi512_pd(_mm512_xor_si512(_mm512_castpd_si512(xmm0.r3), mask))
        );
    }
    /**
     \brief Round the packed double-precision (32-bit) floating-point elements in xmm0 down to an integer value, and store the results as packed single precision (32-bits).
     */
    template<>
    forceinline  simd_trait<int,memory::mic,1>::register_type _mm_floor<double,memory::mic,1>(simd_trait<double,memory::mic,1>::register_type xmm0){
        return  _mm512_castpd_si512(_mm512_floor_pd(xmm0));
    }

    template<>
    forceinline  simd_trait<int,memory::mic,2>::register_type _mm_floor<double,memory::mic,2>( simd_trait<double,memory::mic,2>::register_type xmm0){
        return simd_trait<int,memory::mic,2>::register_type(
            _mm512_castpd_si512(_mm512_floor_pd(xmm0.r0)),
            _mm512_castpd_si512(_mm512_floor_pd(xmm0.r1))
        );
    }

    template<>
    forceinline  simd_trait<int,memory::mic,4>::register_type _mm_floor<double,memory::mic,4>( simd_trait<double,memory::mic,4>::register_type xmm0){
        return simd_trait<int,memory::mic,4>::register_type(
            _mm512_castpd_si512(_mm512_floor_pd(xmm0.r0)),
            _mm512_castpd_si512(_mm512_floor_pd(xmm0.r1)),
            _mm512_castpd_si512(_mm512_floor_pd(xmm0.r2)),
            _mm512_castpd_si512(_mm512_floor_pd(xmm0.r3))
        );
    }
    /**
     \brief Convert packedi single precision (32-bit) in xmm0 to packed double-precision (64-bit) floating-point elements, and store the results in dst.
     */
    template<>
    forceinline  simd_trait<double,memory::mic,1>::register_type _mm_cast<double,memory::mic,1>(simd_trait<int,memory::mic,1>::register_type xmm0){
        return _mm512_castsi512_pd(xmm0);
    }

    template<>
    forceinline  simd_trait<double,memory::mic,2>::register_type _mm_cast<double,memory::mic,2>(simd_trait<int,memory::mic,2>::register_type xmm0){
        return simd_trait<double,memory::mic,2>::register_type(
            _mm512_castsi512_pd(xmm0.r0),
            _mm512_castsi512_pd(xmm0.r1)
        );
    }

    template<>
    forceinline  simd_trait<double,memory::mic,4>::register_type _mm_cast<double,memory::mic,4>(simd_trait<int,memory::mic,4>::register_type xmm0){
        return simd_trait<double,memory::mic,4>::register_type(
            _mm512_castsi512_pd(xmm0.r0),
            _mm512_castsi512_pd(xmm0.r1),
            _mm512_castsi512_pd(xmm0.r2),
            _mm512_castsi512_pd(xmm0.r3)
        );
    }
    /**
     \brief Compute 2^k packed integer (64-bit) elements in xmm0 to packed double-precision (64-bit) floating-point elements, and store the results in dest.
     \warning performed with float exponent, precision so so
     */
    template<>
    forceinline  simd_trait<double,memory::mic,1>::register_type _mm_twok<double,memory::mic,1>(simd_trait<int,memory::mic,1>::register_type xmm0){
/*       for debug
         #include <micvec.h>
         __declspec(align(64)) Is32vec16  test;
         test = Is32vec16(tmp0);
         std::cout<< std::hex << test << std::endl;
 hybrid float/double _mm512_cvtpslo_pd(_mm512_castsi512_ps(_mm512_sllv_epi32(_mm512_add_epi32(_mm512_cvtfxpnt_round_adjustps_epi32(xmm0, _MM_ROUND_MODE_TOWARD_ZERO, _MM_EXPADJ_NONE),_mm512_set1_epi32(127)),_mm512_set1_epi32(23)))); // hum ... calculate 2^n with float too much
*/
         __m512i tmp0 = _mm512_cvtfxpnt_roundpd_epi32lo(_mm512_castsi512_pd(xmm0), _MM_ROUND_MODE_TOWARD_ZERO); // double to uint32  A B C D - E F G H - 0 0 0 0 - 0 0 0 0
         tmp0 = _mm512_permute4f128_epi32(tmp0,_MM_PERM_BBAA);    // fill second part of the register by copy, there are empty A B C D -  A B C D - E F G H - E F G H
         tmp0 = _mm512_mask_swizzle_epi32(tmp0,0xF0F,tmp0,_MM_SWIZ_REG_CDAB);   // reshuffling step1 B A D C - A B C D - F E H G - E F G H
         tmp0 = _mm512_mask_swizzle_epi32(tmp0,0xFFFF,tmp0,_MM_SWIZ_REG_DACB);  // step2 A D B C - B C A D - E H F G - F G E H
         tmp0 = _mm512_mask_swizzle_epi32(tmp0,0xF0F,tmp0,_MM_SWIZ_REG_CDAB);   // step3 D A C B - B C A D - H E G F - F G E H // This 3 steps equivalent to >>32
         tmp0 = _mm512_mask_and_epi32(_mm512_setzero_epi32(),0xAAAA,tmp0, _mm512_set1_epi32(0xffffffff)); // 0 A 0 B 0 C 0 D 0 E 0 F 0 G 0 H
         tmp0 = _mm512_mask_add_epi32(_mm512_setzero_epi32(),0xAAAA,tmp0,_mm512_set1_epi32(1023)); // Preparing double: classic + 1023
         tmp0 = _mm512_mask_slli_epi32(_mm512_setzero_epi32(),0xAAAA,tmp0,20); // preparing double next >>20
         return _mm512_castsi512_pd(tmp0); // switch 32bit representation to double
    }

    template<>
    forceinline  simd_trait<double,memory::mic,2>::register_type _mm_twok<double,memory::mic,2>(simd_trait<int,memory::mic,2>::register_type xmm0){
         __m512i tmp0 = _mm512_cvtfxpnt_roundpd_epi32lo(_mm512_castsi512_pd(xmm0.r0), _MM_ROUND_MODE_TOWARD_ZERO); // double to uint32  A B C D - E F G H - 0 0 0 0 - 0 0 0 0
         __m512i tmp1 = _mm512_cvtfxpnt_roundpd_epi32lo(_mm512_castsi512_pd(xmm0.r1), _MM_ROUND_MODE_TOWARD_ZERO); // double to uint32  A B C D - E F G H - 0 0 0 0 - 0 0 0 0

         tmp0 = _mm512_permute4f128_epi32(tmp0,_MM_PERM_BBAA);    // fill second part of the register by copy, there are empty A B C D -  A B C D - E F G H - E F G H
         tmp1 = _mm512_permute4f128_epi32(tmp1,_MM_PERM_BBAA);    // fill second part of the register by copy, there are empty A B C D -  A B C D - E F G H - E F G H

         tmp0 = _mm512_mask_swizzle_epi32(tmp0,0xF0F,tmp0,_MM_SWIZ_REG_CDAB);   // reshuffling step1 B A D C - A B C D - F E H G - E F G H
         tmp1 = _mm512_mask_swizzle_epi32(tmp1,0xF0F,tmp1,_MM_SWIZ_REG_CDAB);   // reshuffling step1 B A D C - A B C D - F E H G - E F G H

         tmp0 = _mm512_mask_swizzle_epi32(tmp0,0xFFFF,tmp0,_MM_SWIZ_REG_DACB);  // step2 A D B C - B C A D - E H F G - F G E H
         tmp1 = _mm512_mask_swizzle_epi32(tmp1,0xFFFF,tmp1,_MM_SWIZ_REG_DACB);  // step2 A D B C - B C A D - E H F G - F G E H

         tmp0 = _mm512_mask_swizzle_epi32(tmp0,0xF0F,tmp0,_MM_SWIZ_REG_CDAB);   // step3 D A C B - B C A D - H E G F - F G E H // This 3 steps equivalent to >>32
         tmp1 = _mm512_mask_swizzle_epi32(tmp1,0xF0F,tmp1,_MM_SWIZ_REG_CDAB);   // step3 D A C B - B C A D - H E G F - F G E H // This 3 steps equivalent to >>32

         tmp0 = _mm512_mask_and_epi32(_mm512_setzero_epi32(),0xAAAA,tmp0, _mm512_set1_epi32(0xffffffff)); // 0 A 0 B 0 C 0 D 0 E 0 F 0 G 0 H
         tmp1 = _mm512_mask_and_epi32(_mm512_setzero_epi32(),0xAAAA,tmp1, _mm512_set1_epi32(0xffffffff)); // 0 A 0 B 0 C 0 D 0 E 0 F 0 G 0 H

         tmp0 = _mm512_mask_add_epi32(_mm512_setzero_epi32(),0xAAAA,tmp0,_mm512_set1_epi32(1023)); // Preparing double: classic + 1023
         tmp1 = _mm512_mask_add_epi32(_mm512_setzero_epi32(),0xAAAA,tmp1,_mm512_set1_epi32(1023)); // Preparing double: classic + 1023

         tmp0 = _mm512_mask_slli_epi32(_mm512_setzero_epi32(),0xAAAA,tmp0,20); // preparing double next >>20
         tmp1 = _mm512_mask_slli_epi32(_mm512_setzero_epi32(),0xAAAA,tmp1,20); // preparing double next >>20

         return simd_trait<double,memory::mic,2>::register_type(
             _mm512_castsi512_pd(tmp0),
             _mm512_castsi512_pd(tmp1)
         );
    }

    template<>
    forceinline  simd_trait<double,memory::mic,4>::register_type _mm_twok<double,memory::mic,4>(simd_trait<int,memory::mic,4>::register_type xmm0){
         __m512i tmp0 = _mm512_cvtfxpnt_roundpd_epi32lo(_mm512_castsi512_pd(xmm0.r0), _MM_ROUND_MODE_TOWARD_ZERO); // double to uint32  A B C D - E F G H - 0 0 0 0 - 0 0 0 0
         __m512i tmp1 = _mm512_cvtfxpnt_roundpd_epi32lo(_mm512_castsi512_pd(xmm0.r1), _MM_ROUND_MODE_TOWARD_ZERO); // double to uint32  A B C D - E F G H - 0 0 0 0 - 0 0 0 0
         __m512i tmp2 = _mm512_cvtfxpnt_roundpd_epi32lo(_mm512_castsi512_pd(xmm0.r2), _MM_ROUND_MODE_TOWARD_ZERO); // double to uint32  A B C D - E F G H - 0 0 0 0 - 0 0 0 0
         __m512i tmp3 = _mm512_cvtfxpnt_roundpd_epi32lo(_mm512_castsi512_pd(xmm0.r3), _MM_ROUND_MODE_TOWARD_ZERO); // double to uint32  A B C D - E F G H - 0 0 0 0 - 0 0 0 0

         tmp0 = _mm512_permute4f128_epi32(tmp0,_MM_PERM_BBAA);    // fill second part of the register by copy, there are empty A B C D -  A B C D - E F G H - E F G H
         tmp1 = _mm512_permute4f128_epi32(tmp1,_MM_PERM_BBAA);    // fill second part of the register by copy, there are empty A B C D -  A B C D - E F G H - E F G H
         tmp2 = _mm512_permute4f128_epi32(tmp2,_MM_PERM_BBAA);    // fill second part of the register by copy, there are empty A B C D -  A B C D - E F G H - E F G H
         tmp3 = _mm512_permute4f128_epi32(tmp3,_MM_PERM_BBAA);    // fill second part of the register by copy, there are empty A B C D -  A B C D - E F G H - E F G H

         tmp0 = _mm512_mask_swizzle_epi32(tmp0,0xF0F,tmp0,_MM_SWIZ_REG_CDAB);   // reshuffling step1 B A D C - A B C D - F E H G - E F G H
         tmp1 = _mm512_mask_swizzle_epi32(tmp1,0xF0F,tmp1,_MM_SWIZ_REG_CDAB);   // reshuffling step1 B A D C - A B C D - F E H G - E F G H
         tmp2 = _mm512_mask_swizzle_epi32(tmp2,0xF0F,tmp2,_MM_SWIZ_REG_CDAB);   // reshuffling step1 B A D C - A B C D - F E H G - E F G H
         tmp3 = _mm512_mask_swizzle_epi32(tmp3,0xF0F,tmp3,_MM_SWIZ_REG_CDAB);   // reshuffling step1 B A D C - A B C D - F E H G - E F G H

         tmp0 = _mm512_mask_swizzle_epi32(tmp0,0xFFFF,tmp0,_MM_SWIZ_REG_DACB);  // step2 A D B C - B C A D - E H F G - F G E H
         tmp1 = _mm512_mask_swizzle_epi32(tmp1,0xFFFF,tmp1,_MM_SWIZ_REG_DACB);  // step2 A D B C - B C A D - E H F G - F G E H
         tmp2 = _mm512_mask_swizzle_epi32(tmp2,0xFFFF,tmp2,_MM_SWIZ_REG_DACB);  // step2 A D B C - B C A D - E H F G - F G E H
         tmp3 = _mm512_mask_swizzle_epi32(tmp3,0xFFFF,tmp3,_MM_SWIZ_REG_DACB);  // step2 A D B C - B C A D - E H F G - F G E H

         tmp0 = _mm512_mask_swizzle_epi32(tmp0,0xF0F,tmp0,_MM_SWIZ_REG_CDAB);   // step3 D A C B - B C A D - H E G F - F G E H // This 3 steps equivalent to >>32
         tmp1 = _mm512_mask_swizzle_epi32(tmp1,0xF0F,tmp1,_MM_SWIZ_REG_CDAB);   // step3 D A C B - B C A D - H E G F - F G E H // This 3 steps equivalent to >>32
         tmp2 = _mm512_mask_swizzle_epi32(tmp2,0xF0F,tmp2,_MM_SWIZ_REG_CDAB);   // step3 D A C B - B C A D - H E G F - F G E H // This 3 steps equivalent to >>32
         tmp3 = _mm512_mask_swizzle_epi32(tmp3,0xF0F,tmp3,_MM_SWIZ_REG_CDAB);   // step3 D A C B - B C A D - H E G F - F G E H // This 3 steps equivalent to >>32

         tmp0 = _mm512_mask_and_epi32(_mm512_setzero_epi32(),0xAAAA,tmp0, _mm512_set1_epi32(0xffffffff)); // 0 A 0 B 0 C 0 D 0 E 0 F 0 G 0 H
         tmp1 = _mm512_mask_and_epi32(_mm512_setzero_epi32(),0xAAAA,tmp1, _mm512_set1_epi32(0xffffffff)); // 0 A 0 B 0 C 0 D 0 E 0 F 0 G 0 H
         tmp2 = _mm512_mask_and_epi32(_mm512_setzero_epi32(),0xAAAA,tmp2, _mm512_set1_epi32(0xffffffff)); // 0 A 0 B 0 C 0 D 0 E 0 F 0 G 0 H
         tmp3 = _mm512_mask_and_epi32(_mm512_setzero_epi32(),0xAAAA,tmp3, _mm512_set1_epi32(0xffffffff)); // 0 A 0 B 0 C 0 D 0 E 0 F 0 G 0 H

         tmp0 = _mm512_mask_add_epi32(_mm512_setzero_epi32(),0xAAAA,tmp0,_mm512_set1_epi32(1023)); // Preparing double: classic + 1023
         tmp1 = _mm512_mask_add_epi32(_mm512_setzero_epi32(),0xAAAA,tmp1,_mm512_set1_epi32(1023)); // Preparing double: classic + 1023
         tmp2 = _mm512_mask_add_epi32(_mm512_setzero_epi32(),0xAAAA,tmp2,_mm512_set1_epi32(1023)); // Preparing double: classic + 1023
         tmp3 = _mm512_mask_add_epi32(_mm512_setzero_epi32(),0xAAAA,tmp3,_mm512_set1_epi32(1023)); // Preparing double: classic + 1023

         tmp0 = _mm512_mask_slli_epi32(_mm512_setzero_epi32(),0xAAAA,tmp0,20); // preparing double next >>20
         tmp1 = _mm512_mask_slli_epi32(_mm512_setzero_epi32(),0xAAAA,tmp1,20); // preparing double next >>20
         tmp2 = _mm512_mask_slli_epi32(_mm512_setzero_epi32(),0xAAAA,tmp2,20); // preparing double next >>20
         tmp3 = _mm512_mask_slli_epi32(_mm512_setzero_epi32(),0xAAAA,tmp3,20); // preparing double next >>20

         return simd_trait<double,memory::mic,4>::register_type(
             _mm512_castsi512_pd(tmp0),
             _mm512_castsi512_pd(tmp1),
             _mm512_castsi512_pd(tmp2),
             _mm512_castsi512_pd(tmp3)
         );
    }
    /**
    \brief Compute the exponential value of e raised to the power of packed double-precision (64-bit) floating-point elements in xmm0, and store the results in dst.
    */
    template<>
    forceinline  simd_trait<double,memory::mic,1>::register_type _mm_exp<double,memory::mic,1>( simd_trait<double,memory::mic,1>::register_type xmm0){
        return _mm512_exp_pd(xmm0);
    }

    template<>
    forceinline  simd_trait<double,memory::mic,2>::register_type _mm_exp<double,memory::mic,2>( simd_trait<double,memory::mic,2>::register_type xmm0){
        return simd_trait<double,memory::mic,2>::register_type(
                         _mm512_exp_pd(xmm0.r0),
                         _mm512_exp_pd(xmm0.r1)
                      );
    }

    template<>
    forceinline  simd_trait<double,memory::mic,4>::register_type _mm_exp<double,memory::mic,4>( simd_trait<double,memory::mic,4>::register_type xmm0){
        return simd_trait<double,memory::mic,4>::register_type(
                         _mm512_exp_pd(xmm0.r0),
                         _mm512_exp_pd(xmm0.r1),
                         _mm512_exp_pd(xmm0.r2),
                         _mm512_exp_pd(xmm0.r3)
                      );
    }
    /**
     \brief   Compute the logarithm value of e raised to the power of packed single-precision (32-bit) floating-point elements in xmm0, and store the results in dst.
     */
    template<>
    forceinline  simd_trait<double,memory::mic,1>::register_type _mm_log<double,memory::mic,1>( simd_trait<double,memory::mic,1>::register_type xmm0){
        return _mm512_log_pd(xmm0);
    }

    template<>
    forceinline  simd_trait<double,memory::mic,2>::register_type _mm_log<double,memory::mic,2>( simd_trait<double,memory::mic,2>::register_type xmm0){
        return simd_trait<double,memory::mic,2>::register_type(
                         _mm512_log_pd(xmm0.r0),
                         _mm512_log_pd(xmm0.r1)
                      );
    }

    template<>
    forceinline  simd_trait<double,memory::mic,4>::register_type _mm_log<double,memory::mic,4>( simd_trait<double,memory::mic,4>::register_type xmm0){
        return simd_trait<double,memory::mic,4>::register_type(
                         _mm512_log_pd(xmm0.r0),
                         _mm512_log_pd(xmm0.r1),
                         _mm512_log_pd(xmm0.r2),
                         _mm512_log_pd(xmm0.r3)
                      );
    }
   /**
     \brief Compute the approximate reciprocal of packed single-precision (32-bit) floating-point elements in xmm0, and store the results in dst. The maximum relative error for this approximation is less than 1.5*2^-12.
      \warning using float, rcp is not implemented for double, precision not good !
    */
    template<>
    forceinline simd_trait<double,memory::mic,1>::register_type _mm_rec<double,memory::mic,1>(simd_trait<double,memory::mic,1>::register_type xmm0){
        return _mm512_cvtpslo_pd(_mm512_rcp23_ps(_mm512_cvtpd_pslo(xmm0)));
    };

    template<>
    forceinline  simd_trait<double,memory::mic,2>::register_type _mm_rec<double,memory::mic,2>( simd_trait<double,memory::mic,2>::register_type xmm0){
        return simd_trait<double,memory::mic,2>::register_type(
            _mm512_cvtpslo_pd(_mm512_rcp23_ps(_mm512_cvtpd_pslo(xmm0.r0))),
            _mm512_cvtpslo_pd(_mm512_rcp23_ps(_mm512_cvtpd_pslo(xmm0.r1)))
        );
    }

    template<>
    forceinline  simd_trait<double,memory::mic,4>::register_type _mm_rec<double,memory::mic,4>( simd_trait<double,memory::mic,4>::register_type xmm0){
        return simd_trait<double,memory::mic,4>::register_type(
            _mm512_cvtpslo_pd(_mm512_rcp23_ps(_mm512_cvtpd_pslo(xmm0.r0))),
            _mm512_cvtpslo_pd(_mm512_rcp23_ps(_mm512_cvtpd_pslo(xmm0.r1))),
            _mm512_cvtpslo_pd(_mm512_rcp23_ps(_mm512_cvtpd_pslo(xmm0.r2))),
            _mm512_cvtpslo_pd(_mm512_rcp23_ps(_mm512_cvtpd_pslo(xmm0.r3)))
        );
    }
    /**
     \brief Multiply packed double-precision (64-bit) floating-point elements in xmm0 and xmm1, add the intermediate result to packed elements in xmm2, and store the results in dst.
     */
    template<>
    forceinline simd_trait<double,memory::mic,1>::register_type _mm_fma<double,memory::mic,1>(simd_trait<double,memory::mic,1>::register_type xmm0,
                                                                                         simd_trait<double,memory::mic,1>::register_type xmm1,
                                                                                         simd_trait<double,memory::mic,1>::register_type xmm2){
        return _mm512_fmadd_pd(xmm0, xmm1, xmm2);
    }

    template<>
    forceinline  simd_trait<double,memory::mic,2>::register_type _mm_fma<double,memory::mic,2>(simd_trait<double,memory::mic,2>::register_type xmm0,
                                                                                               simd_trait<double,memory::mic,2>::register_type xmm1,
                                                                                               simd_trait<double,memory::mic,2>::register_type xmm2){
        return simd_trait<double,memory::mic,2>::register_type(
                        _mm512_fmadd_pd(xmm0.r0, xmm1.r0, xmm2.r0),
                        _mm512_fmadd_pd(xmm0.r1, xmm1.r1, xmm2.r1)
                      );
    }

    template<>
    forceinline  simd_trait<double,memory::mic,4>::register_type _mm_fma<double,memory::mic,4>(simd_trait<double,memory::mic,4>::register_type xmm0,
                                                                                               simd_trait<double,memory::mic,4>::register_type xmm1,
                                                                                               simd_trait<double,memory::mic,4>::register_type xmm2){
        return simd_trait<double,memory::mic,4>::register_type(
                        _mm512_fmadd_pd(xmm0.r0, xmm1.r0, xmm2.r0),
                        _mm512_fmadd_pd(xmm0.r1, xmm1.r1, xmm2.r1),
                        _mm512_fmadd_pd(xmm0.r2, xmm1.r2, xmm2.r2),
                        _mm512_fmadd_pd(xmm0.r3, xmm1.r3, xmm2.r3)
                      );
    }
    /**
     \brief Multiply packed double-precision (64-bit) floating-point elements in xmm0 and xmm1, subtract packed elements in xmm2 from the intermediate result, and store the results in dst.
     */
    template<>
    forceinline simd_trait<double,memory::mic,1>::register_type _mm_fms<double,memory::mic,1>(simd_trait<double,memory::mic,1>::register_type xmm0,
                                                                                              simd_trait<double,memory::mic,1>::register_type xmm1,
                                                                                              simd_trait<double,memory::mic,1>::register_type xmm2){
        return _mm512_fmsub_pd(xmm0, xmm1, xmm2);
    }

    template<>
    forceinline  simd_trait<double,memory::mic,2>::register_type _mm_fms<double,memory::mic,2>(simd_trait<double,memory::mic,2>::register_type xmm0,
                                                                                                    simd_trait<double,memory::mic,2>::register_type xmm1,
                                                                                                    simd_trait<double,memory::mic,2>::register_type xmm2){
        return simd_trait<double,memory::mic,2>::register_type(
                        _mm512_fmsub_pd(xmm0.r0, xmm1.r0, xmm2.r0),
                        _mm512_fmsub_pd(xmm0.r1, xmm1.r1, xmm2.r1)
                      );
    }

    template<>
    forceinline  simd_trait<double,memory::mic,4>::register_type _mm_fms<double,memory::mic,4>(simd_trait<double,memory::mic,4>::register_type xmm0,
                                                                                                    simd_trait<double,memory::mic,4>::register_type xmm1,
                                                                                                    simd_trait<double,memory::mic,4>::register_type xmm2){
        return simd_trait<double,memory::mic,4>::register_type(
                        _mm512_fmsub_pd(xmm0.r0, xmm1.r0, xmm2.r0),
                        _mm512_fmsub_pd(xmm0.r1, xmm1.r1, xmm2.r1),
                        _mm512_fmsub_pd(xmm0.r2, xmm1.r2, xmm2.r2),
                        _mm512_fmsub_pd(xmm0.r3, xmm1.r3, xmm2.r3)
                      );
    }
    /**
    \brief Multiply packed double-precision (64-bit) floating-point elements in xmm0 and xmm1, subtract packed elements in xmm2 from the negated intermediate result, and store the results in dst.
     */
    template<>
    forceinline simd_trait<double,memory::mic,1>::register_type _mm_nfms<double,memory::mic,1>(simd_trait<double,memory::mic,1>::register_type xmm0,
                                                                                               simd_trait<double,memory::mic,1>::register_type xmm1,
                                                                                               simd_trait<double,memory::mic,1>::register_type xmm2){
        return _mm512_fnmsub_pd(xmm0, xmm1, xmm2);
    }

    template<>
    forceinline  simd_trait<double,memory::mic,2>::register_type _mm_nfms<double,memory::mic,2>(simd_trait<double,memory::mic,2>::register_type xmm0,
                                                                                           simd_trait<double,memory::mic,2>::register_type xmm1,
                                                                                           simd_trait<double,memory::mic,2>::register_type xmm2){
        return simd_trait<double,memory::mic,2>::register_type(
                        _mm512_fnmsub_pd(xmm0.r0, xmm1.r0, xmm2.r0),
                        _mm512_fnmsub_pd(xmm0.r1, xmm1.r1, xmm2.r1)
                      );
    }

    template<>
    forceinline  simd_trait<double,memory::mic,4>::register_type _mm_nfms<double,memory::mic,4>(simd_trait<double,memory::mic,4>::register_type xmm0,
                                                                                           simd_trait<double,memory::mic,4>::register_type xmm1,
                                                                                           simd_trait<double,memory::mic,4>::register_type xmm2){
        return simd_trait<double,memory::mic,4>::register_type(
                        _mm512_fnmsub_pd(xmm0.r0, xmm1.r0, xmm2.r0),
                        _mm512_fnmsub_pd(xmm0.r1, xmm1.r1, xmm2.r1),
                        _mm512_fnmsub_pd(xmm0.r2, xmm1.r2, xmm2.r2),
                        _mm512_fnmsub_pd(xmm0.r3, xmm1.r3, xmm2.r3)
                      );
    }
    /**
    \brief Multiply packed double-precision (64-bit) floating-point elements in xmm0 and xmm1, add the negated intermediate result to packed elements in xmm2, and store the results in dst.
     */
    template<>
    forceinline simd_trait<double,memory::mic,1>::register_type _mm_nfma<double,memory::mic,1>(simd_trait<double,memory::mic,1>::register_type xmm0,
                                                                                               simd_trait<double,memory::mic,1>::register_type xmm1,
                                                                                               simd_trait<double,memory::mic,1>::register_type xmm2){
        return _mm512_fnmadd_pd(xmm0, xmm1, xmm2);
    }

    template<>
    forceinline  simd_trait<double,memory::mic,2>::register_type _mm_nfma<double,memory::mic,2>(simd_trait<double,memory::mic,2>::register_type xmm0,
                                                                                          simd_trait<double,memory::mic,2>::register_type xmm1,
                                                                                          simd_trait<double,memory::mic,2>::register_type xmm2){
        return simd_trait<double,memory::mic,2>::register_type(
                        _mm512_fnmadd_pd(xmm0.r0, xmm1.r0, xmm2.r0),
                        _mm512_fnmadd_pd(xmm0.r1, xmm1.r1, xmm2.r1)
                      );
    }

    template<>
    forceinline  simd_trait<double,memory::mic,4>::register_type _mm_nfma<double,memory::mic,4>(simd_trait<double,memory::mic,4>::register_type xmm0,
                                                                                                simd_trait<double,memory::mic,4>::register_type xmm1,
                                                                                                simd_trait<double,memory::mic,4>::register_type xmm2){
        return simd_trait<double,memory::mic,4>::register_type(
                        _mm512_fnmadd_pd(xmm0.r0, xmm1.r0, xmm2.r0),
                        _mm512_fnmadd_pd(xmm0.r1, xmm1.r1, xmm2.r1),
                        _mm512_fnmadd_pd(xmm0.r2, xmm1.r2, xmm2.r2),
                        _mm512_fnmadd_pd(xmm0.r3, xmm1.r3, xmm2.r3)
                      );
    }
    /*  -------------------------------------------------------------------------------------------------------------------- float */
    /**
     \brief Broadcast single-precision (32-bit) floating-point value a to all elements of dst.
     */
    template<>
     simd_trait<float,memory::mic,1>::register_type _mm_load1<float,memory::mic,1>(const simd_trait<float,memory::mic,1>::value_type& a){
        return _mm512_set1_ps(a);
    }

    template<>
    forceinline  simd_trait<float,memory::mic,2>::register_type _mm_load1<float,memory::mic,2>(const simd_trait<float,memory::mic,2>::value_type& a){
        return simd_trait<float,memory::mic,2>::register_type(_mm512_set1_ps(a),_mm512_set1_ps(a));
    }

    template<>
    forceinline  simd_trait<float,memory::mic,4>::register_type _mm_load1<float,memory::mic,4>(const simd_trait<float,memory::mic,4>::value_type& a){
        return simd_trait<float,memory::mic,4>::register_type(_mm512_set1_ps(a),_mm512_set1_ps(a),_mm512_set1_ps(a),_mm512_set1_ps(a));
    }
    /**
     \brief Load 512-bits (composed of 16 packed single-precision (32-bit) floating-point elements) from memory into dst. mem_addr must be aligned on a 64-byte boundary or a general-protection exception will be generated.
     */
    template<>
    forceinline simd_trait<float,memory::mic,1>::register_type _mm_load<float,memory::mic,1>(simd_trait<float,memory::mic,1>::const_pointer a){
        return _mm512_load_ps(a);
    }

    template<>
    forceinline  simd_trait<float,memory::mic,2>::register_type _mm_load<float,memory::mic,2>(simd_trait<float,memory::mic,2>::const_pointer a){
        return simd_trait<float,memory::mic,2>::register_type(_mm512_load_ps(a),_mm512_load_ps(a+16));
    }

    template<>
    forceinline  simd_trait<float,memory::mic,4>::register_type _mm_load<float,memory::mic,4>(simd_trait<float,memory::mic,4>::const_pointer a){
        return simd_trait<float,memory::mic,4>::register_type(_mm512_load_ps(a),_mm512_load_ps(a+16),_mm512_load_ps(a+32),_mm512_load_ps(a+48));
    }
    /**
     \brief Store 512-bits (composed of 16 packed single-precision (32-bit) floating-point elements) from a into memory. mem_addr must be aligned on a 64-byte boundary or a general-protection exception will be generated.
     */
    template<>
    void _mm_store<float,memory::mic,1>( simd_trait<float,memory::mic,1>::register_type xmm0,simd_trait<float,memory::mic,1>::pointer a){
        _mm512_store_ps(a,xmm0);
    }

    template<>
    forceinline void _mm_store<float,memory::mic,2>( simd_trait<float,memory::mic,2>::register_type xmm0,  simd_trait<float,memory::mic,2>::pointer a){
        _mm512_store_ps(a,xmm0.r0);
        _mm512_store_ps(a+16,xmm0.r1);
    }

    template<>
    forceinline void _mm_store<float,memory::mic,4>( simd_trait<float,memory::mic,4>::register_type xmm0,  simd_trait<float,memory::mic,4>::pointer a){
        _mm512_store_ps(a,xmm0.r0);
        _mm512_store_ps(a+16,xmm0.r1);
        _mm512_store_ps(a+32,xmm0.r2);
        _mm512_store_ps(a+48,xmm0.r3);
    }
    /**
      \brief Multiply packed single-precision (32-bit) floating-point elements in xmm0 and xmm1, and store the results in dst.
     */
    template<>
    forceinline simd_trait<float,memory::mic,1>::register_type _mm_mul<float,memory::mic,1>( simd_trait<float,memory::mic,1>::register_type xmm0,  simd_trait<float,memory::mic,1>::register_type xmm1){
        return _mm512_mul_ps(xmm0, xmm1);
    }

    template<>
    forceinline  simd_trait<float,memory::mic,2>::register_type _mm_mul<float,memory::mic,2>( simd_trait<float,memory::mic,2>::register_type xmm0,  simd_trait<float,memory::mic,2>::register_type xmm1){
        return simd_trait<float,memory::mic,2>::register_type(
                        _mm512_mul_ps(xmm0.r0, xmm1.r0),
                        _mm512_mul_ps(xmm0.r1, xmm1.r1)
                      );
    }

    template<>
    forceinline  simd_trait<float,memory::mic,4>::register_type _mm_mul<float,memory::mic,4>( simd_trait<float,memory::mic,4>::register_type xmm0,  simd_trait<float,memory::mic,4>::register_type xmm1){
        return simd_trait<float,memory::mic,4>::register_type(
                        _mm512_mul_ps(xmm0.r0, xmm1.r0),
                        _mm512_mul_ps(xmm0.r1, xmm1.r1),
                        _mm512_mul_ps(xmm0.r2, xmm1.r2),
                        _mm512_mul_ps(xmm0.r3, xmm1.r3)
                      );
    }
    /**
     \brief Divide packed single-precision (32-bit) floating-point elements in xmm0 and xmm1, and store the results in dst.
     */
    template<>
    forceinline  simd_trait<float,memory::mic,1>::register_type _mm_div<float,memory::mic,1>( simd_trait<float,memory::mic,1>::register_type xmm0,  simd_trait<float,memory::mic,1>::register_type xmm1){
        return _mm512_div_ps(xmm0, xmm1);
    }

    template<>
    forceinline  simd_trait<float,memory::mic,2>::register_type _mm_div<float,memory::mic,2>( simd_trait<float,memory::mic,2>::register_type xmm0,  simd_trait<float,memory::mic,2>::register_type xmm1){
        return simd_trait<float,memory::mic,2>::register_type(
                        _mm512_div_ps(xmm0.r0, xmm1.r0),
                        _mm512_div_ps(xmm0.r1, xmm1.r1)
                      );
    }

    template<>
    forceinline  simd_trait<float,memory::mic,4>::register_type _mm_div<float,memory::mic,4>( simd_trait<float,memory::mic,4>::register_type xmm0,  simd_trait<float,memory::mic,4>::register_type xmm1){
        return simd_trait<float,memory::mic,4>::register_type(
                        _mm512_div_ps(xmm0.r0, xmm1.r0),
                        _mm512_div_ps(xmm0.r1, xmm1.r1),
                        _mm512_div_ps(xmm0.r2, xmm1.r2),
                        _mm512_div_ps(xmm0.r3, xmm1.r3)
                      );
    }
    /**
     \brief Add packed single-precision (32-bit) floating-point elements in xmm0 and xmm1, and store the results in dst.
     */
    template<>
    forceinline  simd_trait<float,memory::mic,1>::register_type _mm_add<float,memory::mic,1>( simd_trait<float,memory::mic,1>::register_type xmm0,  simd_trait<float,memory::mic,1>::register_type xmm1){
        return _mm512_add_ps(xmm0, xmm1);
    }

    template<>
    forceinline  simd_trait<float,memory::mic,2>::register_type _mm_add<float,memory::mic,2>( simd_trait<float,memory::mic,2>::register_type xmm0,  simd_trait<float,memory::mic,2>::register_type xmm1){
        return simd_trait<float,memory::mic,2>::register_type(
                        _mm512_add_ps(xmm0.r0, xmm1.r0),
                        _mm512_add_ps(xmm0.r1, xmm1.r1)
                      );
    }

    template<>
    forceinline  simd_trait<float,memory::mic,4>::register_type _mm_add<float,memory::mic,4>( simd_trait<float,memory::mic,4>::register_type xmm0,  simd_trait<float,memory::mic,4>::register_type xmm1){
        return simd_trait<float,memory::mic,4>::register_type(
                        _mm512_add_ps(xmm0.r0, xmm1.r0),
                        _mm512_add_ps(xmm0.r1, xmm1.r1),
                        _mm512_add_ps(xmm0.r2, xmm1.r2),
                        _mm512_add_ps(xmm0.r3, xmm1.r3)
                      );
    }

    /**
     \brief Substract packed single-precision (32-bit) floating-point elements in xmm0 and xmm1, and store the results in dst.
     */
    template<>
    forceinline  simd_trait<float,memory::mic,1>::register_type _mm_sub<float,memory::mic,1>( simd_trait<float,memory::mic,1>::register_type xmm0,  simd_trait<float,memory::mic,1>::register_type xmm1){
        return _mm512_sub_ps(xmm0, xmm1);
    }

    template<>
    forceinline  simd_trait<float,memory::mic,2>::register_type _mm_sub<float,memory::mic,2>( simd_trait<float,memory::mic,2>::register_type xmm0,  simd_trait<float,memory::mic,2>::register_type xmm1){
        return simd_trait<float,memory::mic,2>::register_type(
                        _mm512_sub_ps(xmm0.r0, xmm1.r0),
                        _mm512_sub_ps(xmm0.r1, xmm1.r1)
                      );
    }

    template<>
    forceinline  simd_trait<float,memory::mic,4>::register_type _mm_sub<float,memory::mic,4>( simd_trait<float,memory::mic,4>::register_type xmm0,  simd_trait<float,memory::mic,4>::register_type xmm1){
        return simd_trait<float,memory::mic,4>::register_type(
                        _mm512_sub_ps(xmm0.r0, xmm1.r0),
                        _mm512_sub_ps(xmm0.r1, xmm1.r1),
                        _mm512_sub_ps(xmm0.r2, xmm1.r2),
                        _mm512_sub_ps(xmm0.r3, xmm1.r3)
                      );
    }
    /**
        \brief Negate packed double-precision (32-bit) floating-point elements in xmm0 to packed double-precision (32-bit) floating-point elements, and store the results in dst.
    */
    template<>
    forceinline  simd_trait<float,memory::mic,1>::register_type _mm_neg<float,memory::mic,1>(simd_trait<float,memory::mic,1>::register_type xmm0){
        return _mm512_castsi512_ps(_mm512_xor_si512( _mm512_castps_si512(xmm0),_mm512_set1_epi32(0x80000000))); //right if the number fill up into the mantissa ....
    };

    template<>
    forceinline  simd_trait<float,memory::mic,2>::register_type _mm_neg<float,memory::mic,2>(simd_trait<float,memory::mic,2>::register_type xmm0){
        simd_trait<int,memory::mic,1>::register_type mask =  _mm512_set1_epi32(0x80000000);
        return simd_trait<float,memory::mic,2>::register_type(
            _mm512_castsi512_ps(_mm512_xor_si512(_mm512_castps_si512(xmm0.r0), mask)),
            _mm512_castsi512_ps(_mm512_xor_si512(_mm512_castps_si512(xmm0.r1), mask))
        );
    }

    template<>
    forceinline  simd_trait<float,memory::mic,4>::register_type _mm_neg<float,memory::mic,4>(simd_trait<float,memory::mic,4>::register_type xmm0){
        simd_trait<int,memory::mic,1>::register_type mask =  _mm512_set1_epi32(0x80000000);
        return simd_trait<float,memory::mic,4>::register_type(
            _mm512_castsi512_ps(_mm512_xor_si512(_mm512_castps_si512(xmm0.r0), mask)),
            _mm512_castsi512_ps(_mm512_xor_si512(_mm512_castps_si512(xmm0.r1), mask)),
            _mm512_castsi512_ps(_mm512_xor_si512(_mm512_castps_si512(xmm0.r2), mask)),
            _mm512_castsi512_ps(_mm512_xor_si512(_mm512_castps_si512(xmm0.r3), mask))
        );
    }
    /**
     \brief Floor the packed double-precision (32-bit) floating-point elements in xmm0 down to an integer value, and store the results as packed single precision (32-bits).
     */
    template<>
    forceinline  simd_trait<int,memory::mic,1>::register_type _mm_floor<float,memory::mic,1>(simd_trait<float,memory::mic,1>::register_type xmm0){
        return  _mm512_castps_si512(_mm512_floor_ps(xmm0));
    };

    template<>
    forceinline  simd_trait<int,memory::mic,2>::register_type _mm_floor<float,memory::mic,2>( simd_trait<float,memory::mic,2>::register_type xmm0){
        return simd_trait<int,memory::mic,2>::register_type(
            _mm512_castps_si512(_mm512_floor_ps(xmm0.r0)),
            _mm512_castps_si512(_mm512_floor_ps(xmm0.r1))
        );
    }

    template<>
    forceinline  simd_trait<int,memory::mic,4>::register_type _mm_floor<float,memory::mic,4>( simd_trait<float,memory::mic,4>::register_type xmm0){
        return simd_trait<int,memory::mic,4>::register_type(
            _mm512_castps_si512(_mm512_floor_ps(xmm0.r0)),
            _mm512_castps_si512(_mm512_floor_ps(xmm0.r1)),
            _mm512_castps_si512(_mm512_floor_ps(xmm0.r2)),
            _mm512_castps_si512(_mm512_floor_ps(xmm0.r3))
        );
    }
    /**
     \brief Nothing
     */
    template<>
    forceinline  simd_trait<float,memory::mic,1>::register_type _mm_cast<float,memory::mic,1>(simd_trait<int,memory::mic,1>::register_type xmm0){
        return _mm512_castsi512_ps(xmm0);
    };

    template<>
    forceinline  simd_trait<float,memory::mic,2>::register_type _mm_cast<float,memory::mic,2>(simd_trait<int,memory::mic,2>::register_type xmm0){
        return simd_trait<float,memory::mic,2>::register_type(
            _mm512_castsi512_ps(xmm0.r0),
            _mm512_castsi512_ps(xmm0.r1)
        );
    }

    template<>
    forceinline  simd_trait<float,memory::mic,4>::register_type _mm_cast<float,memory::mic,4>(simd_trait<int,memory::mic,4>::register_type xmm0){
        return simd_trait<float,memory::mic,4>::register_type(
            _mm512_castsi512_ps(xmm0.r0),
            _mm512_castsi512_ps(xmm0.r1),
            _mm512_castsi512_ps(xmm0.r2),
            _mm512_castsi512_ps(xmm0.r3)
        );    }
    /**
     \brief Compute 2^k packed integer (32-bit) elements in xmm0 to packed single-precision (32-bit) floating-point elements, and store the results in dest.
    */
    template<>
    forceinline  simd_trait<float,memory::mic,1>::register_type _mm_twok<float,memory::mic,1>(simd_trait<int,memory::mic,1>::register_type xmm0){
        return _mm512_castsi512_ps(_mm512_sllv_epi32(_mm512_add_epi32(_mm512_cvtfxpnt_round_adjustps_epi32(_mm512_castsi512_ps(xmm0), _MM_ROUND_MODE_TOWARD_ZERO, _MM_EXPADJ_NONE),_mm512_set1_epi32(127)),_mm512_set1_epi32(23)));
    };

    template<>
    forceinline  simd_trait<float,memory::mic,2>::register_type _mm_twok<float,memory::mic,2>(simd_trait<int,memory::mic,2>::register_type xmm0){
         return simd_trait<float,memory::mic,2>::register_type(
            _mm512_castsi512_ps(_mm512_sllv_epi32(_mm512_add_epi32(_mm512_cvtfxpnt_round_adjustps_epi32(_mm512_castsi512_ps(xmm0.r0), _MM_ROUND_MODE_TOWARD_ZERO, _MM_EXPADJ_NONE),_mm512_set1_epi32(127)),_mm512_set1_epi32(23))),
            _mm512_castsi512_ps(_mm512_sllv_epi32(_mm512_add_epi32(_mm512_cvtfxpnt_round_adjustps_epi32(_mm512_castsi512_ps(xmm0.r1), _MM_ROUND_MODE_TOWARD_ZERO, _MM_EXPADJ_NONE),_mm512_set1_epi32(127)),_mm512_set1_epi32(23)))
         );
    };

    template<>
    forceinline  simd_trait<float,memory::mic,4>::register_type _mm_twok<float,memory::mic,4>(simd_trait<int,memory::mic,4>::register_type xmm0){
         return simd_trait<float,memory::mic,4>::register_type(
            _mm512_castsi512_ps(_mm512_sllv_epi32(_mm512_add_epi32(_mm512_cvtfxpnt_round_adjustps_epi32(_mm512_castsi512_ps(xmm0.r0), _MM_ROUND_MODE_TOWARD_ZERO, _MM_EXPADJ_NONE),_mm512_set1_epi32(127)),_mm512_set1_epi32(23))),
            _mm512_castsi512_ps(_mm512_sllv_epi32(_mm512_add_epi32(_mm512_cvtfxpnt_round_adjustps_epi32(_mm512_castsi512_ps(xmm0.r1), _MM_ROUND_MODE_TOWARD_ZERO, _MM_EXPADJ_NONE),_mm512_set1_epi32(127)),_mm512_set1_epi32(23))),
            _mm512_castsi512_ps(_mm512_sllv_epi32(_mm512_add_epi32(_mm512_cvtfxpnt_round_adjustps_epi32(_mm512_castsi512_ps(xmm0.r2), _MM_ROUND_MODE_TOWARD_ZERO, _MM_EXPADJ_NONE),_mm512_set1_epi32(127)),_mm512_set1_epi32(23))),
            _mm512_castsi512_ps(_mm512_sllv_epi32(_mm512_add_epi32(_mm512_cvtfxpnt_round_adjustps_epi32(_mm512_castsi512_ps(xmm0.r3), _MM_ROUND_MODE_TOWARD_ZERO, _MM_EXPADJ_NONE),_mm512_set1_epi32(127)),_mm512_set1_epi32(23)))
         );
    };
    /**
    \brief Approximates the reciprocals of the float32 vector v2 elements to 23 bits of accuracy.
    */
    template<>
    forceinline simd_trait<float,memory::mic,1>::register_type _mm_rec<float,memory::mic,1>(simd_trait<float,memory::mic,1>::register_type xmm0){
        return _mm512_rcp23_ps(xmm0);
    };

    template<>
    forceinline  simd_trait<float,memory::mic,2>::register_type _mm_rec<float,memory::mic,2>( simd_trait<float,memory::mic,2>::register_type xmm0){
        return simd_trait<float,memory::mic,2>::register_type(
            _mm512_rcp23_ps(xmm0.r0),
            _mm512_rcp23_ps(xmm0.r1)
        );
    }

    template<>
    forceinline  simd_trait<float,memory::mic,4>::register_type _mm_rec<float,memory::mic,4>( simd_trait<float,memory::mic,4>::register_type xmm0){
        return simd_trait<float,memory::mic,4>::register_type(
            _mm512_rcp23_ps(xmm0.r0),
            _mm512_rcp23_ps(xmm0.r1),
            _mm512_rcp23_ps(xmm0.r2),
            _mm512_rcp23_ps(xmm0.r3)
        );
    }
    /**
     \brief Compute the exponential value of e raised to the power of packed float-precision (32-bit) floating-point elements in xmm0, and store the results in dst.
     */
    template<>
    forceinline  simd_trait<float,memory::mic,1>::register_type _mm_exp<float,memory::mic,1>( simd_trait<float,memory::mic,1>::register_type xmm0){
        return _mm512_exp_ps(xmm0);
    }

    template<>
    forceinline  simd_trait<float,memory::mic,2>::register_type _mm_exp<float,memory::mic,2>( simd_trait<float,memory::mic,2>::register_type xmm0){
        return simd_trait<float,memory::mic,2>::register_type(
                         _mm512_exp_ps(xmm0.r0),
                         _mm512_exp_ps(xmm0.r1)
                      );
    }

    template<>
    forceinline  simd_trait<float,memory::mic,4>::register_type _mm_exp<float,memory::mic,4>( simd_trait<float,memory::mic,4>::register_type xmm0){
        return simd_trait<float,memory::mic,4>::register_type(
                         _mm512_exp_ps(xmm0.r0),
                         _mm512_exp_ps(xmm0.r1),
                         _mm512_exp_ps(xmm0.r2),
                         _mm512_exp_ps(xmm0.r3)
                      );
    }
    /**
     \brief Multiply packed single-precision (32-bit) floating-point elements in xmm0 and xmm1, add the intermediate result to packed elements in xmm2, and store the results in dst.
     */
    template<>
    forceinline  simd_trait<float,memory::mic,1>::register_type _mm_fma<float,memory::mic,1>( simd_trait<float,memory::mic,1>::register_type xmm0,  simd_trait<float,memory::mic,1>::register_type xmm1,  simd_trait<float,memory::mic,1>::register_type xmm2){
        return _mm512_fmadd_ps(xmm0, xmm1, xmm2);
    }

    template<>
    forceinline  simd_trait<float,memory::mic,2>::register_type _mm_fma<float,memory::mic,2>(simd_trait<float,memory::mic,2>::register_type xmm0,
                                                                                             simd_trait<float,memory::mic,2>::register_type xmm1,
                                                                                             simd_trait<float,memory::mic,2>::register_type xmm2){
        return simd_trait<float,memory::mic,2>::register_type(
                        _mm512_fmadd_ps(xmm0.r0, xmm1.r0, xmm2.r0),
                        _mm512_fmadd_ps(xmm0.r1, xmm1.r1, xmm2.r1)
                      );
    }

    template<>
    forceinline  simd_trait<float,memory::mic,4>::register_type _mm_fma<float,memory::mic,4>(simd_trait<float,memory::mic,4>::register_type xmm0,
                                                                                             simd_trait<float,memory::mic,4>::register_type xmm1,
                                                                                             simd_trait<float,memory::mic,4>::register_type xmm2){
        return simd_trait<float,memory::mic,4>::register_type(
                        _mm512_fmadd_ps(xmm0.r0, xmm1.r0, xmm2.r0),
                        _mm512_fmadd_ps(xmm0.r1, xmm1.r1, xmm2.r1),
                        _mm512_fmadd_ps(xmm0.r2, xmm1.r2, xmm2.r2),
                        _mm512_fmadd_ps(xmm0.r3, xmm1.r3, xmm2.r3)
                      );
    }
    /**
     \brief Multiply packed single-precision (32-bit) floating-point elements in xmm0 and xmm1, subtract packed elements in xmm2 from the intermediate result, and store the results in dst.
     */
    template<>
    forceinline  simd_trait<float,memory::mic,1>::register_type _mm_fms<float,memory::mic,1>( simd_trait<float,memory::mic,1>::register_type xmm0,  simd_trait<float,memory::mic,1>::register_type xmm1,  simd_trait<float,memory::mic,1>::register_type xmm2){
        return _mm512_fmsub_ps(xmm0, xmm1, xmm2);
    }

    template<>
    forceinline  simd_trait<float,memory::mic,2>::register_type _mm_fms<float,memory::mic,2>(simd_trait<float,memory::mic,2>::register_type xmm0,
                                                                                             simd_trait<float,memory::mic,2>::register_type xmm1,
                                                                                             simd_trait<float,memory::mic,2>::register_type xmm2){
        return simd_trait<float,memory::mic,2>::register_type(
                        _mm512_fmsub_ps(xmm0.r0, xmm1.r0, xmm2.r0),
                        _mm512_fmsub_ps(xmm0.r1, xmm1.r1, xmm2.r1)
                      );
    }

    template<>
    forceinline  simd_trait<float,memory::mic,4>::register_type _mm_fms<float,memory::mic,4>(simd_trait<float,memory::mic,4>::register_type xmm0,
                                                                                             simd_trait<float,memory::mic,4>::register_type xmm1,
                                                                                             simd_trait<float,memory::mic,4>::register_type xmm2){
        return simd_trait<float,memory::mic,4>::register_type(
                        _mm512_fmsub_ps(xmm0.r0, xmm1.r0, xmm2.r0),
                        _mm512_fmsub_ps(xmm0.r1, xmm1.r1, xmm2.r1),
                        _mm512_fmsub_ps(xmm0.r2, xmm1.r2, xmm2.r2),
                        _mm512_fmsub_ps(xmm0.r3, xmm1.r3, xmm2.r3)
                      );
    }
    /**
     \brief Multiply packed single-precision (32-bit) floating-point elements in xmm0 and xmm1, subtract packed elements in xmm2 from the negated intermediate result, and store the results in dst.
     */
    template<>
    forceinline  simd_trait<float,memory::mic,1>::register_type _mm_nfms<float,memory::mic,1>( simd_trait<float,memory::mic,1>::register_type xmm0,  simd_trait<float,memory::mic,1>::register_type xmm1,  simd_trait<float,memory::mic,1>::register_type xmm2){
        return _mm512_fnmsub_ps(xmm0, xmm1, xmm2);
    }

    template<>
    forceinline  simd_trait<float,memory::mic,2>::register_type _mm_nfms<float,memory::mic,2>(simd_trait<float,memory::mic,2>::register_type xmm0,
                                                                                                simd_trait<float,memory::mic,2>::register_type xmm1,
                                                                                                simd_trait<float,memory::mic,2>::register_type xmm2){
        return simd_trait<float,memory::mic,2>::register_type(
                        _mm512_fnmsub_ps(xmm0.r0, xmm1.r0, xmm2.r0),
                        _mm512_fnmsub_ps(xmm0.r1, xmm1.r1, xmm2.r1)
                      );
    }

    template<>
    forceinline  simd_trait<float,memory::mic,4>::register_type _mm_nfms<float,memory::mic,4>(simd_trait<float,memory::mic,4>::register_type xmm0,
                                                                                           simd_trait<float,memory::mic,4>::register_type xmm1,
                                                                                           simd_trait<float,memory::mic,4>::register_type xmm2){
        return simd_trait<float,memory::mic,4>::register_type(
                        _mm512_fnmsub_ps(xmm0.r0, xmm1.r0, xmm2.r0),
                        _mm512_fnmsub_ps(xmm0.r1, xmm1.r1, xmm2.r1),
                        _mm512_fnmsub_ps(xmm0.r2, xmm1.r2, xmm2.r2),
                        _mm512_fnmsub_ps(xmm0.r3, xmm1.r3, xmm2.r3)
                      );
    }
    /**
     \brief Multiply packed single-precision (32-bit) floating-point elements in xmm0 and xmm1, add the negated intermediate result to packed elements in xmm2, and store the results in dst.
     */
    template<>
    forceinline  simd_trait<float,memory::mic,1>::register_type _mm_nfma<float,memory::mic,1>( simd_trait<float,memory::mic,1>::register_type xmm0,  simd_trait<float,memory::mic,1>::register_type xmm1,  simd_trait<float,memory::mic,1>::register_type xmm2){
        return _mm512_fnmadd_ps(xmm0, xmm1, xmm2);
    }

    template<>
    forceinline  simd_trait<float,memory::mic,2>::register_type _mm_nfma<float,memory::mic,2>(simd_trait<float,memory::mic,2>::register_type xmm0,
                                                                                              simd_trait<float,memory::mic,2>::register_type xmm1,
                                                                                              simd_trait<float,memory::mic,2>::register_type xmm2){
        return simd_trait<float,memory::mic,2>::register_type(
                        _mm512_fnmadd_ps(xmm0.r0, xmm1.r0, xmm2.r0),
                        _mm512_fnmadd_ps(xmm0.r1, xmm1.r1, xmm2.r1)
                      );
    }

    template<>
    forceinline  simd_trait<float,memory::mic,4>::register_type _mm_nfma<float,memory::mic,4>(simd_trait<float,memory::mic,4>::register_type xmm0,
                                                                                              simd_trait<float,memory::mic,4>::register_type xmm1,
                                                                                              simd_trait<float,memory::mic,4>::register_type xmm2){
        return simd_trait<float,memory::mic,4>::register_type(
                        _mm512_fnmadd_ps(xmm0.r0, xmm1.r0, xmm2.r0),
                        _mm512_fnmadd_ps(xmm0.r1, xmm1.r1, xmm2.r1),
                        _mm512_fnmadd_ps(xmm0.r2, xmm1.r2, xmm2.r2),
                        _mm512_fnmadd_ps(xmm0.r3, xmm1.r3, xmm2.r3)
                      );
    }
} //end namespace

#endif
