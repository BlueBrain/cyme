/*
 * CYME, License
 * 
 * Timothee Ewart - Swiss Federal Institute of technology in Lausanne 
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef CYME_SIMD_VEC_HPP
#define CYME_SIMD_VEC_HPP

#include "core/simd_vector/trait.hpp"
#include "core/simd_vector/simd_wrapper.hpp"

namespace numeric{

    /**
      \brief Vector computation class. The SIMD register (hardware) is encapsulated. It is generic, it can be SEE, AVX or QPX.
      the type is given by the trait class (simd_trait)
    */
    template<class T,memory::simd O, int N>
    struct vec_simd{
        typedef typename simd_trait<T,O,N>::value_type value_type;
        typedef typename simd_trait<T,O,N>::pointer pointer;
        typedef typename simd_trait<T,O,N>::const_pointer const_pointer;
        typedef typename simd_trait<T,O,N>::register_type register_type;

        /**
         \brief construtor desired value else 0, note copy constructor generated automaticaly. Only used for constant.
         */
        forceinline explicit vec_simd(const value_type a);

        /**
         \brief construtor without nothing load a value cost */
        forceinline explicit vec_simd();

        /**
         \brief construtor for exp and log */
        forceinline explicit vec_simd(register_type x);

        /**
         \brief construtor from a pointer
         */
        forceinline vec_simd(const_pointer a);

        /**
         \brief bracket operator called by the parser (expr_vec)
         */
        forceinline vec_simd& operator()();

        /**
         \brief bracket operator called by the parser (expr_vec)
         */
        forceinline const vec_simd& operator()() const;

        /**
         \brief operator *= between two vectors
         */
        forceinline vec_simd& operator *=(const vec_simd& rhs);

        /**
         \brief operator /= between two vectors
         */
        forceinline vec_simd& operator /=(const vec_simd& rhs);

        /**
        \brief operator += between two vectors
        */
        forceinline vec_simd& operator +=(const vec_simd& rhs);

        /**
         \brief operator -= between two vectors
        */
        forceinline vec_simd& operator -=(const vec_simd& rhs);

        /**
         \brief Save the value into the register into the memory
        */
        forceinline void store(pointer a) const;

        /**
         \brief negate the value of the register 
        */
        forceinline vec_simd& neg();

#ifdef __FMA__
        /**
         \brief FMA operator
         */
        forceinline void ma(const vec_simd& lhs, const vec_simd& rhs);

        /**
         \brief FMS operator
         */
        forceinline void ms(const vec_simd& lhs, const vec_simd& rhs);

        /**
         \brief FMS operator, 2nd case of the operator -
         */
        forceinline void nma(const vec_simd& lhs, const vec_simd& rhs);

        /**
         \brief FMS operator, 2nd case of the operator -
         */
        forceinline void nms(const vec_simd& lhs, const vec_simd& rhs);
#endif
         /**
         \brief hardware Register
         */
        register_type xmm;
    };

    /**
     \brief cast int to float
     */
    template<class T, memory::simd O, int N>
    forceinline vec_simd<T,O,N> cast(const vec_simd<int,O,N>& ths);

    /**
     \brief return the 2^k where k is a vector base on an integer
     */
    template<class T,memory::simd O, int N>
    forceinline vec_simd<T,O,N> twok(const vec_simd<int,O,N>& rhs);

    /**
     \brief floor the value return a int simd register
     */
    template<class T,memory::simd O, int N>
    forceinline vec_simd<int,O,N> floor(vec_simd<T,O,N>& rhs);

    /**
    \brief free function for call the vendor exponential, this function uses the return value optimization
    */
    template<class T,memory::simd O, int N>
    forceinline vec_simd<T,O,N> exp_v(const vec_simd<T,O,N>& rhs){
        vec_simd<T,O,N> nrv(_mm_exp<T,O,N>(rhs.xmm));
        return nrv;
    }

    /**
    \brief free function for call the vendor logarithm, this function uses the return value optimization
    */
    template<class T,memory::simd O, int N>
    forceinline vec_simd<T,O,N> log_v(const vec_simd<T,O,N>& rhs){
        vec_simd<T,O,N> nrv(_mm_log<T,O,N>(rhs.xmm));
        return nrv;
    }
} //end namespace

#include "core/simd_vector/simd_vec.ipp"
#include "core/simd_vector/simd_math.hpp" // contains all math operations include

#endif
