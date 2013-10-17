//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_COMPLEX_GENERIC_SECD_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_COMPLEX_GENERIC_SECD_HPP_INCLUDED
#include <nt2/trigonometric/functions/secd.hpp>
#include <nt2/include/functions/cosd.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>

//secd(x+iy)=rec(cosd(x+iy)).
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::secd_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return rec(nt2::cosd(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::secd_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return rec(nt2::cosd(a0));
    }
  };
} }

#endif
