/*
* Cyme - simd_vec.ipp, Copyright (c), 2014,
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
 * @file cyme/core/simd_vector/simd_vec.ipp
 * Implements SIMD generic vector class
 */

/** \cond */
#ifndef CYME_SIMD_VEC_IPP
#define CYME_SIMD_VEC_IPP

namespace cyme {

/** Round up to the next even integer */
template <cyme::simd O, int N>
vec_simd<int, O, N> round_up_even(const vec_simd<int, O, N> &rhs) {
    vec_simd<int, O, N> nrv;
    nrv.xmm = _mm_round_up_even<O, N>(rhs.xmm);
    return nrv;
}

template <class T, cyme::simd O, int N>
vec_simd<T, O, N>::vec_simd(const typename simd_trait<T, O, N>::value_type &a) {
    xmm = _mm_load1<typename simd_trait<T, O, N>::value_type, O, N>(a);
}

template <class T, cyme::simd O, int N>
vec_simd<T, O, N>::vec_simd() {}

template <class T, cyme::simd O, int N>
vec_simd<T, O, N>::vec_simd(typename simd_trait<T, O, N>::const_pointer a) {
    xmm = _mm_load<typename simd_trait<T, O, N>::value_type, O, N>(a);
}

template <class T, cyme::simd O, int N>
vec_simd<T, O, N>::vec_simd(typename simd_trait<T, O, N>::register_type x) {
    xmm = x;
}

template <class T, cyme::simd O, int N>
vec_simd<T, O, N> &vec_simd<T, O, N>::operator()() {
    return *this;
}

template <class T, cyme::simd O, int N>
const vec_simd<T, O, N> &vec_simd<T, O, N>::operator()() const {
    return *this;
}

template <class T, cyme::simd O, int N>
vec_simd<T, O, N> &vec_simd<T, O, N>::operator*=(const vec_simd<T, O, N> &rhs) {
    xmm = _mm_mul<typename simd_trait<T, O, N>::value_type, O, N>(xmm, rhs.xmm);
    return *this;
}

template <class T, cyme::simd O, int N>
vec_simd<T, O, N> &vec_simd<T, O, N>::operator/=(const vec_simd<T, O, N> &rhs) {
    xmm = _mm_div<typename simd_trait<T, O, N>::value_type, O, N>(xmm, rhs.xmm);
    return *this;
}

template <class T, cyme::simd O, int N>
vec_simd<T, O, N> &vec_simd<T, O, N>::operator+=(const vec_simd<T, O, N> &rhs) {
    xmm = _mm_add<typename simd_trait<T, O, N>::value_type, O, N>(xmm, rhs.xmm);
    return *this;
}

template <class T, cyme::simd O, int N>
vec_simd<T, O, N> &vec_simd<T, O, N>::operator-=(const vec_simd<T, O, N> &rhs) {
    xmm = _mm_sub<typename simd_trait<T, O, N>::value_type, O, N>(xmm, rhs.xmm);
    return *this;
}

template <class T, cyme::simd O, int N>
vec_simd<T, O, N> &vec_simd<T, O, N>::operator&=(const vec_simd<T, O, N> &rhs) {
    xmm = _mm_and<typename simd_trait<T, O, N>::value_type, O, N>(xmm, rhs.xmm);
    return *this;
}

template <class T, cyme::simd O, int N>
vec_simd<T, O, N> &vec_simd<T, O, N>::operator|=(const vec_simd<T, O, N> &rhs) {
    xmm = _mm_or<typename simd_trait<T, O, N>::value_type, O, N>(xmm, rhs.xmm);
    return *this;
}

template <class T, cyme::simd O, int N>
vec_simd<T, O, N> &vec_simd<T, O, N>::operator>>=(const vec_simd<T, O, N> &rhs) {
    xmm = _mm_srl<typename simd_trait<T, O, N>::value_type, O, N>(xmm, rhs.xmm);
    return *this;
}

template <class T, cyme::simd O, int N>
vec_simd<T, O, N> &vec_simd<T, O, N>::operator~() {
    xmm = _mm_andnot<typename simd_trait<T, O, N>::value_type, O, N>(xmm);
    return *this;
}

template <class T, cyme::simd O, int N>
vec_simd<T, O, N> &vec_simd<T, O, N>::single(const typename vec_simd<T, O, N>::value_type &b) {
    xmm = _mm_single_load<typename simd_trait<T, O, N>::value_type, O, N>(b);
    return *this;
}

template <class T, cyme::simd O, int N>
typename vec_simd<T, O, N>::value_type vec_simd<T, O, N>::single(typename vec_simd<T, O, N>::pointer b) {
    return _mm_single_store<typename simd_trait<T, O, N>::value_type, O, N>(xmm, b);
}

template <class T, cyme::simd O, int N>
void vec_simd<T, O, N>::store(typename simd_trait<T, O, N>::pointer a) const {
    _mm_store<value_type, O, N>(xmm, a);
}

template <class T, cyme::simd O, int N>
void vec_simd<T, O, N>::print(std::ostream &out) const {
    const int size = elems_helper<T, N>::size;
    T elems[size] __attribute__((aligned(static_cast<int>(cyme::trait_register<T, cyme::__GETSIMD__()>::size))));
    store(elems);
    for (unsigned int i = 0; i < size; i++)
        out << " " << elems[i];
}

template <class T, cyme::simd O, int N>
vec_simd<T, O, N> &vec_simd<T, O, N>::neg() {
    xmm = _mm_neg<typename simd_trait<T, O, N>::value_type, O, N>(xmm);
    return *this;
}

template <class T, cyme::simd O, int N>
bool vec_simd<T, O, N>::is_empty() {
    return _mm_is_empty<typename simd_trait<T, O, N>::value_type, O, N>(xmm);
}

template <class T, cyme::simd O, int N>
vec_simd<T, O, N> cast(const vec_simd<int, O, N> &rhs) {
    vec_simd<T, O, N> nrv;
    nrv.xmm = _mm_cast<typename simd_trait<T, O, N>::value_type, O, N>(rhs.xmm);
    return nrv;
}

template <class T, cyme::simd O, int N>
vec_simd<int, O, N> floor(const vec_simd<T, O, N> &rhs) {
    vec_simd<int, O, N> nrv;
    nrv.xmm = _mm_floor<typename simd_trait<T, O, N>::value_type, O, N>(rhs.xmm);
    return nrv;
}

template <class T, cyme::simd O, int N>
vec_simd<T, O, N> ge(const vec_simd<T, O, N> &rhs) {
    vec_simd<T, O, N> nrv;
    nrv.xmm = _mm_ge<typename simd_trait<T, O, N>::value_type, O, N>(rhs.xmm);
    return nrv;
}

template <class T, cyme::simd O, int N>
vec_simd<T, O, N> gf(const vec_simd<T, O, N> &rhs) {
    vec_simd<T, O, N> nrv;
    nrv.xmm = _mm_gf<typename simd_trait<T, O, N>::value_type, O, N>(rhs.xmm);
    return nrv;
}

template <class T, cyme::simd O, int N>
vec_simd<T, O, N> twok(const vec_simd<int, O, N> &rhs) {
    vec_simd<T, O, N> nrv;
    nrv.xmm = _mm_twok<typename simd_trait<T, O, N>::value_type, O, N>(rhs.xmm);
    return nrv;
}

template <class T, cyme::simd O, int N>
vec_simd<T, O, N> fabs(const vec_simd<T, O, N> &rhs) {
    vec_simd<T, O, N> nrv;
    nrv.xmm = _mm_fabs<typename simd_trait<T, O, N>::value_type, O, N>(rhs.xmm);
    return nrv;
}

template <class T, cyme::simd O, int N>
vec_simd<T, O, N> min(const vec_simd<T, O, N> &v1, const vec_simd<T, O, N> &v2) {
    vec_simd<T, O, N> nrv;
    nrv.xmm = _mm_min<typename simd_trait<T, O, N>::value_type, O, N>(v1.xmm, v2.xmm);
    return nrv;
}

template <class T, cyme::simd O, int N>
vec_simd<T, O, N> select_poly(const vec_simd<int, O, N> &sel, const vec_simd<T, O, N> &lhs,
                              const vec_simd<T, O, N> &rhs) {
    vec_simd<T, O, N> nrv;
    nrv.xmm = _mm_select_poly<typename simd_trait<T, O, N>::value_type, O, N>(sel.xmm, lhs.xmm, rhs.xmm);
    return nrv;
}

template <class T, cyme::simd O, int N>
vec_simd<T, O, N> select_sign_sin(const vec_simd<int, O, N> &swap, const vec_simd<T, O, N> &lhs,
                                  const vec_simd<T, O, N> &rhs) {
    vec_simd<T, O, N> nrv;
    nrv.xmm = _mm_select_sign_sin<typename simd_trait<T, O, N>::value_type, O, N>(swap.xmm, lhs.xmm, rhs.xmm);
    return nrv;
}

template <class T, cyme::simd O, int N>
vec_simd<T, O, N> select_sign_cos(const vec_simd<int, O, N> &swap, const vec_simd<T, O, N> &rhs) {
    vec_simd<T, O, N> nrv;
    nrv.xmm = _mm_select_sign_cos<typename simd_trait<T, O, N>::value_type, O, N>(swap.xmm, rhs.xmm);
    return nrv;
}

template <class T1, cyme::simd O, int N, class T2>
void cast(const vec_simd<T1, O, N> &v1, vec_simd<T2, O, N> &v2) {
    v2.xmm =
        _mm_cast<typename simd_trait<T1, O, N>::value_type, O, N, typename simd_trait<T2, O, N>::value_type>(v1.xmm);
}

#ifdef __FMA__
template <class T, cyme::simd O, int N>
void vec_simd<T, O, N>::ma(const vec_simd &lhs, const vec_simd &rhs) {
    xmm = _mm_fma<typename simd_trait<T, O, N>::value_type, O, N>(xmm, lhs.xmm, rhs.xmm);
}

template <class T, cyme::simd O, int N>
void vec_simd<T, O, N>::ms(const vec_simd &lhs, const vec_simd &rhs) {
    xmm = _mm_fms<typename simd_trait<T, O, N>::value_type, O, N>(xmm, lhs.xmm, rhs.xmm);
}

template <class T, cyme::simd O, int N>
void vec_simd<T, O, N>::nma(const vec_simd &lhs, const vec_simd &rhs) {
    xmm = _mm_nfma<typename simd_trait<T, O, N>::value_type, O, N>(xmm, lhs.xmm, rhs.xmm);
}

template <class T, cyme::simd O, int N>
void vec_simd<T, O, N>::nms(const vec_simd &lhs, const vec_simd &rhs) {
    xmm = _mm_nfms<typename simd_trait<T, O, N>::value_type, O, N>(xmm, lhs.xmm, rhs.xmm);
}
#endif
} // end namespace

template <class T, cyme::simd O, int N>
std::ostream &operator<<(std::ostream &out, const cyme::vec_simd<T, O, N> &vec) {
    vec.print(out);
    return out;
}

#endif
/** \endcond */
