//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_SPLAT_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_SPLAT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/operator/functions/splat.hpp>

//==============================================================================
// Implementation when type A0 is double
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::splat_, boost::simd::tag::avx_, (A0)(A1)
                            , (scalar_< fundamental_<A0> >)
                              ((target_< simd_< double_<A1>, boost::simd::tag::avx_ > >))
                      )
  {
    typedef typename A1::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return _mm256_set1_pd(double(a0));
    }
  };
} } }

//==============================================================================
// Implementation when type A0 is float
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::splat_, boost::simd::tag::avx_, (A0)(A1)
                            , (scalar_< fundamental_<A0> >)
                              ((target_< simd_< single_<A1>, boost::simd::tag::avx_ > >))
                      )
  {
    typedef typename A1::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return _mm256_set1_ps(float(a0));
    }
  };
} } }

//==============================================================================
// Implementation when type A0 is ints8
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::splat_, boost::simd::tag::avx_, (A0)(A1)
                            , (scalar_< fundamental_<A0> >)
                              ((target_< simd_< ints8_<A1>, boost::simd::tag::avx_ > >))
                      )
  {
    typedef typename A1::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return _mm256_set1_epi8(a0);
    }
  };
} } }

//==============================================================================
// Implementation when type A0 is ints16
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::splat_, boost::simd::tag::avx_, (A0)(A1)
                            , (scalar_< fundamental_<A0> >)
                              ((target_< simd_< ints16_<A1>, boost::simd::tag::avx_ > >))
                      )
  {
    typedef typename A1::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return _mm256_set1_epi16(a0);
    }
  };
} } }

//==============================================================================
// Implementation when type A0 is ints32
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::splat_, boost::simd::tag::avx_, (A0)(A1)
                            , (scalar_< fundamental_<A0> >)
                              ((target_< simd_< ints32_<A1>, boost::simd::tag::avx_ > >))
                      )
  {
    typedef typename A1::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return _mm256_set1_epi32(a0);
    }
  };
} } }

//==============================================================================
// Implementation when type A0 is ints64
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::splat_, boost::simd::tag::avx_, (A0)(A1)
                            , (scalar_< fundamental_<A0> >)
                              ((target_< simd_< ints64_<A1>, boost::simd::tag::avx_ > >))
                      )
  {
    typedef typename A1::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
#ifndef BOOST_MSVC
      result_type that = _mm256_set1_epi64x(a0);
#else
      result_type that = make<result_type>(a0, a0, a0, a0);
#endif
      return that;
    }
  };
} } }

#endif
#endif
