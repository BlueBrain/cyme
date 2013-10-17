//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_SIMD_COMMON_SINHC_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_SIMD_COMMON_SINHC_HPP_INCLUDED

#include <nt2/hyperbolic/functions/sinhc.hpp>
#include <nt2/include/functions/simd/sinh.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#include <nt2/include/functions/simd/is_greater_equal.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/constants/oneo_6.hpp>
#include <nt2/include/constants/moneo_6.hpp>
#include <nt2/include/constants/oneo_120.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/fourthrooteps.hpp>
#include <nt2/sdk/meta/as_floating.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sinhc_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {

    typedef typename meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::sinhc(tofloat(a0));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sinhc_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                            )
  {

    typedef typename meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      A0 a = nt2::abs(a0);
      A0 r1 = sel(eq(a, Inf<A0>()), a, sinh(a)*rec(a));
      A0 a2 = sqr(a);
      A0 r2 = oneplus(a2*fma(a2, Oneo_120<A0>(), Oneo_6<A0>()));
      return sel(ge(a,Four<A0>()*Four<A0>()*Fourthrooteps<A0>()), r1, r2);
    }
  };
} }


#endif
