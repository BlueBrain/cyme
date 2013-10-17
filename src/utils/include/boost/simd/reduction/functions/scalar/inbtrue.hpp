//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_SCALAR_INBTRUE_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_SCALAR_INBTRUE_HPP_INCLUDED

#include <boost/simd/reduction/functions/inbtrue.hpp>
#include <boost/simd/include/functions/is_nez.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/zero.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::inbtrue_, tag::cpu_
                                   , (A0)
                                   , (scalar_< unspecified_<A0> >)
                                   )
  {
    typedef std::size_t result_type;
    inline result_type operator()(A0 const & a0) const
    {
      return is_nez(a0) ? One<result_type>() : Zero<result_type>();
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::inbtrue_, tag::cpu_
                                   , (A0)(A1)
                                   , (scalar_< unspecified_<A0> >)
                                     (scalar_< integer_<A1> > )
                                   )
  {
    typedef std::size_t result_type;
    inline result_type operator()(A0 const & a0, A1 const &) const
    {
      return is_nez(a0) ? One<result_type>() : Zero<result_type>();
    }
  };
} } }

#endif
