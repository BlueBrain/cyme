/*
 * Cyme - coefficients.ipp, Copyright (c), 2014,
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
 * @file cyme/core/simd_vector/math/detail/method/coefficients/coefficients.ipp
 * Provide the order of the different polynomial for the evaluation of the exponential
 */

#ifndef POLY_COEFFICIENTS_IPP
#define POLY_COEFFICIENTS_IPP

#include "cyme/core/simd_vector/math/detail/method/coefficients/P2.ipp"
#include "cyme/core/simd_vector/math/detail/method/coefficients/P4.ipp"
#include "cyme/core/simd_vector/math/detail/method/coefficients/P6.ipp"
#include "cyme/core/simd_vector/math/detail/method/coefficients/P8.ipp"
#include "cyme/core/simd_vector/math/detail/method/coefficients/P10.ipp"

namespace poly{

    template<template<class,int> class C>
    struct poly_order;

    /* P2 family */
    template<>
    struct poly_order<coeffP2_1>
    {
        static const std::size_t value=2;
    };

    template<>
    struct poly_order<coeffP2_2>
    {
        static const std::size_t value=2;
    };

    template<>
    struct poly_order<coeffP2_3>
    {
        static const std::size_t value=2;
    };

    template<>
    struct poly_order<coeffP2_4>
    {
        static const std::size_t value=2;
    };

    template<>
    struct poly_order<coeffP2_5>
    {
        static const std::size_t value=2;
    };

    /*P4 family */
    template<>
    struct poly_order<coeffP4_1>
    {
        static const std::size_t value=4;
    };

    template<>
    struct poly_order<coeffP4_2>
    {
        static const std::size_t value=4;
    };

    template<>
    struct poly_order<coeffP4_3>
    {
        static const std::size_t value=4;
    };

    /*P6 */
    template<>
    struct poly_order<coeffP6>
    {
        static const std::size_t value=6;
    };

    /*P8 */
    template<>
    struct poly_order<coeffP8>
    {
        static const std::size_t value=8;
    };

    /* P10 */
    template<>
    struct poly_order<coeffP10>
    {
        static const std::size_t value=10;
    };
}

#endif
