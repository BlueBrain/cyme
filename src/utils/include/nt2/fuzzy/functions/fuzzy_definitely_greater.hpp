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
#ifndef NT2_FUZZY_FUNCTIONS_FUZZY_DEFINITELY_GREATER_HPP_INCLUDED
#define NT2_FUZZY_FUNCTIONS_FUZZY_DEFINITELY_GREATER_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup fuzzy
 * \defgroup fuzzy_fuzzy_definitely_greater fuzzy_definitely_greater
 *
 * \par Description
 * \f$a_0 \gt a_1+a_2*\max(|a_0|,|a1|)\f$
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/fuzzy_definitely_greater.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::fuzzy_definitely_greater_(A0,A0,A0)>::type
 *     fuzzy_definitely_greater(const A0 & a0,const A0 & a1,const A0 & a2);
 * }
 * \endcode
 *
 * \param a0 the first parameter of fuzzy_definitely_greater
 * \param a1 the second parameter of fuzzy_definitely_greater
 * \param a2 the third parameter of fuzzy_definitely_greater
 *
 * \return a value of the common type of the parameters
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 * This is a predicate operation. Such operations return bool in scalar mode,
 * but not in SIMD mode.
 * \par
 * The return type in SIMD mode is the common type of the parameters and is
 * a 'signed boolean' type. This means that in this case True has all its bits
 * sets to one. This is to facilitate masking operations. You are invited to
 * consult the rationale.
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag fuzzy_definitely_greater_ of functor fuzzy_definitely_greater
     *        in namespace nt2::tag for toolbox fuzzy
    **/
    struct fuzzy_definitely_greater_ : ext::elementwise_<fuzzy_definitely_greater_> { typedef ext::elementwise_<fuzzy_definitely_greater_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::fuzzy_definitely_greater_, fuzzy_definitely_greater, 3)
}

#endif

// modified by jt the 25/12/2010
