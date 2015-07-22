/*
 * Cyme - expr_vec_ops.ipp, Copyright (c), 2014,
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
 * @file cyme/core/expression/expr_vec_ops.ipp
 * Defines usual mathematical operators
 */

#ifndef CYME_EXPR_VEC_OPS_IPP
#define CYME_EXPR_VEC_OPS_IPP

namespace cyme{
    /**  helper for the pow function.
    *
    * This extructure helps to transform the integer argument of pow(x,e) here e
    * as a template parameter for the pow_helper wrapper. The compiler will complain
    * because the e will be not used. Consenquently I disable the warning for the wrapper.
    */
    template<int M>
    struct exponent{
        const static int e = M;
    };

   /**  curious idendity object ^_^ .
    *
    * - thread on stackoverflow : http://stackoverflow.com/questions/26705581
    * - why?  http://en.cppreference.com/w/cpp/language/template_argument_deduction#Deduction_from_a_function_call
    */
    template <typename T>
    struct identity {
        typedef T value_type;
    };

    /**
    * abs(a) function
    */
    template<class T, cyme::simd O, int N, class R1>
    rvec<T,O,N,vec_abs<T,O,N,R1> >
    forceinline abs(rvec<T,O,N,R1> const& a){
        return rvec<T,O,N,vec_abs<T,O,N,R1> >(vec_abs<T,O,N,R1>(a.rep()));
    }

    /**
    * sin(a) function
    */
    template<class T, cyme::simd O, int N, class R1>
    rvec<T,O,N,vec_sin<T,O,N,R1> >
    forceinline sin(rvec<T,O,N,R1> const& a){
        return rvec<T,O,N,vec_sin<T,O,N,R1> >(vec_sin<T,O,N,R1>(a.rep()));
    }

    /**
    * cos(a) function
    */
    template<class T, cyme::simd O, int N, class R1>
    rvec<T,O,N,vec_cos<T,O,N,R1> >
    forceinline cos(rvec<T,O,N,R1> const& a){
        return rvec<T,O,N,vec_cos<T,O,N,R1> >(vec_cos<T,O,N,R1>(a.rep()));
    }

    /**
    * tan(a) function
    */
    template<class T, cyme::simd O, int N, class R1>
    rvec<T,O,N,vec_tan<T,O,N,R1> >
    forceinline tan(rvec<T,O,N,R1> const& a){
        return rvec<T,O,N,vec_tan<T,O,N,R1> >(vec_tan<T,O,N,R1>(a.rep()));
    }

    /**
    * sqrt(a) function
    */
    template<class T, cyme::simd O, int N, class R1>
    rvec<T,O,N,vec_sqrt<T,O,N,R1> >
    forceinline sqrt(rvec<T,O,N,R1> const& a){
        return rvec<T,O,N,vec_sqrt<T,O,N,R1> >(vec_sqrt<T,O,N,R1>(a.rep()));
    }

    /**
    * exp(a) function
    */
    template<class T, cyme::simd O, int N, class R1>
    rvec<T,O,N,vec_exp<T,O,N,R1> >
    forceinline exp(rvec<T,O,N,R1> const& a){
        return rvec<T,O,N,vec_exp<T,O,N,R1> >(vec_exp<T,O,N,R1>(a.rep()));
    }

    /**
    * exp2(a) function
    */
    template<class T, cyme::simd O, int N, class R1>
    rvec<T,O,N,vec_exp2<T,O,N,R1> >
    forceinline exp2(rvec<T,O,N,R1> const& a){
        return rvec<T,O,N,vec_exp2<T,O,N,R1> >(vec_exp2<T,O,N,R1>(a.rep()));
    }

    /**
    * exp10(a) function
    */
    template<class T, cyme::simd O, int N, class R1>
    rvec<T,O,N,vec_exp10<T,O,N,R1> >
    forceinline exp10(rvec<T,O,N,R1> const& a){
        return rvec<T,O,N,vec_exp10<T,O,N,R1> >(vec_exp10<T,O,N,R1>(a.rep()));
    }

    /**
    * log(a) function
    */
    template<class T, cyme::simd O, int N, class R1>
    rvec<T,O,N,vec_log<T,O,N,R1> >
    forceinline log(rvec<T,O,N,R1> const& a){
        return rvec<T,O,N,vec_log<T,O,N,R1> >(vec_log<T,O,N,R1>(a.rep()));
    }

