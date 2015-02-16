/*
 * Cyme - storage.hpp, Copyright (c), 2014,
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
* @file cyme/memory/detail/storage.hpp
* Defines Defines the basic subblock of a cyme container
*/

#ifndef CYME_STORAGE_HPP
#define CYME_STORAGE_HPP

#include "cyme/core/simd_vector/simd_vec.hpp"
#include "cyme/core/expression/expr_vec.hpp"

namespace cyme{
     /**   Basic subblock of cyme for the cyme container*/
     template <class T, std::size_t Size, order O>
     class storage;

     /** subblock of cyme needed by the block class, AoS specialization */
     template <class T, std::size_t Size>
     class storage<T,Size,AoS>{
         public:

         typedef std::size_t       size_type;
         typedef T                 value_type;
         typedef value_type*       pointer;
         typedef const pointer*    const_pointer;
         typedef value_type&       reference;
         typedef const value_type& const_reference;

         static const int size = Size;

         /** Default constructor, the subblock is set up to 0 */
         storage();

         /** Default constructor, the subblock is set up to a desired value */
         storage(value_type value);

         /** write access operator, only use to a direct access to the datas */
         inline reference operator()(size_type i);

         /** read access operator, only use to a direct access to the datas */
         inline const_reference operator()(size_type i) const;

         /** write access operator, only use by the iterator when calculations are performed */
         inline reference operator[](size_type i);

         /** read access operator, only use by the iterator when calculations are performed */
         inline const_reference operator[](size_type i) const;

         /** return cyme layout of the container */
         static const cyme::order MemoryOrder = AoS;

         private:
         /** a basic array is the container */
         value_type data[Size];
     };

     /** subblock of cyme needed by the block class, AoSoA specialization */
     template <class T, std::size_t Size>
     class storage<T,Size,AoSoA>{
         public:

         typedef std::size_t       size_type;
         typedef T                 value_type;
         typedef value_type*       pointer;
         typedef const pointer*    const_pointer;
         typedef value_type&       reference;
         typedef const value_type& const_reference;

         static const int size = Size;

         /** Default constructor, the subblock is set up to 0 */
         storage();

         /** Default constructor, the subblock is set up to a desired value */
         storage(value_type value);

         /** write access operator, only use to a direct access to the datas */
         inline reference operator()(size_type i);

         /** read access operator, only use to a direct access to the datas */
         inline const_reference operator()(size_type i) const;

         inline cyme::wvec<T,cyme::__GETSIMD__()> operator[](size_type i);

         inline const cyme::rvec<T,cyme::__GETSIMD__()> operator[](size_type i) const;

         /** return cyme layout of the container */
         static const cyme::order MemoryOrder = AoSoA;

         private:
         /**  storage type is basic array for AoSoA*/
         value_type data[Size];
     };
} //end namespace

#include "cyme/memory/detail/storage.ipp"

#endif
