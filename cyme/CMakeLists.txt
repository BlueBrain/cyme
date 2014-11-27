source_group(\\ FILES CMakeLists.txt)
set(CYME_LIBRARY_TYPE STATIC)
set(CYME_PUBLIC_HEADERS ${COMMON_INCLUDES} "instance/cyme_math.h"
                                           "cyme.hpp"
                                           "core/expression/expr_vec.hpp"
                                           "core/expression/expr_vec_fma.hpp"
                                           "core/expression/expr_vec_ops.hpp"
                                           "core/simd_vector/simd_math.hpp"
                                           "core/simd_vector/simd_vec.hpp"
                                           "core/simd_vector/simd_vec.ipp"
                                           "core/simd_vector/simd_wrapper.hpp"
                                           "core/simd_vector/trait.hpp"
                                           "core/simd_vector/detail/mic/simd_wrapper_mic.ipp"
                                           "core/simd_vector/detail/mic/trait_mic.ipp"
                                           "core/simd_vector/detail/powerpc64/simd_wrapper_qpx.ipp"
                                           "core/simd_vector/detail/powerpc64/trait_powerpc64.ipp"
                                           "core/simd_vector/detail/x86/simd_svml.hpp"
                                           "core/simd_vector/detail/x86/trait_x86.ipp"
                                           "core/simd_vector/detail/x86/simd_wrapper_avx.ipp"
                                           "core/simd_vector/detail/x86/simd_wrapper_sse.ipp"
                                           "core/simd_vector/math/simd_div.hpp"
                                           "core/simd_vector/math/simd_fma.hpp"
                                           "core/simd_vector/math/simd_log.hpp"
                                           "core/simd_vector/math/simd_neg.hpp"
                                           "core/simd_vector/math/simd_rec.hpp"
                                           "core/simd_vector/math/simd_sqrt.hpp"
                                           "core/simd_vector/math/simd_add.hpp"
                                           "core/simd_vector/math/simd_exp.hpp"
                                           "core/simd_vector/math/simd_fms.hpp"
                                           "core/simd_vector/math/simd_mul.hpp"
                                           "core/simd_vector/math/simd_pow.hpp"
                                           "core/simd_vector/math/simd_sub.hpp"
                                           "core/simd_vector/math/simd_recsqrt.hpp"
                                           "core/simd_vector/math/detail/remez.hpp"
                                           "memory/allocator.hpp"
                                           "memory/array.hpp"
                                           "memory/serial.hpp"
                                           "memory/vector.hpp"
                                           "memory/detail/array_helper.hpp"
                                           "memory/detail/simd.hpp"
                                           "memory/detail/storage.hpp"
                                           "memory/detail/storage.ipp"
    )
set(CYME_SOURCES ${COMMON_SOURCES} "instance/cyme.cpp") # math lib serial only

common_library(cyme)

if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "ppc64")
    set_target_properties(cyme PROPERTIES COMPILE_FLAGS "-D__CYME_SIMD_VALUE__=qpx -D__CYME_UNROLL_VALUE__=1 ${CYME_FMA_FLAGS}")
else()
    set_target_properties(cyme PROPERTIES COMPILE_FLAGS "-D__CYME_SIMD_VALUE__=sse -D__CYME_UNROLL_VALUE__=1 -msse4.1 ${CYME_FMA_FLAGS}")
endif()
