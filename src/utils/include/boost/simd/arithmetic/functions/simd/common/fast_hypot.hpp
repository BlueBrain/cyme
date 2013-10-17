//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_FAST_HYPOT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_FAST_HYPOT_HPP_INCLUDED
#include <boost/simd/arithmetic/functions/fast_hypot.hpp>
#include <boost/simd/include/functions/simd/abs.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/is_greater.hpp>
#include <boost/simd/include/functions/simd/is_greater_equal.hpp>
#include <boost/simd/include/functions/simd/sqrt.hpp>
#include <boost/simd/include/functions/simd/sqr.hpp>
#include <boost/simd/include/functions/simd/plus.hpp>
#include <boost/simd/include/functions/simd/multiplies.hpp>
#include <boost/simd/include/functions/simd/divides.hpp>
#include <boost/simd/include/constants/eps.hpp>
#include <boost/simd/include/constants/one.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::fast_hypot_, tag::cpu_
                                   , (A0)(X)
                                   , ((simd_<floating_<A0>,X>))
                                     ((simd_<floating_<A0>,X>))
                                   )
  {

    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      A0 x =  boost::simd::abs(a0);
      A0 y =  boost::simd::abs(a1);
      bA0 gtyx = gt(y,x);
      A0 xx = if_else(gtyx,y,x);
      A0 yy = if_else(gtyx,x,y);
      A0 r =  xx*sqrt(One<A0>()+sqr(yy/xx));
      return if_else(ge(xx*Eps<A0>(), yy), xx, r);
   }
  };
} } }


#endif
