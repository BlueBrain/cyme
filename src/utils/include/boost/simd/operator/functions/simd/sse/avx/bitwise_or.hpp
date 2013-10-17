//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_BITWISE_OR_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_BITWISE_OR_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/operator/functions/bitwise_or.hpp>
#include <boost/simd/include/functions/simd/genmask.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitwise_or_, boost::simd::tag::avx_
                            , (A0)(A1)
                            , ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                              ((simd_<arithmetic_<A1>,boost::simd::tag::avx_>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef native<float, tag::avx_> ftype;
      return bitwise_cast<A0>( _mm256_or_ps ( bitwise_cast<ftype>(a0)
                                            , bitwise_cast<ftype>(a1)
                                            )
                             );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitwise_or_, boost::simd::tag::avx_
                            , (A0)(A1)
                            , ((simd_<double_<A0>,boost::simd::tag::avx_>))
                              ((simd_<double_<A1>,boost::simd::tag::avx_>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return _mm256_or_pd(a0, a1);
    }
  };

//   BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::bitwise_or_, boost::simd::tag::avx_,
//                                 (A0),
//                                 ((simd_<logical_<A0>,boost::simd::tag::avx_>))
//                                 ((simd_<logical_<A0>,boost::simd::tag::avx_>))
//                               )
//   {
//     typedef A0 result_type;
//     BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
//     {
//       return bitwise_cast<result_type>(bitwise_or(genmask(a0), genmask(a1)));
//     }
//   };
} } }

#endif
#endif