    /**
    * log2(a) function
    */
    template<class T, cyme::simd O, int N, class R1>
    rvec<T,O,N,vec_log2<T,O,N,R1> >
    forceinline log2(rvec<T,O,N,R1> const& a){
        return rvec<T,O,N,vec_log2<T,O,N,R1> >(vec_log2<T,O,N,R1>(a.rep()));
    }

    /**
    * log10(a) function
    */
    template<class T, cyme::simd O, int N, class R1>
    rvec<T,O,N,vec_log10<T,O,N,R1> >
    forceinline log10(rvec<T,O,N,R1> const& a){
        return rvec<T,O,N,vec_log10<T,O,N,R1> >(vec_log10<T,O,N,R1>(a.rep()));
    }

    /**
    * pow(a,e) function, integer only
    */
    template<class T, cyme::simd O, int N, class R1, int M>
    rvec<T,O,N,vec_pow<T,O,N,R1,M> >
    forceinline pow(rvec<T,O,N,R1> const& a, exponent<M> const&  __attribute__((unused))e){ // fake for compiler
        return rvec<T,O,N,vec_pow<T,O,N,R1,M> >(vec_pow<T,O,N,R1,M>(a.rep()));
    }

    /**
    * negate operator optimisation --a = a
    */
    template<class T, cyme::simd O, int N, class R1>
    rvec<T,O,N,R1>
    forceinline operator-(rvec<T,O,N,vec_neg<T,O,N,R1> > const& a){
        return rvec<T,O,N,R1>(a.rep().op1());
    }

    /**
    * negate operator -a
    */
    template<class T, cyme::simd O, int N, class R1>
    rvec<T,O,N,vec_neg<T,O,N,R1> >
    forceinline operator-(rvec<T,O,N,R1> const& a){
        return rvec<T,O,N,vec_neg<T,O,N,R1> >(vec_neg<T,O,N,R1>(a.rep()));
    }

    /**
    * addition operator a+b
    */
    template<class T, cyme::simd O, int N, class R1, class R2>
    rvec<T,O, N,vec_add<T,O,N,R1,R2> >
    forceinline operator +(rvec<T,O,N,R1> const& a, rvec<T,O,N,R2> const& b){
        return rvec<T,O,N,vec_add<T,O,N,R1,R2> >(vec_add<T,O,N,R1,R2>(a.rep(),b.rep()));
    }

    /**
    * substraction operator a-b, warning substraction is not commutative
    */
    template<class T, cyme::simd O, int N, class R1, class R2>
    rvec<T,O,N,vec_sub<T,O,N,R1,R2> >
    forceinline operator -(rvec<T,O,N,R1> const& a, rvec<T,O,N,R2> const& b){
        return rvec<T,O,N,vec_sub<T,O,N,R1,R2> >(vec_sub<T,O,N,R1,R2>(a.rep(),b.rep()));
    }

    /**
    * division operator a/b, warning division is not commutative
    */
    template<class T, cyme::simd O, int N, class R1, class R2>
    rvec<T,O,N, vec_div<T,O,N,R1,R2> >
    forceinline operator /(rvec<T,O,N,R1> const& a, rvec<T,O,N,R2> const& b){
        return rvec<T,O,N,vec_div<T,O,N,R1,R2> >(vec_div<T,O,N,R1,R2>(a.rep(),b.rep()));
    }

    /**
    * multiplication operator a*b
    */
    template<class T, cyme::simd O, int N, class R1, class R2>
    rvec<T,O,N, vec_mul<T,O,N,R1,R2> >
    forceinline operator *(rvec<T,O,N,R1> const& a, rvec<T,O,N,R2> const& b){
        return rvec<T,O,N,vec_mul<T,O,N,R1,R2> >(vec_mul<T,O,N,R1,R2>(a.rep(),b.rep()));
    }


