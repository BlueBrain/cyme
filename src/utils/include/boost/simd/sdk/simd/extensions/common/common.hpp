//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_COMMON_COMMON_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_COMMON_COMMON_HPP_INCLUDED

#if !defined(BOOST_SIMD_DETECTED)
#define BOOST_SIMD_NO_SIMD

#define BOOST_SIMD_BYTES      16
#define BOOST_SIMD_BITS       128
#define BOOST_SIMD_STRING     "simd_emulation"
#define BOOST_SIMD_CARDINALS  (2)(4)(8)(16)
#define BOOST_SIMD_DEFAULT_EXTENSION ::boost::simd::tag::simd_emulation_<16u>
#define BOOST_SIMD_DEFAULT_SITE ::boost::dispatch::tag::cpu_
#endif

#if !defined(BOOST_SIMD_GPR_COUNT)
#define BOOST_SIMD_GPR_COUNT 1u
#endif

#if !defined(BOOST_SIMD_VR_COUNT)
#define BOOST_SIMD_VR_COUNT  0u
#endif

#include <boost/simd/sdk/config/type_lists.hpp>

#if !defined(BOOST_SIMD_DETECTED) || defined(BOOST_SIMD_SIMD_HAS_ALL_TYPES)
#define BOOST_SIMD_SIMD_INTEGRAL_UNSIGNED_TYPES BOOST_SIMD_INTEGRAL_UNSIGNED_TYPES
#define BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES BOOST_SIMD_INTEGRAL_SIGNED_TYPES
#define BOOST_SIMD_SIMD_REAL_TYPES BOOST_SIMD_REAL_TYPES
#define BOOST_SIMD_SIMD_INT_CONVERT_TYPES BOOST_SIMD_INT_CONVERT_TYPES
#define BOOST_SIMD_SIMD_UINT_CONVERT_TYPES BOOST_SIMD_UINT_CONVERT_TYPES
#define BOOST_SIMD_SIMD_GROUPABLE_TYPES BOOST_SIMD_GROUPABLE_TYPES
#define BOOST_SIMD_SIMD_SPLITABLE_TYPES BOOST_SIMD_SPLITABLE_TYPES
#define BOOST_SIMD_SIMD_REAL_GROUPABLE_TYPES BOOST_SIMD_REAL_GROUPABLE_TYPES
#define BOOST_SIMD_SIMD_REAL_SPLITABLE_TYPES BOOST_SIMD_REAL_SPLITABLE_TYPES
#endif

#include <boost/simd/memory/aligned_array.hpp>
#include <boost/simd/sdk/config.hpp>

#define BOOST_SIMD_SIMD_INTEGRAL_TYPES BOOST_SIMD_SIMD_INTEGRAL_UNSIGNED_TYPES BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES
#define BOOST_SIMD_SIMD_UNSIGNED_TYPES BOOST_SIMD_SIMD_INTEGRAL_UNSIGNED_TYPES
#define BOOST_SIMD_SIMD_SIGNED_TYPES BOOST_SIMD_SIMD_REAL_TYPES BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES
#define BOOST_SIMD_SIMD_REAL_CONVERTIBLE_TYPES  BOOST_SIMD_SIMD_INT_CONVERT_TYPES BOOST_SIMD_SIMD_UINT_CONVERT_TYPES BOOST_SIMD_SIMD_REAL_TYPES
#define BOOST_SIMD_SIMD_TYPES BOOST_SIMD_SIMD_REAL_TYPES BOOST_SIMD_SIMD_INTEGRAL_TYPES

#endif