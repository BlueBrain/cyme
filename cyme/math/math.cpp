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
float cyme_fexp(float a) { return cyme::sexp(a); }
float cyme_fexp2(float a) { return cyme::sexp2(a); }
float cyme_fexp10(float a) { return cyme::sexp10(a); }
float cyme_flog(float a) { return cyme::slog(a); }
float cyme_flog2(float a) { return cyme::slog2(a); }
float cyme_flog10(float a) { return cyme::slog10(a); }
float cyme_fsqrt(float a) { return cyme::ssqrt(a); }
float cyme_ffabs(float a) { return cyme::sfabs(a); }
float cyme_fsin(float a) { return cyme::ssin(a); }
float cyme_fcos(float a) { return cyme::scos(a); }
float cyme_ftan(float a) { return cyme::stan(a); }

double cyme_exp(double a) { return cyme::sexp(a); }
double cyme_exp2(double a) { return cyme::sexp2(a); }
double cyme_exp10(double a) { return cyme::sexp10(a); }
double cyme_log(double a) { return cyme::slog(a); }
double cyme_log2(double a) { return cyme::slog2(a); }
double cyme_log10(double a) { return cyme::slog10(a); }
double cyme_sqrt(double a) { return cyme::ssqrt(a); }
double cyme_fabs(double a) { return cyme::sfabs(a); }
double cyme_sin(double a) { return cyme::ssin(a); }
double cyme_cos(double a) { return cyme::scos(a); }
double cyme_tan(double a) { return cyme::stan(a); }
}
