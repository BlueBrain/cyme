/*
 * Cyme - array_helper.hpp, Copyright (c), 2014,
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


// this file is just a copy past of the boost array_helper, clean up, I need to align to get better performance


#ifndef BOOST_ARRAY_CYME_HPP
#define BOOST_ARRAY_CYME_HPP

#include <cstddef>
#include <stdexcept>
#include <boost/assert.hpp>
#include <boost/swap.hpp>

#include <boost/throw_exception.hpp>
#include <boost/functional/hash_fwd.hpp>
#include <algorithm>

#include "cyme/memory/detail/simd.h"


namespace cyme { 

    template<class T, std::size_t N>
    class array_helper {
      public:
        T elems[N] __attribute__((aligned(static_cast<int>(memory::trait_register<T,memory::__GETSIMD__()>::size))));    // fixed-size array_helper of elements of type T, align
      //  T elems[N];    // fixed-size array_helper of elements of type T, align
      public:
        // type definitions
        typedef T              value_type;
        typedef T*             iterator;
        typedef const T*       const_iterator;
        typedef T&             reference;
        typedef const T&       const_reference;
        typedef std::size_t    size_type;
        typedef std::ptrdiff_t difference_type;

        // iterator support
        iterator        begin()       { return elems; }
        const_iterator  begin() const { return elems; }
        const_iterator cbegin() const { return elems; }
        
        iterator        end()       { return elems+N; }
        const_iterator  end() const { return elems+N; }
        const_iterator cend() const { return elems+N; }

        // reverse iterator support
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        reverse_iterator rbegin() { return reverse_iterator(end()); }
        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }
        const_reverse_iterator crbegin() const {
            return const_reverse_iterator(end());
        }

        reverse_iterator rend() { return reverse_iterator(begin()); }
        const_reverse_iterator rend() const {
            return const_reverse_iterator(begin());
        }
        const_reverse_iterator crend() const {
            return const_reverse_iterator(begin());
        }

        // operator[]
        reference operator[](size_type i) {
            BOOST_ASSERT_MSG( i < N, "out of range" );
            return elems[i];
        }
        
        const_reference operator[](size_type i) const {
            BOOST_ASSERT_MSG( i < N, "out of range" );
            return elems[i]; 
        }

        // at() with range check
        reference at(size_type i) { rangecheck(i); return elems[i]; }
        const_reference at(size_type i) const { rangecheck(i); return elems[i]; }
    
        // front() and back()
        reference front() {
            return elems[0]; 
        }
        
        const_reference front() const {
            return elems[0];
        }
        
        reference back() {
            return elems[N-1]; 
        }
        
        const_reference back() const {
            return elems[N-1]; 
        }

        // size is constant
        static size_type size() { return N; }
        static bool empty() { return false; }
        static size_type max_size() { return N; }
        enum { static_size = N };

        // swap (note: linear complexity)
        void swap (array_helper<T,N>& y) {
            for (size_type i = 0; i < N; ++i)
                boost::swap(elems[i],y.elems[i]);
        }

        // direct access to data (read-only)
        const T* data() const { return elems; }
        T* data() { return elems; }

        // use array_helper as C array_helper (direct read/write access to data)
        T* c_array_helper() { return elems; }

        // assignment with type conversion
        template <typename T2>
        array_helper<T,N>& operator= (const array_helper<T2,N>& rhs) {
            std::copy(rhs.begin(),rhs.end(), begin());
            return *this;
        }

        // assign one value to all elements
        void assign (const T& value) { fill ( value ); }    // A synonym for fill
        void fill   (const T& value)
        {
            std::fill_n(begin(),size(),value);
        }

        // check range (may be private because it is static)
        static void rangecheck (size_type i) {
            if (i >= size()) {
                std::out_of_range e("array_helper<>: index out of range");
                boost::throw_exception(e);
            }
        }

    };

    // comparisons
    template<class T, std::size_t N>
    bool operator== (const array_helper<T,N>& x, const array_helper<T,N>& y) {
        return std::equal(x.begin(), x.end(), y.begin());
    }
    template<class T, std::size_t N>
    bool operator< (const array_helper<T,N>& x, const array_helper<T,N>& y) {
        return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());
    }
    template<class T, std::size_t N>
    bool operator!= (const array_helper<T,N>& x, const array_helper<T,N>& y) {
        return !(x==y);
    }
    template<class T, std::size_t N>
    bool operator> (const array_helper<T,N>& x, const array_helper<T,N>& y) {
        return y<x;
    }
    template<class T, std::size_t N>
    bool operator<= (const array_helper<T,N>& x, const array_helper<T,N>& y) {
        return !(y<x);
    }
    template<class T, std::size_t N>
    bool operator>= (const array_helper<T,N>& x, const array_helper<T,N>& y) {
        return !(x<y);
    }

    // global swap()
    template<class T, std::size_t N>
    inline void swap (array_helper<T,N>& x, array_helper<T,N>& y) {
        x.swap(y);
    }

    template<class T, std::size_t N>
    std::size_t hash_value(const array_helper<T,N>& arr) {
        return boost::hash_range(arr.begin(), arr.end());
    }

} /* namespace boost */


#endif /*BOOST_ARRAY_HPP*/

    /* \endcond I do not need this part in the doc*/
