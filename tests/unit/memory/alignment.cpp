/*
 * Cyme - alignement.cpp, Copyright (c), 2014,
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
#include <vector>

#include "cyme/memory/allocator.hpp"

using namespace cyme::test;

BOOST_AUTO_TEST_CASE_TEMPLATE(alignement_test, T, full_test_types)
{
    std::vector<T, cyme::Allocator<T, cyme::Align_POSIX<T, cyme::__GETSIMD__()> > > simd_vec(128);
    boost::uint64_t align = cyme::trait_register<T,cyme::__GETSIMD__()>::size;
    boost::uint64_t adress = (boost::uint64_t)(const void* )(&simd_vec[0]); // convert the adress to a real number, and I calculate the rest, it should be zero c++11 -> (uintptr_t)ptr
    boost::uint64_t res = adress%align; // should be a multiple of the alignment
    BOOST_CHECK_EQUAL(res,0);
}
