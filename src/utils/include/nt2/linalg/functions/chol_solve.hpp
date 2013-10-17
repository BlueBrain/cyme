//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_CHOL_SOLVE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_CHOL_SOLVE_HPP_INCLUDED

#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/linalg/functions/details/chol_solve.hpp>

//  chol_solve solve linear system a*x=b.
//     x = chol_solve(a,b) solves the linear system a*x=b using
//     lu factorization with partial pivoting. a must be square,

namespace nt2
{
  namespace tag
  {
    namespace solvers
    {
      struct chol_solve_ : ext::unspecified_<solvers::chol_solve_>
      {
        typedef ext::unspecified_<solvers::chol_solve_> parent;
      };
    }

    struct chol_solve_ :  ext::tieable_<chol_solve_>
    {
      typedef ext::tieable_<chol_solve_>  parent;
    };
  }

  /**
   * @brief Perform Chol_solve factorization
   *
   * For any given matrix expression a, and right hand side b performs
   * Chol_solve resolution of
   * said system using the specified output layout for the Chol_solve method.
   *
   * Contrary to the nt2::factorization::chol_solve function which
   * performs a partial evaluation of
   * said resolution, nt2::chol_solve returns a result similar to the Matlab interface,
   * making it useful for Matlab like usage.
   *
   * @param  xpr  Matrix expression
   * @param  b    rigt hand side expression
   *
   * @return A tuple-like type containing the solution and optionnaly the rcond number of the system
   * of the success of the factorization
   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::chol_solve_, chol_solve, 3)

  namespace solvers
  {
    /**
     * @brief Initialize a Chol_solve factorization
     *
     * For any given matrix expression, initialize a Chol_solve factorization of
     * said matrix using the specified output layout for the Chol_solve method
     * and return a precomputed factorization object.
     *
     * Contrary to the chol_solve function which performs such a factorization and
     * return a Matlab like output, factorization::chol_solve returns an object
     * containing the initial evaluation of said factorization. This object can
     * then be used to fasten other algorithms implementation.
     *
     * @param  xpr  Matrix expression to factorize
     * @param  ip   Notify if chol_solve should be performed in-place over xpr
     *
     * @return A unspecified type containing the precomputed elements of the
     * Chol_solve factorization.
     **/
    NT2_FUNCTION_IMPLEMENTATION(tag::solvers::chol_solve_, chol_solve, 3)
    NT2_FUNCTION_IMPLEMENTATION(tag::solvers::chol_solve_, chol_solve, 4)
    NT2_FUNCTION_IMPLEMENTATION_TPL(tag::solvers::chol_solve_, chol_solve,(A0&)(A1&)(const A1&), 3)
    NT2_FUNCTION_IMPLEMENTATION_TPL(tag::solvers::chol_solve_, chol_solve,(A0&)(A1&)(const A1&)(const A2&), 4)
  }
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::chol_solve_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::chol_solve_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
