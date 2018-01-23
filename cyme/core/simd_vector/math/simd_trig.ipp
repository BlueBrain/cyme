/*
 * Cyme - simd_trig.hpp, Copyright (c), 2015,
 * Timothee Ewart - Swiss Federal Institute of technology in Lausanne,
 * timothee.ewart@epfl.ch,
 * Kai Langen,
 * kai.langen@usask.ca,
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
 * @file cyme/core/simd_vector/math/simd_trig.ipp
 * Implements sin for vec_simd class
 */

#ifndef CYME_SIMD_TRIG_IPP
#define CYME_SIMD_TRIG_IPP

#include "cyme/core/simd_vector/math/detail/horner.ipp"
#include "cyme/core/simd_vector/math/detail/coeff_sin_cos.ipp"

namespace cyme {
/** Base struct*/
template <class T, cyme::simd O, int N, template <typename, std::size_t> class C>
struct Poly_helper;

/** Helper for polynom where 0 <= x <= Pi/4 (sin/cos lo)*/
template <class T, cyme::simd O, int N>
struct Poly_helper<T, O, N, coeff_cephes_cos> {
    static forceinline vec_simd<T, O, N> poly(vec_simd<T, O, N> x) {
        vec_simd<T, O, N> z(x * x);
        vec_simd<T, O, N> y =
            helper_horner<T, O, N, coeff_cephes_cos, poly_order<T, coeff_cephes_cos>::value>::horner(z);
        y *= z;
        y -= (z * vec_simd<T, O, N>(0.5));
        y += vec_simd<T, O, N>(1);
        return y;
    }
};

/** Helper for polynom where Pi/4 <= x <= Pi/2 (sin/cos hi)*/
template <class T, cyme::simd O, int N>
struct Poly_helper<T, O, N, coeff_cephes_sin> {
    static forceinline vec_simd<T, O, N> poly(vec_simd<T, O, N> x) {
        vec_simd<T, O, N> z(x * x);
        vec_simd<T, O, N> y =
            helper_horner<T, O, N, coeff_cephes_sin, poly_order<T, coeff_cephes_sin>::value>::horner(z);
        y *= x;
        y += x;
        return y;
    }
};

/** free function for sin
Used references:
(http://github.com/jeremybarnes/cephes)
(http://gruntthepeon.free.fr/ssemath/sse_mathfun.h)
*/
template <class T, cyme::simd O, int N>
forceinline vec_simd<T, O, N> sin(const vec_simd<T, O, N> &rhs) {
    const vec_simd<T, O, N> cephes_FOPI(1.27323954473516); // 4/PI

    // take abs value
    vec_simd<T, O, N> x = fabs(rhs);

    // create values p and j
    vec_simd<T, O, N> y = x * cephes_FOPI;
    vec_simd<int, O, N> j = round_up_even(floor(y));
    vec_simd<T, O, N> p(convert<T, O, N>(j)); // j float

    // magic pass
    /*x = ((x - y * DP1) - y * DP2) - y * DP3; */
    vec_simd<T, O, N> neg_DP1(-0.78515625);
    vec_simd<T, O, N> neg_DP2(-2.4187564849853515625e-4);
    vec_simd<T, O, N> neg_DP3(-3.77489497744594108e-8);
    neg_DP1 *= p;
    neg_DP2 *= p;
    neg_DP3 *= p;
    x += neg_DP1;
    x += neg_DP2;
    x += neg_DP3;

    // Select Polynomial
    vec_simd<T, O, N> poly1 = Poly_helper<T, O, N, coeff_cephes_cos>::poly(x);
    vec_simd<T, O, N> poly2 = Poly_helper<T, O, N, coeff_cephes_sin>::poly(x);
    x = select_poly(j, poly1, poly2);
    // Select Sign
    return select_sign_sin(j, rhs, x);
}

/**
  free function for cos
  Used references:
  (http://github.com/jeremybarnes/cephes)
  (http://gruntthepeon.free.fr/ssemath/sse_mathfun.h)
*/
template <class T, cyme::simd O, int N>
forceinline vec_simd<T, O, N> cos(const vec_simd<T, O, N> &rhs) {
    const vec_simd<T, O, N> cephes_FOPI(1.27323954473516); // 4/PI

    // take abs value
    vec_simd<T, O, N> x = fabs(rhs);

    // create values p and j
    vec_simd<T, O, N> y = x * cephes_FOPI;
    vec_simd<int, O, N> j = round_up_even(floor(y));
    vec_simd<T, O, N> p(convert<T, O, N>(j)); // j float

    // magic pass
    /*x = ((x - y * DP1) - y * DP2) - y * DP3; */
    vec_simd<T, O, N> neg_DP1(-0.78515625);
    vec_simd<T, O, N> neg_DP2(-2.4187564849853515625e-4);
    vec_simd<T, O, N> neg_DP3(-3.77489497744594108e-8);
    neg_DP1 *= p;
    neg_DP2 *= p;
    neg_DP3 *= p;
    x += neg_DP1;
    x += neg_DP2;
    x += neg_DP3;

    j = round_up_even(floor(y - vec_simd<T, O, N>(2.0)));

    // Select Polynomial
    vec_simd<T, O, N> poly1 = Poly_helper<T, O, N, coeff_cephes_cos>::poly(x);
    vec_simd<T, O, N> poly2 = Poly_helper<T, O, N, coeff_cephes_sin>::poly(x);
    x = select_poly(j, poly1, poly2);
    // Select Sign
    x = select_sign_cos(j, x);
    return (x);
}

/**
  free function for tan
  Used references:
  (http://github.com/jeremybarnes/cephes)
  (http://gruntthepeon.free.fr/ssemath/sse_mathfun.h)
*/
template <class T, cyme::simd O, int N>
forceinline vec_simd<T, O, N> tan(const vec_simd<T, O, N> &rhs) {
    const vec_simd<T, O, N> cephes_FOPI(1.27323954473516); // 4/PI

    // take abs value
    vec_simd<T, O, N> x = fabs(rhs);

    // create values p and j
    vec_simd<T, O, N> y = x * cephes_FOPI;
    vec_simd<int, O, N> j = round_up_even(floor(y));
    vec_simd<T, O, N> p(convert<T, O, N>(j)); // j float

    // magic pass
    /*x = ((x - y * DP1) - y * DP2) - y * DP3; */
    vec_simd<T, O, N> z = x;
    vec_simd<T, O, N> neg_DP1(-0.78515625);
    vec_simd<T, O, N> neg_DP2(-2.4187564849853515625e-4);
    vec_simd<T, O, N> neg_DP3(-3.77489497744594108e-8);
    neg_DP1 *= p;
    neg_DP2 *= p;
    neg_DP3 *= p;
    z += neg_DP1;
    z += neg_DP2;
    z += neg_DP3;

    // Select Polynomial for sin
    vec_simd<T, O, N> poly1 = Poly_helper<T, O, N, coeff_cephes_cos>::poly(z);
    vec_simd<T, O, N> poly2 = Poly_helper<T, O, N, coeff_cephes_sin>::poly(z);
    x = select_poly(j, poly1, poly2);
    x = select_sign_sin(j, rhs, x);

    // Select Polynomial for cos
    j = round_up_even(floor(y - vec_simd<T, O, N>(2.0)));
    poly1 = Poly_helper<T, O, N, coeff_cephes_cos>::poly(z);
    poly2 = Poly_helper<T, O, N, coeff_cephes_sin>::poly(z);
    y = select_poly(j, poly1, poly2);
    y = select_sign_cos(j, y);

    // Select Sign
    return x / y;
}
} // namespace cyme
#endif
