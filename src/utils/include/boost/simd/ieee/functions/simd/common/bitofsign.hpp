//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_BITOFSIGN_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_BITOFSIGN_HPP_INCLUDED
#include <boost/simd/ieee/functions/bitofsign.hpp>
#include <boost/simd/include/constants/mzero.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/signmask.hpp>
#include <boost/simd/include/functions/simd/bitwise_and.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitofsign_, tag::cpu_, (A0)(X)
                            , ((simd_<signed_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1) { return b_and(a0, boost::simd::Signmask<A0>()); }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitofsign_, tag::cpu_, (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    inline result_type operator()(const A0&)const { return Zero<A0>(); }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitofsign_, tag::cpu_, (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1) { return b_and(a0, boost::simd::Mzero<result_type>()); }
  };
} } }

#endif
