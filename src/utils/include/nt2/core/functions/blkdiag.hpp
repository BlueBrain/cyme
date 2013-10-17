//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_BLKDIAG_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_BLKDIAG_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the blkdiag function
**/

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the blkdiag functor
    **/
    struct  blkdiag_ : ext::elementwise_<blkdiag_>
    {
      typedef ext::elementwise_<blkdiag_> parent;
    };
  }

  /*!
    @brief Build a block diabgonal matrix

    Build a block diagonal matrix by concatenating two matrix along their
    diagonal.

    @param a0 First matrix to concatenate
    @param a1 Second matrix to concatenate
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::blkdiag_, blkdiag, 2)

  /// INTERNAL ONLY
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::blkdiag_, blkdiag, 1)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::blkdiag_,Domain,N,Expr>
  {
    // TODO: case for dual static of_size_
    typedef _2D result_type;

    BOOST_FORCEINLINE result_type operator ()(Expr& e) const
    {
      if( !numel(boost::proto::child_c<0>(e).extent()) )
      {
        return boost::proto::child_c<1>(e).extent();
      }
      else if( !numel(boost::proto::child_c<1>(e).extent()) )
      {
        return boost::proto::child_c<0>(e).extent();
      }
      // otherwise compute the size properly
      else
      {
        result_type sizee(boost::proto::child_c<0>(e).extent());
        sizee[0] += boost::fusion::at_c<0>(boost::proto::child_c<1>(e).extent());
        sizee[1] += boost::fusion::at_c<1>(boost::proto::child_c<1>(e).extent());

        return sizee;
      }
    }
  };

  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::blkdiag_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }

#endif
