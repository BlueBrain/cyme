//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BITWISE_FUNCTIONS_FFS_HPP_INCLUDED
#define NT2_BITWISE_FUNCTIONS_FFS_HPP_INCLUDED

#include <boost/simd/bitwise/include/functions/ffs.hpp>
#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    using boost::simd::tag::ffs_;
  }

  using boost::simd::ffs;
}

#endif