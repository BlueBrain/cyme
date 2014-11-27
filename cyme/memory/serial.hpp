/*
 * Cyme - serial.hpp, Copyright (c), 2014,
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

#ifndef CYME_SERIAL_HPP
#define CYME_SERIAL_HPP

namespace cyme{
    /**
       \brief The serial class provides a solution for temporary object into mechanism.
       it the order is AoS, it will provide a basic float/double, else it encapsulates
       a SIMD vector. Note for AoSoA version: is serial = ... , it will generates the
       the tree but it will not save the data into memory.
    */
    template<class T, memory::order O, int N = memory::unroll_factor::N>
    class serial{
    };

    /**
     \brief The serial class for AoS layout
    */
    template<class T, int N>
    struct serial<T,memory::AoS,N>{
        typedef T value_type;

        /**
         \brief Default constructor, nothing special
         */
        serial(value_type m=value_type()):a(m){}

        /**
         \brief assignement operatior for basic type 
         */
        inline serial& operator =(value_type b){
            a = b;
            return *this; 
        }

        /**
         \brief implicit conversion operator 
         */
        inline operator value_type (){
            return a;
        }

        /**
         \brief bracket operator to fit with AoSoA syntax
         */
        inline const value_type& operator ()() const{
            return a;
        }

        T a;
    };

    /**
     \brief The serial class for AoSoA layout
     */
    template<class T, int N>
    struct serial<T,memory::AoSoA,N>{
        typedef T value_type;
        typedef numeric::rvec<value_type,memory::__GETSIMD__(),N> base_type;

        /**
         \brief constructor
         */
        serial(base_type m = base_type()):a(m){}

        /**
         \brief constructor constant
         */
        explicit serial(typename base_type::value_type m):a(m){}


        /**
         \brief copy constructor create the tree with bracket operator call
                 not a = rhs.rep()() else I call store -> a crash (pointer not initialized)
         */
        template<class T2, memory::simd O, class Rep>
        serial(numeric::rvec<T2,O,N,Rep > const& rhs){
            a.rep()() = rhs.rep()();
        }

        /**
        \brief normal situation initialize serial by vector returned by the iteratos serial = (*it)[1];
        */
        inline serial& operator=(base_type b){
            a.rep()() = b.rep()();
            return *this;
        }

        /**
         \brief implicit conversion operator
         */
        inline operator base_type (){
            return a;
        }

        /**
         \brief bracket operator return the vector
         */
        inline const base_type& operator ()() const{
            return a;
        }

        base_type a;
    };
}

#endif
