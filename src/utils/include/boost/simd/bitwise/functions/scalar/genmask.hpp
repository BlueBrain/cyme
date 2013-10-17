//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SCALAR_GENMASK_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SCALAR_GENMASK_HPP_INCLUDED

#include <boost/simd/bitwise/functions/genmask.hpp>
#include <boost/simd/include/functions/scalar/unary_minus.hpp>
#include <boost/simd/include/constants/allbits.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/sdk/meta/as_arithmetic.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::genmask_, tag::cpu_, (A0)
                                   , (scalar_< fundamental_<A0> >)
                                   )
  {
    typedef typename meta::as_arithmetic<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return a0 ? Allbits<result_type>() : Zero<result_type>();
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::genmask_, tag::cpu_, (A0)
                                   , (scalar_< integer_<A0> >)
                                   )
  {
    typedef typename meta::as_arithmetic<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return unary_minus(result_type(a0 != 0));
    }
  };
} } }

#endif
