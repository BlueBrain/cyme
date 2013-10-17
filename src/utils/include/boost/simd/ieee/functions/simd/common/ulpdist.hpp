//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_ULPDIST_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SIMD_COMMON_ULPDIST_HPP_INCLUDED
#include <boost/simd/ieee/functions/ulpdist.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>
#include <boost/simd/include/functions/simd/divides.hpp>
#include <boost/simd/include/functions/simd/is_equal.hpp>
#include <boost/simd/include/functions/simd/is_nan.hpp>
#include <boost/simd/include/functions/simd/max.hpp>
#include <boost/simd/include/functions/simd/min.hpp>
#include <boost/simd/include/functions/simd/abs.hpp>
#include <boost/simd/include/functions/simd/frexp.hpp>
#include <boost/simd/include/functions/simd/ldexp.hpp>
#include <boost/simd/include/functions/simd/if_zero_else.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/logical_and.hpp>
#include <boost/simd/include/functions/simd/logical_or.hpp>
#include <boost/simd/include/constants/eps.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

///////////////////////////////////////////////////////////////////////////////
// It is often difficult to  answer to the following question:
//  - are these two floating computations results similar enough ?
//
// The ulpdist is a way to answer tuned for relative errors estimations
// and peculiarity of limited bits accuracy of floating point representation
// The method is the following:
//    Properly normalize the two numbers by the same factor in a way that
//    the largest of the two numbers exponents will be brought to zero
//
//    Return this boost::simd::absolute difference of these normalized numbers
//    divided by the rounding error Eps
//
//    The roundind error is the ulp (unit in the last place) value, i.e. the
//    floating number, the exponent of which is 0 and the mantissa is all zeros
//    but a 1 in the last digit (it is not hard coded that way however).
//    Yhis means 2^-23 for floats and 2^-52 for double
//
//    For instance if two floating numbers (of same type) have an ulpdist of
//    zero that means that their floating representation are identical.
//
//    Generally equality up to 0.5ulp is the best that one can wish beyond
//    strict equality.
//
//    Typically if a double is compared to the double representation of
//    its floating conversion (they are exceptions as for fully representable
//    reals) the ulpdist will be around 2^26.5 (~10^8)
//
//    The ulpdist is also roughly equivalent to the number of representable
//    floating points values between two given floating points values.
//
//     ulpdist( 1.0, 1+boost::simd::Eps<double>())   == 0.5
//     ulpdist( 1.0, 1+boost::simd::Eps<double>()/2) == 0.0
//     ulpdist( 1.0, 1-boost::simd::Eps<double>()/2) == 0.25
//     ulpdist( 1.0, 1-boost::simd::Eps<double>())   == 0.5
//     ulpdist(double(boost::simd::Pi<float>()), boost::simd::Pi<double>()) == 9.84293e+07
///////////////////////////////////////////////////////////////////////////////

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ulpdist_, tag::cpu_, (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                              ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return (max(a0, a1)-min(a0,a1));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ulpdist_, tag::cpu_, (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                              ((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::as_integer<A0>::type itype;
      itype e1, e2;
      A0 m1, m2;
      m1 = boost::simd::frexp(a0, e1);
      m2 = boost::simd::frexp(a1, e2);
      itype expo = -boost::simd::max(e1, e2);
      A0 e = select( boost::simd::is_equal(e1, e2)
                , boost::simd::abs(m1-m2)
                , boost::simd::abs(boost::simd::ldexp(a0, expo)-boost::simd::ldexp(a1, expo))
                );
      return if_zero_else(logical_or(logical_and(is_nan(a0), is_nan(a1)), boost::simd::is_equal(a0, a1)),
                          e/Eps<A0>());
    }
  };
} } }


#endif
