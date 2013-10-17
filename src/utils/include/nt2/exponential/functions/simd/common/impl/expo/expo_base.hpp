//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_IMPL_EXPO_EXPO_BASE_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_IMPL_EXPO_EXPO_BASE_HPP_INCLUDED

#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/include/functions/simd/is_nan.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <boost/simd/sdk/config.hpp>

namespace nt2 { namespace details
{
  template < class A0, class Tag,  class Speed_Tag >
  struct exponential < A0, Tag, tag::simd_type, Speed_Tag>
  {
    typedef exp_reduction<A0,Tag>                        reduc_t;
    typedef exp_finalization<A0,Tag,Speed_Tag>        finalize_t;
    typedef typename meta::as_logical<A0>::type              bA0;

    // compute exp(ax)
    static inline A0 expa(const A0& a0)
    {
      A0 hi, lo, x;
      A0 k = reduc_t::reduce(a0, hi, lo, x);
      A0 c = reduc_t::approx(x);
      bA0 le = reduc_t::isleminlog(a0);
      A0 z = nt2::if_zero_else(le,
                               finalize_t::finalize(a0, x, c, k, hi, lo)
                              );
      A0 z1 =  nt2::if_else( reduc_t::isgemaxlog(a0), nt2::Inf<A0>(), z);
#ifdef BOOST_SIMD_NO_INVALIDS
      return z1;
#else
      return if_nan_else(is_nan(a0), z1);
#endif
    }
  };
} }

#endif
