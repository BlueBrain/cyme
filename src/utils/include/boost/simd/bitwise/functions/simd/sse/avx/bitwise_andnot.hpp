//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_SSE_AVX_BITWISE_ANDNOT_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_SSE_AVX_BITWISE_ANDNOT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
#include <boost/simd/bitwise/functions/bitwise_andnot.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::bitwise_andnot_, boost::simd::tag::avx_, (A0),
                             ((simd_<double_<A0>,boost::simd::tag::avx_>))
                             ((simd_<double_<A0>,boost::simd::tag::avx_>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return _mm256_andnot_pd(a1, a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::bitwise_andnot_, boost::simd::tag::avx_, (A0),
                             ((simd_<single_<A0>,boost::simd::tag::avx_>))
                             ((simd_<single_<A0>,boost::simd::tag::avx_>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return _mm256_andnot_ps(a1, a0);
    }
  };
} } }

#endif
#endif
