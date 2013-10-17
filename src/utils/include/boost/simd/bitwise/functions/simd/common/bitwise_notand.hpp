//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_COMMON_BITWISE_NOTAND_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_COMMON_BITWISE_NOTAND_HPP_INCLUDED
#include <boost/simd/bitwise/functions/bitwise_notand.hpp>
#include <boost/simd/include/functions/simd/complement.hpp>
#include <boost/simd/include/functions/simd/bitwise_and.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF(boost::simd::tag::bitwise_notand_, tag::cpu_,(A0)(A1)(X)
                                      , (boost::mpl::equal_to < boost::simd::meta::cardinal_of<A0>
                                                              , boost::simd::meta::cardinal_of<A1>
                                                              >
                                      )
                                    , ((simd_<arithmetic_<A0>,X>))
                                      ((simd_<arithmetic_<A1>,X>))
                                      )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2) { return bitwise_and(complement(a0), a1); }

  };
} } }

#endif
