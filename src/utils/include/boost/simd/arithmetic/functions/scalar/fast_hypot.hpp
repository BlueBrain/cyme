//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_FAST_HYPOT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_FAST_HYPOT_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/fast_hypot.hpp>
#include <boost/simd/include/functions/scalar/sqrt.hpp>
#include <boost/simd/include/functions/scalar/sqr.hpp>
#include <boost/simd/include/functions/scalar/is_nan.hpp>
#include <boost/simd/include/functions/scalar/is_inf.hpp>
#include <boost/simd/include/functions/scalar/ldexp.hpp>
#include <boost/simd/include/functions/scalar/fma.hpp>
#include <boost/simd/include/constants/eps.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/meta/as_floating.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::fast_hypot_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)
                              (scalar_< double_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
#if !defined(BOOST_SIMD_NO_NANS) && !defined(BOOST_SIMD_NO_INFINITIES)
      A0 x =  boost::simd::abs(a0);
      A0 y =  boost::simd::abs(a1);
      if (boost::simd::is_inf(x+y)) return Inf<float>();
      if (boost::simd::is_inf(x)) return Inf<float>();
      if (boost::simd::is_inf(y)) return Inf<float>();
      if (y > x) std::swap(x, y);
      if (x*Eps<A0>() >=  y) return x;
      return x*boost::simd::sqrt(One<A0>()+boost::simd::sqr(y/x));
#else
      return boost::simd::sqrt(boost::simd::fma(a0, a0, a1*a1));
#endif
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::fast_hypot_, tag::cpu_
                            , (A0)
                            , (scalar_< single_<A0> >)
                              (scalar_< single_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
#if !defined(BOOST_SIMD_NO_NANS) && !defined(BOOST_SIMD_NO_INFINITIES)
      // flibc do that in ::fast_hypotf(a0, a1) in asm with no more speed!
      // proper impl as for double is 30% slower
      return static_cast<result_type>(boost::simd::sqrt(fma(static_cast<double>(a0), static_cast<double>(a0),
                                                            boost::simd::sqr(static_cast<double>(a1)))));
#else
      return boost::simd::sqrt(boost::simd::fma(a0, a0, a1*a1));
#endif
    }
  };
} } }


#endif
