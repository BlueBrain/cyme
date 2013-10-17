//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SCALAR_COND_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SCALAR_COND_HPP_INCLUDED
#include <nt2/linalg/functions/cond.hpp>
#include <nt2/include/functions/svd.hpp>
#include <nt2/include/functions/inv.hpp>
#include <nt2/include/functions/norm.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/functions/issquare.hpp>

namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cond_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef typename A0::value_type type_t;
    typedef typename meta::as_real<type_t>::type rtype_t;
    typedef typename meta::as_floating<rtype_t>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      BOOST_ASSERT_MSG(issquare(a0), "cond for non square matrix");
      return nt2::details::svd_result<A0>(a0,'N','N').cond();
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cond_, tag::cpu_
                            , (A0)
                            , (scalar_< unspecified_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return a0 ? One<A0>() : Inf<A0>();
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cond_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (unspecified_<A1>)
                            )
  {
    typedef typename A0::value_type                   type_t;
    typedef typename meta::as_real<type_t>::type      rtype_t;
    typedef typename meta::as_floating<rtype_t>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      BOOST_ASSERT_MSG( issquare(a0)
                      , "condition number of non square matrix requested"
                      );

      if (a1 != 2 && a1 != '2')
      {
        result_type n = nt2::norm(a0, a1);
        return n ? n*nt2::norm(nt2::inv(a0), a1) : Inf<result_type>();
      }
      else
      {
        return cond(a0);
      }
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cond_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> > )
                              (unspecified_<A1>)
                            )
  {
    typedef A0 result_type;
    result_type operator()(A0 const & a0,  A1 const&)
    {
      return a0 ? One<A0>() : Inf<A0>();
    }
  };
} }

#endif
