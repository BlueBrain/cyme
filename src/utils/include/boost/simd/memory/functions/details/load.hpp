//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_DETAILS_LOAD_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_DETAILS_LOAD_HPP_INCLUDED

#include <boost/simd/memory/functions/insert.hpp>
#include <boost/dispatch/meta/as.hpp>
#include <boost/dispatch/functor/meta/make_functor.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/value_at.hpp>
#include <boost/config.hpp>

// Helper for load over a fusion sequence.
namespace boost { namespace simd { namespace details
{
  template<typename Call> struct loader;

  template<typename Tag, typename A0, typename A1, typename A2>
  struct loader<Tag(A0,A1,A2)>
  {
    loader(A0 const& a0_, A1 const& a1_, A2& a2_) : a0(a0_), a1(a1_), a2(a2_) {}

    template<int I> BOOST_FORCEINLINE void operator()() const
    {
      typedef typename fusion::result_of::value_at_c<A2,I>::type type_t;
      typename dispatch:: make_functor<Tag,A0>::type callee;

      fusion::at_c<I>(a2) = callee( fusion::at_c<I>(a0)
                                  , a1
                                  , dispatch::meta::as_<type_t>()
                                  );
    }

    A0 const& a0;
    A1 const& a1;
    A2 &      a2;

    private:
    loader& operator=(loader const&);
  };

  template<typename Tag, typename A0, typename A2>
  struct loader<Tag(A0,A2)>
  {
    loader(A0 const& a0_, A2& a2_) : a0(a0_), a2(a2_) {}

    template<int I> BOOST_FORCEINLINE void operator()() const
    {
      typedef typename fusion::result_of::value_at_c<A2,I>::type type_t;
      typename dispatch:: make_functor<Tag,A0>::type callee;

      fusion::at_c<I>(a2) = callee( fusion::at_c<I>(a0)
                                  , dispatch::meta::as_<type_t>()
                                  );
    }

    A0 const& a0;
    A2 &      a2;

    private:
    loader& operator=(loader const&);
  };

  template<typename A0, typename A1, typename A2 = int> struct inserter
  {
    inserter( A0 a0_, A1& a1_, A2 a2_ = 0)
            : a0(a0_), a1(a1_), a2(a2_)
    {}

    template<int I> void operator()() const
    {
      typedef typename fusion::result_of::at_c<A1,I>::type type;
      for(std::size_t i=0;i<meta::cardinal_of<type>::value;++i)
        insert(fusion::at_c<I>(*(a0+a2)),fusion::at_c<I>(a1),i);
    }

    A0  a0;
    A1& a1;
    A2  a2;

    private:
    inserter& operator=(inserter const&);
  };
} } }

#endif
