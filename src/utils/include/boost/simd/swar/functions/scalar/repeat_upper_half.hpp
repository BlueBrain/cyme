//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SCALAR_REPEAT_UPPER_HALF_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SCALAR_REPEAT_UPPER_HALF_HPP_INCLUDED

#include <boost/simd/swar/functions/repeat_upper_half.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::repeat_upper_half_, tag::cpu_
                                    , (A0)
                                    , (scalar_< unspecified_<A0> >)
                                    )
  {
    typedef A0 result_type;

    result_type operator()(A0 const& a0) const
    {
      return a0;
    }
  };
} } }

#endif
