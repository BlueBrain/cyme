//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_COMMON_IS_INCLUDED_C_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_COMMON_IS_INCLUDED_C_HPP_INCLUDED
#include <boost/simd/reduction/functions/is_included_c.hpp>
#include <boost/simd/include/functions/simd/bitwise_and.hpp>
#include <boost/simd/include/functions/simd/none.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_included_c_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                              ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef typename meta::scalar_of<A0>::type sA0;
    typedef typename meta::as_logical<sA0>::type result_type;
    inline result_type operator()(A0 const& a0,A0 const& a1) const
    {
      return none(bitwise_and(a1, a0));
    }
  };

} } }
#endif
