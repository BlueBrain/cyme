/*
 * Cyme - cyme.cpp, Copyright (c), 2014,
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
 * @file cyme/math/math.cpp
 * Signature for the C library
 */

#include <iostream>
#include <cyme/cyme.h>
#include <cyme/math/math.h>

extern "C" {
    float cyme_fexp(float a){return cyme::sexp(a);}
    float cyme_flog(float a){return cyme::slog(a);}
    float cyme_fsqrt(float a){return cyme::ssqrt(a);}

    double cyme_exp(double a){return cyme::sexp(a);}
    double cyme_log(double a){return cyme::slog(a);}
    double cyme_sqrt(double a){return cyme::ssqrt(a);}
}
