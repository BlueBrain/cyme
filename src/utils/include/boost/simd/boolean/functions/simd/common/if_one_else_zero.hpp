//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BOOLEAN_FUNCTIONS_SIMD_COMMON_IF_ONE_ELSE_ZERO_HPP_INCLUDED
#define BOOST_SIMD_BOOLEAN_FUNCTIONS_SIMD_COMMON_IF_ONE_ELSE_ZERO_HPP_INCLUDED

#include <boost/simd/boolean/functions/if_one_else_zero.hpp>
#include <boost/simd/include/functions/simd/if_else_zero.hpp>
#include <boost/simd/include/constants/one.hpp>


namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::if_one_else_zero_
                                      , tag::cpu_
                                      , (A0)(X)
                                      , ((simd_<unspecified_<A0>,X>))
                                )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return if_else_zero(a0, One<A0>());
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::if_one_else_zero_
                                      , tag::cpu_
                                      , (A0)(X)
                                      , ((simd_<logical_<A0>,X>))
                                )
  {
    typedef typename A0::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return if_else_zero(a0, One<result_type>());
    }
  };
} } }

#endif
