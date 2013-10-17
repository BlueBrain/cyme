//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_COMMON_CLZ_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_COMMON_CLZ_HPP_INCLUDED

#include <boost/simd/bitwise/functions/clz.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/dec.hpp>
#include <boost/simd/include/functions/simd/reversebits.hpp>
#include <boost/simd/include/functions/simd/ffs.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/operator/functions/details/assert_utils.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::clz_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {

    typedef typename dispatch::meta::as_integer<A0>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type t =  bitwise_cast<result_type>(a0);
      BOOST_ASSERT_MSG( assert_all(a0), "clz not defined for 0" );
      return bitwise_cast<result_type>(dec(boost::simd::ffs(boost::simd::reversebits(t))));
    }
  };
} } }


#endif
