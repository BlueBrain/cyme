//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_COLON_COLON_HPP_INCLUDED
#define NT2_CORE_CONTAINER_COLON_COLON_HPP_INCLUDED

#include <nt2/sdk/meta/as.hpp>
#include <nt2/include/functions/colon.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>

namespace nt2 { namespace container
{
  //==========================================================================
  // colon_ is an helper class that handles the _ placeholders behavior
  //==========================================================================
  struct colon_
  {
    // colon_ as a sink for tie
    template<class T> colon_ const& operator=(T const&) const { return *this; }

    // _() as []
    boost::proto::result_of::
    make_expr< nt2::tag::empty_colon_, container::domain
             , box< of_size_<0> >
             , box< meta::constant_<nt2::tag::unity_colon_, double> >
             , meta::as_<double>
             >::type
    operator()() const
    {
      return boost::proto::make_expr< nt2::tag::empty_colon_, container::domain >
            ( boxify(of_size_<0>()), boxify(meta::constant_<nt2::tag::unity_colon_, double>(1.)), meta::as_<double>() );
    }

    // colon as a:b
    template<class Begin, class End>
    typename meta::call<nt2::tag::colon_(Begin,End)>::type
    operator()(Begin b, End e) const
    {
      return nt2::colon(b,e);
    }

    // colon as a:s:b
    template<class Begin, class Step, class End>
    typename meta::call<nt2::tag::colon_(Begin,Step,End)>::type
    operator()(Begin  b, Step s, End e) const
    {
      return nt2::colon(b,s,e);
    }
  };
} }

namespace nt2
{
  //==========================================================================
  /*!
   * _ is a multi-purpose placeholder in \nt2:
   *
   *   - it acts as \matlab \c : in indexing expression
   *   - it enables \c :(b,s,e) to mimic \matlab \c b:s:e iota notation
   *   - _() is Matlab []
   *   - it acts as a sink in tie expressions
   **/
  //==========================================================================
  container::colon_ const _ = {};
}

#endif
