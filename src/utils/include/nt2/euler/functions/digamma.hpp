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
#ifndef NT2_EULER_FUNCTIONS_DIGAMMA_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_DIGAMMA_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup euler
 * \defgroup euler_digamma digamma
 *
 * \par Description
 * digamma function\par Formula
 * \f[\Psi(a_0) = \frac{\Gamma^\prime(a_0)}{\Gamma(a_0}\f]
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/digamma.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::digamma_(A0)>::type
 *     digamma(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of digamma
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
     * \brief Define the tag digamma_ of functor digamma
     *        in namespace nt2::tag for toolbox euler
    **/
    struct digamma_ : ext::elementwise_<digamma_> { typedef ext::elementwise_<digamma_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::digamma_, digamma, 1)
}

#endif

// modified by jt the 25/12/2010
