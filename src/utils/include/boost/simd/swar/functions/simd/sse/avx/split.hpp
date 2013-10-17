//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_SPLIT_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_SPLIT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/swar/functions/split.hpp>
#include <boost/simd/sdk/simd/meta/retarget.hpp>
#include <boost/simd/sdk/meta/is_upgradable.hpp>

namespace boost { namespace simd { namespace ext
{
  //============================================================================
  // Implementation when type is single_
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::split_
                                    , boost::simd::tag::avx_
                                    , (A0)(A1)
                                    , ((simd_<single_<A0>,boost::simd::tag::avx_>))
                                      ((simd_<double_<A1>,boost::simd::tag::avx_>))
                                      ((simd_<double_<A1>,boost::simd::tag::avx_>))
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0 & a0,  A1& a1, A1& a2) const
    {
      a1 = _mm256_cvtps_pd(_mm256_extractf128_ps(a0, 0)) ;
      a2 = _mm256_cvtps_pd(_mm256_extractf128_ps(a0, 1)) ;
    }
  };

  //============================================================================
  // Implementation when type is arithmetic_
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::split_
                                      , boost::simd::tag::avx_
                                      , (A0)(A1)
                                      , (simd::meta::is_upgradable_to<A0,A1>)
                                      , ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                                        ((simd_<arithmetic_<A1>,boost::simd::tag::avx_>))
                                        ((simd_<arithmetic_<A1>,boost::simd::tag::avx_>))
                                      )
  {
    typedef void result_type;
    typedef typename meta::retarget<A0,tag::sse_>::type A0_sse_;
    typedef typename meta::retarget<A1,tag::sse_>::type A1_sse_;

    BOOST_FORCEINLINE
    result_type operator()(const A0 & a0,  A1& a1, A1& a2)const
    {
      A0_sse_ a00 = _mm256_extractf128_si256(a0, 0);
      A0_sse_ a01 = _mm256_extractf128_si256(a0, 1);

      A1_sse_ ha000, ha001;
      split(a00, ha000, ha001);
      a1 = _mm256_castsi128_si256(ha000);
      a1 = _mm256_insertf128_si256(a1, ha001, 1);

      A1_sse_ ha010, ha011;
      split(a01, ha010, ha011);
      a2 = _mm256_castsi128_si256(ha010);
      a2 = _mm256_insertf128_si256(a2, ha011, 1);
    }
  };
} } }

#endif
#endif
