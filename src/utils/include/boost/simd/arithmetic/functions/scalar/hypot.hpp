//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_HYPOT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_HYPOT_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/hypot.hpp>
#include <boost/simd/include/functions/scalar/bitwise_cast.hpp>
#include <boost/simd/include/functions/scalar/sqrt.hpp>
#include <boost/simd/include/functions/scalar/sqr.hpp>
#include <boost/simd/include/functions/scalar/max.hpp>
#include <boost/simd/include/functions/scalar/min.hpp>
#include <boost/simd/include/functions/scalar/logical_or.hpp>
#include <boost/simd/include/functions/scalar/logical_and.hpp>
#include <boost/simd/include/functions/scalar/exponent.hpp>
#include <boost/simd/include/functions/scalar/is_nan.hpp>
#include <boost/simd/include/functions/scalar/is_inf.hpp>
#include <boost/simd/include/functions/scalar/ldexp.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/sdk/meta/make_dependent.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  template < class T, class I = typename dispatch::meta::as_integer<T, signed>::type>
  struct hypot_constants;
  //TODO make proper constants

  template <class I> struct hypot_constants<float, I>
  {
    typedef I  int_type;
    static inline int_type C0() { return (30);};
    static inline int_type C1() { return (50);};
    static inline int_type C2() { return (60);};
    static inline int_type MC1(){ return (-50);};
    static inline int_type MC2(){ return (-60);};
    static inline int_type C3() { return (0x00800000);};
    static inline int_type M1() { return (0xfffff000);};
  };

  template <class I> struct hypot_constants<double, I>
  {
    typedef I  int_type;
    static inline int_type C0() { return (60);};
    static inline int_type C1() { return (500);};
    static inline int_type C2() { return (600);};
    static inline int_type MC1(){ return (-500);};
    static inline int_type MC2(){ return (-600);};
    static inline int_type C3() { return (0x0010000000000000ll);}
    static inline int_type M1() { return (0xffffffff00000000ll);};
  };

 BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::hypot_, tag::cpu_,
                       (A0),
                       (scalar_<floating_<A0> >)(scalar_<floating_<A0> >)
                      )
 {
   typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return internal(a0, a1);
    }
  private:

    static inline float internal(const float& a0, const  float& a1)
      {
      // flibc does that in ::hypotf(a0, a1) in asm with no more speed!
      // proper internal is 30% slower
        return static_cast<float>(::sqrt(boost::simd::sqr(static_cast<typename meta::make_dependent<double, A0>::type>(a0))+
                                         boost::simd::sqr(static_cast<typename meta::make_dependent<double, A0>::type>(a1))));
      }

    template < class AA0>
    static inline AA0  internal(const AA0& a0, const  AA0& a1)
    {
      // in double ::hypot is very slow and is 4 times slower than internal
      // this routine in float (with float constants) is 30% slower than
      // the straightforward preceding overload for floats
      // The float constants are provided in order to modify
      // the algorithm if a architecture gived different speed results
      if ( logical_or(logical_and(is_nan(a0), is_inf(a1)),
                      logical_and(is_nan(a1), is_inf(a0)))) return Inf<result_type>();
      typedef typename dispatch::meta::as_integer<AA0, signed>::type  int_type;
      AA0 x =  boost::simd::abs(a0);
      AA0 y =  boost::simd::abs(a1);
      if (boost::simd::is_inf(x+y)) return Inf<AA0>();
      if (boost::simd::is_nan(x+y)) return Nan<AA0>();
      AA0 a =  boost::simd::max(x, y);
      AA0 b =  boost::simd::min(x, y);
      int_type ea =   boost::simd::exponent(a);
      int_type eb  =  boost::simd::exponent(b);
      if (ea-eb > hypot_constants<AA0>::C0()) return a+b;
      int_type e = Zero<int_type>();
      if (ea > hypot_constants<AA0>::C1())
      {
        e = hypot_constants<AA0>::MC2();
      }
      if (eb < hypot_constants<AA0>::MC1())
      {
        e = hypot_constants<AA0>::C1();
      }
      if (e)
      {
        a =  boost::simd::ldexp(a, e);
        b =  boost::simd::ldexp(b, e);
      }
      AA0 w = a-b;
      if (w > b)
      {
        AA0 t1 = b_and(a, hypot_constants<AA0>::M1());
        AA0 t2 = a-t1;
        w  = (t1*t1-(b*(-b)-t2*(a+t1)));
      }
      else
      {
        AA0 y1 = b_and(b, hypot_constants<AA0>::M1());
        AA0 y2 = b - y1;
        typedef typename dispatch::meta::as_integer<AA0, unsigned>::type type;
        AA0 t1 =  bitwise_cast<AA0>(bitwise_cast<type>(a)+hypot_constants<AA0>::C3());
        AA0 t2 = (a+a) - t1;
        w  = (t1*y1-(w*(-w)-(t1*y2+t2*b)));
      }
      w = boost::simd::sqrt(w);
      if (e) w = boost::simd::ldexp(w, -e);
      return w;
    }
  };
} } }

#endif
