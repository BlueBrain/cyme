/*
 * Cyme - expr_vec_fma.hpp, Copyright (c), 2014,
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

#ifndef CYME_EXPR_VEC_FMA_HPP
#define CYME_EXPR_VEC_FMA_HPP

namespace numeric{
/** \cond I do not need this part in the doc */
    //mul add a*b + c
    template<class T, memory::simd O, int N, class R1, class R2, class R3>
    rvec<T,O,N, vec_muladd<T,O,N,R1,R2,R3> >
    forceinline operator +(rvec<T,O,N,vec_mul<T,O,N,R1,R2> >const& a, rvec<T,O,N,R3> const& b){
        return  rvec<T,O,N,vec_muladd<T,O,N,R1,R2,R3> >(vec_muladd<T,O,N,R1,R2,R3>(a.rep(),b.rep()));
    }

    //mul add a*b + c where c (lambda)
    template<class T, memory::simd O, int N, class R1, class R2>
    rvec<T,O,N, vec_muladd<T,O,N,R1,R2,vec_scalar<T,O,N> > >
    forceinline operator +(rvec<T,O,N,vec_mul<T,O,N,R1,R2> >const& a, typename identity<T>::value_type const& b){
        return  rvec<T,O,N,vec_muladd<T,O,N,R1,R2,vec_scalar<T,O,N> > >(vec_muladd<T,O,N,R1,R2,vec_scalar<T,O,N> >(a.rep(),vec_scalar<T,O,N>(static_cast<T>(b))));
    }

    //mul add a + b*c
    template<class T, memory::simd O, int N, class R1, class R2, class R3>
    rvec<T,O,N, vec_muladd<T,O,N,R1,R2,R3> >
    forceinline operator +(rvec<T,O,N,R3> const& b, rvec<T,O,N,vec_mul<T,O,N,R1,R2> >const& a){
        return operator+(a,b); //take previous one ^_^, as the addition is commutative 
    }

    //mul add c+ a*b  where c (lambda)
    template<class T, memory::simd O, int N, class R1, class R2>
    rvec<T,O,N, vec_muladd<T,O,N,R1,R2,vec_scalar<T,O,N> > >
    forceinline operator +(typename identity<T>::value_type const& b, rvec<T,O,N,vec_mul<T,O,N,R1,R2> >const& a){
        return operator+(a,b);
    }

    //mul add a*b + c*d, I introduce this new case, because the compiler can't distinguish a*b + c*d (ambiguous fma(a,b,c*d) or fma(c,d,a*b)), with the two previous wrappers
    template<class T, memory::simd O, int N, class R1, class R2, class R3, class R4>
    rvec<T,O,N, vec_mul_add_mul<T,O,N,R1,R2,R3,R4> >
    forceinline operator +(rvec<T,O,N,vec_mul<T,O,N,R1,R2> >const& a, rvec<T,O,N,vec_mul<T,O,N,R3,R4> >const& b){
        return  rvec<T,O,N, vec_mul_add_mul<T,O,N,R1,R2,R3,R4> >(vec_mul_add_mul<T,O,N,R1,R2,R3,R4>(a.rep(),b.rep()));
    }

    //mul sub a*b - c
    template<class T, memory::simd O, int N, class R1, class R2, class R3>
    rvec<T,O,N, vec_mulsub<T,O,N,R1,R2,R3> >
    forceinline operator -(rvec<T,O,N,vec_mul<T,O,N,R1,R2> >const& a, rvec<T,O,N,R3> const& b){
        return  rvec<T,O,N, vec_mulsub<T,O,N,R1,R2,R3> >(vec_mulsub<T,O,N,R1,R2,R3>(a.rep(),b.rep()));
    }

    //mul add a*b - c where c (lambda)
    template<class T, memory::simd O, int N, class R1, class R2>
    rvec<T,O,N, vec_mulsub<T,O,N,R1,R2,vec_scalar<T,O,N> > >
    forceinline operator -(rvec<T,O,N,vec_mul<T,O,N,R1,R2> >const& a, typename identity<T>::value_type const& b){
        return  rvec<T,O,N,vec_mulsub<T,O,N,R1,R2,vec_scalar<T,O,N> > >(vec_mulsub<T,O,N,R1,R2,vec_scalar<T,O,N> >(a.rep(),vec_scalar<T,O,N>(static_cast<T>(b))));
    }

    //mul sub a - b*c
    template<class T, memory::simd O, int N, class R1, class R2, class R3>
    rvec<T,O,N, vec_negate_muladd<T,O,N,R1,R2,R3> >
    forceinline operator -(rvec<T,O,N,R3> const& a, rvec<T,O,N,vec_mul<T,O,N,R1,R2> >const& b){
        return  rvec<T,O,N, vec_negate_muladd<T,O,N,R1,R2,R3> >(vec_negate_muladd<T,O,N,R1,R2,R3>(b.rep(),a.rep()));
    }

    //mul add c - a*b  where c (lambda)
    template<class T, memory::simd O, int N, class R1, class R2>
    rvec<T,O,N, vec_mulsub<T,O,N,R1,R2,vec_scalar<T,O,N> > >
    forceinline operator -(typename identity<T>::value_type const& a,rvec<T,O,N,vec_mul<T,O,N,R1,R2> >const& b){
        return  rvec<T,O,N,vec_negate_muladd<T,O,N,R1,R2,vec_scalar<T,O,N> > >(vec_negate_muladd<T,O,N,R1,R2,vec_scalar<T,O,N> >(b.rep(),vec_scalar<T,O,N>(static_cast<T>(a))));
    }

    //mul add a*b - c*d, I introduce this new case, because the compiler can't distinguish a*b - c*d (ambiguous fms(a,b,c*d) or fms(c,d,a*b)), with the two previous wrappers
    template<class T, memory::simd O, int N,class R1, class R2, class R3, class R4>
    rvec<T,O,N, vec_mul_sub_mul<T,O,N,R1,R2,R3,R4> >
    forceinline operator -(rvec<T,O,N,vec_mul<T,O,N,R1,R2> >const& a, rvec<T,O,N,vec_mul<T,O,N,R3,R4> >const& b){
        return  rvec<T,O,N, vec_mul_sub_mul<T,O,N,R1,R2,R3,R4> >(vec_mul_sub_mul<T,O,N,R1,R2,R3,R4>(a.rep(),b.rep()));
    }
}
#endif
