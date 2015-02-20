/*
 * Cyme - simd_vec.hpp, Copyright (c), 2014,
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
 * @file cyme/core/simd_vector/simd_vec.hpp
 * Defines SIMD generic vector class
 */

#ifndef CYME_SIMD_VEC_HPP
#define CYME_SIMD_VEC_HPP

#include "cyme/core/simd_vector/trait.hpp"
#include "cyme/core/simd_vector/simd_wrapper.hpp"

namespace cyme{
    /** SIMD vector computation class.

      The vector is generic, it can be SSE, AVX or QPX. The type is given by the trait class cyme::simd_trait
    */
    template<class T,cyme::simd O, int N>
    struct vec_simd{
        typedef typename simd_trait<T,O,N>::value_type value_type;
        typedef typename simd_trait<T,O,N>::pointer pointer;
        typedef typename simd_trait<T,O,N>::const_pointer const_pointer;
        typedef typename simd_trait<T,O,N>::register_type register_type;

        /** Construtor desired value else 0, note copy constructor generated automaticaly. Only used for constant.  */
        forceinline explicit vec_simd(const value_type& a);

        /** Construtor without nothing load a value cost */
        forceinline explicit vec_simd();

        /** Construtor for exp and log */
        forceinline explicit vec_simd(register_type x);

        /** Construtor from a pointer */
        forceinline vec_simd(const_pointer a);

        /** Bracket operator called by the parser (expr_vec) */
        forceinline vec_simd& operator()();

        /** Bracket operator called by the parser (expr_vec) */
        forceinline const vec_simd& operator()() const;

        /** Operator *= between two vectors */
        forceinline vec_simd& operator *=(const vec_simd& rhs);

        /** Operator /= between two vectors */
        forceinline vec_simd& operator /=(const vec_simd& rhs);

        /** Operator += between two vectors */
        forceinline vec_simd& operator +=(const vec_simd& rhs);

        /** Operator -= between two vectors */
        forceinline vec_simd& operator -=(const vec_simd& rhs);

        /** Save the value into the register into the cyme */
        forceinline void store(pointer a) const;

        /** Negate the value of the register */
        forceinline vec_simd& neg();

        /** Function for load only one value type, serial library */
        forceinline vec_simd& single(const value_type& b);

        /** Function for load only one value type, serial library */
        forceinline value_type single(pointer b);

#ifdef __FMA__
        /** FMA operator */
        forceinline void ma(const vec_simd& lhs, const vec_simd& rhs);

        /** FMS operator */
        forceinline void ms(const vec_simd& lhs, const vec_simd& rhs);

        /** FMS operator, 2nd case of the operator - */
        forceinline void nma(const vec_simd& lhs, const vec_simd& rhs);

        /** FMS operator, 2nd case of the operator - */
        forceinline void nms(const vec_simd& lhs, const vec_simd& rhs);
#endif
        /** 1,2 or 4 Hardware Registers (SSE, AVXR ...) */
        register_type xmm;
    };

    /** Sast int to float */
    template<class T, cyme::simd O, int N>
    forceinline vec_simd<T,O,N> cast(const vec_simd<int,O,N>& ths);

    /** Return the 2^k where k is a vector base on an integer */
    template<class T,cyme::simd O, int N>
    forceinline vec_simd<T,O,N> twok(const vec_simd<int,O,N>& rhs);

    /** Return the exponent of the floating point representation */
    template<class T,cyme::simd O, int N>
    forceinline vec_simd<T,O,N> ge(const vec_simd<T,O,N>& rhs);

    /** Return the fraction of the floating point representation */
    template<class T,cyme::simd O, int N>
    forceinline vec_simd<T,O,N> gf(const vec_simd<T,O,N>& rhs);

    /** Return the exponent/2 of the floating point representation multiplied by sqrt(2) if n is an odd number */
    template<class T,cyme::simd O, int N>
    forceinline vec_simd<T,O,N> gesqrt2(const vec_simd<T,O,N>& rhs);

