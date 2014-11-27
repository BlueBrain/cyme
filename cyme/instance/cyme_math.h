/*
 * Cyme - cyme.h, Copyright (c), 2014,
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

#ifndef CYME_MATH_H
#define CYME_MATH_H
    /*
        This file (cyme.h) exposed signature for serial use library C-only. cyme.hpp contains
        everything, specially perform computation with the cyme container. 
    */

    /**
     \brief single-precision 32-bit serial exponential, C library only
    */
    float  cyme_fexp(float a);

    /**
     \brief single-precision 32-bit serial logarithm base e, C library only
    */
    float  cyme_flog(float a);

    /**
     \brief single-precision 32-bit serial sqrt, C library only
    */
    float  cyme_fsqrt(float a);

    /**
     \brief double-precision 64-bit serial exponential base e, C library only
    */
    double cyme_exp(double a);

    /**
     \brief double-precision 64-bit serial exponential base e, C library only
    */
    double cyme_log(double a);

    /**
     \brief double-precision 64-bit serial exponential base e, C library only
    */
    double cyme_sqrt(double a);
#endif 
