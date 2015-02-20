/*
 * Cyme - vector.hpp, Copyright (c), 2014,
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
* @file cyme/memory/vector.hpp
* Defines a vector class
*/

#ifndef CYME_VECTOR_HPP
#define CYME_VECTOR_HPP

#include <vector>
#include "cyme/memory/allocator.hpp"
#include "cyme/memory/detail/storage.hpp"

namespace cyme{

/** cyme::vector container based on the std::vector.
*
*
*  The cyme::vector provides a dynamic container. The container must be
*  declared with a structure under the following form
*  \code{.cpp}
*  template<class T> struct my_object{
*    typedef T value_type; // the value_type float or double
*    const int value_size = 8; // your object has 8 fields
*  };
*  \endcode
*  The container supports two memory layout AoS and AoSoA. The
*  containers of cyme are constructed over a basic vector named cyme::storage
*  (or storage_type), the size of storage depends of the value_size and the
*  requested SIMD technology.
*/
    template<class T, cyme::order O> class vector{};

/** Specialisation of the cyme::vector for the AoS layout.  */
    template<class T>
    class vector<T,cyme::AoS>{
    public:
        const static cyme::order order_value = cyme::AoSoA;
        typedef std::size_t size_type;
        typedef typename    T::value_type value_type;
        typedef value_type&                                                  reference;
        typedef const value_type&                                            const_reference;
        typedef cyme::storage<value_type,T::value_size,cyme::AoS>        storage_type;
        typedef std::vector<storage_type, cyme::Allocator<storage_type> >  base_type;
        typedef typename base_type::iterator iterator;
        typedef typename base_type::const_iterator const_iterator;

        /** Default constructor, initialisation to given value or default value type */
        vector(const size_t Size=1, value_type value=value_type())
        :data(Size,value){
        }

        /** Copy constructor */
        vector(vector& v):data(v.size()){
            std::copy(v.begin(),v.end(),begin());
        }

        /** Resize data container */
        void resize(size_type Size){
            data.resize(Size);
        }

        /** Return first iterator */
        iterator begin(){
            return data.begin();
        }

        /** Return last iterator */
        iterator end(){
            return data.end();
        }

        /** Return the storage_type needed for writing */
        inline storage_type& operator [](size_type i){
            return data[i];
        }

        /** Return the storage_type needed for reading */
        const inline storage_type& operator [](size_type i) const{
            return data[i];
        }

        /** Return the size of storage_type */
        static inline size_type size_block() {
            return T::value_size;
        }

        /** Return the number of storage_type */
        inline size_type size() {
            return data.size();
        }

        /** Return a needed element of particular storage_type - serial - write */
        inline reference operator()(size_type i, size_type j){
            BOOST_ASSERT_MSG( i < data.size(), "out of range: block_v AoS i" );
            BOOST_ASSERT_MSG( j < T::value_size, "out of range: block_v AoS j" );
            return data[i](j);
        }

        /** Return a needed element of particular storage_type - serial - read */
        inline const_reference operator()(size_type i, size_type j) const{
            BOOST_ASSERT_MSG( i < data.size(), "out of range: block_v AoS i" );
            BOOST_ASSERT_MSG( j < T::value_size, "out of range: block_v AoS j" );
            return data[i](j);
        }

    private:
        base_type data;
    };


/** Specialisation of the cyme::vector for the AoSoA layout.  */
    template<class T>
    class vector<T,cyme::AoSoA>{
    public:
        const static cyme::order order_value = cyme::AoSoA;
        typedef std::size_t size_type;
        typedef typename    T::value_type value_type;
        typedef value_type&                                               reference;
        typedef const value_type&                                         const_reference;

        static const size_type offset =  cyme::unroll_factor::N
                                         *cyme::trait_register<value_type,cyme::__GETSIMD__()>::size
                                         /sizeof(value_type);

        static const size_type storage_width = offset*T::value_size;

        typedef cyme::storage<value_type,storage_width,cyme::AoSoA>  storage_type;
        typedef std::vector<
        storage_type,
        cyme::Allocator<storage_type>
        > base_type;
        typedef typename base_type::iterator iterator;
        typedef typename base_type::const_iterator const_iterator;

        /** Default constructor, initialisation to given value or default value type */
        vector(const size_t Size=1  , value_type value=value_type()):data(Size/offset+1,value),size_cyme(Size){
        }

        /** Copy constructor */
        vector(vector& v):data(v.size()),size_cyme(v.cyme_size()){
            std::copy(v.begin(),v.end(),begin());
        }

        /** Resize data container */
        void resize(size_type Size){
            data.resize(Size/offset+1);
        }

        /** Return first iterator */
        iterator begin(){
            return data.begin();
        }

        /** Return last iterator */
        iterator end(){
            return data.end();
        }

        /** Return the storage_type needed for writing */
        inline  storage_type& operator [](size_type i){
            return data[i];
        }

        /** Return the storage_type needed for reading */
        const inline  storage_type& operator [](size_type i) const{
            return data[i];
        }

        /** Return the size of storage_type */
        static inline size_type size_block() {
            return T::value_size;
        }

        /** Return the number of storage_type */
        inline size_type size() {
            return data.size();
        }

        /** Return the AoSoA stride size */
        inline size_type cyme_size() {
            return size_cyme;
        }

        /** Return a needed element of perticular storage_type - serial - write */
        inline reference operator()(size_type i, size_type j){
        // nothing on i as the original size is destroyed in the constructor
        BOOST_ASSERT_MSG(     j < T::value_size, "out of range: block_v AoSoA j" );
        // Please tune me ! (does it exist an alternative to this ? ^_^
        return data[(i*T::value_size+j)/(T::value_size*offset)](j*offset+i%offset);  // [..i..](..j..)
        }

        /** Return a needed element of perticular storage_type - serial - read */
        inline const_reference operator()(size_type i, size_type j) const{
        // nothing on i as the original size is destroyed in the constructor
        BOOST_ASSERT_MSG(     j < T::value_size, "out of range: block_v AoSoA j" );
        // Please tune me ! (does it exist an alternative to this ? ^_^
        return data[(i*T::value_size+j)/(T::value_size*offset)](j*offset+i%offset);  // [..i..](..j..)
        }

    private:
        base_type data;
        size_type size_cyme;
    };

}

#endif
