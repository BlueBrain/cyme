//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_CONSTANTS_STIRLINGLARGELIM_HPP_INCLUDED
#define NT2_EULER_CONSTANTS_STIRLINGLARGELIM_HPP_INCLUDED

#include <boost/simd/constant/hierarchy.hpp>
#include <boost/simd/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    BOOST_SIMD_CONSTANT_REGISTER( Stirlinglargelim, double
                                , 0, 0x41d628f6         // 35.0399895f
                                , 0x4061e083ba3443d4ll  // 172.0
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Stirlinglargelim, Stirlinglargelim);
}

#endif
