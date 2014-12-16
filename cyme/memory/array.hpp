/*
 * Cyme - array.hpp, Copyright (c), 2014,
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

#ifndef CYME_ARRAY_HPP
#define CYME_ARRAY_HPP

#include "cyme/memory/detail/array_helper.ipp" // copy of boost::array + align
#include "cyme/memory/detail/storage.hpp"

namespace cyme{

/**
    \brief This class facilitates the creation of an array of structures (ex: synapses), the condition the class
    must encapsulate the basic type (value_type) and the size (value_size) of the basic object
*/
template<class T, std::size_t N, memory::order O>
class array{};


template<class T, std::size_t N>
class array<T,N,memory::AoS>{
public:
    const static memory::order     order_value = memory::AoSoA;
    typedef std::size_t            size_type;
    typedef typename T::value_type value_type;
    typedef value_type&            reference;
    typedef const value_type&      const_reference;
    typedef memory::storage<value_type,T::value_size,memory::AoS>     storage_type;
    typedef cyme::array_helper<storage_type,N>   base_type; //default template seems impossible on partial specialization

    typedef typename base_type::iterator iterator;
    typedef typename base_type::const_iterator const_iterator;

    explicit array(){
        std::fill(data.begin(),data.end(),storage_type());
    }

    array(value_type value){
        std::fill(data.begin(),data.end(),storage_type(value));
    }

    iterator begin(){
        return this->data.begin();
    }

    iterator end(){
        return this->data.end();
    }

    inline storage_type& operator [](int i){
        return this->data[i];
    }

    const inline storage_type& operator [](int i) const{
        return this->data[i];
    }

    static inline size_type size_block() {
        return T::value_size;
    }

    inline size_type size() {
        return this->data.size();
    }

    inline reference operator()(size_type i, size_type j){
        BOOST_ASSERT_MSG( i < base_type::size(), "out of range: block_v AoS i" );
        BOOST_ASSERT_MSG( j < T::value_size, "out of range: block_v AoS j" );
        return this->data[i](j);
    }

    inline const_reference operator()(size_type i, size_type j) const{
        BOOST_ASSERT_MSG( i < base_type::size(), "out of range: block_v AoS i" );
        BOOST_ASSERT_MSG( j < T::value_size, "out of range: block_v AoS j" );
        return this->data[i](j);
    }

private:
    base_type data;
};


template<class T, std::size_t N>
class array<T,N,memory::AoSoA>{
public:
    const static memory::order     order_value = memory::AoSoA;
    typedef std::size_t            size_type;
    typedef typename T::value_type value_type;
    typedef value_type&            reference;
    typedef const value_type&      const_reference;
    static const size_type  storage_width = N/(memory::unroll_factor::N*memory::trait_register<value_type,memory::__GETSIMD__()>::size/sizeof(value_type))+1;
    typedef memory::storage<value_type,memory::unroll_factor::N*memory::trait_register<value_type,memory::__GETSIMD__()>::size/sizeof(value_type)*T::value_size,memory::AoSoA>                storage_type;
    typedef cyme::array_helper<storage_type,storage_width> base_type; //default template seems impossible on partial specialization

    typedef typename base_type::iterator iterator;
    typedef typename base_type::const_iterator const_iterator;

    explicit array(){
        for(size_type i(0); i<storage_width; ++i)
            data[i] = storage_type(); // fill up to 0
    }

    array(value_type value){
        for(size_type i(0); i<storage_width; ++i)
            data[i] = storage_type(value); // fill up to 0
    }

    iterator begin(){
        return this->data.begin();
    }

    iterator end(){
        return this->data.end();
    }

    inline  storage_type& operator [](int i){
        return this->data[i];
    }

    const inline  storage_type& operator [](int i) const{
        return this->data[i];
    }

    static inline size_type size_block() {
        return T::value_size;
    }

    inline size_type size() {
        return this->data.size();
    }

    inline reference operator()(size_type i, size_type j){
        // nothing on i as the original size is destroyed in the constructor
        // BOOST_ASSERT_MSG( i < size(), "out of range: block_v AoS i" );
        BOOST_ASSERT_MSG(     j < T::value_size, "out of range: block_v AoSoA j" );
        // Please tune me ! (does it exist an alternative to this ? ^_^
        return this->data[(i*T::value_size+j)/(T::value_size*memory::unroll_factor::N*memory::trait_register<value_type,memory::__GETSIMD__()>::size/sizeof(value_type))] //(i)
            (j*(memory::unroll_factor::N*memory::trait_register<value_type,memory::__GETSIMD__()>::size/sizeof(value_type)) + i%(memory::unroll_factor::N*memory::trait_register<value_type,memory::__GETSIMD__()>::size/sizeof(value_type)));      //(j)
    }

    inline const_reference operator()(size_type i, size_type j) const{
        // nothing on i as the original size is destroyed in the constructor
        BOOST_ASSERT_MSG(     j < T::value_size, "out of range: block_v AoSoA j" );
        // Please tune me ! (does it exist an alternative to this ? ^_^
        return this->data[(i*T::value_size+j)/(T::value_size*memory::unroll_factor::N*memory::trait_register<value_type,memory::__GETSIMD__()>::size/sizeof(value_type))] //(i)
            (j*(memory::unroll_factor::N*memory::trait_register<value_type,memory::__GETSIMD__()>::size/sizeof(value_type)) + i%(memory::unroll_factor::N*memory::trait_register<value_type,memory::__GETSIMD__()>::size/sizeof(value_type)));      //(j)
    }

private:
    base_type data;
    size_type size_cyme;
};

}

#endif
