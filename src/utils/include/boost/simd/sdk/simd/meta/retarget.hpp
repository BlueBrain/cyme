//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_META_RETARGET_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_META_RETARGET_HPP_INCLUDED

#include <boost/simd/sdk/simd/native_fwd.hpp>

namespace boost { namespace simd { namespace meta
{
  template<class T, class Extension>
  struct retarget
  {
    typedef typename T::value_type              value_type;
    typedef simd::native<value_type,Extension>  type;
  };
} } }

#endif
