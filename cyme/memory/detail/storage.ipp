/*
* Cyme - storage.ipp, Copyright (c), 2014,
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
* @file cyme/memory/detail/storage.ipp
* Implements the basic subblock of a cyme container
*/

#ifndef CYME_STORAGE_IPP
#define CYME_STORAGE_IPP

namespace cyme{
    /* --------------------------------------- AOS --------------------------------------- */

    template <class T, std::size_t Size>
    storage<T, Size, AoS>::storage(){
        for(size_type i=0; i<Size; ++i)
            data[i] = T();
    }

    template <class T, std::size_t Size>
    storage<T, Size, AoS>::storage(value_type value){
        for(size_type i=0; i<Size; ++i)
            data[i] = value;
    }

    template <class T, std::size_t Size>
    typename storage<T, Size, AoS>::reference
    storage<T, Size, AoS>::operator()(size_type i){
        BOOST_ASSERT_MSG( i < Size, "out of range" );
        return data[i];
    }

    template <class T, std::size_t Size>
    typename storage<T, Size, AoS>::const_reference
    storage<T, Size, AoS>::operator()(size_type i) const{
        BOOST_ASSERT_MSG( i < Size, "out of range" );
        return data[i];
    }

    template <class T, std::size_t Size>
    typename storage<T, Size, AoS>::reference storage<T, Size, AoS>::operator[](size_type i){
        return operator()(i);
    }

    template <class T, std::size_t Size>
    typename storage<T, Size, AoS>::const_reference storage<T, Size, AoS>::operator[](size_type i) const{
        return operator()(i);
    }

    /* --------------------------------------- AOSOA --------------------------------------- */

    template <class T, std::size_t Size>
    storage<T, Size, AoSoA>::storage(){
        for(size_type i=0; i<Size; ++i)
            data[i] = T();
    }

    template <class T, std::size_t Size>
    storage<T, Size, AoSoA>::storage(value_type value){
        for(size_type i=0; i<Size; ++i)
            data[i] = value;
    }

    template <class T, std::size_t Size>
    typename storage<T, Size, AoSoA>::reference
    storage<T, Size, AoSoA>::operator()(size_type i){
        BOOST_ASSERT_MSG( i < Size, "out of range" );
        return data[i];
    }

    template <class T, std::size_t Size>
    typename storage<T, Size, AoSoA>::const_reference
    storage<T, Size, AoSoA>::operator()(size_type i) const{
        BOOST_ASSERT_MSG( i < Size, "out of range" );
        return data[i];
    }

    template <class T, std::size_t Size>
    cyme::wvec<T,cyme::__GETSIMD__()>
    storage<T, Size, AoSoA>::operator[](size_type i){
        return cyme::wvec<T,cyme::__GETSIMD__()>(&data[i*stride<T,AoSoA>::helper_stride()]);
    }

    template <class T, std::size_t Size>
    const cyme::rvec<T,cyme::__GETSIMD__()> storage<T, Size, AoSoA>::operator[](size_type i) const{
        return cyme::rvec<T,cyme::__GETSIMD__()>(&data[i*stride<T,AoSoA>::helper_stride()]);
    }
} //end namespace
#endif
