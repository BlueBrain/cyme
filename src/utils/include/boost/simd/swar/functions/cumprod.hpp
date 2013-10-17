//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_CUMPROD_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_CUMPROD_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/simd/operator/functions/multiplies.hpp>
#include <boost/simd/constant/constants/one.hpp>


/*!
 * \ingroup boost_simd_swar
 * \defgroup boost_simd_swar_cumprod cumprod
 *
 * \par Description
 * compute the cumulate prod of the vector elements
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/cumprod.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::cumprod_(A0)>::type
 *     cumprod(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of cumprod
 *
 * \return a value of the same type as the parameter
 *
 * \par Notes
 * \par
 * This is a swar operation. As such it has no real interest outside
 * SIMD mode.
 * \par
 * Such an operation is a transform of an SIMD vector, that will return
 * vectors obtained on a non necessarily elementwise basis from the inputs
 * elements
 * \par
 * If usable and used in scalar mode, it reduces to the operation
 * on a one element vector.
 *
**/

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  cumprod generic tag

      Represents the cumprod function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct cumprod_ : ext::cumulative_<cumprod_, tag::multiplies_, tag::One>
    {
      /// @brief Parent hierarchy
      typedef ext::cumulative_<cumprod_, tag::multiplies_, tag::One> parent;
    };
  }
  /*!
    Computes the cumulated product of the vector elements

    @par semantic:
    For any given vector @c x of type @c T:

    @code
    T r = cumprod(x);
    @endcode

    The function coincide with plus for floating point parameters.
    For integers is similar to:

    @code
    T r =x;
    for(int i=0;i < T::static_size; ++i)
      r[i]*= r[i-1];
    @endcode

    @param  a0

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::cumprod_, cumprod, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::cumprod_, cumprod, 2)
} }

#endif
