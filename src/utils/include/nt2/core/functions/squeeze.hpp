//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SQUEEZE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SQUEEZE_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::squeeze function
 */

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/reshaping.hpp>
#include <nt2/sdk/meta/reshaping_hierarchy.hpp>

namespace nt2
{
  namespace tag
  {
    struct squeeze_ : ext::reshaping_<squeeze_>
    {
      typedef ext::reshaping_<squeeze_> parent;
    };
  }

  //============================================================================
  /*!
   * squeeze an expression by removing its singleton dimensions
   *
   * \param xpr   Expression to squeeze
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::squeeze_, squeeze, 1)
}

//==============================================================================
// Setup squeeze generator traits
//==============================================================================
namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct size_of<nt2::tag::squeeze_,Domain,N,Expr>
  {
    typedef typename  boost::proto::result_of
                      ::child_c<Expr&,0>::value_type::extent_type result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee;
      result_type ex = boost::proto::child_c<0>(e).extent();

      // Squeeze don't affect 2D array
      if(result_type::static_size <= 2)
      {
        sizee = ex;
      }
      else
      {
        // Copy non singleton dimensions
        std::size_t u = 0;
        for(std::size_t i=0;i<result_type::static_size;++i)
        {
          if(ex[i] != 1) { sizee[u] = ex[i]; ++u; }
        }

        // Ensure non-empty size
        sizee[0] = sizee[0] ? sizee[0] : 1;
      }

      return sizee;
    }
  };

} }

#endif
