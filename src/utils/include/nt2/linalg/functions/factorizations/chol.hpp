//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_FACTORIZATIONS_CHOL_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_FACTORIZATIONS_CHOL_HPP_INCLUDED

#include <nt2/linalg/functions/chol.hpp>
#include <nt2/options.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/linalg/functions/details/chol.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::factorization::chol_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_< type8_<A1> >)
                            )
  {
    typedef typename meta::strip<A0>::type                        base_t;
    typedef typename base_t::value_type                           value_t;
    typedef typename base_t::settings_type                        settings_t;
    typedef details::cholesky_result< table<value_t,settings_t> > result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& uplo) const
    {
      BOOST_ASSERT_MSG( nt2::issquare(a0)
                      , "??? Error using 'chol' : Matrix must be square."
                      );

      result_type that(uplo, a0);
      return that;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::factorization::chol_, tag::cpu_
                            , (A0)(A1)(IP)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_< type8_<A1> >)
                              (unspecified_< IP >)
                            )
  {
    typedef details::cholesky_result<A0&> result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0,
               A1 const& uplo,
               IP const&) const
    {
      BOOST_ASSERT_MSG( nt2::issquare(a0)
                      , "??? Error using 'chol' : Matrix must be square."
                      );

      result_type that(uplo, a0);
      return that;
    }
  };
} }

#endif
