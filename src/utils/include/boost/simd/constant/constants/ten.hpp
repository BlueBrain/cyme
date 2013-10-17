//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_TEN_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_TEN_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Ten generic tag

     Represents the Ten constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Ten, double, 10
                                , 0x41200000UL, 0x4024000000000000ULL
                                );
  }
  /*!
   Generates value 10

    @par Semantic:

    @code
    T r = Ten<T>();
    @endcode

    is similar to:

    @code
    T r = T(10);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Ten, Ten)
} }

#include <boost/simd/constant/common.hpp>

#endif

