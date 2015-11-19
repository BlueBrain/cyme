/*
 * Cyme - estrin.hpp, Copyright (c), 2014,
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
 * @file cyme/core/simd_vector/math/detail/method/horner.ipp
 * Implements the horner algo for the evaluation of a polynomial
 */

#ifndef POLY_HORNER_IPP
#define POLY_HORNER_IPP

namespace poly{

    template<class T, cyme::simd O, int N, template <class,int> class C, int n, int m, bool b1 = (n<=poly_order<C>::value),
                                           bool b2 = (n == poly_order<C>::value)> // idem than estrin pb
    struct helper_horner{
        static inline cyme::vec_simd<T,O,N> horner(cyme::vec_simd<T,O,N> const& x){
            return cyme::vec_simd<T,O,N>(C<T,n>::coefficient())+x*helper_horner<T,O,N,C,n+m,m>::horner(x);
        }
    };

    template<class T, cyme::simd O, int N, template <class,int> class C,int n, int m>
    struct helper_horner<T,O,N,C,n,m,true,true>{ // n is the max degree
        static inline cyme::vec_simd<T,O,N> horner(cyme::vec_simd<T,O,N> const&){
            return cyme::vec_simd<T,O,N>(C<T,poly_order<C>::value>::coefficient());
        }
    };

    /** case where it return 0 and class is not like 0 and basic type, I use trick see vec_simd.hpp */
    template<class T, cyme::simd O, int N, template <class,int> class C,int n, int m>
    struct helper_horner<T,O,N,C,n,m,false,false>{ // looking for a coefficient larger than the max degree
        static inline cyme::ZERO horner(cyme::vec_simd<T,O,N> const&){
            return cyme::ZERO();
        }
    };

    /**
    Generalization of Horner's Rule for polynomial evaluation - W.S. Dorn, year 1962, page 240-245
    Horner k-order scheme - paper equation (3.4)
    */
    template<class T, cyme::simd O, int N, template <class,int> class C,int k,int m>
    struct helper_horner_kth{
        static inline cyme::vec_simd<T,O,N> horner_kth(cyme::vec_simd<T,O,N> const& x){
            return cyme::pow<T,O,N,k-1>(x)*helper_horner<T,O,N,C,k-1,m>::horner(cyme::pow<T,O,N,m>(x))
                                          +helper_horner_kth<T,O,N,C,k-1,m>::horner_kth(x);
        }
    };

    /** partial spezialisation when k=1 -> k-1 =0 I do not want compute the pow(0)*/ 
    template<class T, cyme::simd O, int N, template <class,int> class C,int m>
    struct helper_horner_kth<T,O,N,C,1,m>{
        static inline cyme::vec_simd<T,O,N> horner_kth(cyme::vec_simd<T,O,N> const& x){
            return helper_horner<T,O,N,C,0,m>::horner(cyme::pow<T,O,N,m>(x))
                   + helper_horner_kth<T,O,N,C,0,m>::horner_kth(x);
        }
    };

    /** case where it return 0 and class is not like 0 and basic type, I use
    trick see vec_simd.hpp */
    template<class T, cyme::simd O, int N, template <class,int> class C,int m>
    struct helper_horner_kth<T,O,N,C,0,m>{
        static inline cyme::ZERO horner_kth(cyme::vec_simd<T,O,N> const& ){
            return cyme::ZERO();
        }
    };

    template<class T, cyme::simd O, int N, template <class,int> class C, int m>
    inline cyme::vec_simd<T,O,N> horner_kth(cyme::vec_simd<T,O,N> const& x){
        return helper_horner_kth<T,O,N,C,m,m>::horner_kth(x);
    }
}
#endif
