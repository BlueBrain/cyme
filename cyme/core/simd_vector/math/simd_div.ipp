/*
 * Cyme - simd_div.hpp, Copyright (c), 2014,
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

#ifndef CYME_SIMD_DIV_HPP
#define CYME_SIMD_DIV_HPP

namespace numeric{
    /**
     \brief reccursive implementation of the Newton-Raphson algo
     */
    template<class T, memory::simd O, int N, std::size_t n>
    struct helper_div{
        static forceinline vec_simd<T,O,N> div(vec_simd<T,O,N> const& rhs){
#ifdef __FMA__
            return helper_div<T,O,N,n-1>::div(rhs)*negatemuladd(rhs,helper_div<T,O,N,n-1>::div(rhs),vec_simd<T,O,N>(2.0)); // FMA negate operations are differents between INTEL-IBM
#else
            return helper_div<T,O,N,n-1>::div(rhs)*(vec_simd<T,O,N>(2.0)-rhs*helper_div<T,O,N,n-1>::div(rhs));
#endif
        }
    };

    /**
     \brief reccursive init with 1/r approximation
     */
    template<class T, memory::simd O, int N>
    struct helper_div<T,O,N,0>{
        static forceinline vec_simd<T,O,N> div(vec_simd<T,O,N> const& rhs){
            return rec<T,O,N>(rhs);
        }
    };

    /**
     \brief function object calling Newton-Raphson algo <3, ^_^'
     */
    template<class T,memory::simd O, int N>
    struct NewtonRaphson_div{
        static forceinline vec_simd<T,O,N> div (const vec_simd<T,O,N>& lhs, const vec_simd<T,O,N>& rhs){ // lhs/rhs
            vec_simd<T,O,N> nrv = lhs*helper_div<T,O,N,div_recursion<T,O>::value>::div(rhs);
            return nrv;
        }
    };

    /**
     \brief function object calling vendor algo
     */
    template<class T,memory::simd O, int N>
    struct Vendor_div{
        static forceinline vec_simd<T,O,N> div(const vec_simd<T,O,N>& lhs, const vec_simd<T,O,N>& rhs){ // lhs/rhs
             vec_simd<T,O,N> nrv(lhs);
             nrv /= rhs;
             return nrv;
        }
    };    

    /**
    \brief selector for the division algorithm (vendor or Newton-Raphson)
    */
    template<class T, memory::simd O, int N, class Solver = NewtonRaphson_div<T,O,N> >
    struct Helper_div{
        static forceinline  vec_simd<T,O,N> div (const vec_simd<T,O,N>& lhs, const vec_simd<T,O,N>& rhs){ // lhs/rhs
            return Solver::div(lhs,rhs);
        }
    };

    /**
     \brief free function / operator between two vectors this function uses the return value optimization
     */
    template<class T,memory::simd O, int N>
    forceinline vec_simd<T,O,N> operator/ (const vec_simd<T,O,N>& lhs, const vec_simd<T,O,N>& rhs){
           return Helper_div<T,O,N>::div(lhs,rhs);
    }
} //end namespace
#endif
