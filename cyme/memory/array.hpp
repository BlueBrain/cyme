/*
 * Cyme - array.hpp, Copyright (c), 2014,
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
* @file cyme/memory/array.hpp
* Defines array class based on boost::array
*/

#ifndef CYME_ARRAY_HPP
#define CYME_ARRAY_HPP

#include "cyme/memory/detail/array_helper.ipp" // copy of boost::array + align
#include "cyme/memory/detail/storage.hpp"

namespace cyme {

/** cyme::array container based on the boost::array.
*
*
*  The cyme::array provides a static container. The container must be
*  declared with a structure under the following form
*  \code{.cpp}
*  template<class T> struct
*  my_object{ typedef T value_type; // the value_type float or double static
*  const int value_size = 8; // your object has 8 fields };
*  \endcode
*  The container supports
*  two memory layout AoS and AoSoA. The containers of cyme are constructed over
*  a basic array named cyme::storage (or storage_type), the size of storage
*  depends of the value_size and the requested SIMD technology.
*/
template <class T, std::size_t N, cyme::order O>
class array {};

/** Specialisation of the cyme::array for the AoS layout.  */
template <class T, std::size_t N>
class array<T, N, cyme::AoS> {
  public:
    const static cyme::order order_value = cyme::AoS;
    typedef std::size_t size_type;
    typedef typename T::value_type value_type;
    typedef value_type &reference;
    typedef const value_type &const_reference;
    typedef cyme::storage<value_type, T::value_size, cyme::AoS> storage_type;
    typedef cyme::array_helper<storage_type, N> base_type;
    typedef typename base_type::iterator iterator;
    typedef typename base_type::const_iterator const_iterator;

    /** Default constructor, initialisation to zero */
    explicit array() { std::fill(data.begin(), data.end(), storage_type()); }

    /** Constructor, initialisation to given value */
    array(value_type value) { std::fill(data.begin(), data.end(), storage_type(value)); }

    /** Return first iterator */
    iterator begin() { return data.begin(); }

    /** Return last iterator */
    iterator end() { return data.end(); }

    /** Return the storage_type needed for writing */
    inline storage_type &operator[](size_type i) { return data[i]; }

    /** Return the storage_type needed for reading */
    const inline storage_type &operator[](size_type i) const { return data[i]; }

    /** Return the size of storage_type */
    static inline size_type size_block() { return T::value_size; }

    /** Return the number of storage_type */
    inline size_type size() { return data.size(); }

    /** Return a needed element of particular storage_type - serial - write */
    inline reference operator()(size_type i, size_type j) {
        BOOST_ASSERT_MSG(i < base_type::size(), "out of range: storage_type_v AoS i");
        BOOST_ASSERT_MSG(j < T::value_size, "out of range: storage_type_v AoS j");
        return data[i](j);
    }

    /** Return a needed element of particular storage_type - serial - read */
    inline const_reference operator()(size_type i, size_type j) const {
        BOOST_ASSERT_MSG(i < base_type::size(), "out of range: storage_type_v AoS i");
        BOOST_ASSERT_MSG(j < T::value_size, "out of range: storage_type_v AoS j");
        return data[i](j);
    }

  private:
    base_type data;
};

/** Specialisation of the cyme::array for the AoSoS layout.  */
template <class T, std::size_t N>
class array<T, N, cyme::AoSoA> {
  public:
    const static cyme::order order_value = cyme::AoSoA;
    typedef std::size_t size_type;
    typedef typename T::value_type value_type;
    typedef value_type &reference;
    typedef const value_type &const_reference;

    static const size_type offset =
        cyme::unroll_factor::N * cyme::trait_register<value_type, cyme::__GETSIMD__()>::size / sizeof(value_type);

    static const size_type storage_width = N / offset + 1;

    typedef cyme::storage<value_type, offset * T::value_size, cyme::AoSoA> storage_type;
    typedef cyme::array_helper<storage_type, storage_width> base_type;

    typedef typename base_type::iterator iterator;
    typedef typename base_type::const_iterator const_iterator;

    /** Default constructor, initialisation to zero */
    explicit array() {
        for (size_type i(0); i < storage_width; ++i)
            data[i] = storage_type(); // fill up to 0
    }

    /** Constructor, initialisation to given value */
    array(value_type value) {
        for (size_type i(0); i < storage_width; ++i)
            data[i] = storage_type(value);
    }

    /** Return first iterator */
    iterator begin() { return data.begin(); }

    /** Return last iterator */
    iterator end() { return data.end(); }

    /** Return the storage_type needed for writing */
    inline storage_type &operator[](size_type i) { return data[i]; }

    /** Return the storage_type needed for reading */
    const inline storage_type &operator[](size_type i) const { return data[i]; }

    /** Return the size of storage_type */
    static inline size_type size_block() { return T::value_size; }

    /** Return the number of storage_type */
    inline size_type size() { return data.size(); }

    /** Return a needed element of perticular storage_type - serial - write */
    inline reference operator()(size_type i, size_type j) {
        // nothing on i as the original size is destroyed in the constructor
        BOOST_ASSERT_MSG(j < T::value_size, "out of range: storage_type_v AoSoA j");
        // Please tune me ! (does it exist an alternative to this ? ^_^
        return data[(i * T::value_size + j) / (T::value_size * offset)](j * offset + i % offset); // [..i..](..j..)
    }

    /** Return a needed element of perticular storage_type - serial - read */
    inline const_reference operator()(size_type i, size_type j) const {
        // nothing on i as the original size is destroyed in the constructor
        BOOST_ASSERT_MSG(j < T::value_size, "out of range: storage_type_v AoSoA j");
        // Please tune me ! (does it exist an alternative to this ? ^_^
        return data[(i * T::value_size + j) / (T::value_size * offset)](j * offset + i % offset); // [..i..](..j..)
    }

  private:
    base_type data;
    size_type size_cyme;
};
}

#endif
