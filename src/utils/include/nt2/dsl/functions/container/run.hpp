//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DSL_FUNCTIONS_CONTAINER_RUN_HPP_INCLUDED
#define NT2_DSL_FUNCTIONS_CONTAINER_RUN_HPP_INCLUDED

#include <nt2/dsl/functions/run.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/transform.hpp>
#include <nt2/include/functions/inner_fold.hpp>
#include <nt2/include/functions/outer_fold.hpp>
#include <nt2/include/functions/inner_scan.hpp>
#include <nt2/include/functions/outer_scan.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/ndims.hpp>
#include <nt2/include/functions/terminal.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/sdk/memory/category.hpp>
#include <nt2/sdk/meta/is_container.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>
#include <boost/proto/traits.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <numeric>

namespace nt2 { namespace ext
{
  //============================================================================
  // Element-wise operations go to transform
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(T0)(N0)(A1)(T1)(N1)
                            , ((node_<A0, elementwise_<T0>, N0, nt2::container::domain>))
                              ((node_<A1, elementwise_<T1>, N1, nt2::container::domain>))
                            )
  {
    typedef A0&                                             result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1) const
    {
      a0.resize(a1.extent());
      nt2::transform(container::as_view(a0), a1);
      return a0;
    }
  };

  //============================================================================
  // Copies go to transform as well, but we check for self-assignment.
  // This is not a pessimization, some code patterns rely on this!
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(T0)
                            , ((node_<A0, elementwise_<T0>, boost::mpl::long_<0> , nt2::container::domain>))
                              ((node_<A0, elementwise_<T0>, boost::mpl::long_<0> , nt2::container::domain>))
                            )
  {
    typedef A0&                                             result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A0& a1) const
    {
      a0.resize(a1.extent());
      if(a0.raw() != a1.raw())
        nt2::transform(container::as_view(a0), a1);
      return a0;
    }
  };

  //============================================================================
  // Reductions operations go to inner/outer fold
  // Note that MATLAB reduction functions have a f(x) and a f(x,i) form
  // that we handle with reduction_dim
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(T0)(N0)(A1)(T1)(O1)(Neutral1)(N1)
                            , ((node_<A0, elementwise_<T0>, N0, nt2::container::domain>))
                              ((node_<A1, reduction_<T1,O1,Neutral1>, N1 , nt2::container::domain>))
                            )
  {
    typedef A0&                                                                result_type;
    typedef typename boost::proto::result_of::child_c<A1&, 0>::type            input_type;
    typedef typename boost::remove_reference<input_type>::type::extent_type    extent_type;
    typedef typename boost::remove_reference<input_type>::type::value_type     value_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1) const
    {
      a0.resize(a1.extent());

      input_type input = boost::proto::child_c<0>(a1);
      extent_type ext = input.extent();
      std::size_t dim = nt2::ndims(ext);
      std::size_t lo_dim = nt2::firstnonsingleton(ext);
      std::size_t red = reduction_dim(a1, boost::mpl::bool_<!(boost::proto::arity_of<A1>::value <= 1)>());

      std::size_t inner = red-1 < ext.size() ? ext[red-1] : 1;

      std::size_t lo = std::accumulate( ext.begin()
                                      , ext.begin()+std::min(red-1, dim)
                                      , std::size_t(1)
                                      , std::multiplies<std::size_t>()
                                      );

      std::size_t hi = std::accumulate( ext.begin()+std::min(red, dim)
                                      , ext.begin()+dim
                                      , std::size_t(1)
                                      , std::multiplies<std::size_t>()
                                      );

      if(red <= lo_dim)
      {
        nt2::inner_fold( container::as_view(a0)
                       , reshape(input, of_size(inner, hi))
                       , typename nt2::make_functor<Neutral1, A0>::type()
                       , typename nt2::make_functor<O1, A0>::type()
                       , typename nt2::make_functor<T1, A0>::type()
                       );
      }
      else
      {
        nt2::outer_fold( reshape(a0, of_size(lo, hi))
                       , reshape(input, of_size(lo, inner, hi))
                       , typename nt2::make_functor<Neutral1, A0>::type()
                       , typename nt2::make_functor<O1, A0>::type()
                       , typename nt2::make_functor<T1, A0>::type()
                       );
      }

      return a0;
    }

    inline std::size_t reduction_dim(A1& a1, boost::mpl::false_) const
    {
      return nt2::firstnonsingleton(boost::proto::child_c<0>(a1).extent());
    }

    inline std::size_t reduction_dim(A1& a1, boost::mpl::true_) const
    {
      return nt2::run(boost::proto::child_c<1>(a1));
    }
  };

  //============================================================================
  // Cumulative operations go to inner/outer scan
  // Note that MATLAB reduction functions have a f(x) and a f(x,i) form
  // that we handle with reduction_dim
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(T0)(N0)(A1)(T1)(O1)(Neutral1)(N1)
                            , ((node_<A0, elementwise_<T0>, N0, nt2::container::domain>))
                              ((node_<A1, cumulative_<T1,O1,Neutral1>, N1 , nt2::container::domain>))
                            )
  {
    typedef A0&                                                                result_type;
    typedef typename boost::proto::result_of::child_c<A1&, 0>::type            input_type;
    typedef typename boost::remove_reference<input_type>::type::extent_type    extent_type;
    typedef typename boost::remove_reference<input_type>::type::value_type     value_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1) const
    {
      a0.resize(a1.extent());

      input_type input = boost::proto::child_c<0>(a1);
      extent_type ext = input.extent();
      std::size_t dim = nt2::ndims(ext);
      std::size_t lo_dim = nt2::firstnonsingleton(ext);
      std::size_t red = reduction_dim(a1, boost::mpl::bool_<!(boost::proto::arity_of<A1>::value <= 1)>());

      std::size_t inner = red-1 < ext.size() ? ext[red-1] : 1;

      std::size_t lo = std::accumulate( ext.begin()
                                      , ext.begin()+std::min(red-1, dim)
                                      , std::size_t(1)
                                      , std::multiplies<std::size_t>()
                                      );

      std::size_t hi = std::accumulate( ext.begin()+std::min(red, dim)
                                      , ext.begin()+dim
                                      , std::size_t(1)
                                      , std::multiplies<std::size_t>()
                                      );

      if(red <= lo_dim)
      {
        nt2::inner_scan( container::as_view(a0)
                       , reshape(input, of_size(inner, hi))
                       , typename nt2::make_functor<Neutral1, A0>::type()
                       , typename nt2::make_functor<O1, A0>::type()
                       , typename nt2::make_functor<T1, A0>::type()
                       );
      }
      else
      {
        nt2::outer_scan( reshape(a0, of_size(lo, inner, hi))
                       , reshape(input, of_size(lo, inner, hi))
                       , typename nt2::make_functor<Neutral1, A0>::type()
                       , typename nt2::make_functor<O1, A0>::type()
                       , typename nt2::make_functor<T1, A0>::type()
                       );
      }

      return a0;
    }

    inline std::size_t reduction_dim(A1& a1, boost::mpl::false_) const
    {
      return nt2::firstnonsingleton(boost::proto::child_c<0>(a1).extent());
    }

    inline std::size_t reduction_dim(A1& a1, boost::mpl::true_) const
    {
      return nt2::run(boost::proto::child_c<1>(a1));
    }
  };

  //============================================================================
  // Non-assign table expressions are reduced to assign expressions
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::run_, tag::cpu_
                            , (A0)(S0)(K0)(T)(N)
                            , (mpl::not_< is_same<T, boost::simd::tag::assign_> >)
                            , ((expr_< container_<K0,unspecified_<A0>,S0>
                                     , T
                                     , N
                                     >
                              ))
                            )
  {
    typedef typename boost::dispatch::meta::
            terminal_of< typename boost::dispatch::meta::
                         semantic_of<A0&>::type
                       >::type
                                                           result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0) const
    {
      result_type tmp;
      run_assign(tmp, a0);
      return tmp;
    }
  };

  //============================================================================
  // Running a table terminal does nothing and returns it
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(S0)(K0)(T)
                            , ((expr_< container_<K0,unspecified_<A0>,S0>
                                     , T
                                     , boost::mpl::long_<0>
                                     >
                              ))
                            )
  {
    typedef typename boost::proto::result_of::value<A0>::value_type value_type;

    // avoid copying table
    typedef typename boost::mpl::
            if_c< meta::is_container<value_type>::value
                  && !meta::is_container_ref<value_type>::value
                  && !boost::is_reference<value_type>::value
                , A0&
                , A0
                >::type
    result_type;
    BOOST_FORCEINLINE result_type operator()(A0& a0) const
    {
      return a0;
    }
  };

  //============================================================================
  // Non-assign scalar expressions are evaluated directly
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::run_, tag::cpu_
                            , (A0)(T)(N)
                            , (mpl::and_< is_same<typename A0::proto_domain, nt2::container::domain>
                                        , mpl::not_< is_same<T, boost::simd::tag::assign_> >
                                        >)
                            , ((expr_< scalar_< unspecified_<A0> >
                                     , T
                                     , N
                                     >
                              ))
                            )
  {
    typedef typename boost::dispatch::meta::
    semantic_of<A0>::type                                  result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0) const
    {
      return impl(a0, typename meta::is_elementwise<T>::type());
    }

    BOOST_FORCEINLINE result_type impl(A0& a0, boost::mpl::false_) const
    {
      result_type tmp;
      return nt2::run(nt2::assign(meta::as_child<result_type, nt2::container::domain>::call(tmp), a0));
      return tmp;
    }

    BOOST_FORCEINLINE result_type impl(A0& a0, boost::mpl::true_) const
    {
      typedef typename meta::strip<result_type>::type stype;
      return nt2::run(a0, 0u, meta::as_<stype>());
    }
  };

  //============================================================================
  // Assign expressions call run_assign
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)
                            , ((node_< A0
                                     , boost::simd::tag::assign_
                                     , boost::mpl::long_<2>
                                     , nt2::container::domain
                                     >
                              ))
                            )
  {
    typedef typename boost::dispatch::meta::
            call<tag::run_assign_( typename boost::proto::result_of::child_c<A0&, 0>::type
                                 , typename boost::proto::result_of::child_c<A0&, 1>::type
                                 )
                >::type                                        result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0) const
    {
      return nt2::run_assign(boost::proto::child_c<0>(a0), boost::proto::child_c<1>(a0));
    }
  };
} }

#endif
