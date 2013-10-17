
//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_LOGICAL_XOR_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_LOGICAL_XOR_HPP_INCLUDED
#include <boost/simd/arithmetic/functions/logical_xor.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::logical_xor_, tag::cpu_
                                    , (A0)
                                    , (scalar_< fundamental_<A0> >)
                                      (scalar_< fundamental_<A0> >)
                                    )
  {
    typedef typename meta::as_logical<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0,A0 a1) const
    {
      return result_type( !a0 != !a1 );
    }
  };
} } }

#endif
