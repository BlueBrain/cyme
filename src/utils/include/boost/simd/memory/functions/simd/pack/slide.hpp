//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_PACK_SLIDE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_PACK_SLIDE_HPP_INCLUDED

#include <boost/simd/memory/functions/slide.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/simd/include/functions/evaluate.hpp>
#include <boost/simd/sdk/simd/pack/forward.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/dispatch/meta/mpl.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/and.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - slide between scalar values
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::slide_
                                      , tag::cpu_
                                      , (A0)(A1)(N)
                                      // , ((
                                      //      boost::is_same
                                      //       < typename meta::scalar_of<A0>::type
                                      //       , typename meta::scalar_of<A1>::type
                                      //       >
                                      //     // , boost::mpl::bool_
                                      //     //   <   typename A0::static_size
                                      //     //   ==  typename A1::static_size
                                      //     //   >

                                      //   ))
                                      , ((ast_<A0, boost::simd::domain>))
                                        ((ast_<A1, boost::simd::domain>))
                                        (mpl_integral_< scalar_< integer_<N> > >)
                                      )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A1 const& a1, N const&) const
    {
      return slide<N::value>( evaluate(a0), evaluate(a1) );
    }
  };
} } }

#endif
