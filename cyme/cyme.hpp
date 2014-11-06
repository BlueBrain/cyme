/*
 * Cyme - cyme.hpp, Copyright (c), 2014,
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

#ifndef CYME_CYME_HPP
#define CYME_CYME_HPP

#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wunused-parameter" // for the exponent of pow
#pragma GCC diagnostic ignored "-Wuninitialized" // for the optimization of log


#define forceinline inline __attribute__((always_inline))

#include <math.h> // exp system
#include <cmath> // log system
#include "cyme/core/simd_vector/simd_vec.hpp" // simd vector
#include "cyme/core/expression/expr_vec.hpp" // template expression
#include "cyme/memory/serial.hpp" // container
#include "cyme/memory/array.hpp"  // container
#include "cyme/memory/vector.hpp" // container

// This macro is dangerous maybe later undefined behaviour with std or boost
// #define pow(x,e) pow(x,numeric::exponent<e>())

#endif
