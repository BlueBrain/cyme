//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_REVERSE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_REVERSE_HPP_INCLUDED

#include <boost/simd/swar/functions/reverse.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::reverse_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_< arithmetic_<A0>, X>))
                                    )
  {
    typedef A0 result_type;

    result_type operator()(A0 const& a0) const
    {
      result_type that;
      std::size_t n = meta::cardinal_of<A0>::value-1;
      for(std::size_t i=0;i<= n;++i) that[i] = a0[n-i];
      return that;
    }
  };

} } }

#endif
