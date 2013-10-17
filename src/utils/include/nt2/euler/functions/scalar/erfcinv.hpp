//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SCALAR_ERFCINV_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SCALAR_ERFCINV_HPP_INCLUDED

#include <nt2/euler/functions/erfcinv.hpp>
#include <nt2/include/functions/scalar/erfinv.hpp>
#include <nt2/include/functions/scalar/oneminus.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::erfcinv_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::erfinv(nt2::oneminus(result_type(a0)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::erfcinv_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {

    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
      {
        return nt2::erfinv(nt2::oneminus(a0));
      }
  };
} }

#endif
