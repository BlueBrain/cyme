/*
 * Cyme - expr_vec_ops.hpp, Copyright (c), 2014,
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

#ifndef CYME_EXPR_VEC_OPS_HPP
#define CYME_EXPR_VEC_OPS_HPP

namespace numeric{
/** \cond I do not need this part in the doc */
    /*
        this extructure helps to transform the integer argument of pow(x,e) here e
        as a template parameter for the pow_helper wrapper
    */
    template<int M>
    struct exponent{
        const static int e = M;
    };


    /*
        curious idendity object ^_^ : 
        - thread on stackoverlow : http://stackoverflow.com/questions/26705581/operator-and-float-argument 
        - why?  http://en.cppreference.com/w/cpp/language/template_argument_deduction#Deduction_from_a_function_call
    */
    template <typename T>
    struct identity {
        typedef T value_type;
    };
    
    /* parser for the exp */
    template<class T, memory::simd O, int N, class R1>
    rvec<T,O,N,vec_sqrt<T,O,N,R1> >
    forceinline sqrt(rvec<T,O,N,R1> const& a){
        return rvec<T,O,N,vec_sqrt<T,O,N,R1> >(vec_sqrt<T,O,N,R1>(a.rep()));
    }
    
    /* parser for the exp */
    template<class T, memory::simd O, int N, class R1>
    rvec<T,O,N,vec_exp<T,O,N,R1> >
    forceinline exp(rvec<T,O,N,R1> const& a){
        return rvec<T,O,N,vec_exp<T,O,N,R1> >(vec_exp<T,O,N,R1>(a.rep()));
    }

    /* parser for the log */
    template<class T, memory::simd O, int N, class R1>
    rvec<T,O,N,vec_log<T,O,N,R1> >
    forceinline log(rvec<T,O,N,R1> const& a){
        return rvec<T,O,N,vec_log<T,O,N,R1> >(vec_log<T,O,N,R1>(a.rep()));
    }
    
    /* parser for pow */
    template<class T, memory::simd O, int N, class R1, int M>
    rvec<T,O,N,vec_pow<T,O,N,R1,M> >
    forceinline pow(rvec<T,O,N,R1> const& a, exponent<M> const& e){
        return rvec<T,O,N,vec_pow<T,O,N,R1,M> >(vec_pow<T,O,N,R1,M>(a.rep()));
    }
    
    /* parser for neg */
    // optimization -*- = +
    template<class T, memory::simd O, int N, class R1>
    rvec<T,O,N,R1>
    forceinline operator-(rvec<T,O,N,vec_neg<T,O,N,R1> > const& a){
        return rvec<T,O,N,R1>(a.rep().op1());
    }
    
    // orginal negation
    template<class T, memory::simd O, int N, class R1>
    rvec<T,O,N,vec_neg<T,O,N,R1> >
    forceinline operator-(rvec<T,O,N,R1> const& a){
        return rvec<T,O,N,vec_neg<T,O,N,R1> >(vec_neg<T,O,N,R1>(a.rep()));
    }
    
    /* this is the key of parser, describe every possibilities */
    //addition of two vectors v+w
    template<class T, memory::simd O, int N, class R1, class R2>
    rvec<T,O, N,vec_add<T,O,N,R1,R2> >
    forceinline operator +(rvec<T,O,N,R1> const& a, rvec<T,O,N,R2> const& b){
        return rvec<T,O,N,vec_add<T,O,N,R1,R2> >(vec_add<T,O,N,R1,R2>(a.rep(),b.rep()));
    }

    //subtraction of two vectors v-w
    template<class T, memory::simd O, int N, class R1, class R2>
    rvec<T,O,N,vec_sub<T,O,N,R1,R2> >
    forceinline operator -(rvec<T,O,N,R1> const& a, rvec<T,O,N,R2> const& b){
        return rvec<T,O,N,vec_sub<T,O,N,R1,R2> >(vec_sub<T,O,N,R1,R2>(a.rep(),b.rep()));
    }

    //division of two vectors v/w
    template<class T, memory::simd O, int N, class R1, class R2>
    rvec<T,O,N, vec_div<T,O,N,R1,R2> >
    forceinline operator /(rvec<T,O,N,R1> const& a, rvec<T,O,N,R2> const& b){
        return rvec<T,O,N,vec_div<T,O,N,R1,R2> >(vec_div<T,O,N,R1,R2>(a.rep(),b.rep()));
    }

    //multiplication of two vectors v*w
    template<class T, memory::simd O, int N, class R1, class R2>
    rvec<T,O,N, vec_mul<T,O,N,R1,R2> >
    forceinline operator *(rvec<T,O,N,R1> const& a, rvec<T,O,N,R2> const& b){
        return rvec<T,O,N,vec_mul<T,O,N,R1,R2> >(vec_mul<T,O,N,R1,R2>(a.rep(),b.rep()));
    }

    /* OK I give the type because the compiler makes me partial specialization*/
    /* C - TIM TO DO, PLEASE FIND A SOLUTION DUPLICATION IS EVIL */

    //addition of scalar/vector, lambda+v
    template<class T, memory::simd O, int N, class R2>
    forceinline rvec<T,O,N, vec_add<T,O,N,vec_scalar<T,O,N>,R2> >
    operator +(typename identity<T>::value_type const& s, rvec<T,O,N,R2> const& b){
        return rvec<T,O,N, vec_add<T,O,N, vec_scalar<T,O,N>, R2> >(vec_add<T,O,N,vec_scalar<T,O,N>,R2>(vec_scalar<T,O,N>(static_cast<T>(s)),b.rep()));
    }

    //v + lambda
    template<class T, memory::simd O, int N, class R2>
    forceinline rvec<T,O,N, vec_add<T,O,N,vec_scalar<T,O,N>,R2> >
    operator +(rvec<T,O,N,R2> const& b, typename identity<T>::value_type const& s){
        return operator+(s,b);// CHECK IF NO COPY
    }

    // Tim to Tim FYI A-B != B-A
    //subtraction of scalar/vector
    template<class T, memory::simd O, int N, class R2>
    forceinline rvec<T,O,N, vec_sub<T,O,N, vec_scalar<T,O,N>,R2> >
    operator -(typename identity<T>::value_type const& s, rvec<T,O,N,R2> const& b){
        return rvec<T,O,N, vec_sub<T,O,N, vec_scalar<T,O,N>, R2> >(vec_sub<T,O,N, vec_scalar<T,O,N>,R2>(vec_scalar<T,O,N>(static_cast<T>(s)),b.rep()));
    }

    template<class T, memory::simd O, int N, class R2>
    forceinline rvec<T,O,N, vec_sub<T,O,N,R2, vec_scalar<T,O,N> > >
    operator -(rvec<T,O,N,R2> const& b,typename identity<T>::value_type const& s){
        return rvec<T,O,N, vec_sub<T,O,N,R2,vec_scalar<T,O,N> > >(vec_sub<T,O,N,R2,vec_scalar<T,O,N> >(b.rep(),vec_scalar<T,O,N>(static_cast<T>(s))));
    }

    //multiplication of scalar/vector, lambda*
    template<class T, memory::simd O, int N, class R2>
    forceinline rvec<T,O,N, vec_mul<T,O,N,vec_scalar<T,O,N>,R2> >
    operator *(typename identity<T>::value_type const& s, rvec<T,O,N,R2> const& b){
        return rvec<T,O,N, vec_mul<T,O,N,vec_scalar<T,O,N>, R2> >(vec_mul<T,O,N,vec_scalar<T,O,N>,R2>(vec_scalar<T,O,N>(static_cast<T>(s)),b.rep()));
    }

    //multiplication of scalar/vector, lambda*v 
    template<class T, memory::simd O, int N, class R2>
    forceinline rvec<T,O,N, vec_mul<T,O,N,vec_scalar<T,O,N>,R2> >
    operator *(rvec<T,O,N,R2> const& b, typename identity<T>::value_type const& s){
        return operator*(s,b); 
    }
    
    // Tim to Tim FYI A/B != B/A
    //division of scalar/vector, lambda*v 
    template<class T, memory::simd O, int N, class R2>
    forceinline rvec<T,O,N, vec_div<T,O,N, vec_scalar<T,O,N>,R2> >
    operator /(typename identity<T>::value_type const& s, rvec<T,O,N,R2> const& b){
        return rvec<T,O,N, vec_div<T,O,N,vec_scalar<T,O,N>, R2> >(vec_div<T,O,N,vec_scalar<T,O,N>,R2>(vec_scalar<T,O,N>(static_cast<T>(s)),b.rep()));
    }

    //v / lambda(double)   =   v * (1/lambda ) [optimization for scalars]
    template<class T, memory::simd O, int N, class R2>
    forceinline rvec<T,O,N, vec_mul<T,O,N, R2,vec_scalar<T,O,N> > >
    operator /(rvec<T,O,N, R2> const& b, typename identity<T>::value_type const& s){
        return  rvec<T,O,N,vec_mul<T,O,N,R2,vec_scalar<T,O,N> > >(vec_mul<T,O,N,R2,vec_scalar<T,O,N> >(b.rep(),vec_scalar<T,O,N>(1./static_cast<T>(s))));
    }

/** \endcond I do not need this part in the doc */
}
    
#endif
