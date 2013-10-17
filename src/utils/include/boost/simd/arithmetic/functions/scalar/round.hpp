//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_ROUND_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_ROUND_HPP_INCLUDED
#include <boost/simd/arithmetic/functions/round.hpp>
#include <boost/simd/include/functions/scalar/toint.hpp>
#include <boost/simd/include/functions/scalar/bitwise_or.hpp>
#include <boost/simd/include/functions/scalar/abs.hpp>
#include <boost/simd/include/functions/scalar/bitofsign.hpp>
#include <boost/simd/include/constants/maxflint.hpp>
#include <boost/simd/include/constants/half.hpp>
#include <boost/simd/sdk/math.hpp>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::round_, tag::cpu_
                            , (A0)
                            , (scalar_< integer_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return a0;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::round_, tag::cpu_
                            , (A0)
                            , (scalar_< single_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
#ifdef BOOST_SIMD_HAS_ROUNDF
      return ::roundf(a0);
#else
      const result_type v = simd::abs(a0);
      if (!(v <=  Maxflint<result_type>()))
          return a0;
      const uint32_t d = v+Half<result_type>();
      return b_or(result_type(d), bitofsign(a0));
#endif
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::round_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
#ifdef BOOST_SIMD_HAS_ROUND
      return ::round(a0);
#else
      const result_type v = simd::abs(a0);
      if (!(v <=  Maxflint<result_type>()))
          return a0;
      const uint64_t d = v+Half<result_type>();
      return b_or(result_type(d), bitofsign(a0));
#endif
     }
  };
} } }


#endif
