/*
 * Cyme - simd_exp.hpp, Copyright (c), 2014,
 * Timothee Ewart - Swiss Federal Institute of technology in Lausanne,
 * timothee.ewart@epfl.ch,
 * Kai Langen,
 * kai.langen@usask.ca,
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
 * @file cyme/core/simd_vector/math/simd_scatter.ipp
 * Implements scatter for vec_simd class
 */

#ifndef CYME_SIMD_SCATTER_IPP
#define CYME_SIMD_SCATTER_IPP

#include <boost/assert.hpp>

namespace cyme{

    template<class T,cyme::simd O, int N, cyme::scatter_op P>
    struct scatter_op_selector_helper{};

    template<class T,cyme::simd O, int N>
    struct scatter_op_selector_helper<T,O,N,cyme::add>{
        static void forceinline scatter_op_selector(vec_simd<T,O,N> const& a,vec_simd<T,O,N> & b){
            b += a;
        }
    };

    template<class T,cyme::simd O, int N>
    struct scatter_op_selector_helper<T,O,N,cyme::sub>{
        static void forceinline scatter_op_selector(vec_simd<T,O,N> const& a,vec_simd<T,O,N> & b){
            b -= a;
        }
    };

    template<class T,cyme::simd O, int N>
    struct scatter_op_selector_helper<T,O,N,cyme::mul>{
        static void forceinline scatter_op_selector(vec_simd<T,O,N> const& a,vec_simd<T,O,N> & b){
            b *= a;
        }
    };

    template<class T,cyme::simd O, int N>
    struct scatter_op_selector_helper<T,O,N,cyme::div>{
        static void forceinline scatter_op_selector(vec_simd<T,O,N> const& a,vec_simd<T,O,N> & b){
            b /= a;
        }
    };

    /** Free function that associate a scatter operations with an operations
     * We are looking for scatter add
     * 1) load the "destination" data into array
     * 2) create tmp SIMD vector
     * 3) do the op.
     * 4) scatter the res
     */
    template<class T,cyme::simd O, int N, cyme::scatter_op P>
    struct scatter_ops_helper{
        static void forceinline scatter_ops(vec_simd<T,O,N> const& u, T* dst, const int* ind, const int range){
            const int size = elems_helper<T,N>::size;
            BOOST_ASSERT_MSG( range <= size, "range larger than size" );
            T elems[size] __attribute__((aligned(static_cast<std::size_t>(cyme::trait_register<T,cyme::__GETSIMD__()>::size))));

            /** load data from the destination */
            for(int i = 0; i < range; i++)
                elems[i] = dst[ind[i]];

            vec_simd<T,O,N> tmp(_mm_load<typename simd_trait<T,O,N>::value_type,O,N>(elems));

            /** compute the operation before the final scatter */
            scatter_op_selector_helper<T,O,N,P>::scatter_op_selector(u,tmp);

            _mm_store<T,O,N>(tmp.xmm,elems);

            for(int i = 0; i < range; i++)
                dst[ind[i]] = elems[i];
        }
    };

    /** partial specialization for pure scatter operation */
    template<class T,cyme::simd O, int N>
    struct scatter_ops_helper<T,O,N,cyme::eq>{
        static void forceinline scatter_ops(vec_simd<T,O,N> const& u, T* dst, const int* ind, const int range){
            const std::size_t size = elems_helper<T,N>::size;
            T elems[size] __attribute__((aligned(static_cast<std::size_t>(cyme::trait_register<T,cyme::__GETSIMD__()>::size))));
            _mm_store<T,O,N>(u.xmm,elems);

            for(int i = 0; i < range; i++)
                dst[ind[i]] = elems[i];
        }
    };

    /** Free function for scatter */
    template<class T,cyme::simd O, int N, cyme::scatter_op P>
    void forceinline help_scatter(cyme::vec_simd<T,O,N> const& u, T* dst, const int* ind, const int range){
        scatter_ops_helper<T,O,N,P>::scatter_ops(u,dst,ind,range);
    }

}
#endif
