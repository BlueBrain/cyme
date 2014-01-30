/* The following code declares class array,
 * an STL container (as wrapper) for arrays of constant size.
 *
 * See
 *      http://www.boost.org/libs/array/
 * for documentation.
 *
 * The original author site is at: http://www.josuttis.com/
 *
 * (C) Copyright Nicolai M. Josuttis 2001.
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * 30 jan 2014 - Tim big clean up (limited support)
 * 14 Apr 2012 - (mtc) Added support for boost::hash
 * 28 Dec 2010 - (mtc) Added cbegin and cend (and crbegin and crend) for C++Ox compatibility.
 * 10 Mar 2010 - (mtc) fill method added, matching resolution of the standard library working group.
 *      See <http://www.open-std.org/jtc1/sc22/wg21/docs/lwg-defects.html#776> or Trac issue #3168
 *      Eventually, we should remove "assign" which is now a synonym for "fill" (Marshall Clow)
 * 10 Mar 2010 - added workaround for SUNCC and !STLPort [trac #3893] (Marshall Clow)
 * 29 Jan 2004 - c_array() added, BOOST_NO_PRIVATE_IN_AGGREGATE removed (Nico Josuttis)
 * 23 Aug 2002 - fix for Non-MSVC compilers combined with MSVC libraries.
 * 05 Aug 2001 - minor update (Nico Josuttis)
 * 20 Jan 2001 - STLport fix (Beman Dawes)
 * 29 Sep 2000 - Initial Revision (Nico Josuttis)
 *
 * Jan 29, 2004
 */


// this file is just a copy past of the boost array, clean up, I need to align to get better performance


#ifndef BOOST_ARRAY_HPP
#define BOOST_ARRAY_HPP

#include <cstddef>
#include <stdexcept>
#include <boost/assert.hpp>
#include <boost/swap.hpp>

#include <boost/throw_exception.hpp>
#include <boost/functional/hash_fwd.hpp>
#include <algorithm>

#include "memory/detail/simd.h"


namespace boost { // Tim:  I keep the same name space else I am going to big mistake

    template<class T, std::size_t N>
    class array {
      public:
       T elems[N] __attribute__((aligned(static_cast<int>(memory::__GETSIMD__()))));    // fixed-size array of elements of type T, align
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
        reference operator[](size_type i) 
        { 
            BOOST_ASSERT_MSG( i < N, "out of range" );
            return elems[i];
        }
        
        const_reference operator[](size_type i) const 
        {     
            BOOST_ASSERT_MSG( i < N, "out of range" );
            return elems[i]; 
        }

        // at() with range check
        reference at(size_type i) { rangecheck(i); return elems[i]; }
        const_reference at(size_type i) const { rangecheck(i); return elems[i]; }
    
        // front() and back()
        reference front() 
        { 
            return elems[0]; 
        }
        
        const_reference front() const 
        {
            return elems[0];
        }
        
        reference back() 
        { 
            return elems[N-1]; 
        }
        
        const_reference back() const 
        { 
            return elems[N-1]; 
        }

        // size is constant
        static size_type size() { return N; }
        static bool empty() { return false; }
        static size_type max_size() { return N; }
        enum { static_size = N };

        // swap (note: linear complexity)
        void swap (array<T,N>& y) {
            for (size_type i = 0; i < N; ++i)
                boost::swap(elems[i],y.elems[i]);
        }

        // direct access to data (read-only)
        const T* data() const { return elems; }
        T* data() { return elems; }

        // use array as C array (direct read/write access to data)
        T* c_array() { return elems; }

        // assignment with type conversion
        template <typename T2>
        array<T,N>& operator= (const array<T2,N>& rhs) {
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
                std::out_of_range e("array<>: index out of range");
                boost::throw_exception(e);
            }
        }

    };

    // comparisons
    template<class T, std::size_t N>
    bool operator== (const array<T,N>& x, const array<T,N>& y) {
        return std::equal(x.begin(), x.end(), y.begin());
    }
    template<class T, std::size_t N>
    bool operator< (const array<T,N>& x, const array<T,N>& y) {
        return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());
    }
    template<class T, std::size_t N>
    bool operator!= (const array<T,N>& x, const array<T,N>& y) {
        return !(x==y);
    }
    template<class T, std::size_t N>
    bool operator> (const array<T,N>& x, const array<T,N>& y) {
        return y<x;
    }
    template<class T, std::size_t N>
    bool operator<= (const array<T,N>& x, const array<T,N>& y) {
        return !(y<x);
    }
    template<class T, std::size_t N>
    bool operator>= (const array<T,N>& x, const array<T,N>& y) {
        return !(x<y);
    }

    // global swap()
    template<class T, std::size_t N>
    inline void swap (array<T,N>& x, array<T,N>& y) {
        x.swap(y);
    }

    template<class T, std::size_t N>
    std::size_t hash_value(const array<T,N>& arr)
    {
        return boost::hash_range(arr.begin(), arr.end());
    }

} /* namespace boost */


#endif /*BOOST_ARRAY_HPP*/

    /* \endcond I do not need this part in the doc*/
