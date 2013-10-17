//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_NORM_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_NORM_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <nt2/sdk/memory/container.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_norm norm
 *
 * \par Description
 * Elementary Least square
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/norm.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \param a the matrix or vector expression a
 *
 * \param type of norm required
 *
 * \par Notes
 *   Call the dedicated lapack routines available on the target.
 * \par
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag norm_ of functor norm
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct norm_ :  tag::formal_ { typedef tag::formal_ parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::norm_, norm, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::norm_, norm, 1)

}

#endif

