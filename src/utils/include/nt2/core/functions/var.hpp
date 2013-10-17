//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_VAR_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_VAR_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup core
 * \defgroup core var
 *
 * \par Description
 * Returns the var of the elements of the SIMD vector
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/var.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::var_(A0)>::type
 *     var(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of var
 *
 * \return always a scalar value
 *
 * \par Notes
 * \par
 * This is a reduction operation. As such it has no real interest outside
 * SIMD mode.
 * \par
 * Such an operation always has a scalar result which translate a property
 * of the whole SIMD vector.
 * \par
 * If usable and used in scalar mode, it reduces to the operation as acting
 * on a one element vector.
 *
**/


namespace nt2
{
  namespace tag
  {
    struct var_ : boost::dispatch::tag::formal_
    {
       typedef boost::dispatch::tag::formal_ parent;
    };
  }

  //============================================================================
  /*!
   * var of a table
   *
   * \param xpr  table
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::var_       , var, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::var_       , var, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::var_       , var, 3)
}


#endif
