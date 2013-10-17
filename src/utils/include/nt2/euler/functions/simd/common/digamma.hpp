//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SIMD_COMMON_DIGAMMA_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SIMD_COMMON_DIGAMMA_HPP_INCLUDED

#include <nt2/euler/functions/digamma.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/if_else_zero.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/selsub.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/polevl.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/any.hpp>
#include <nt2/include/functions/simd/is_lez.hpp>
#include <nt2/include/functions/simd/is_nez.hpp>
#include <nt2/include/functions/simd/inbtrue.hpp>
#include <nt2/include/functions/simd/floor.hpp>
#include <nt2/include/functions/simd/bitwise_ornot.hpp>
#include <nt2/include/functions/simd/bitwise_andnot.hpp>
#include <nt2/include/functions/simd/tanpi.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/polynomials/functions/scalar/impl/poleval.hpp>
#include <nt2/euler/constants/digammalargelim.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/two.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::digamma_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::digamma(nt2::tofloat(a0));
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::digamma_, tag::cpu_,
                       (A0)(X),
                       ((simd_<floating_<A0>,X>))
                       )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      typedef typename meta::scalar_of<A0>::type sA0;
      //
      // This handles reflection of negative arguments, and all our
      // error handling, then forwards to the T-specific approximation.
      //
      A0 result = nt2::Zero<A0>();
      A0 x = a0;
      bA0 test = nt2::is_lez(a0);
      std::size_t nb;
      if( (nb = nt2::inbtrue(test)) > 0)
      {
        x = nt2::if_else(test, nt2::oneminus(a0), a0);
        A0 remainder = x - nt2::floor(x);
        remainder =  nt2::selsub(nt2::gt(remainder,Half<A0>()),remainder,nt2::One<A0>());
        remainder = nt2::if_zero_else(nt2::is_eqz(remainder), nt2::Pi<A0>()/nt2::tanpi(remainder));
        result = nt2::if_else_zero(test, remainder);
        //          remainder =  selsub(gt(remainder,Half<A0>()),remainder,One<A0>());
        //          result = b_and(b_andnot(Pi<A0>()/tanpi(remainder),is_eqz(remainder)), test);
        // we are ready to increment result that was
        // Pi<A0>()/tanpi(remainder) if a0 < 0  and remainder != 0
        // Nan<A0>                   if a0 < 0  and remainder == 0
        // 0                         in any other cases
      }
      A0 r1 = nt2::Zero<A0>(), r2= nt2::Zero<A0>();
      test = nt2::gt(x, Digammalargelim<A0>());
      nb = nt2::inbtrue(test);
      if(nb)
      { // If we're above the lower-limit for the asymptotic expansion then use it:
        r1 = nt2::if_else_zero(test, digamma_imp_large(x, sA0()))+result;//b_and(digamma_imp_large(x, sA0()), test)+result;
        if (nb >= (uint32_t)meta::cardinal_of<A0>::value) return r1;
      }
      // If x > 2 reduce to the interval [1,2]:
      bA0 cond;
      while(nt2::any(cond = nt2::gt(x, nt2::Two<A0>())))
      {
        x      -= nt2::if_else_zero(cond, nt2::One<A0>());
        result += nt2::if_else_zero(cond, nt2::rec(x));
      }
      // If x < 1 use shift to > 1:
      if(nt2::any(cond = nt2::lt(x, nt2::One<A0>())))
      {
        result = nt2::if_else(cond, -nt2::rec(x), result);
        x      += nt2::ifelsezero(cond, nt2::One<A0>());
      }
      r2 =  nt2::if_zero_else(test, digamma_imp_1_2(x, sA0()))+result;//b_andnot(digamma_imp_1_2(x, sA0()), test)+result;
      if (nb == 0) return r2;
      return nt2::if_else(test, r1, r2);
    }
  private:
    template <class A>
      static inline A digamma_imp_1_2(A const& a0, float)
    {
      //
      // Now the approximation, we use the form:
      //
      // digamma(x) = (x - root) * (Y + R(x-1))
      //
      // Where root is the location of the positive root of digamma,
      // Y is a constant, and R is optimised for low nt2::absolute error
      // compared to Y.
      //
      // Maximum Deviation Found:              3.388e-010
      // At float precision, max error found:  2.008725e-008
      //
      typedef typename meta::scalar_of<A>::type sA;
      static const A Y = nt2::splat<A>(0.99558162689208984);
      static const A root = nt2::splat<A>(1532632.0 / 1048576);
      static const A root_minor = splat<A>(double(0.3700660185912626595423257213284682051735604e-6L));
      static const boost::array<sA, 4> P = {{
          sA(0.25479851023250261e0),
          sA(-0.44981331915268368e0),
          sA(-0.43916936919946835e0),
          sA(-0.61041765350579073e-1)
        }};
      static const  boost::array<sA, 4> Q = {{
          sA(0.1e1),
          sA(0.15890202430554952e1),
          sA(0.65341249856146947e0),
          sA(0.63851690523355715e-1)
        }};
      A x = a0;
      A g = x - root;
      g -= root_minor;
      x-= nt2::One<A>();
      A r = nt2::eval_poly<4>(x, P)/nt2::eval_poly<4>(x, Q);
      A result = nt2::fma(g, Y, g * r);
      return result;
    }

    template <class A>
      static inline A digamma_imp_large(A const& a0, float)
    {
      typedef typename meta::scalar_of<A>::type sA;
      // 9-digit precision for x >= 10:
      static const  boost::array<sA, 3> P = {{
          sA(0.083333333333333333333333333333333333333333333333333L),
          sA(-0.0083333333333333333333333333333333333333333333333333L),
          sA(0.003968253968253968253968253968253968253968253968254L)
        }};
      A x = a0;
      x -= nt2::One<A>();
      A result = log(x);
      result += nt2::rec(nt2::Two<A>()*x);
      A z = nt2::rec(nt2::sqr(x));
      result -= z * nt2::eval_poly<3>(z, P);
      return result;
    }
    template <class A>
      static inline A digamma_imp_1_2(A const& a0, double)
    {
      //
      // Now the approximation, we use the form:
      //
      // digamma(x) = (x - root) * (Y + R(x-1))
      //
      // Where root is the location of the positive root of digamma,
      // Y is a constant, and R is optimised for low nt2::absolute error
      // compared to Y.
      //
      // Maximum Deviation Found:              3.388e-010
      // At float precision, max error found:  2.008725e-008
      //
      typedef typename meta::scalar_of<A>::type sA;
      static const A Y = splat<A>(0.99558162689208984);

      static const A root1 = splat<A>(1569415565.0 / 1073741824uL);
      static const A root2 = splat<A>((381566830.0 / 1073741824uL) / 1073741824uL);
      static const A root3 = splat<A>(double(0.9016312093258695918615325266959189453125e-19L));

      static const boost::array<sA, 6> P = {{
          sA(0.25479851061131551L),
          sA(-0.32555031186804491L),
          sA(-0.65031853770896507L),
          sA(-0.28919126444774784L),
          sA(-0.045251321448739056L),
          sA(-0.0020713321167745952L)
        }};
      static const  boost::array<sA, 7> Q = {{
          sA(1L),
          sA(2.0767117023730469L),
          sA(1.4606242909763515L),
          sA(0.43593529692665969L),
          sA(0.054151797245674225L),
          sA(0.0021284987017821144L),
          sA(-0.55789841321675513e-6L)
        }};
      A x = a0;
      A g = x - root1;
      g -= root2;
      g -= root3;
      x-= nt2::One<A>();
      A r = nt2::eval_poly<6>(x, P)/nt2::eval_poly<7>(x, Q);
      A result = nt2::fma(g, Y, g * r);
      return result;
    }

    template <class A>
      static inline A digamma_imp_large(A const& a0, double)
    {
      typedef typename meta::scalar_of<A>::type sA;
      // 9-digit precision for x >= 10:
      static const  boost::array<sA, 8> P = {{
          sA(0.083333333333333333333333333333333333333333333333333L),
          sA(-0.0083333333333333333333333333333333333333333333333333L),
          sA(0.003968253968253968253968253968253968253968253968254L),
          sA(-0.0041666666666666666666666666666666666666666666666667L),
          sA(0.0075757575757575757575757575757575757575757575757576L),
          sA(-0.021092796092796092796092796092796092796092796092796L),
          sA(0.083333333333333333333333333333333333333333333333333L),
          sA(-0.44325980392156862745098039215686274509803921568627L)
        }};
      A x = a0;
      x -= nt2::One<A>();
      A result = nt2::log(x);
      result += nt2::rec(nt2::Two<A>()*x);
      A z = nt2::rec(nt2::sqr(x));
      result -= z * nt2::eval_poly<8>(z, P);
      return result;
    }
  };
} }

#endif
