//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ELLIPTIC_FUNCTIONS_SCALAR_ELLINT_1_HPP_INCLUDED
#define NT2_ELLIPTIC_FUNCTIONS_SCALAR_ELLINT_1_HPP_INCLUDED
#include <nt2/elliptic/functions/ellint_1.hpp>
#include <boost/math/special_functions.hpp>
#include <nt2/trigonometric/constants.hpp>
#include <nt2/include/functions/scalar/is_eqz.hpp>
#include <nt2/sdk/error/policies.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/pio_2.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ellint_1_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {
    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      result_type x = a0;
      if (x > nt2::One<result_type>()) return nt2::Nan<result_type>();
      if (x == nt2::One<result_type>())  return nt2::Inf<result_type>();
      if (nt2::is_eqz(x))      return nt2::Pio_2<result_type>();
      return boost::math::ellint_1(x, nt2_policy());
    }
  };
} }


#endif
