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

namespace cyme {
/**     The serial class provides a solution for temporary object.
 *
 *  if the order is AoS, it will provide a basic float/double, else it
 *  encapsulates a SIMD vector. Note for AoSoA version: is serial = ... , it
 *  will generates the tree but it will not save the data into cyme.
 *  Default cyme::AoSoA because I use this object in mod2cyme where
 *  the data layout AoSoA does not "exist"
 */
template <class T, cyme::order O = cyme::AoSoA, int N = cyme::unroll_factor::N>
class serial {};

/** Specialisation of the cyme::serial for AoS layout */
template <class T, int N>
struct serial<T, cyme::AoS, N> {
    typedef T value_type;

    /** Default constructor, nothing special */
    serial(value_type m = value_type()) : a(m) {}

    /** Assignment operator for basic type */
    inline serial &operator=(value_type b) {
        a = b;
        return *this;
    }

    /** Implicit conversion operator */
    inline operator value_type() { return a; }

    T a;
};

/** Specialisation of the cyme::serial for AoSoA layout */
template <class T, int N>
struct serial<T, cyme::AoSoA, N> : public vec<T, cyme::__GETSIMD__(), N> {
    typedef T value_type;

    /** default constructor */
    explicit serial() : vec<T, cyme::__GETSIMD__(), N>() {}

    /** constructor constant */
    serial(value_type m) : vec<T, cyme::__GETSIMD__(), N>(m) {}

    /** serial -> serial mod2cyme */
    forceinline serial operator=(serial const &s) {
        this->rep()() = s.rep()();
        return *this;
    }

    /* T1 because it is also used for u<int>( u<double> < v<double> ) */
    template <class T1, class Rep>
    serial(cyme::vec<T1, cyme::__GETSIMD__(), N, Rep> const &v) {
        this->rep()() = v.rep()();
    }

    /* T1 because it is also used for u<int>( u<double> < v<double> ) */
    template <class T1, class Rep>
    forceinline serial operator=(vec<T1, cyme::__GETSIMD__(), N, Rep> const &v) {
        this->rep()() = v.rep()();
        return *this;
    }

    template <class Rep>
    forceinline serial operator=(vec<T, cyme::__GETSIMD__(), N, Rep> const &v) {
        this->rep()() = v.rep()();
        return *this;
    }

    template <class Rep>
    forceinline serial operator+=(vec<T, cyme::__GETSIMD__(), N, Rep> const &v) {
        this->rep()() += v.rep()();
        return *this;
    }

    template <class Rep>
    forceinline serial operator-=(vec<T, cyme::__GETSIMD__(), N, Rep> const &v) {
        this->rep()() -= v.rep()();
        return *this;
    }

    template <class Rep>
    forceinline serial operator*=(vec<T, cyme::__GETSIMD__(), N, Rep> const &v) {
        this->rep()() *= v.rep()();
        return *this;
    }

    template <class Rep>
    forceinline serial operator/=(vec<T, cyme::__GETSIMD__(), N, Rep> const &v) {
        this->rep()() /= v.rep()();
        return *this;
    }

    forceinline bool operator!=(bool b) { return this->rep()() != b; }

    forceinline bool operator==(bool b) { return this->rep()() == b; }
};
} // namespace cyme

#endif
