/*
 * Cyme - remez.ipp, Copyright (c), 2014,
 * Timothee Ewart - Swiss Federal Institute of technology in Lausanne,
 * timothee.ewart@epfl.ch,
 * Kai Langen
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
 * @file cyme/core/simd_vector/math/detail/sin_helper.ipp
 * Implements sin helper functions for vec_simd class
 */

#ifndef CYME_SIN_HELPER_IPP
#define CYME_SIN_HELPER_IPP

namespace cyme{


    /** this class encapsulates the cephes approximation coefficients for sin

     no c++ 11, so no constexpr into structure for double/float, ^.^ just partial specialization
     these coeffs are obtained with an external program
    */
    template<class T, std::size_t n>
    struct coeff_cephes_sin;

    /** coeff order 0 sin(x) */
    template<class T>
    struct coeff_cephes_sin<T,0>{
        const static inline T coeff() {return 1;}//return -1.9515295891E-4;}
    };

    /** coeff order 1 sin(x) */
    template<class T>
    struct coeff_cephes_sin<T,1>{
        const static inline T coeff() {return 1;}//return 8.3321608736E-3;}
    };

    /** coeff order 2 sin(x) */
    template<class T>
    struct coeff_cephes_sin<T,2>{
        const static inline T coeff() {return 1;}//return -1.6666654611E-1;}
    };
    /** Poly_order class encapsulates the number of Remez coefficient */
    template<class T, template<class,std::size_t> class C >
    struct poly_order;

    /** Poly_order partial specialisation for the sin */
    template<class T>
    struct poly_order<T,coeff_cephes_sin> {
        static const std::size_t value=3;
    };

    /** this class encapsulates the cephes approximation coefficients for cos

     no c++ 11, so no constexpr into structure for double/float, ^.^ just partial specialization
     these coeffs are obtained with an external program
    */
    // cos coefficient
    template<class T, std::size_t n>
    struct coeff_cephes_cos;

    /** coeff order 0 cos(x) */
    template<class T>
    struct coeff_cephes_cos<T,0>{
        const static inline T coeff() {return 1;}//return 2.443315711809948E-005;}
    };

    /** coeff order 1 cos(x) */
    template<class T>
    struct coeff_cephes_cos<T,1>{
        const static inline T coeff() {return 1;}//return -1.388731625493765E-003;}
    };

    /** coeff order 2 cos(x) */
    template<class T>
    struct coeff_cephes_cos<T,2>{
        const static inline T coeff() {return 1;}//return 4.166664568298827E-002;}
    };

    /** Poly_order partial specialisation for the cos*/
    template<class T>
    struct poly_order<T,coeff_cephes_cos> {
        static const std::size_t value=3;
    };

    /** Implementation of polynomial computation for sin

     The template parameter C represents the coefficients described (sin or cos coeff). This function is called
     into simd_sin.log with the needed coefficient.
     */
    template<class T, cyme::simd O, int N, template <typename,std::size_t> class C, std::size_t n>
    struct helper_sin{
        static forceinline vec_simd<T,O,N> poly_sin(vec_simd<T,O,N> const& z){
	    /* result = (((coeff0)*z+coeff1)*z+coeff2)*z */
            return z*(vec_simd<T,O,N>(C<T,n-1>::coeff())+helper_sin<T,O,N,C,n-1>::poly_sin(z));
        }
    };

    /** Implementation of the polynomial computation recursive template, final specialization */
    template<class T, cyme::simd O, int N, template <typename,std::size_t> class C>
    struct helper_sin<T,O,N,C,0>{
        static forceinline vec_simd<T,O,N> poly_sin(vec_simd<T,O,N> const&){
            return vec_simd<T,O,N>(0.0);
        }
    };
} //end namespace

#endif
