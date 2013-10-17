//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SVD_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SVD_HPP_INCLUDED

#include <nt2/options.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/linalg/functions/details/svd.hpp>

namespace nt2
{
  namespace tag
  {
    namespace factorization
    {
      struct svd_ : ext::unspecified_<factorization::svd_>
      {
        typedef ext::unspecified_<factorization::svd_> parent;
      };
    }

    struct svd_ : ext::unspecified_<svd_>
    {
       typedef ext::tieable_<svd_>  parent;
    };
  }

  /**
   * @brief Perform Svd factorization
   *
   * For any given matrix expression, performs a Svd factorization of
   * said matrix using the specified output layout for the Svdevsky method.
   *
   * Contrary to the nt2::factorization::svd function which performs a partial evaluation of
   * said decomposition, nt2::svd returns a result similar to the Matlab interface,
   * making it useful for Matlab like usage.
   *
   * @param  xpr  Matrix expression to factorize
   *
   * @return A tuple-like type containing the factorized matrix and an indicator
   * of the success of the factorization
   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::svd_, svd, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::svd_, svd, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::svd_, svd, 3)

  namespace factorization
  {
    /**
     * @brief Initialize a Svd factorization
     *
     * For any given matrix expression, initialize a Svd factorization of
     * said matrix using the specified output layout for the Svd method
     * and return a precomputed factorization object.
     *
     * Contrary to the svd function which performs such a factorization and
     * return a Matlab like output, factorization::svd returns an object
     * containing the initial evaluation of said factorization. This object can
     * then be used to fasten other algorithms implementation.
     *
     * @param  xpr  Matrix expression to factorize
     * @param  econ Notify if svd should return an economy size decomposition
     *
     * @return A unspecified type containing the precomputed elements of the
     * Svd factorization.
     **/
    NT2_FUNCTION_IMPLEMENTATION(tag::factorization::svd_, svd, 3)
    NT2_FUNCTION_IMPLEMENTATION_SELF(tag::factorization::svd_, svd, 4)
  }
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::svd_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::svd_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
