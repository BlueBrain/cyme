//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_META_IS_BITWISE_LOGICAL_HPP_INCLUDED
#define BOOST_SIMD_SDK_META_IS_BITWISE_LOGICAL_HPP_INCLUDED

#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/simd/sdk/meta/as_arithmetic.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/sizeof.hpp>

namespace boost { namespace simd { namespace meta
{
  template<class T>
  struct is_bitwise_logical
   : mpl::equal_to< mpl::sizeof_< typename as_arithmetic<T>::type >
                  , mpl::sizeof_< typename as_logical<T>::type >
                  >
  {
  };
} } }

#endif
