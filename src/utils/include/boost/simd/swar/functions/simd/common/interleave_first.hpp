//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_INTERLEAVE_FIRST_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_INTERLEAVE_FIRST_HPP_INCLUDED

#include <boost/simd/swar/functions/interleave_first.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::interleave_first_, tag::cpu_
                                    , (A0)(A1)(X)
                                    , ((simd_< unspecified_<A0>, X>))
                                      ((simd_< unspecified_<A1>, X>))
                                    )
  {
    typedef A0 result_type;

    result_type operator()(A0 const& a0, A1 const& a1) const
    {
      result_type that;
      const std::size_t middle = meta::cardinal_of<A0>::value/2;
      for(std::size_t i=0;i<middle;++i)
      {
        that[i*2]   = a0[i];
        that[i*2+1] = a1[i];
      }
      return that;
    }
  };
} } }

#endif
