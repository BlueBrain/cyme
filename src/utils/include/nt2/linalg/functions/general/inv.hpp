//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GENERAL_INV_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GENERAL_INV_HPP_INCLUDED

#include <nt2/linalg/functions/inv.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/lu.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(A1)(N)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_ < A1, nt2::tag::inv_
                                      , N , nt2::container::domain
                                      >
                              ))
                            )
  {
    typedef A0&                                                   result_type;

    result_type operator()(A0& out, const A1& in) const
    {
      out.resize(in.extent());

      bool warn = choice(in, N());

      out = boost::proto::child_c<0>(in);
      out = nt2::details::lu_result<A0>(out).inv(warn);

      return out;
    }

    private :
    static bool choice(const A1&, boost::mpl::long_<1> const &)
    {
      return true;
    }

    static bool choice(const A1& in, boost::mpl::long_<2> const &)
    {
      return boost::proto::child_c<1>(in);
    }
  };
} }

#endif
