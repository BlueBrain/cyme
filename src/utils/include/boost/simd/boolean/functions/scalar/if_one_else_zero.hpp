//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BOOLEAN_FUNCTIONS_SCALAR_IF_ONE_ELSE_ZERO_HPP_INCLUDED
#define BOOST_SIMD_BOOLEAN_FUNCTIONS_SCALAR_IF_ONE_ELSE_ZERO_HPP_INCLUDED

#include <boost/simd/boolean/functions/if_one_else_zero.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/false.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_one_else_zero_, tag::cpu_, (A0)
                                   , (scalar_< logical_<A0> >)
                                   )
  {
    typedef typename A0::value_type result_type;
    inline result_type operator()(const A0 & a0) const
    { return result_type(a0!= boost::simd::False<A0>()); }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_one_else_zero_, tag::cpu_, (A0)
                                   , (scalar_< fundamental_<A0> >)
                                   )
  {
    typedef A0 result_type;
    inline result_type operator()(const A0 & a0) const
    { return  result_type(a0!= boost::simd::Zero<A0>()); }
  };
} } }

#endif
