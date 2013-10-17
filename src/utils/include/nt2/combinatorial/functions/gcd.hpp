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
#ifndef NT2_COMBINATORIAL_FUNCTIONS_GCD_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_GCD_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup combinatorial
 * \defgroup combinatorial_gcd gcd
 *
 * \par Description
 * greatest common divisor
 * \par
 * If parameters are floating point and not flint,
 * nan is returned.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/gcd.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::gcd_(A0,A0)>::type
 *     gcd(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of gcd
 * \param a1 the second parameter of gcd
 *
 * \return a value of the common type of the parameters
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag gcd_ of functor gcd
     *        in namespace nt2::tag for toolbox combinatorial
    **/
    struct gcd_ : ext::elementwise_<gcd_> { typedef ext::elementwise_<gcd_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::gcd_, gcd, 2)
}

#endif

// modified by jt the 25/12/2010
