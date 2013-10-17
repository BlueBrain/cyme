//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_HYPOT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_HYPOT_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  hypot generic tag

      Represents the hypot function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct hypot_ : ext::elementwise_<hypot_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<hypot_> parent;
    };
  }
  /*!
    Computes  computes \f$(x^2 + y^2)^{1/2}\f$

    @par semantic:
    For any given value @c x,  @c y of floating type @c T:

    @code
    T r = hypot(x, y);
    @endcode

    The code is similar to:

    @code
    T r = sqrt(sqr(x)+sqr(y));
    @endcode

    Provision are made to avoid overflow as possible and to compute
    @c hypot accurately.
    If these considerations can be put aside use
    @c fast_hypot.

    @param  a0
    @param  a1

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::hypot_, hypot, 2)
} }

#endif


