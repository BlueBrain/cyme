//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SCALAR_CBRT_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SCALAR_CBRT_HPP_INCLUDED

#include <nt2/exponential/functions/cbrt.hpp>
#include <boost/simd/sdk/math.hpp>
#include <boost/math/special_functions/cbrt.hpp>
#include <nt2/include/functions/scalar/is_invalid.hpp>
#include <nt2/sdk/error/policies.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cbrt_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::cbrt(result_type(a0));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cbrt_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      if (is_invalid(a0)) return a0;
#ifdef BOOST_SIMD_HAS_CBRT
      return ::cbrt(a0);
#else
      return boost::math::cbrt(a0, nt2_policy());
#endif
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cbrt_, tag::cpu_
                            , (A0)
                            , (scalar_< single_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      if (is_invalid(a0)) return a0;
#ifdef BOOST_SIMD_HAS_CBRTF
      return ::cbrtf(a0);
#else
      return boost::math::cbrt(a0, nt2_policy());
#endif
    }
  };
} }


#endif
