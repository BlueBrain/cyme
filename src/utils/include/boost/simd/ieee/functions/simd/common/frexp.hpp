//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_FREXP_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_FREXP_HPP_INCLUDED

#include <boost/simd/ieee/functions/frexp.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/bitwise_and.hpp>
#include <boost/simd/include/functions/simd/bitwise_or.hpp>
#include <boost/simd/include/functions/simd/bitwise_notand.hpp>
#include <boost/simd/include/functions/simd/logical_notand.hpp>
#include <boost/simd/include/functions/simd/shr.hpp>
#include <boost/simd/include/functions/simd/is_greater.hpp>
#include <boost/simd/include/functions/simd/seladd.hpp>
#include <boost/simd/include/functions/simd/is_nez.hpp>
#include <boost/simd/include/functions/simd/if_else_zero.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>
#include <boost/simd/include/functions/simd/splat.hpp>
#include <boost/simd/include/constants/maxexponent.hpp>
#include <boost/simd/include/constants/nbmantissabits.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::frexp_
                                      , tag::cpu_, (A0)(A1)(A2)(X)
                                      , ( boost::mpl::and_
                                          < boost::is_same<A0,A1>
                                          , boost::is_same
                                            < typename dispatch::meta
                                                        ::as_integer<A0>::type
                                            , A2
                                            >
                                          >
                                        )
                                      , ((simd_< floating_<A0>, X>))
                                        ((simd_< floating_<A1>, X>))
                                        ((simd_< integer_<A2>, X>))
                                      )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A1 & r0,A2 & r1) const
    {
      typedef typename meta::as_logical<A0>::type bA0;
      typedef typename dispatch::meta::as_integer<A0, signed>::type      int_type;
      typedef typename meta::as_logical<int_type>::type                 bint_type;
      typedef typename meta::scalar_of<int_type>::type                  sint_type;
      typedef typename meta::scalar_of<A0>::type                           s_type;

      const sint_type me = Maxexponent<s_type>()-1;
      const sint_type nmb= Nbmantissabits<s_type>();
      const sint_type n1 = ((2*me+3)<<nmb);
      const sint_type n2 = me<<nmb;
      const int_type vme = splat<int_type>(me);

      A0 ci   = simd::bitwise_cast<A0>(splat<int_type>(n1));

          r1  = simd::bitwise_cast<int_type>(b_and(ci, a0));  // extract exponent
      A0  x   = b_notand(ci, a0);                             // clear exponent in a0
          r1  = sub(shri(r1,nmb), vme);                       // compute exponent
          r0  = b_or(x,splat<int_type>(n2));                  // insert exponent+1 in x

      bA0       test0 = is_nez(a0);
      bint_type test1 = gt(r1,Maxexponent<A0>());

      r1 = if_else_zero(logical_notand(test1, test0), r1);
      r0 = if_else_zero(test0, seladd(test1,r0,a0));
    }
  };
} } }

#endif
