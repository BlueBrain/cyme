/*
 * Cyme - expr_vec_fma.ipp, Copyright (c), 2014,
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
 * @file cyme/core/expression/expr_vec_fma.ipp
 * Defines usual mathematical operators to allow the use of FMA
 */

#ifndef CYME_EXPR_VEC_FMA_IPP
#define CYME_EXPR_VEC_FMA_IPP

namespace cyme{
    /**
    * FMA from operator a*b+c
    */
    template<class T, cyme::simd O, int N, class R1, class R2, class R3>
    vec<T,O,N, vec_muladd<T,O,N,R1,R2,R3> >
    forceinline operator +(vec<T,O,N,vec_mul<T,O,N,R1,R2> >const& a, vec<T,O,N,R3> const& b){
        return  vec<T,O,N,vec_muladd<T,O,N,R1,R2,R3> >(vec_muladd<T,O,N,R1,R2,R3>(a.rep(),b.rep()));
    }

    /**
    * FMA from operator a*b+c where c is a scalar
    */
    template<class T, cyme::simd O, int N, class R1, class R2>
    vec<T,O,N, vec_muladd<T,O,N,R1,R2,vec_scalar<T,O,N> > >
    forceinline operator +(vec<T,O,N,vec_mul<T,O,N,R1,R2> >const& a, typename identity<T>::value_type const& b){
        return  vec<T,O,N,vec_muladd<T,O,N,R1,R2,vec_scalar<T,O,N> > >
            (vec_muladd<T,O,N,R1,R2,vec_scalar<T,O,N> >(a.rep(),vec_scalar<T,O,N>(static_cast<T>(b))));
    }

    /**
    * FMA from operator a+b*c
    */
    template<class T, cyme::simd O, int N, class R1, class R2, class R3>
    vec<T,O,N, vec_muladd<T,O,N,R1,R2,R3> >
    forceinline operator +(vec<T,O,N,R3> const& b, vec<T,O,N,vec_mul<T,O,N,R1,R2> >const& a){
        return operator+(a,b); //take previous one ^_^, as the addition is commutative
    }

    /**
    * FMA from operator a+b*c where c is a scalar
    */
    template<class T, cyme::simd O, int N, class R1, class R2>
    vec<T,O,N, vec_muladd<T,O,N,R1,R2,vec_scalar<T,O,N> > >
    forceinline operator +(typename identity<T>::value_type const& b, vec<T,O,N,vec_mul<T,O,N,R1,R2> >const& a){
        return operator+(a,b);
    }

    /**
    * FMA from operator a*b+c*d, I introduce this new case, because the compiler can't distinguish a*b + c*d
    * (ambiguous fma(a,b,c*d) or fma(c,d,a*b), with the two previous wrappers)
    */
    template<class T, cyme::simd O, int N, class R1, class R2, class R3, class R4>
    vec<T,O,N, vec_mul_add_mul<T,O,N,R1,R2,R3,R4> >
    forceinline operator +(vec<T,O,N,vec_mul<T,O,N,R1,R2> >const& a, vec<T,O,N,vec_mul<T,O,N,R3,R4> >const& b){
        return  vec<T,O,N, vec_mul_add_mul<T,O,N,R1,R2,R3,R4> >(vec_mul_add_mul<T,O,N,R1,R2,R3,R4>(a.rep(),b.rep()));
    }

    /**
    * FMS from operator a*b-c
    */
    template<class T, cyme::simd O, int N, class R1, class R2, class R3>
    vec<T,O,N, vec_mulsub<T,O,N,R1,R2,R3> >
    forceinline operator -(vec<T,O,N,vec_mul<T,O,N,R1,R2> >const& a, vec<T,O,N,R3> const& b){
        return  vec<T,O,N, vec_mulsub<T,O,N,R1,R2,R3> >(vec_mulsub<T,O,N,R1,R2,R3>(a.rep(),b.rep()));
    }

    /**
    * FMS from operator a*b-c where c is a scalar
    */
    template<class T, cyme::simd O, int N, class R1, class R2>
    vec<T,O,N, vec_mulsub<T,O,N,R1,R2,vec_scalar<T,O,N> > >
    forceinline operator -(vec<T,O,N,vec_mul<T,O,N,R1,R2> >const& a, typename identity<T>::value_type const& b){
        return  vec<T,O,N,vec_mulsub<T,O,N,R1,R2,vec_scalar<T,O,N> > >
            (vec_mulsub<T,O,N,R1,R2,vec_scalar<T,O,N> >(a.rep(),vec_scalar<T,O,N>(static_cast<T>(b))));
    }

    /**
    * FMS from operator a-b*c
    */
    template<class T, cyme::simd O, int N, class R1, class R2, class R3>
    vec<T,O,N, vec_negate_muladd<T,O,N,R1,R2,R3> >
    forceinline operator -(vec<T,O,N,R3> const& a, vec<T,O,N,vec_mul<T,O,N,R1,R2> >const& b){
        return  vec<T,O,N, vec_negate_muladd<T,O,N,R1,R2,R3> >(vec_negate_muladd<T,O,N,R1,R2,R3>(b.rep(),a.rep()));
    }

    /**
    * FMS from operator a-b*c where c is a scalar
    */
    template<class T, cyme::simd O, int N, class R1, class R2>
    vec<T,O,N, vec_mulsub<T,O,N,R1,R2,vec_scalar<T,O,N> > >
    forceinline operator -(typename identity<T>::value_type const& a,vec<T,O,N,vec_mul<T,O,N,R1,R2> >const& b){
        return  vec<T,O,N,vec_negate_muladd<T,O,N,R1,R2,vec_scalar<T,O,N> > >
            (vec_negate_muladd<T,O,N,R1,R2,vec_scalar<T,O,N> >(b.rep(),vec_scalar<T,O,N>(static_cast<T>(a))));
    }

    /**
    * FMS from operator a*b-c*d I introduce this new case, because the compiler can't distinguish
    * a*b - c*d (ambiguous fms(a,b,c*d) or fms(c,d,a*b)), with the two previous wrappers
    */
    template<class T, cyme::simd O, int N,class R1, class R2, class R3, class R4>
    vec<T,O,N, vec_mul_sub_mul<T,O,N,R1,R2,R3,R4> >
    forceinline operator -(vec<T,O,N,vec_mul<T,O,N,R1,R2> >const& a, vec<T,O,N,vec_mul<T,O,N,R3,R4> >const& b){
        return  vec<T,O,N, vec_mul_sub_mul<T,O,N,R1,R2,R3,R4> >(vec_mul_sub_mul<T,O,N,R1,R2,R3,R4>(a.rep(),b.rep()));
    }
}
#endif
