/*
 * Cyme - serial.hpp, Copyright (c), 2014,
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
* @file cyme/memory/serial.hpp
* Defines serial class for temporary object
*/

#ifndef CYME_SERIAL_HPP
#define CYME_SERIAL_HPP

namespace cyme{
/**     The serial class provides a solution for temporary object.
*
*  if the order is AoS, it will provide a basic float/double, else it
*  encapsulates a SIMD vector. Note for AoSoA version: is serial = ... , it
*  will generates the tree but it will not save the data into cyme.
*/
    template<class T, cyme::order O, int N = cyme::unroll_factor::N> class
serial{ };

    /** Specialisation of the cyme::serial for AoS layout */
    template<class T, int N>
    struct serial<T,cyme::AoS,N>{
        typedef T value_type;

        /** Default constructor, nothing special */
        serial(value_type m=value_type()):a(m){}

        /** Assignment operator for basic type */
        inline serial& operator =(value_type b){
            a = b;
            return *this;
        }

        /** Implicit conversion operator */
        inline operator value_type (){
            return a;
        }

        /** Bracket operator to fit with AoSoA syntax */
        inline const value_type& operator ()() const{
            return a;
        }

        T a;
    };

    /** Specialisation of the cyme::serial for AoSoA layout */
    template<class T, int N>
    struct serial<T,cyme::AoSoA,N>{
        typedef T value_type;
        typedef cyme::rvec<value_type,cyme::__GETSIMD__(),N> base_type;

        /** constructor */
        serial(base_type m = base_type()):a(m){}

        /** constructor constant */
        explicit serial(typename base_type::value_type m):a(m){}


        /** copy constructor create the tree with bracket operator call

           \warning   not a = rhs.rep()() else I call store -> a crash (pointer not initialized)
         */
        template<class T2, cyme::simd O, class Rep>
        serial(cyme::rvec<T2,O,N,Rep > const& rhs){
            a.rep()() = rhs.rep()();
        }

        /** normal situation initialize serial by vector returned by the iterates serial = (*it)[1]; */
        inline serial& operator=(base_type b){
            a.rep()() = b.rep()();
            return *this;
        }

        /** implicit conversion operator */
        inline operator base_type (){
            return a;
        }

        /** bracket operator return the vector */
        inline const base_type& operator ()() const{
            return a;
        }

        base_type a;
    };
}

#endif
