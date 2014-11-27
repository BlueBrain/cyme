source_group(\\ FILES CMakeLists.txt)
set(CYME_LIBRARY_TYPE STATIC)
set(CYME_PUBLIC_HEADERS ${COMMON_INCLUDES} 
                                           "memory/detail/simd.hpp"
                                           "core/simd_vector/trait.hpp"
                                           "core/simd_vector/simd_math.ipp"
                                           "core/simd_vector/simd_vec.hpp"
                                           "core/simd_vector/simd_vec.ipp"
                                           "core/simd_vector/simd_wrapper.hpp"
                                           "core/simd_vector/detail/mic/simd_wrapper_mic.ipp"
                                           "core/simd_vector/detail/mic/trait_mic.ipp"
                                           "core/simd_vector/detail/powerpc64/simd_wrapper_qpx.ipp"
                                           "core/simd_vector/detail/powerpc64/trait_powerpc64.ipp"
                                           "core/simd_vector/detail/x86/simd_svml.ipp"
                                           "core/simd_vector/detail/x86/trait_x86.ipp"
                                           "core/simd_vector/detail/x86/simd_wrapper_avx.ipp"
                                           "core/simd_vector/detail/x86/simd_wrapper_sse.ipp"
                                           "core/simd_vector/math/simd_div.ipp"
                                           "core/simd_vector/math/simd_fma.ipp"
                                           "core/simd_vector/math/simd_log.ipp"
                                           "core/simd_vector/math/simd_neg.ipp"
                                           "core/simd_vector/math/simd_rec.ipp"
                                           "core/simd_vector/math/simd_sqrt.ipp"
                                           "core/simd_vector/math/simd_add.ipp"
                                           "core/simd_vector/math/simd_exp.ipp"
                                           "core/simd_vector/math/simd_fms.ipp"
                                           "core/simd_vector/math/simd_mul.ipp"
                                           "core/simd_vector/math/simd_pow.ipp"
                                           "core/simd_vector/math/simd_sub.ipp"
                                           "core/simd_vector/math/simd_recsqrt.ipp"
                                           "core/simd_vector/math/detail/remez.ipp"
                                           "core/expression/expr_vec.hpp"
                                           "core/expression/expr_vec_fma.ipp"
                                           "core/expression/expr_vec_ops.ipp"
                                           "memory/allocator.hpp"
                                           "memory/array.hpp"
                                           "memory/serial.hpp"
                                           "memory/vector.hpp"
                                           "memory/detail/array_helper.ipp"
                                           "memory/detail/storage.hpp"
                                           "memory/detail/storage.ipp"
                                           "instance/math.h"
                                           "instance/instance.h"     )
set(CYME_SOURCES ${COMMON_SOURCES} "instance/cyme.cpp") # math lib serial only

common_library(cyme)

if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "ppc64")
    set_target_properties(cyme PROPERTIES COMPILE_FLAGS "-D__CYME_SIMD_VALUE__=qpx -D__CYME_UNROLL_VALUE__=1 ${CYME_FMA_FLAGS}")
else()
    set_target_properties(cyme PROPERTIES COMPILE_FLAGS "-D__CYME_SIMD_VALUE__=sse -D__CYME_UNROLL_VALUE__=1 -msse4.1 ${CYME_FMA_FLAGS}")
endif()
