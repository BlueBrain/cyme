//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BOOLEAN_FUNCTIONS_SELADD_HPP_INCLUDED
#define BOOST_SIMD_BOOLEAN_FUNCTIONS_SELADD_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief seladd generic tag

     Represents the seladd function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct seladd_ : ext::elementwise_<seladd_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<seladd_> parent;
    };
  }
  /*!
    The function returns the second entry or the sum of the second and third entries,
    according to the first entry being True or False

    @par Semantic:

    For every parameters of types respectively T0, T1, T1:

    @code
    T1 r = seladd(a0,a1,a2);
    @endcode

    is similar to:

    @code
    T1 r = a0 ? a1+a2 : a1;
    @endcode

    @par Alias:
    @c ifadd

    @param a0

    @param a1

    @param a2

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::seladd_, seladd, 3)
    BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::seladd_, ifadd,  3)
} }

#endif

