//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_DETAILS_FULL_QR_SOLVE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_DETAILS_FULL_QR_SOLVE_HPP_INCLUDED

#include <nt2/linalg/details/lapack/gelsy.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/expand.hpp>
#include <nt2/sdk/error/warning.hpp>
namespace nt2 { namespace details
{
  //============================================================================
  // full_qr_solve actual functor
  //============================================================================
  template<class A> struct full_qr_solve_result
  {
    typedef typename meta::strip<A>::type                          strip_t;
    typedef typename strip_t::value_type                            type_t;
    typedef typename strip_t::index_type                           index_t;
    typedef typename meta::as_real<type_t>::type                   btype_t;
    typedef nt2::container::table<type_t,nt2::_2D>                  ftab_t;
    typedef nt2::container::table<btype_t,nt2::_2D>                fbtab_t;
    typedef nt2::container::table<nt2_la_int,nt2::_2D>             fitab_t;
    typedef nt2::container::table<type_t,index_t>                    tab_t;
    typedef nt2::container::table<btype_t,index_t>                  btab_t;
    typedef nt2::container::table<nt2_la_int,index_t>               itab_t;
    typedef A                                            data_t;

    ////////////////////////////////////////////////////////////////////////////
    // General QR Solver
    //  A is            N x M
    //  B is            N x nrhs
    ////////////////////////////////////////////////////////////////////////////
    template < class Input, class B >
    full_qr_solve_result(Input& a, const B& b, const char &/*trans*/, const btype_t& rcond = btype_t(0))
      : a_(a)
      , lda_(a_.leading_size())
      , ldb_(b.leading_size())
      , m_(height(a))
      , n_(width(a))
      , nrhs_(width(b))
      , x_(nt2::expand(b, nt2::max(n_, m_), nrhs_))
      , jpvt_(nt2::zeros(n_, 1, nt2::meta::as_<nt2_la_int>()))
    {
      nt2_la_int ldx  = x_.leading_size();
      nt2::details::gelsy (&m_, &n_, &nrhs_, a_.raw(), &lda_,
                           x_.raw(), &ldx, jpvt_.raw(), &rcond,
                           &rank_, &info_);
      //      NT2_WARNING(info_ <= 0, "Warning: Matrix is singular to working precision.");
    }

    const fitab_t& ipiv()      const { return jpvt_; }
    size_t  rank()             const { return rank_; }
    nt2_la_int status()        const { return info_; }
    typedef typename  meta::call < tag::expand_(tab_t, nt2_la_int, nt2_la_int)>::type  x_result;
    x_result  x()         const
    {
      return nt2::expand(x_, n_, nrhs_);
    }
  private:
    data_t                a_;
    nt2_la_int          lda_;
    nt2_la_int          ldb_;
    nt2_la_int            m_;
    nt2_la_int            n_;
    nt2_la_int         nrhs_;
    tab_t                 x_;
    fitab_t            jpvt_;
    nt2_la_int         info_;
    nt2_la_int         rank_;
  };
} }


#endif
