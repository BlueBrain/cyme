//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_COMPLEMENT_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_COMPLEMENT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::complement_, boost::simd::tag::altivec_, (A0)
                            , ((simd_<arithmetic_<A0>,boost::simd::tag::altivec_>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return vec_nor(a0(), a0());
    }
  };
} } }

#endif
#endif
