//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SCALAR_NORM_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SCALAR_NORM_HPP_INCLUDED
#include <nt2/linalg/functions/norm.hpp>
#include <nt2/include/functions/scalar/norm.hpp>
#include <nt2/include/functions/scalar/isvector.hpp>
#include <nt2/include/functions/scalar/ismatrix.hpp>
#include <nt2/include/functions/scalar/vecnorm.hpp>
#include <nt2/include/functions/scalar/is_nan.hpp>
#include <nt2/include/functions/scalar/isempty.hpp>
#include <nt2/include/functions/scalar/globalmax.hpp>
#include <nt2/include/functions/scalar/asum1.hpp>
#include <nt2/include/functions/scalar/svd.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/container/table/table.hpp>
#include <string>

// *     DLANGE = ( max(abs(A(i,j))), NORM = 'M' or 'm'
// *              (
// *              ( norm1(A),         NORM = '1', 'O' or 'o'
// *              (
// *              ( normI(A),         NORM = 'I' or 'i'
// *              (
// *              ( normF(A),         NORM = 'F', 'f', 'E' or 'e'
// *
// *  where  norm1  denotes the  one norm of a matrix (maximum column sum),
// *  normI  denotes the  infinity norm  of a matrix  (maximum row sum) and
// *  normF  denotes the  Frobenius norm of a matrix (square root of sum of
// *  squares).  Note that  max(abs(A(i,j)))  is not a consistent matrix norm.

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::norm_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<arithmetic_<A1> > )
    )
  {
    typedef typename meta::strip<typename A0::value_type>::type type_t;
    typedef typename meta::as_real<type_t>::type rtype_t;
    typedef rtype_t result_type;
    NT2_FUNCTOR_CALL(2)
    {
      if (isvector(a0))
      {
        return vecnorm(a0, a1);
      }
      else if (ismatrix(a0))
      {
        if (isempty(a0)){
          return Zero<result_type>();
        } else if (a1 == 'I'|| a1 == 'i'|| a1 == Inf<A1>()){
          return nt2::globalmax(nt2::asum1(a0, 2));
        } else if (a1 == Two<A1>()){
          return nt2::details::svd_result<A0>(a0, 'N', 'N').norm();
        } else if (a1 == '1' || a1 == 'O' || a1 == 'o' ||a1 == One<A1>()) {
         return nt2::globalmax(nt2::asum1(a0, 1));
        } else if (a1 == 'F' || a1 == 'f' || a1 == 'E' ||a1 == 'e'){
          return vecnorm(a0);
        } else {
          BOOST_ASSERT_MSG(false, "Sorry Not Implemented for this parameter a1 value");
          return Nan<result_type>();
        }
      }
      else
      {
        BOOST_ASSERT_MSG(false, "a0 is not matrix nor vector");
        return Nan<result_type>();
      }
      return Nan<result_type>();
    }
  };



  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::norm_, tag::cpu_,
                              (A0)(C),
                              ((ast_<A0, nt2::container::domain>))
                              (unspecified_<C> )
    )
  {
    typedef typename A0::value_type type_t;
    typedef typename meta::as_real<type_t>::type rtype_t;
    typedef typename meta::as_floating<rtype_t>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0& a0, const char * a1) const
    {
      if (strcmp(a1, "fro") == 0)
      {
        return norm(a0, 'F');
      }
      else if (strcmp(std::string(a1).c_str(), "inf") == 0)
      {
        return norm(a0, 'I');
      }
      else
      {
        BOOST_ASSERT_MSG(false, "unknown option calling norm");
        return Nan<result_type>();
      }
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::norm_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain>))
    )
  {
    typedef typename A0::value_type type_t;
    typedef typename meta::as_real<type_t>::type rtype_t;
    typedef typename meta::as_floating<rtype_t>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      if (isvector(a0))
      {
        return vecnorm(a0);
      }
      else if (ismatrix(a0))
      {
        return norm(a0, 2);
      }
      else
      {
        BOOST_ASSERT_MSG(false, "a0 is not matrix nor vector");
        return Nan<result_type>();
      }
    }
  };
} }

#endif
