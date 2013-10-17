//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SCALAR_MINUS_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SCALAR_MINUS_HPP_INCLUDED

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::minus_, tag::cpu_, (A0)
                            , (scalar_< arithmetic_<A0> >)
                              (scalar_< arithmetic_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2) { return a0-a1; }
  };
} } }

#endif
