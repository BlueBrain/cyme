//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_EXPONENT_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_EXPONENT_HPP_INCLUDED

#include <boost/simd/ieee/functions/exponent.hpp>
#include <boost/simd/include/functions/scalar/is_invalid.hpp>
#include <boost/simd/include/functions/scalar/shr.hpp>
#include <boost/simd/include/functions/scalar/exponentbits.hpp>
#include <boost/simd/include/functions/scalar/is_eqz.hpp>
#include <boost/simd/include/functions/scalar/if_else_zero.hpp>
#include <boost/simd/include/constants/nbmantissabits.hpp>
#include <boost/simd/include/constants/maxexponent.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/sdk/math.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::exponent_, tag::cpu_
                            , (A0)
                            , (scalar_< integer_<A0> >)
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, signed>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0) const
    {
      return Zero<result_type>();
    }
  };

#ifdef BOOST_SIMD_HAS_ILOGB
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::exponent_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, signed>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      if (is_invalid(a0) || is_eqz(a0)) return Zero<result_type>();
      return ::ilogb(a0);
    }
  };
#endif

#ifdef BOOST_SIMD_HAS_ILOGBF
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::exponent_, tag::cpu_
                            , (A0)
                            , (scalar_< single_<A0> >)
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, signed>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      if (is_invalid(a0) || is_eqz(a0)) return Zero<result_type>();
      return ::ilogbf(a0);
    }
  };
#endif

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::exponent_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, signed>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      if (is_invalid(a0) || is_eqz(a0)) return Zero<result_type>();
      const int nmb = int(Nbmantissabits<A0>());
      const result_type x = shri(exponentbits(a0), nmb);
      return x-if_else_zero(a0, Maxexponent<A0>());
    }
  };
} } }


#endif
