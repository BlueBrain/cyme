/*
 * Cyme - allocator.hpp, Copyright (c), 2014,
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

#ifndef CYME_ALLOCATOR_HPP 
#define CYME_ALLOCATOR_HPP

#include <assert.h> 
#include <stdlib.h> // POSIX, size_t is inside
#include "cyme/memory/detail/simd.h"
#include <limits>

namespace memory{

   /**
        \brief This class encapsulated the function allocate and deallocate for the memory allocation. I used POSX
        to allign on special memory bound.
    */
    template<class T, memory::simd O>
    class Align_POSIX{
    public:
        typedef std::size_t        size_type;
    protected:
        void* allocate_policy(size_type size) {
            assert((memory::trait_register<T,memory::__GETSIMD__()>::size) >=  sizeof(void*));
            if (size == 0)
                return NULL;

            void* ptr = NULL;
            int rc = posix_memalign(&ptr, memory::trait_register<T,memory::__GETSIMD__()>::a, size);

            if (rc != 0)
                return NULL;

            return ptr;
        }

        void deallocate_policy(void* ptr){
            free(ptr);
        }
    };

    /**
        \brief this class is an allocator for STL container especailly std::vector, I garanty the allocated buffer is bound 
        on 8-16 or 32 byte memory. It is a copy past from standard allocator, the only difference is the functions allocate
        and deallocate where I call my own function with the help of the policy pattern
    */
    template<class T, class Policy = Align_POSIX<T,__GETSIMD__()> >
    class Allocator : private Policy {
        using Policy::allocate_policy;
        using Policy::deallocate_policy;
    public:
        // stl compatibity
        typedef T                  value_type;
        typedef value_type*        pointer;
        typedef const value_type*  const_pointer;
        typedef value_type&        reference;
        typedef const value_type&  const_reference;
        typedef std::size_t        size_type;
        typedef std::ptrdiff_t     difference_type;

    public:
        // convert allocator<T, Policy> to allocator <U, Policy>
        template<class U>
        struct rebind{
            typedef Allocator<U, Policy> other;
        };

    public:
        inline explicit Allocator() {}
        inline ~Allocator() {}
        inline explicit Allocator(Allocator const&) {}
        template<typename U>
        inline explicit Allocator(Allocator<U, Policy> const&) {} 

        //adress
        inline pointer adress(reference r){return &r; }
        inline const_pointer adress(const_reference r){return &r;}

        //memory allocation
        inline pointer allocate(size_type cnt, typename std::allocator<void>::const_pointer = 0){
            return reinterpret_cast<pointer>(allocate_policy(cnt*sizeof(T))); // I call my allocator using my pattern
        }

        inline void deallocate(pointer p, size_type){
            deallocate_policy(p); // I call my dealocator
        }

        inline size_type max_size() const {
            return std::numeric_limits<size_type>::max() / sizeof(T);
        }

        //    construction/destruction
        inline void construct(pointer p, const T& t) { new(p) T(t); }
        inline void destroy(pointer p) { p->~T(); }

        inline bool operator==(Allocator const&) { return true; }
        inline bool operator!=(Allocator const& a) { return !operator==(a); }
    };

    template <class T, class TPolicy, class U, class UPolicy>
    inline bool operator== (Allocator<T,TPolicy> const& lhs, Allocator<U, UPolicy> const& rhs){ 
        return operator==(static_cast<TPolicy&>(lhs), static_cast<UPolicy&>(rhs));
    }

    template <class T, class TPolicy, class U, class UPolicy>
    inline bool operator!= (Allocator<T,TPolicy> const& lhs, Allocator<U, UPolicy> const& rhs){ 
        return operator!=(static_cast<TPolicy&>(lhs), static_cast<UPolicy&>(rhs));
    }

} //end namespace
#endif
