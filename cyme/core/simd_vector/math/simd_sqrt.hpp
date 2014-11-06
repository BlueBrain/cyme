/*
 * Cyme - simd_sqrt.hpp, Copyright (c), 2014,
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

#ifndef CYME_SIMD_SQRT_HPP
#define CYME_SIMD_SQRT_HPP

namespace numeric{

    /**
     \brief reccursive implementation of the Newton-Raphson algo
     */
    template<class T, memory::simd O, int N, std::size_t n>
    struct helper_rsqrt{
        static forceinline vec_simd<T,O,N> rsqrt(vec_simd<T,O,N> const& rhs){
#ifdef __FMA__
          return vec_simd<T,O,N>(0.5)*helper_rsqrt<T,O,N,n-1>::rsqrt(rhs)*negatemuladd(rhs,helper_rsqrt<T,O,N,n-1>::rsqrt(rhs)*helper_rsqrt<T,O,N,n-1>::rsqrt(rhs),vec_simd<T,O,N>(3.0)); // FMA negate operations are differents between INTEL-IBM
#else
            return vec_simd<T,O,N>(0.5)*helper_rsqrt<T,O,N,n-1>::rsqrt(rhs)*(vec_simd<T,O,N>(3.0)-rhs*helper_rsqrt<T,O,N,n-1>::rsqrt(rhs)*helper_rsqrt<T,O,N,n-1>::rsqrt(rhs));
#endif
        }
    };

    /**
     \brief reccursive init with 1/r approximation
     */
    template<class T, memory::simd O, int N>
    struct helper_rsqrt<T,O,N,0>{
        static forceinline vec_simd<T,O,N> rsqrt(vec_simd<T,O,N> const& rhs){
            return recsqrt<T,O,N>(rhs);
        }
    };

    /**
     \brief function object calling Newton-Raphson algo <3, ^_^'
     */
    template<class T,memory::simd O, int N>
    struct NewtonRaphson_sqrt{
        static forceinline vec_simd<T,O,N> sqrt (const vec_simd<T,O,N>& rhs){ // lhs/rhs
            vec_simd<T,O,N> nrv = rhs*helper_rsqrt<T,O,N,sqrt_recursion<T,O>::value>::rsqrt(rhs); // x * 1/sqrt(x)
            return nrv;
        }
    };

    /**
     \brief Vendor implementation of the sqrtarithm
     */
    template<class T, memory::simd O, int N>
    struct Vendor_sqrt{
        static forceinline vec_simd<T,O,N> sqrt(vec_simd<T,O,N> const& a){
            return sqrt_v(a); /* call vendor wrapper */
        }
    };


    /**
     \brief helper selector for the sqrt because BG/Q does not support natively square root
     */
    template<class T, memory::simd O, int N>
    struct helper_Solver{
#ifdef __x86_64__
        typedef Vendor_sqrt<T,O,N> Solver_sqrt;
#elif _ARCH_QP
        typedef NewtonRaphson_sqrt<T,O,N> Solver_sqrt;
#endif
    };

    /**
     \brief Selector for the sqrt
     \warning BG/Q does not support natively square root
    */
    template<class T, memory::simd O, int N, class Solver = typename helper_Solver<T,O,N>::Solver_sqrt >
    struct Selector_sqrt{
         static forceinline vec_simd<T,O,N> sqrt(vec_simd<T,O,N> x){
               x = Solver::sqrt(x);
               return x;
         }
    };

    /**
        \brief final wrapper for the sqrt
    */
    template<class T,memory::simd O, int N>
    forceinline vec_simd<T,O,N> sqrt(const vec_simd<T,O,N>& rhs){
        return Selector_sqrt<T,O,N>::sqrt(rhs);
    }
}
#endif

