//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_MANTISSA_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_MANTISSA_HPP_INCLUDED

#include <boost/simd/ieee/functions/mantissa.hpp>
#include <boost/simd/include/functions/simd/is_eqz.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/logical_or.hpp>
#include <boost/simd/include/functions/simd/bitwise_or.hpp>
#include <boost/simd/include/functions/simd/bitwise_and.hpp>
#include <boost/simd/include/functions/simd/is_invalid.hpp>
#include <boost/simd/include/functions/simd/splat.hpp>
#include <boost/simd/include/functions/simd/splat.hpp>
#include <boost/simd/include/constants/nbmantissabits.hpp>
#include <boost/simd/include/constants/maxexponent.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::mantissa_, tag::cpu_,
                                     (A0)(X),
                                     ((simd_<integer_<A0>,X>))
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return a0;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::mantissa_, tag::cpu_,
                                     (A0)(X),
                                     ((simd_<floating_<A0>,X>))
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename dispatch::meta::as_integer<A0, unsigned>::type  int_type;
      typedef typename meta::scalar_of<int_type>::type      sint_type;
      typedef typename meta::scalar_of<A0>::type               s_type;
      const sint_type n1 = ((2*Maxexponent<s_type>()+1)<<Nbmantissabits<s_type>());
      const sint_type n2 = (sizeof(sint_type)-2);
      const int_type  mask0 = (splat<int_type>((n1<<2)>>2));
      const int_type  mask1 = (splat<int_type>((~n1)|n2));
      return select(logical_or(is_invalid(a0),is_eqz(a0)),a0,b_or(b_and(a0,mask1),mask0));
    }
  };
} } }
#endif
