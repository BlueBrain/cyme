//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_COMMON_LOAD_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_COMMON_LOAD_HPP_INCLUDED

#include <boost/simd/memory/functions/load.hpp>
#include <boost/simd/memory/functions/details/load.hpp>
#include <boost/dispatch/functor/preprocessor/dispatch.hpp>
#include <boost/simd/include/functions/simd/insert.hpp>
#include <boost/simd/include/functions/simd/extract.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/iterate.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - SIMD load via Scalar emulation without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A2)(X)
                                    , (iterator_<unspecified_<A0> >)
                                      ((target_<simd_< unspecified_<A2>, X> >))
                                    )
  {
    typedef typename A2::type result_type;
    typedef typename meta::scalar_of<result_type>::type stype;

    BOOST_FORCEINLINE result_type operator()(A0 a0, A2 const&) const
    {
      result_type that;
      for(std::size_t i=0; i!=meta::cardinal_of<result_type>::value; ++i)
        that[i] = static_cast<stype>(a0[i]);
      return that;
    }
  };

  /// INTERNAL ONLY - SIMD load via Scalar emulation with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)(X)
                                    , (iterator_<unspecified_<A0> >)
                                      (scalar_< integer_<A1> >)
                                      ((target_<simd_< unspecified_<A2>, X> >))
                                    )
  {
    typedef typename A2::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 a0, A1 a1, A2 const&) const
    {
      return load<result_type>(a0+a1);
    }
  };

  /// INTERNAL ONLY - Unaligned gather
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::load_
                                      , tag::cpu_
                                      , (A0)(A1)(A2)(X)(Y)
                                      , (mpl::equal_to
                                        < boost::simd::meta
                                          ::cardinal_of<A1>
                                        , boost::simd::meta
                                          ::cardinal_of<typename A2::type>
                                        >
                                        )
                                      , (iterator_< unspecified_<A0> >)
                                        ((simd_< integer_<A1>, X >))
                                        ((target_<simd_<unspecified_<A2>, Y> >))
                                      )
  {
    typedef typename A2::type                           result_type;
    typedef typename meta::scalar_of<result_type>::type stype;

    BOOST_FORCEINLINE result_type
    operator()(A0 a0, const A1& a1, const A2&) const
    {
      result_type that;
      for(std::size_t i=0; i!=meta::cardinal_of<result_type>::value; ++i)
        that[i] = static_cast<stype>(a0[a1[i]]);
      return that;
    }
  };

  /// INTERNAL ONLY - SIMD unaligned load for Fusion Sequence
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)(X)
                                    , (fusion_sequence_<A0>)
                                      (generic_< integer_<A1> >)
                                      ((target_ < simd_ < fusion_sequence_<A2>
                                                        , X
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(const A0& a0, const A1& a1, const A2&) const
    {
      static const int N = fusion::result_of::size<A0>::type::value;
      result_type that;
      meta::iterate<N>( details::loader< boost::simd::
                                         tag::load_(A0, A1, result_type)
                                       >(a0, a1, that)
                      );
      return that;
    }
  };

  /// INTERNAL ONLY - SIMD unaligned load for Fusion Sequence
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A2)(X)
                                    , (fusion_sequence_<A0>)
                                      ((target_ < simd_ < fusion_sequence_<A2>
                                                        , X
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(const A0& a0, const A2&) const
    {
      static const int N = fusion::result_of::size<A0>::type::value;
      result_type that;
      meta::iterate<N>( details::loader< boost::simd::
                                         tag::load_(A0, result_type)
                                       >(a0, that)
                      );
      return that;
    }
  };


} } }

#endif
