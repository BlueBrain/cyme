//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_FAST_FREXP_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_FAST_FREXP_HPP_INCLUDED
#include <boost/simd/ieee/functions/fast_frexp.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/functions/simd/shr.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>
#include <boost/simd/include/functions/simd/bitwise_andnot.hpp>
#include <boost/simd/include/constants/maxexponent.hpp>
#include <boost/simd/include/constants/nbmantissabits.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::fast_frexp_
                                      , tag::cpu_
                                      , (A0)(A1)(X)
                                      , ( boost::is_same
                                          < typename  dispatch::meta
                                                      ::as_integer<A0>::type
                                          , A1
                                          >
                                        )
                                      , ((simd_< floating_<A0>, X>))
                                        ((simd_< floating_<A0>, X>))
                                        ((simd_< integer_<A1>, X>))
                                      )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A0 & r0,A1 & r1) const
    {
      typedef typename dispatch::meta::as_integer<A0, signed>::type int_type;
      typedef typename meta::scalar_of<int_type>::type              sint_type;
      typedef typename meta::scalar_of<A0>::type                    s_type;

      const sint_type me = Maxexponent<s_type>()-1;
      const sint_type nmb= Nbmantissabits<s_type>();
      const int_type vn1 = boost::simd::splat<int_type>((2*me+3)<<nmb);
      const sint_type n2 = me<<nmb;

      r1 = b_and(vn1, a0);
      r0 = b_andnot(a0, vn1);
      r1 = shri(r1,nmb) - splat<int_type>(me);
      r0 = b_or(r0,splat<int_type>(n2));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::fast_frexp_, tag::cpu_
                                      , (A0)(A1)(X)
                                      , ( boost::is_same
                                          < typename  dispatch::meta
                                                      ::as_integer<A0>::type
                                          , A1
                                          >
                                        )
                                      , ((simd_< floating_<A0>, X>))
                                        ((simd_< integer_<A1>, X>))
                                      )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE A0 operator()(A0 const& a0,A1 & a2) const
    {
      A0 a1;
      boost::simd::fast_frexp(a0, a1, a2);
      return a1;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::fast_frexp_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<arithmetic_<A0>,X>))
                                    )
  {
    typedef typename dispatch::meta::as_integer<A0, signed>::type exponent;
    typedef std::pair<A0,exponent>                                result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      A0 first;
      exponent second;
      boost::simd::fast_frexp(a0, first, second);
      return result_type(first, second);
    }
  };
} } }
#endif
