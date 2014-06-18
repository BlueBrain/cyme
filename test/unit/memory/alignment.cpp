
#include <test/unit/test_header.hpp>
#include <vector>

#include "memory/allocator.hpp" 

using namespace cyme::test;

BOOST_AUTO_TEST_CASE_TEMPLATE(alignement_test, T, full_test_types)
{
    std::vector<T, memory::Allocator<T, memory::Align_POSIX<memory::__CYME_SIMD_VALUE__ > > > simd_vec(128);
    boost::uint64_t align = memory::__CYME_SIMD_VALUE__ ;
    boost::uint64_t adress = (boost::uint64_t)(const void* )(&simd_vec[0]); // convert the adress to a real number, and I calculate the rest, it should be zero c++11 -> (uintptr_t)ptr
    boost::uint64_t res = adress%align; // should be a multiple of the alignment
    BOOST_CHECK_EQUAL(res,0);
}
