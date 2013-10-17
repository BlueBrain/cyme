//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_CONFIG_DETAILS_POWERPC_SUPPORT_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_DETAILS_POWERPC_SUPPORT_HPP_INCLUDED

namespace boost { namespace simd { namespace details
{
  // register detection of VMX extensions
  support_registration ppc_vmx( "vmx"
                              , &boost::simd::is_supported<tag::altivec_>
                              , &registration_list
                              );

} } }

#endif
