//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_FREQSPACE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_FREQSPACE_HPP_INCLUDED

#include <nt2/core/functions/freqspace.hpp>
#include <nt2/include/functions/freqspace1.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/scalar/floor.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/options.hpp>
#include <boost/mpl/bool.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // This version of freqspace is called whenever a tie(...) = freqspace(...) is
  // captured before assign is resolved. As a tieable function, freqspace
  // retrieves rhs/lhs pair as inputs
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::freqspace_, tag::cpu_
                              , (A0)(N0)(A1)(N1)
                              , ((node_ < A0, nt2::tag::freqspace_
                                        , N0, nt2::container::domain
                                        >
                                ))
                                ((node_ < A1, nt2::tag::tie_
                                        , N1, nt2::container::domain
                                        >
                                ))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A0&,0>::type       child0;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type      child10;
    typedef typename boost::proto::result_of::child_c<A0&,1>::type       child1;
    typedef typename boost::proto::result_of::value<child1>::type        type_t;
    typedef typename meta::is_scalar<type_t>::type                     choice_t;

    typedef typename boost::dispatch::meta::
            terminal_of< typename boost::dispatch::meta::
                         semantic_of<child0>::type
                       >::type                                            in0_t;
    typedef typename boost::dispatch::meta::
            terminal_of< typename boost::dispatch::meta::
                         semantic_of<child10>::type
                       >::type                                            out_t;

    typedef typename out_t::value_type                                  value_t;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      int n = 0, m = 0;
      bool whole =  false;
      bool meshgrid = false;
      getmn(a0, m, n, whole, meshgrid, N0(), N1() );
      compute(a1, m, n, whole, meshgrid, N1());
    }

    private:
    BOOST_FORCEINLINE void compute( A1 & a1, int m, int, bool whole
                                  , bool, boost::mpl::long_<1> const&
                                  ) const
    {
      if (whole)
        boost::proto
             ::child_c<0>(a1) = freqspace1(m,nt2::whole_,meta::as_<value_t>());
      else
        boost::proto::child_c<0>(a1) = freqspace1(m, meta::as_<value_t>());
    }

    void compute( A1 & a1, int m, int n, bool
                , bool /*meshgrid*/, boost::mpl::long_<2> const&
                ) const
    {
      value_t hvm = m*nt2::Half<value_t>();
      value_t hvn = n*nt2::Half<value_t>();
      value_t hm = nt2::rec(hvm);
      value_t hn = nt2::rec(hvn);
      value_t lm = -nt2::floor(hvm)*hm;
      value_t ln = -nt2::floor(hvn)*hn;

      // TODO: implement support for meshgrid option
      //if (meshgrid)
      // {
      boost::proto::child_c<0>(a1) = nt2::_(ln, hn, value_t(1)-value_t(2)/n);
      boost::proto::child_c<1>(a1) = nt2::_(lm, hm, value_t(1)-value_t(1)/m);
      // }
      // else
      // {
      //   boost::proto::child_c<0>(a1) = ??;
      //   boost::proto::child_c<1>(a1) = ??;
      // }
    }

    BOOST_FORCEINLINE  //[f]       = freqspace(n)
    void getmn(A0 const &a0, int &m,  int& n, bool&, bool&,
               boost::mpl::long_<3> const &,//number of inputs
               boost::mpl::long_<1> const &//number of outputs
               ) const
    {
      m = int(boost::proto::value(boost::proto::child_c<1>(a0)));
      n = 0;
    }

    BOOST_FORCEINLINE  //[f1, f2]       = freqspace(n)
    void getmn(A0 const &a0, int &m,  int& n, bool&, bool&
              , boost::mpl::long_<3> const &    //number of inputs
              , boost::mpl::long_<2> const &
              ) const//number of outputs
    {
      m = getval(boost::proto::value(boost::proto::child_c<1>(a0)),0,choice_t());
      n = getval(boost::proto::value(boost::proto::child_c<1>(a0)),1,choice_t());
    }

    template < class T > static int getval(const T & a0, int,
                                           const boost::mpl::bool_<true> &)
      { return a0; }

    template < class T > static int getval(const T & a0, int i,
                                           const boost::mpl::bool_<false>  &)
      {return a0[i]; }

    BOOST_FORCEINLINE //[f]       = freqspace(n, whole_)
      void getmn( A0 const &a0, int &m, int& n, bool &whole, bool&
                , boost::mpl::long_<4> const &  //number of inputs
                , boost::mpl::long_<1> const &  //number of outputs
                ) const
    {
      m = int(boost::proto::value(boost::proto::child_c<1>(a0)));
      n = 0;
      whole =  true;
    }

    BOOST_FORCEINLINE //[f,g]       = freqspace(n, whole_)
    void getmn( A0 const &a0, int &m,  int& n, bool &whole, bool&
              , boost::mpl::long_<4> const &  //number of inputs
              , boost::mpl::long_<2> const &  //number of outputs
              ) const
    {
      m = int(boost::proto::value(boost::proto::child_c<1>(a0)));
      n = 0;
      whole =  true;
    }

    template < class Dummy >
    BOOST_FORCEINLINE // [f1, f2]  = freqspace([m, n])
    void getmn( A0 const &a0, int &m,  int& n, bool&, bool&
              , boost::mpl::long_<3> const &  //number of inputs
              , boost::mpl::long_<2> const &  //number of outputs
              , Dummy()
              ) const
    {
      m = getval(boost::proto::value(boost::proto::child_c<1>(a0)),0,choice_t());
      n = getval(boost::proto::value(boost::proto::child_c<1>(a0)),1,choice_t());
    }

    template < class Dummy >
    BOOST_FORCEINLINE // [f1, f2]  = freqspace([m, n], meshgrid_)
    void getmn( A0 const &a0, int &m,  int& n, bool&, bool& meshgrid
              , boost::mpl::long_<4> const &  //number of inputs
              , boost::mpl::long_<2> const &  //number of outputs
              , Dummy()
              ) const
    {
      m = getval(boost::proto::value(boost::proto::child_c<1>(a0)),0,choice_t());
      n = getval(boost::proto::value(boost::proto::child_c<1>(a0)),1,choice_t());
      meshgrid = true;
    }
  };
} }

#endif
