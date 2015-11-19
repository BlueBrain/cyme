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
 * @file cyme/core/simd_vector/math/detail/method/estrin.ipp
 * Implements the estrin algo for the evaluation of a polynomial
 */

#ifndef POLY_ESTRIN_IPP
#define POLY_ESTRIN_IPP

namespace poly{
    /** general test case, i is lower than the degree of the polynomial */
    template<class T, cyme::simd O, int N, template <class,int> class C,int i,
             bool b1 = (i<=poly_order<C>::value), bool b2 = (i == poly_order<C>::value)>
    struct binomial_helper{
        typedef cyme::vec_simd<T,O,N> helper_type;
        inline const static helper_type binomial(cyme::vec_simd<T,O,N> const& x){
            return cyme::vec_simd<T,O,N>(C<T,i>::coefficient()) + x*cyme::vec_simd<T,O,N>(C<T,i+1>::coefficient()); // a+b*x
        }
    };

    /** perticular case, i the degree of the polynomial */
    template<class T, cyme::simd O, int N,template <class,int> class C, int i>
    struct binomial_helper<T,O,N,C,i,true,true>{ // do i = poly_order<C>::value does not work so I add b2
        typedef cyme::vec_simd<T,O,N> helper_type;
        inline const static helper_type binomial(cyme::vec_simd<T,O,N> const& ){
            return cyme::vec_simd<T,O,N>(C<T,poly_order<C>::value>::coefficient()); // a
        }
    };

    /** perticular case, coefficent i does not exist 
        case where it returns 0 and class is not like 0 and basic type, I use
        trick see vec_simd.hpp, the type of binomial_helper can be ZERO or vec_simd
        that why I define the type in the class
     */
    template<class T, cyme::simd O, int N,template <class,int> class C, int i>
    struct binomial_helper<T,O,N,C,i,false,false>{
        typedef cyme::ZERO helper_type;
        inline const static helper_type binomial(cyme::vec_simd<T,O,N> const& ){
              return cyme::ZERO();
        }
    };

    /** Generalization of Horner's Rule for polynomial evaluation - W.S. Dorn, IBM journal, year 1962, page 240-245
    Estrin scheme - paper equation (3.6)
     */
    template<class T, cyme::simd O, int N,template <class,int> class C, int i, int n>
    struct helper_estrin{
        typedef typename helper_estrin<T,O,N,C,i,n-1>::helper_type helper_type;
        static inline helper_type estrin(cyme::vec_simd<T,O,N> const& x){
            return helper_estrin<T,O,N,C,i,n-1>::estrin(x) + cyme::pow<T,O,N,2*n>(x)*helper_estrin<T,O,N,C,i+(1<<n),n-1>::estrin(x);
        }
    };

    /** Generalization of Horner's Rule for polynomial evaluation - W.S. Dorn, IBM journal, year 1962, page 240-245
     Estrin scheme - final specialization - paper equation (3.5)
     */
    template<class T, cyme::simd O, int N,template <class,int> class C, int i>
    struct helper_estrin<T,O,N,C,i,0>{
        typedef typename binomial_helper<T,O,N,C,i>::helper_type helper_type;
        static inline helper_type estrin(cyme::vec_simd<T,O,N> const& x){
            return binomial_helper<T,O,N,C,i>::binomial(x);
        }
    };

    template<class T, cyme::simd O, int N,template <class,int> class C>
    inline cyme::vec_simd<T,O,N> estrin(cyme::vec_simd<T,O,N> const& x){
        return helper_estrin<T,O,N,C,0,poly_order<C>::value>::estrin(x);
    }

}

#endif
