//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_PREV_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SCALAR_PREV_HPP_INCLUDED
#include <boost/simd/ieee/functions/prev.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/functions/scalar/dec.hpp>
#include <boost/simd/include/functions/scalar/nextafter.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::prev_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1) { return dec(a0); }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::prev_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1) { return nextafter(a0, Minf<A0>()); }
  };
} } }


#endif
