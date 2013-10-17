//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_LDEXP_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_LDEXP_HPP_INCLUDED

#include <boost/simd/ieee/functions/ldexp.hpp>
#include <boost/simd/include/functions/simd/splat.hpp>
#include <boost/simd/include/functions/simd/shift_left.hpp>
#include <boost/simd/include/functions/simd/is_nez.hpp>
#include <boost/simd/include/functions/simd/is_finite.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/logical_and.hpp>
#include <boost/simd/include/functions/simd/rshl.hpp>
#include <boost/simd/include/functions/simd/bitwise_andnot.hpp>
#include <boost/simd/include/functions/simd/bitwise_and.hpp>
#include <boost/simd/include/functions/simd/bitwise_or.hpp>
#include <boost/simd/include/functions/simd/logical_and.hpp>
#include <boost/simd/include/functions/simd/plus.hpp>
#include <boost/simd/include/constants/ldexpmask.hpp>
#include <boost/simd/include/constants/nbmantissabits.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/sizeof.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::ldexp_, tag::cpu_,(A0)(A1)(X)
                                      , (boost::mpl::equal_to < boost::mpl::sizeof_<A0>
                                                              , boost::mpl::sizeof_<A1>
                                                              >
                                        )
                                      , ((simd_<arithmetic_<A0>,X>))
                                        ((simd_<integer_<A1>,X>))
                                      )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2) { return rshl(a0, a1); }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::ldexp_, tag::cpu_, (A0)(A1)(X)
                                    , ((simd_<arithmetic_<A0>,X>))(scalar_< integer_<A1> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2) { return rshl(a0, a1); }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::ldexp_, tag::cpu_,(A0)(A1)(X)
                                      , (boost::mpl::equal_to < boost::mpl::sizeof_<A0>
                                                              , boost::mpl::sizeof_<A1>
                                                              >
                                        )
                                      , ((simd_<floating_<A0>,X>))
                                        ((simd_<integer_<A1>,X>))
                                      )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      // No denormal provision
      typedef typename meta::scalar_of<result_type>::type             s_type;
      typedef typename dispatch::meta::as_integer<result_type, signed>::type  int_type;

      // clear exponent in x
      result_type const x = b_andnot(a0, Ldexpmask<A0>());

      // extract exponent and compute the new one
      int_type e    = b_and(Ldexpmask<A0>(), a0);
      e += shli(a1, Nbmantissabits<s_type>());
      return select( logical_and(is_nez(a0),is_finite(a0))
                     , b_or(x, e)
                     , a0
                     );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::ldexp_, tag::cpu_, (A0)(A1)(X)
                                    , ((simd_<floating_<A0>,X>))(scalar_< integer_<A1> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename dispatch::meta::as_integer<A0>::type iA0;
      return ldexp(a0, boost::simd::splat<iA0>(a1));
    }
  };
} } }

#endif
