//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_BITWISE_AND_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_BITWISE_AND_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/operator/functions/bitwise_and.hpp>
#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <boost/simd/sdk/meta/make_dependent.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::bitwise_and_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                                      ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      typedef typename meta::make_dependent < native<float,tag::avx_>
                                            , A0
                                            >::type                     type;

      return bitwise_cast<A0>( _mm256_and_ps ( bitwise_cast<type>(a0)
                                             , bitwise_cast<type>(a1)
                                             )
                             );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::bitwise_and_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_<double_<A0>,boost::simd::tag::avx_>))
                                      ((simd_<double_<A0>,boost::simd::tag::avx_>))
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      return _mm256_and_pd(a0, a1);
    }
  };
} } }

#endif
#endif
