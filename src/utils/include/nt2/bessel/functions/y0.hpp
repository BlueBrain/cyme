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
#ifndef NT2_BESSEL_FUNCTIONS_Y0_HPP_INCLUDED
#define NT2_BESSEL_FUNCTIONS_Y0_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup bessel
 * \defgroup bessel_y0 y0
 *
 * \par Description
 * Bessel function of the second kind of order 0.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/y0.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::y0_(A0)>::type
 *     y0(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of y0
 *
 * \return a value of the same type as the parameter
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag y0_ of functor y0
     *        in namespace nt2::tag for toolbox bessel
    **/
    struct y0_ : ext::elementwise_<y0_> { typedef ext::elementwise_<y0_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::y0_, y0, 1)
}

#endif

// modified by jt the 25/12/2010
