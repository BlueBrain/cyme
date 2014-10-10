/*
 * CYME, License
 * 
 * Timothee Ewart - Swiss Federal Institute of technology in Lausanne 
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef CYME_H
#define CYME_H
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
