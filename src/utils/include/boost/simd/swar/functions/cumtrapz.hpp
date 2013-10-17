//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_CUMTRAPZ_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_CUMTRAPZ_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/simd/operator/functions/multiplies.hpp>
#include <boost/simd/constant/constants/one.hpp>



namespace boost { namespace simd { namespace tag
  {
   /*!
     @brief cumtrapz generic tag

     Represents the cumtrapz function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct cumtrapz_ : tag::formal_
    {
      /// @brief Parent hierarchy
      typedef tag::formal_ parent;
    };
  }
  /*!
    Computes the cumulate trapz of the vector elements using the abscissae differences
    is they are given
    z = cumtrapz(y) computes an approximation of the cumulative
    integral of y via the trapezoidal method (with unit spacing).  to
    compute the integral for spacing different from one, multiply z by
    the spacing increment or use cumtrapz(dx, y) where dx is the abscisae
    constant and SCALAR increment.

    @par Semantic:

    For every h of scalar type T0 and y of type T1:

    @code
    T0 r = cumtrapz(h, y);
    @endcode

    is similar to:

    @code
    T r(0] = zero;
    for(int i=1;i < size(x); ++i)
      r[i] = r[i-1]+(y[i-1]+y[i])*h*half;
    @endcode

    @param a0

    @param a1

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::cumtrapz_, cumtrapz, 1)
  /*!
    Computes the cumulate trapz of the vector elements using the abscissae differences
    is they are given
    z = cumtrapz(y) computes an approximation of the cumulative
    integral of y via the trapezoidal method (with unit spacing).

    @par Semantic:

    For every  y of type T0:

    @code
    T0 r = cumtrapz(y);
    @endcode

    is similar to:

    @code
    T r(0] = zero;
    for(int i=1;i < size(x); ++i)
      r[i] += (y[i-1]+y[i])*half;
    @endcode

    @param a0

    @return a value of the same type as the second parameter
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::cumtrapz_, cumtrapz, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::cumtrapz_, cumtrapz, 3)
} }

#endif
