//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_IDIVCEIL_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_IDIVCEIL_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd {
  namespace tag
  {
    /*!
      @brief  idivceil generic tag

      Represents the idivceil function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct idivceil_ : ext::elementwise_<idivceil_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<idivceil_> parent;
    };
  }
  /*!
    Computes the integer conversion of the ceil of the division of its parameters.

    @par semantic:
    For any given value @c x,  @c y of type @c T:

    @code
    T r = idivceil(x, y);
    @endcode

    The code is similar to:

    @code
    as_integer<T> r = toints(ceil(x/y));
    @endcode

    If y is null, it returns Valmax (resp. Valmin)
    if x is positive (resp. negative) and 0 if x is null.

    @param  a0
    @param  a1

    @return      a value of the integral type associated to the input.

  **/

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::idivceil_, idivceil, 2)
} }

#endif
