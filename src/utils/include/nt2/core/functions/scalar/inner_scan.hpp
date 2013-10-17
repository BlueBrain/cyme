//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_INNER_SCAN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_INNER_SCAN_HPP_INCLUDED

#include <nt2/core/functions/inner_scan.hpp>
#include <boost/fusion/include/pop_front.hpp>
#include <nt2/include/functions/scalar/numel.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates inner_scan
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::inner_scan_, tag::cpu_, (A0)(A1)(A2)(A3)(A4)
                            , ((ast_< A0, nt2::container::domain>))
                              ((ast_< A1, nt2::container::domain>))
                              (unspecified_<A2>)
                              (unspecified_<A3>)
                              (unspecified_<A4>)
                            )
  {
    typedef void                                                               result_type;
    typedef typename A0::value_type                                            value_type;
    typedef typename boost::remove_reference<A1>::type::extent_type            extent_type;

    BOOST_FORCEINLINE result_type operator()( A0& out, A1& in
                                            , A2 const& neutral
                                            , A3 const& bop
                                            , A4 const&
                                            ) const
    {
      extent_type ext = in.extent();
      std::size_t ibound  = boost::fusion::at_c<0>(ext);
      std::size_t obound =  nt2::numel(boost::fusion::pop_front(ext));

      for(std::size_t j = 0, k = 0; j < obound; ++j)
      {
        value_type prev = neutral(meta::as_<value_type>());
        for(std::size_t m = k+ibound; k != m; ++k)
        {
          prev = bop(prev, nt2::run(in, k, meta::as_<value_type>()));
          nt2::run(out, k, prev);
        }
      }
    }
  };

} }

#endif
