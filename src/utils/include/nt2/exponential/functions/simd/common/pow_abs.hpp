//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_POW_ABS_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_POW_ABS_HPP_INCLUDED

#include <nt2/exponential/functions/pow_abs.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/signnz.hpp>
#include <nt2/include/functions/simd/any.hpp>
#include <nt2/include/functions/simd/if_else_zero.hpp>
#include <nt2/include/functions/simd/is_odd.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/shr.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/include/functions/simd/is_nan.hpp>
#include <nt2/include/functions/simd/is_inf.hpp>
#include <nt2/include/functions/simd/is_gtz.hpp>
#include <nt2/include/functions/simd/pow_absi.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/sdk/meta/as_logical.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_abs_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return nt2::pow_abs(tofloat(a0), tofloat(a1));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_abs_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::as_logical<A0>::type                 bA0;
      bA0 allz = l_and(is_eqz(a0), is_eqz(a1));
      return if_else(allz, One<result_type>(), exp(a1*log(nt2::abs(a0))));

    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is integer_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_abs_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_<arithmetic_<A0>,X>))((simd_<integer_<A1>,X>))
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      typedef result_type r_type;
      r_type a00 =  tofloat(a0);
      r_type x = nt2::abs(a00);
      r_type r = x;
      A1 sign_n = signnz( a1 );
      A1 n = nt2::abs(a1);
      r_type n_oddf = if_else_zero(is_odd(n), One<r_type>());
      r_type nf = n_oddf;
      r_type y = madd(n_oddf,x,oneminus(n_oddf));
      r_type w = x;
      n = shri(n,1);
      while( nt2::any(n) )
      {
        w =sqr(w);
        n_oddf = if_else_zero(is_odd(n), One<r_type>());
        y = y*madd(n_oddf,w,oneminus(n_oddf));
        n = shri(n,1);
      }

      w = y; //b_xor(y, sign_x);
      y = madd(nf, w, (oneminus(nf))*y);

      w = rec(y);
      x = tofloat(shri(oneplus(sign_n),1));  // 1 if positive, else 0
      return if_nan_else(is_nan(a00), sel(is_inf(a00), sel(is_gtz(a1), r, rec(r)), madd(x,y,oneminus(x)*w)));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is scalar integer_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_abs_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_<arithmetic_<A0>,X>))(scalar_< integer_<A1> >)
                            )
  {

    typedef typename meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return pow_absi(a0, a1);
    }
  };
} }


#endif
