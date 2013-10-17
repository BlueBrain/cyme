//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_DETAILS_GENERATOR_TERMINAL_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_DETAILS_GENERATOR_TERMINAL_HPP_INCLUDED

#include <nt2/core/container/dsl/generator.hpp>
#include <nt2/dsl/functions/terminal.hpp>
#include <boost/proto/traits.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace nt2 { namespace details
{
  //============================================================================
  // Generator case for terminals
  //============================================================================
  template<class Domain, class Expr>
  struct generator<nt2::tag::terminal_, Domain, 0, Expr>
  {
    typedef typename boost::remove_const<Expr>::type expr;

    typedef container::expression< expr
                      , typename boost::proto::result_of::value<expr>::type
                      > result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return result_type(e);
    }
  };

  //============================================================================
  // Generator case for nullary expressions
  //============================================================================
  template<class Tag, class Domain, class Expr>
  struct generator<Tag, Domain, 0, Expr>
  {
    typedef container::expression
            < typename boost::remove_const<Expr>::type
            , typename meta::call < Tag ( typename boost::proto::result_of
                                                      ::value<Expr>::type
                                        )
                                  >::type
            > result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return result_type(e);
    }
  };
} }

#endif

