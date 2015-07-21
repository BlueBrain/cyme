/*
 * Cyme - coeff_log.ipp, Copyright (c), 2014,
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
 * @file cyme/core/simd_vector/math/detail/coeff_log.ipp
 * Implements coeff_remez_log class for horner's method
 */

#ifndef CYME_COEFF_LOG_IPP
#define CYME_COEFF_LOG_IPP

namespace cyme{
   
    /** this class encapsulates the remez approximation coefficient for the log

     no c++ 11, so no constexpr into structure for double/float, ^.^ just partial specialization
     these coeffs are obtained with an external program
    */
    // log coefficient
    template<class T, std::size_t n>
    struct coeff_remez_log;

    /** coeff order 0 log(x) */
    template<class T>
    struct coeff_remez_log<T,0>{
        const static inline T coeff() {return 0;}
    };

    /** coeff order 1 log(x) */
    template<class T>
    struct coeff_remez_log<T,1>{
        const static inline T coeff() {return 0.999999999881463517864L;}
    };

    /** coeff order 2 log(x) */
    template<class T>
    struct coeff_remez_log<T,2>{
        const static inline T coeff() {return -0.499999964958725095026L;}
    };

    /** coeff order 3 log(x) */
    template<class T>
    struct coeff_remez_log<T,3>{
        const static inline T coeff() {return 0.333331601133431864538L;}
    };

    /** coeff order 4 log(x) */
    template<class T>
    struct coeff_remez_log<T,4>{
        const static inline T coeff() {return -0.249966118317788475791L;}
    };

    /** coeff order 5 log(x) */
    template<class T>
    struct coeff_remez_log<T,5>{
        const static inline T coeff() {return 0.199652928083999845561L;}
    };

    /** coeff order 6 log(x) */
    template<class T>
    struct coeff_remez_log<T,6>{
        const static inline T coeff() {return -0.164528321547744695595L;}
    };

    /** coeff order 7 log(x) */
    template<class T>
    struct coeff_remez_log<T,7>{
        const static inline T coeff() {return 0.13426431588538376696L;}
    };

    /** coeff order 8 log(x) */
    template<class T>
    struct coeff_remez_log<T,8>{
        const static inline T coeff() {return -0.101241750098569221963L;}
    };

    /** coeff order 9 log(x) */
    template<class T>
    struct coeff_remez_log<T,9>{
        const static inline T coeff() {return 0.0640055965188409194363L;}
    };

    /** coeff order 10 log(x) */
    template<class T>
    struct coeff_remez_log<T,10>{
        const static inline T coeff() {return -0.0301709422209463258125L;}
    };

    /** coeff order 11 log(x) */
    template<class T>
    struct coeff_remez_log<T,11>{
        const static inline T coeff() {return 0.00908032467092469922091L;}
    };

    /** coeff order 12 log(x) */
    template<class T>
    struct coeff_remez_log<T,12>{
        const static inline T coeff() {return -0.00128048855206694750818L;}
    };

    /** Poly_order partial specialisation for the log */
    template<class T>
    struct poly_order<T,coeff_remez_log> {
        static const std::size_t value=12;
    };

} //end namespace

#endif
