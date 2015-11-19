/*
 * Cyme - bruteforce.hpp, Copyright (c), 2014,
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
 * @file cyme/core/simd_vector/math/detail/method/bruteforce.ipp
 * Implements a brute force algo to evaluate a polynomial
 */

#ifndef POLY_BRUTEFORCE_IPP
#define POLY_BRUTEFORCE_IPP

/** namespace for the polynomial evaluation only */
namespace poly{

    template<class T, cyme::simd O, int N, template <class,int> class C, int n, int n0>
    struct bruteforce_helper{
        inline static const cyme::vec_simd<T,O,N> bruteforce(cyme::vec_simd<T,O,N> const& x){
            return bruteforce_helper<T,O,N,C,n/2,n0>::bruteforce(x)
                    + bruteforce_helper<T,O,N,C,n-n/2,n0+n/2>::bruteforce(x);
        }
    };

    template<class T, cyme::simd O, int N, template <class,int> class C, int n0>
    struct bruteforce_helper<T,O,N,C,0,n0>{
        inline static const cyme::ZERO bruteforce(cyme::vec_simd<T,O,N> const& ){
            return cyme::ZERO();
        }
    };

    template<class T, cyme::simd O, int N, template <class,int k> class C, int n0>
    struct bruteforce_helper<T,O,N,C,1,n0>{
        inline static const cyme::vec_simd<T,O,N> bruteforce(cyme::vec_simd<T,O,N> const& x){
            return cyme::pow<T,O,N,n0>(x)*cyme::vec_simd<T,O,N>(C<T,n0>::coefficient()); // offset act here
        }
    };

    // specialization to avoid to compute a0*x^0 = a0, remove one load and one multiply
    template<class T, cyme::simd O, int N, template <class,int k> class C>
    struct bruteforce_helper<T,O,N,C,1,0>{
        inline static const cyme::vec_simd<T,O,N> bruteforce(cyme::vec_simd<T,O,N> const& ){
            return cyme::vec_simd<T,O,N>(C<T,0>::coefficient()); // offset act here
        }
    };

    /** interface with the real world */
    template<class T, cyme::simd O, int N, template <class,int> class C>
    inline cyme::vec_simd<T,O,N> bruteforce(cyme::vec_simd<T,O,N> const& x){
        return bruteforce_helper<T,O,N,C,poly_order<C>::value+1,0>::bruteforce(x);
    }
}
#endif
