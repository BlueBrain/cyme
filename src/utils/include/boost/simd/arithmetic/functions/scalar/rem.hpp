//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_REM_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_REM_HPP_INCLUDED
#include <boost/simd/arithmetic/functions/rem.hpp>
#include <boost/simd/include/functions/scalar/idivfix.hpp>
/////////////////////////////////////////////////////////////////////////////
//  The rem function computes the floating-point remainder of dividing x by y.
//  The return value is x - n * y, where n is the quotient of x / y, rounded
//  toward zero to an integer.
//  The fmod function is just an alias for the same thing.
/////////////////////////////////////////////////////////////////////////////

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::rem_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)(scalar_< arithmetic_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      if (a1) return a0%a1; else return a0;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::rem_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)(scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      if (a1) return a0-a1*idivfix(a0,a1);  else return a0;
    }
  };
} } }


#endif
