//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_META_VECTOR_OF_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_META_VECTOR_OF_HPP_INCLUDED

#include <boost/simd/sdk/simd/extensions.hpp>
#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/fusion/include/fold.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/greater.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace simd { namespace meta
{
  template<class T, std::size_t Card>
  struct vector_of;
}

namespace details
{
  template<class F>
  struct max_value_impl
  {
    template<class Sig>
    struct result;

    template<class This, class T, class U>
    struct result<This(T, U)>
    {
      typedef typename dispatch::meta::strip<T>::type sT;
      typedef typename mpl::apply1<F, sT>::type vT;
      typedef typename dispatch::meta::strip<U>::type sU;
      typedef typename mpl::apply1<F, sU>::type vU;
      typedef typename mpl::if_< mpl::greater<vU, vT>
                               , sU
                               , sT
                               >::type type;
    };

    template<class T, class U>
    typename result<max_value_impl(T const&, U const&)>::type operator()(T const&, U const&) const;
  };

  template<class T, class F>
  struct max_value
       : fusion::result_of::
         fold< T
             , typename fusion::result_of::
               value_of< typename fusion::result_of::begin<T>::type
                       >::type
             , max_value_impl<F>
             >
  {
  };

  template<class T, std::size_t Card, bool Sequence = false, class Enable = void>
  struct vector_of2
  {
    typedef simd::native<T, tag::simd_emulation_< sizeof(T)*Card > > type;
  };

  template<class T, std::size_t Card>
  struct vector_of2<T, Card, true>
  {
    typedef typename max_value<T, mpl::sizeof_<mpl::_> >::type mT;
    typedef typename meta::vector_of<mT, Card>::type nT;
    typedef simd::native<T, typename nT::extension_type> type;
  };

#ifdef BOOST_SIMD_DETECTED
  /* We use boost::mpl::sizeof_ rather than sizeof because MSVC has trouble
   * with sizeof of dependent names in SFINAE contexts */
  #define BOOST_SIMD_LOCAL(z,d,r)                                             \
  template<class T,std::size_t Card>                                          \
  struct vector_of2< T, Card, false                                           \
                   , typename boost::                                         \
                     enable_if_c < (   Card*sizeof(T)                         \
                                   ==  boost::mpl::                           \
                                       sizeof_< typename meta::               \
                                                as_simd<T,r>::type            \
                                              >::value                        \
                                   )                                          \
                                 >::type                                      \
                   >                                                          \
  {                                                                           \
    typedef simd::native<T,r> type;                                           \
  };                                                                          \
  /**/
  BOOST_PP_SEQ_FOR_EACH(BOOST_SIMD_LOCAL,~,BOOST_SIMD_TAG_SEQ)
#endif
#undef BOOST_SIMD_LOCAL

  template<class T, std::size_t Card>
  struct vector_of : vector_of2<T, Card, fusion::traits::is_sequence<T>::value>
  {
  };

  // vectors must have at least 2 elements, vectors of 1 elements are scalar values
  template<class T>
  struct vector_of<T, 1u>
  {
    typedef T type;
  };
} } }

namespace boost { namespace simd { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // vector_of<T,N> computes the proper type for pack of N elements of types T
  // Either <T,N> maps onto a SIMD types, either to array<T,N>
  //////////////////////////////////////////////////////////////////////////////
  template<class T, std::size_t Card>
  struct vector_of
   : details::vector_of<T, Card>
  {
  };

  template<class T, std::size_t Card>
  struct vector_of<T&, Card>
  {
    typedef typename meta::vector_of<T, Card>::type& type;
  };

  template<class T, std::size_t Card>
  struct vector_of<T const, Card>
  {
    typedef typename meta::vector_of<T, Card>::type const type;
  };

} } }

#endif
