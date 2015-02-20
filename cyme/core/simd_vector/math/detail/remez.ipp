/*
 * Cyme - remez.ipp, Copyright (c), 2014,
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
 * @file cyme/core/simd_vector/math/detail/remez.ipp
 * Implements operator+ for vec_simd class
 */

#ifndef CYME_REMEZ_IPP
#define CYME_REMEZ_IPP

namespace cyme{


    /** this class encapsulates the remez approximation coefficient for the exp

     no c++ 11, so no constexpr into structure for double/float, ^.^ just partial specialization
     these coeffs are obtained with an external program
    */
    template<class T, std::size_t n>
    struct coeff_remez_exp;

    /** coeff order 0 exp(x) */
    template<class T>
    struct coeff_remez_exp<T,0>{
        const static inline T coeff() {return 1.0000000000000002114940639705245276038539149099858;}
    };

    /** coeff order 1 exp(x) */
    template<class T>
    struct coeff_remez_exp<T,1>{
        const static inline T coeff() {return 9.9999999999992204062922755139901673043089743845207e-1;}
    };

    /** coeff order 2 exp(x) */
    template<class T>
    struct coeff_remez_exp<T,2>{
        const static inline T coeff() {return 5.0000000000470407075910575853333558195136495835175e-1;}
    };

    /** coeff order 3 exp(x) */
    template<class T>
    struct coeff_remez_exp<T,3>{
        const static inline T coeff() {return 1.6666666655683517447526098517565535790685389986567e-1;}
    };

    /** coeff order 4 exp(x) */
    template<class T>
    struct coeff_remez_exp<T,4>{
        const static inline T coeff() {return 4.1666667972995034755573836934823984390148899855282e-2;}
    };

    /** coeff order 5 exp(x) */
    template<class T>
    struct coeff_remez_exp<T,5>{
        const static inline T coeff() {return 8.3333243238266834234997694128023285974769437237618e-3;}
    };

    /** coeff order 6 exp(x) */
    template<class T>
    struct coeff_remez_exp<T,6>{
        const static inline T coeff() {return 1.3889273989128108635846229092909917615429232247147e-3;}
    };

    /** coeff order 7 exp(x) */
    template<class T>
    struct coeff_remez_exp<T,7>{
        const static inline T coeff() {return 1.9830766718527367242381398724699378201454167561602e-4;}
    };

    /** coeff order 8 exp(x) */
    template<class T>
    struct coeff_remez_exp<T,8>{
        const static inline T coeff() {return 2.4984065458054751527321973285958377956147788917789e-5;}
    };

    /** coeff order 9 exp(x) */
    template<class T>
    struct coeff_remez_exp<T,9>{
        const static inline T coeff() {return 2.5615650803565837424935479251593631699833183180355e-6;}
    };

    /** coeff order 10 exp(x) */
    template<class T>
    struct coeff_remez_exp<T,10>{
        const static inline T coeff() {return 3.8874526912789884677625679351432816392776740411369e-7;}
    };

    /** Poly_order class encapsulates the number of Remez coefficient */
    template<class T, template<class,std::size_t> class C >
    struct poly_order;

    /** Poly_order partial specialisation for the exp */
    template<class T>
    struct poly_order<T,coeff_remez_exp> {
        static const std::size_t value=10;
    };

    /** this class encapsulates the remez approximation coefficient for the log

     no c++ 11, so no constexpr into structure for double/float, ^.^ just partial specialization
     these coeffs are obtained with an external program
    */
    // log coefficient
    template<class T, std::size_t n>
    struct coeff_remez_log;

    /** coeff order 0 log(x) */
    template<class T>
    struct coeff_remez_log<T,0>{
        const static inline T coeff() {return 0;}
    };

    /** coeff order 1 log(x) */
    template<class T>
    struct coeff_remez_log<T,1>{
        const static inline T coeff() {return 0.999999999881463517864L;}
    };

    /** coeff order 2 log(x) */
    template<class T>
    struct coeff_remez_log<T,2>{
        const static inline T coeff() {return -0.499999964958725095026L;}
    };

    /** coeff order 3 log(x) */
    template<class T>
    struct coeff_remez_log<T,3>{
        const static inline T coeff() {return 0.333331601133431864538L;}
    };

    /** coeff order 4 log(x) */
    template<class T>
    struct coeff_remez_log<T,4>{
        const static inline T coeff() {return -0.249966118317788475791L;}
    };

    /** coeff order 5 log(x) */
    template<class T>
    struct coeff_remez_log<T,5>{
        const static inline T coeff() {return 0.199652928083999845561L;}
    };

    /** coeff order 6 log(x) */
    template<class T>
    struct coeff_remez_log<T,6>{
        const static inline T coeff() {return -0.164528321547744695595L;}
    };

    /** coeff order 7 log(x) */
    template<class T>
    struct coeff_remez_log<T,7>{
        const static inline T coeff() {return 0.13426431588538376696L;}
    };

    /** coeff order 8 log(x) */
    template<class T>
    struct coeff_remez_log<T,8>{
        const static inline T coeff() {return -0.101241750098569221963L;}
    };

    /** coeff order 9 log(x) */
    template<class T>
    struct coeff_remez_log<T,9>{
        const static inline T coeff() {return 0.0640055965188409194363L;}
    };

    /** coeff order 10 log(x) */
    template<class T>
    struct coeff_remez_log<T,10>{
        const static inline T coeff() {return -0.0301709422209463258125L;}
    };

    /** coeff order 11 log(x) */
    template<class T>
    struct coeff_remez_log<T,11>{
        const static inline T coeff() {return 0.00908032467092469922091L;}
    };

    /** coeff order 12 log(x) */
    template<class T>
    struct coeff_remez_log<T,12>{
        const static inline T coeff() {return -0.00128048855206694750818L;}
    };

    /** Poly_order partial specialisation for the log */
    template<class T>
    struct poly_order<T,coeff_remez_log> {
        static const std::size_t value=12;
    };

    /** Implementation of a polynomial computation using Horner's method

    (http://en.wikipedia.org/wiki/Horner's_method)
     The template parameter C represents the coefficients described (log or exp coeff). This function is called
     into simd_log.hpp or simd_exp.log with the needed coefficient.
     */
    template<class T, cyme::simd O, int N, template <typename,std::size_t> class C, std::size_t n>
    struct helper_horner{
        static forceinline vec_simd<T,O,N> horner(vec_simd<T,O,N> const& a){
#ifdef __FMA__
            return muladd(helper_horner<T,O,N,C,n-1>::horner(a),a,vec_simd<T,O,N>(C<T,poly_order<T,C>::value-n>::coeff()));
#else
            return vec_simd<T,O,N>(C<T,poly_order<T,C>::value-n>::coeff()) + helper_horner<T,O,N,C,n-1>::horner(a)*a;
#endif
        }
    };

    /** Implementation of the polynomial computation recursive template, final specialization */
    template<class T, cyme::simd O, int N, template <typename,std::size_t> class C>
    struct helper_horner<T,O,N,C,0>{
        static forceinline vec_simd<T,O,N> horner(vec_simd<T,O,N> const&){
            return vec_simd<T,O,N>(C<T,poly_order<T,C>::value>::coeff());
        }
    };

} //end namespace

#endif
