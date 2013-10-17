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
#ifndef NT2_STATISTICS_FUNCTIONS_UNIFRND_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_UNIFRND_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup statistics
 * \defgroup statistics_exp2 exp2
 *
 * \par Description
 * uniform pseudo random numbers generator
 * \par
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/unifrnd.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::unifrnd_(A0)>::type
 *     unifrnd(const A0 & a, const A1 & b, ... dimensions);
 * }
 * \endcode
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag unifrnd_ of functor unifrnd
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct unifrnd_ : boost::dispatch::tag::formal_ { typedef boost::dispatch::tag::formal_ parent; };
  }

 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::unifrnd_, unifrnd, 2)
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::unifrnd_, unifrnd, 3)
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::unifrnd_, unifrnd, 4)
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::unifrnd_, unifrnd, 5)
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::unifrnd_, unifrnd, 6)
 NT2_FUNCTION_IMPLEMENTATION(nt2::tag::unifrnd_, unifrnd, 7)
}

#endif
