//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BOOLEAN_FUNCTIONS_SCALAR_IF_ZERO_ELSE_ONE_HPP_INCLUDED
#define BOOST_SIMD_BOOLEAN_FUNCTIONS_SCALAR_IF_ZERO_ELSE_ONE_HPP_INCLUDED

#include <boost/simd/boolean/functions/if_zero_else_one.hpp>
#include <boost/simd/include/functions/scalar/is_nez.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_zero_else_one_, tag::cpu_, (A0)
                            , (scalar_< logical_<A0> >)
                            )
  {
    typedef typename A0::value_type result_type;
    inline result_type operator()(const A0 & a0) const
      { return a0 ? Zero<result_type>() : One<result_type>(); }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_zero_else_one_, tag::cpu_, (A0)
                            , (scalar_< unspecified_<A0> >)
                            )
  {
    typedef A0 result_type;
    inline result_type operator()(const A0 & a0) const
    { return boost::simd::is_nez(a0) ? Zero<A0>() : One<A0>(); }
  };
} } }

#endif
