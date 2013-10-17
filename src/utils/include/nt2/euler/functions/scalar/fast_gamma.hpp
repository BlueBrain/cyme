//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SCALAR_FAST_GAMMA_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SCALAR_FAST_GAMMA_HPP_INCLUDED
#include <nt2/euler/functions/fast_gamma.hpp>
#include <nt2/include/functions/scalar/sinpi.hpp>
#include <nt2/include/functions/scalar/polevl.hpp>
#include <nt2/include/functions/scalar/stirling.hpp>
#include <nt2/include/functions/scalar/is_even.hpp>
#include <nt2/include/functions/scalar/is_nan.hpp>
#include <nt2/include/functions/scalar/is_eqz.hpp>
#include <nt2/include/functions/scalar/is_ltz.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/euler.hpp>
#include <nt2/include/constants/half.hpp>
#include <boost/simd/sdk/config.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fast_gamma_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {
    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::fast_gamma(result_type(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fast_gamma_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      static boost::array<A0, 7> P = {{
          A0(1.60119522476751861407E-4),
          A0(1.19135147006586384913E-3),
          A0(1.04213797561761569935E-2),
          A0(4.76367800457137231464E-2),
          A0(2.07448227648435975150E-1),
          A0(4.94214826801497100753E-1),
          A0(9.99999999999999996796E-1)
        }};
      static boost::array<A0, 8>  Q = {{
          A0(-2.31581873324120129819E-5),
          A0( 5.39605580493303397842E-4),
          A0(-4.45641913851797240494E-3),
          A0(1.18139785222060435552E-2),
          A0(3.58236398605498653373E-2),
          A0(-2.34591795718243348568E-1),
          A0(7.14304917030273074085E-2),
          A0(1.00000000000000000320E0)
        }};
      A0 x = a0, p, z;
      int32_t sgngam = 1;
#ifndef BOOST_SIMD_NO_INVALIDS
      if( nt2::is_nan(x) || (x == nt2::Minf<A0>()) ) return nt2::Nan<A0>();
      if (x == nt2::Inf<A0>()) return x;
#endif
      A0 q = nt2::abs(x);
      if( q > static_cast<A0>(33.0) )
      {
        if( nt2::is_ltz(x))
        {
          if ((p = nt2::floor(q)) == q) return nt2::Nan<A0>();
          int32_t i = (int32_t)p;
          if( nt2::is_even(i) ) sgngam = -1;
          z = q - p;
          if( z > nt2::Half<A0>() )
          {
            p += nt2::One<A0>();
            z = q - p;
          }
          z = q*nt2::sinpi(z);
          if( nt2::is_eqz(z) ) return nt2::Nan<A0>()*sgngam;
          z = nt2::abs(z);
          z = nt2::Pi<A0>()/(z * nt2::stirling(q) );
        }
        else
        {
          z = nt2::stirling(x);
        }
        return( sgngam * z );
      }

      z = nt2::One<A0>();
      while( x >= nt2::Three<A0>() )
      {
        x -= nt2::One<A0>();
        z *= x;
      }

      while( nt2::is_ltz(x) )
      {
        if( x > static_cast<A0>(-1.E-9) )
        {
          return z / ((nt2::One<A0>() + nt2::Euler<A0>() * x) * x);
        }
        z /= x;
        x += nt2::One<A0>();
      }

      while( x < nt2::Two<A0>() )
      {
        if( nt2::is_eqz(x)) return nt2::Nan<A0>();
        if( x < static_cast<A0>(1.e-9) )
        {
          return z / ((nt2::One<A0>() + nt2::Euler<A0>() * x) * x);
        }
        z /= x;
        x +=  nt2::One<A0>();
      }

      if( x == nt2::Two<A0>() ) return(z);

      x -= nt2::Two<A0>();
      p = nt2::polevl(x,P);
      q = nt2::polevl(x,Q);
      return z*p/q;
    }
  };
} }


#endif
