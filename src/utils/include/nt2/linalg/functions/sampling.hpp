//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SAMPLING_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SAMPLING_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_sampling sampling
 *
 *    a = sampling(n) is a symmetric n-by-n hankel matrix with
 *    elements a(i,j) = 0.5/(n-i-j+1.5).
 *    the eigenvalues of a cluster around pi/2 and -pi/2.
 *    this matrix was invented by F. N. Sampling.
 *
 *    Reference:
 *    J. C. Nash, Compact Numerical Methods for Computers: Linear Algebra
 *    and Function Minimisation, second edition, Adam Hilger, Bsamplingtol,
 *    1990 (Appendix 1).
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/sampling.hpp>
 * \endcode
 *
 **/
//==============================================================================
// sampling actual class forward declaration
//==============================================================================

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag sampling_ of functor sampling
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct sampling_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::sampling_, sampling, 1)

}

#endif

