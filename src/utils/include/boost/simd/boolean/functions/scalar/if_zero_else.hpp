//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BOOLEAN_FUNCTIONS_SCALAR_IF_ZERO_ELSE_HPP_INCLUDED
#define BOOST_SIMD_BOOLEAN_FUNCTIONS_SCALAR_IF_ZERO_ELSE_HPP_INCLUDED

#include <boost/simd/boolean/functions/if_zero_else.hpp>
#include <boost/simd/include/functions/scalar/is_nez.hpp>
#include <boost/simd/include/constants/zero.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::if_zero_else_, tag::cpu_, (A0)(A1)
                                    , (scalar_< logical_<A0> >)
                                      (scalar_< unspecified_<A1> >)
                                    )
  {
    typedef A1 result_type;
    inline A1 operator()(const A0 & a0,const A1 & a1) const
    { return is_nez(a0) ? Zero<result_type>() : a1; }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::if_zero_else_, tag::cpu_, (A0)(A1)
                                    , (scalar_< unspecified_<A0> >)
                                      (scalar_< unspecified_<A1> >)
                                    )
  {
    typedef A1 result_type;
    inline A1 operator()(const A0 & a0,const A1 & a1) const
    { return is_nez(a0) ? Zero<result_type>() : a1; }
  };
} } }

#endif
