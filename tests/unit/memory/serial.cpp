/*
 * Cyme - serial.cpp, Copyright (c), 2014,
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

#include <tests/unit/test_header.hpp>

using namespace cyme::test;

#define TYPE typename T::value_type
#define N T::n
#define M T::m
#define ORDER T::order
#define MAX 1000

template <class T, size_t size>
struct synapse {
    typedef T value_type;
    static const size_t value_size = size;
};

BOOST_AUTO_TEST_CASE_TEMPLATE(block_init_default_constructor, T, floating_point_block_types) {
    cyme::vector<synapse<TYPE, 1>, ORDER> v(cyme::stride<TYPE, ORDER>::helper_stride(), 0.);
    for (size_t i = 0; i < cyme::stride<TYPE, ORDER>::helper_stride() / sizeof(TYPE); ++i)
        BOOST_CHECK_CLOSE(v(i * ORDER, 0), 0, relative_error<TYPE>());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_init_default_constructor_value, T, floating_point_block_types) {
    cyme::serial<TYPE, ORDER> a(1.);
    cyme::vector<synapse<TYPE, 1>, ORDER> v(cyme::stride<TYPE, ORDER>::helper_stride(), 1.);
    for (size_t i = 0; i < cyme::stride<TYPE, ORDER>::helper_stride() / sizeof(TYPE); ++i)
        BOOST_CHECK_CLOSE(v(i * ORDER, 0), 1, relative_error<TYPE>());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(serial_doest_not_store, T, floating_point_block_types) {
    cyme::vector<synapse<TYPE, 1>, ORDER> v(cyme::stride<TYPE, ORDER>::helper_stride(), 2.);
    typename cyme::vector<synapse<TYPE, 1>, ORDER>::const_iterator it_AoSoA = v.begin();
    cyme::serial<TYPE, ORDER> a = (*it_AoSoA)[0];
    v[0][0] = a;
    for (size_t i = 0; i < cyme::stride<TYPE, ORDER>::helper_stride() / sizeof(TYPE); ++i)
        BOOST_CHECK_CLOSE(v(i * ORDER, 0), 2, relative_error<TYPE>());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(block_ops_value, T, floating_point_block_types) {
    cyme::serial<TYPE, ORDER> a(2.);
    cyme::vector<synapse<TYPE, 1>, ORDER> v(cyme::stride<TYPE, ORDER>::helper_stride(), 2.);
    v[0][0] += a;
    for (size_t i = 0; i < cyme::stride<TYPE, ORDER>::helper_stride() / sizeof(TYPE); ++i)
        BOOST_CHECK_CLOSE(v(i * ORDER, 0), 4, relative_error<TYPE>());

    v[0][0] *= a;
    for (size_t i = 0; i < cyme::stride<TYPE, ORDER>::helper_stride() / sizeof(TYPE); ++i)
        BOOST_CHECK_CLOSE(v(i * ORDER, 0), 8, relative_error<TYPE>());

    v[0][0] -= a;
    for (size_t i = 0; i < cyme::stride<TYPE, ORDER>::helper_stride() / sizeof(TYPE); ++i)
        BOOST_CHECK_CLOSE(v(i * ORDER, 0), 6, relative_error<TYPE>());

    v[0][0] /= a;
    for (size_t i = 0; i < cyme::stride<TYPE, ORDER>::helper_stride() / sizeof(TYPE); ++i)
        BOOST_CHECK_CLOSE(v(i * ORDER, 0), 3, relative_error<TYPE>());
}