    /** Floor the value return a int simd register */
    template<class T,cyme::simd O, int N>
    forceinline vec_simd<int,O,N> floor(vec_simd<T,O,N>& rhs);

    /** Free function + operator between two vectors, this function uses the return value optimization */
    template<class T,cyme::simd O, int N>
    forceinline vec_simd<T,O,N> operator+ (const vec_simd<T,O,N>& lhs, const vec_simd<T,O,N>& rhs);

    /** Free function - operator between two vectors, this function uses the return value optimization */
    template<class T,cyme::simd O, int N>
    forceinline vec_simd<T,O,N> operator- (const vec_simd<T,O,N>& lhs, const vec_simd<T,O,N>& rhs);

    /** Free function * operator between two vectors, this function uses the return value optimization */
    template<class T,cyme::simd O, int N>
    forceinline vec_simd<T,O,N> operator* (const vec_simd<T,O,N>& lhs, const vec_simd<T,O,N>& rhs);

    /** Free function / operator between two vectors this function uses the return value optimization */
    template<class T,cyme::simd O, int N>
    forceinline vec_simd<T,O,N> operator/ (const vec_simd<T,O,N>& lhs, const vec_simd<T,O,N>& rhs);

    /** Free function for call the reciprocal for the Newton-Raphson division (initialization only) */
    template<class T,cyme::simd O, int N>
    forceinline vec_simd<T,O,N> rec(vec_simd<T,O,N> const& rhs);

    /** Free function for call the reciprocal for the Newton-Raphson square root (initialization only) */
    template<class T,cyme::simd O, int N>
    forceinline vec_simd<T,O,N> recsqrt(vec_simd<T,O,N> const& rhs);

    /** Free function for the negation */
    template<class T,cyme::simd O,int N>
    forceinline vec_simd<T,O,N> neg(const vec_simd<T,O,N>& rhs);

    /** Free function for the pow */
    template<class T,cyme::simd O, int N, int M>
    forceinline vec_simd<T,O,N> pow(const vec_simd<T,O,N>& lhs);

    /** Free function for the exp */
    template<class T,cyme::simd O, int N>
    forceinline vec_simd<T,O,N> exp(const vec_simd<T,O,N>& rhs);

    /** Free function for the log */
    template<class T,cyme::simd O, int N>
    forceinline vec_simd<T,O,N> log(const vec_simd<T,O,N>& rhs);

    /** Free function for the sqrt */
    template<class T,cyme::simd O, int N>
    forceinline vec_simd<T,O,N> sqrt(const vec_simd<T,O,N>& rhs);

#ifdef __FMA__
    /** Free function FMA between 3 vectors, a*b+c or c + a*B, + is commutative so no pb */
    template<class T,cyme::simd O, int N>
    forceinline vec_simd<T,O,N> muladd(const vec_simd<T,O,N>& lhs, const vec_simd<T,O,N>& mhs, const vec_simd<T,O,N>& rhs);

    /** Free function nFMA */
    template<class T,cyme::simd O,int N>
    forceinline vec_simd<T,O,N> negatemuladd(const vec_simd<T,O,N>& lhs, const vec_simd<T,O,N>& mhs, const vec_simd<T,O,N>& rhs);

    /** Free function FMS between 3 vectors, only a*b - c, - is not commutative */
    template<class T,cyme::simd O, int N>
    forceinline vec_simd<T,O,N> mulsub(const vec_simd<T,O,N>& lhs, const vec_simd<T,O,N>& mhs, const vec_simd<T,O,N>& rhs);

    /** Free function nFMS */
    template<class T,cyme::simd O, int N>
    forceinline vec_simd<T,O,N> negatemulsub(const vec_simd<T,O,N>& lhs, const vec_simd<T,O,N>& mhs, const vec_simd<T,O,N>& rhs);
#endif

} //end namespace

#include "cyme/core/simd_vector/simd_vec.ipp"
#include "cyme/core/simd_vector/simd_math.ipp" // contains all math operations include

#endif