    /**
    * addition operator s+b where s is a scalar
    */
    template<class T, cyme::simd O, int N, class R2>
    forceinline rvec<T,O,N, vec_add<T,O,N,vec_scalar<T,O,N>,R2> >
    operator +(typename identity<T>::value_type const& s, rvec<T,O,N,R2> const& b){
        return rvec<T,O,N, vec_add<T,O,N, vec_scalar<T,O,N>, R2> >
            (vec_add<T,O,N,vec_scalar<T,O,N>,R2>(vec_scalar<T,O,N>(static_cast<T>(s)),b.rep()));
    }

    /**
    * addition operator a+s where s is a scalar
    */
    template<class T, cyme::simd O, int N, class R2>
    forceinline rvec<T,O,N, vec_add<T,O,N,vec_scalar<T,O,N>,R2> >
    operator +(rvec<T,O,N,R2> const& b, typename identity<T>::value_type const& s){
        return operator+(s,b);
    }

    /**
    * substraction operator s-b where s is a scalar
    */
    template<class T, cyme::simd O, int N, class R2>
    forceinline rvec<T,O,N, vec_sub<T,O,N, vec_scalar<T,O,N>,R2> >
    operator -(typename identity<T>::value_type const& s, rvec<T,O,N,R2> const& b){
        return rvec<T,O,N, vec_sub<T,O,N, vec_scalar<T,O,N>, R2> >
            (vec_sub<T,O,N, vec_scalar<T,O,N>,R2>(vec_scalar<T,O,N>(static_cast<T>(s)),b.rep()));
    }

    /**
    * substraction operator a-s where s is a scalar
    */
    template<class T, cyme::simd O, int N, class R2>
    forceinline rvec<T,O,N, vec_sub<T,O,N,R2, vec_scalar<T,O,N> > >
    operator -(rvec<T,O,N,R2> const& b,typename identity<T>::value_type const& s){
        return rvec<T,O,N, vec_sub<T,O,N,R2,vec_scalar<T,O,N> > >
            (vec_sub<T,O,N,R2,vec_scalar<T,O,N> >(b.rep(),vec_scalar<T,O,N>(static_cast<T>(s))));
    }

    /**
    * multiplication operator s*b where s is a scalar
    */
    template<class T, cyme::simd O, int N, class R2>
    forceinline rvec<T,O,N, vec_mul<T,O,N,vec_scalar<T,O,N>,R2> >
    operator *(typename identity<T>::value_type const& s, rvec<T,O,N,R2> const& b){
        return rvec<T,O,N, vec_mul<T,O,N,vec_scalar<T,O,N>, R2> >
            (vec_mul<T,O,N,vec_scalar<T,O,N>,R2>(vec_scalar<T,O,N>(static_cast<T>(s)),b.rep()));
    }

    /**
    * multiplication operator b*s where s is a scalar
    */
    template<class T, cyme::simd O, int N, class R2>
    forceinline rvec<T,O,N, vec_mul<T,O,N,vec_scalar<T,O,N>,R2> >
    operator *(rvec<T,O,N,R2> const& b, typename identity<T>::value_type const& s){
        return operator*(s,b);
    }

    /**
    * division operator s/b where s is a scalar, division is not commutative
    */
    template<class T, cyme::simd O, int N, class R2>
    forceinline rvec<T,O,N, vec_div<T,O,N, vec_scalar<T,O,N>,R2> >
    operator /(typename identity<T>::value_type const& s, rvec<T,O,N,R2> const& b){
        return rvec<T,O,N, vec_div<T,O,N,vec_scalar<T,O,N>, R2> >
            (vec_div<T,O,N,vec_scalar<T,O,N>,R2>(vec_scalar<T,O,N>(static_cast<T>(s)),b.rep()));
    }

    /**
    * division operator b/s where s is a scalar, the operation is transformed to b*1/s
    * where 1/s is computed at compile time
    */
    template<class T, cyme::simd O, int N, class R2>
    forceinline rvec<T,O,N, vec_mul<T,O,N, R2,vec_scalar<T,O,N> > >
    operator /(rvec<T,O,N, R2> const& b, typename identity<T>::value_type const& s){
        return  rvec<T,O,N,vec_mul<T,O,N,R2,vec_scalar<T,O,N> > >
            (vec_mul<T,O,N,R2,vec_scalar<T,O,N> >(b.rep(),vec_scalar<T,O,N>(1./static_cast<T>(s))));
    }
}

#endif
