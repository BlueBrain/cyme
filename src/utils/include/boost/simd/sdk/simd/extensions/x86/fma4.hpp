//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_X86_FMA4_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_X86_FMA4_HPP_INCLUDED

#if defined(__FMA4__)
#  ifndef BOOST_SIMD_HAS_FMA4_SUPPORT
#    define BOOST_SIMD_HAS_FMA4_SUPPORT
#  endif
#elif defined(BOOST_SIMD_HAS_FMA4_SUPPORT) && !defined(_MSC_VER)
#  undef BOOST_SIMD_HAS_FMA4_SUPPORT
#endif

#ifdef BOOST_SIMD_HAS_FMA4_SUPPORT
#  ifndef BOOST_SIMD_HAS_AVX_SUPPORT
#    define BOOST_SIMD_HAS_AVX_SUPPORT
#  endif
#  ifndef BOOST_SIMD_HAS_SSE4A_SUPPORT
#    define BOOST_SIMD_HAS_SSE4A_SUPPORT
#  endif
#endif

#if !defined(BOOST_SIMD_DETECTED) && defined(BOOST_SIMD_HAS_FMA4_SUPPORT)

////////////////////////////////////////////////////////////////////////////////
// FMA4 extensions flags
////////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_DETECTED
#define BOOST_SIMD_FMA4
#define BOOST_SIMD_SSE_FAMILY
#define BOOST_SIMD_STRING             "FMA4"
#define BOOST_SIMD_STRING_LIST        "SSE2 SSE3 SSE4A SSSE3 SSE4_1 SSE4_2 AVX FMA4"
#define BOOST_SIMD_BYTES              32
#define BOOST_SIMD_BITS               256
#define BOOST_SIMD_CARDINALS          (2)(4)(8)(16)(32)
#define BOOST_SIMD_TAG_SEQ            (::boost::simd::tag::avx_)(::boost::simd::tag::sse_)
#define BOOST_SIMD_DEFAULT_EXTENSION  ::boost::simd::tag::avx_
#define BOOST_SIMD_DEFAULT_SITE       ::boost::simd::tag::fma4_
#define BOOST_SIMD_SIMD_HAS_ALL_TYPES

// FMA4 header not standardized
#ifdef _MSC_VER
#include <intrin.h>
#else
#include <x86intrin.h>
#include <fma4intrin.h>
#endif

#include <boost/simd/sdk/simd/extensions/meta/sse.hpp>
#include <boost/simd/sdk/simd/extensions/meta/avx.hpp>

#endif
#endif
