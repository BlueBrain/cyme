//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SCALAR_ROL_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SCALAR_ROL_HPP_INCLUDED

#include <boost/simd/bitwise/functions/rol.hpp>
#include <boost/simd/include/functions/scalar/abs.hpp>
#include <boost/simd/include/functions/scalar/shift_left.hpp>
#include <boost/simd/include/functions/scalar/shr.hpp>
#include <boost/simd/include/functions/scalar/bitwise_cast.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::rol_, tag::cpu_, (A0)(A1)
                            , (scalar_< integer_<A0> >)
                              (scalar_< int_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      static const std::size_t width = sizeof(A0)*CHAR_BIT;
      A1 aa1 = boost::simd::abs(a1);
      return shli(a0, aa1) | shri(a0, (width-aa1) & (width-1));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::rol_, tag::cpu_, (A0)(A1)
                            , (scalar_< integer_<A0> >)
                              (scalar_< uint_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      static const std::size_t width = sizeof(A0)*CHAR_BIT;
      return shli(a0, a1) | shri(a0, (width-a1) & (width-1));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::rol_, tag::cpu_, (A0)(A1)
                                   , (scalar_< floating_<A0> >)
                                     (scalar_< integer_<A1> >)
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename dispatch::meta::as_integer<A0, unsigned>::type itype;
      return bitwise_cast<result_type>(rol(bitwise_cast<itype>(a0), a1));
    }
  };
} } }

#endif
