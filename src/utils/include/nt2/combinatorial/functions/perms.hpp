//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_PERMS_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_PERMS_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functions/prod.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

/*!
 * \ingroup combinatorial
 * \defgroup combinatorial_perms perms
 *
 * \par Description
 *  m = permsn(v, k) returns the first k permutations
 * of the v elements in a table of size_t of size numel(v)Xk
 * If k is not provided k is numel(v)!
 *
 * Take care in this last case that numel(v) <= 10 to avoid exhausting memory
 * See also permsn
 **/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag perms_ of functor perms
     *        in namespace nt2::tag for toolbox combinatorial
    **/
    struct perms_ : ext::unspecified_<perms_> { typedef ext::unspecified_<perms_> parent; };
    }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::perms_, perms, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::perms_, perms, 2)
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::perms_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee;
      sizee[0] = nt2::numel(boost::proto::child_c<0>(e));

      std::size_t l = 1;
      for(std::size_t i=2;i<=sizee[0];++i) l *= i;

      sizee[1] = nt2::min(boost::proto::child_c<1>(e), l);

      return sizee;
    }
  };

  template <class Domain, class Expr, int N>
  struct value_type < tag::perms_, Domain,N,Expr>
    : meta::value_as<Expr,0>
  { };
} }

#endif
