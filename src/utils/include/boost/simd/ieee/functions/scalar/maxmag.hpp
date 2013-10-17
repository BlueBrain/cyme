//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_MAXMAG_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_MAXMAG_HPP_INCLUDED
#include <boost/simd/ieee/functions/maxmag.hpp>
#include <boost/simd/include/functions/scalar/abs.hpp>
#include <boost/simd/include/functions/scalar/max.hpp>


namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::maxmag_, tag::cpu_
                            , (A0)
                            , (scalar_< fundamental_<A0> >)(scalar_< fundamental_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      A0 aa0 =  boost::simd::abs(a0);
      A0 aa1 =  boost::simd::abs(a1);
      return (aa0 > aa1) ? a0 : (aa0 < aa1) ? a1 : boost::simd::max(a0, a1);
    }
  };
} } }


#endif
