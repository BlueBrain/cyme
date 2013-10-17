//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SCALAR_DIGAMMA_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SCALAR_DIGAMMA_HPP_INCLUDED
#include <nt2/euler/functions/digamma.hpp>
#include <boost/math/special_functions.hpp>
#include <nt2/sdk/error/policies.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::digamma_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {
    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return digamma(result_type(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::digamma_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return result_type(boost::math::digamma(a0, nt2_policy()));
    }
  };
} }


#endif
