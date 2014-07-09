#include <iostream>
#include <algorithm>
#include <numeric>

#include <boost/chrono.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>

#define BOOST_TEST_MODULE validty_test
#include <boost/test/unit_test.hpp>

#include "cyme/cyme.hpp"
#include "helpers.hpp"

namespace Na{
    enum properties {
        m, h, mInf, mTau, mAlpha, mBeta, hInf, hTau, hAlpha, hBeta, v
    };

    template<class T>
    struct channel{
        typedef T value_type;
        static const size_t value_size = 11;
    };

    template<class T>
    static inline void cnrn_rates(T& W){
        T const & R = W;
        W[mAlpha] = (0.182*(R[v]+35.0))/(1.-(exp((-35.0-R[v])/9.0)));
        W[mBeta]  = (-0.124*(R[v]+35.0))/(1.-(exp((R[v]+35.0)/9.0)));
        W[mInf]   = R[mAlpha]/(R[mAlpha]+R[mBeta]);
        W[mTau]   = 1./(R[mAlpha]+R[mBeta]);
        W[hAlpha] = (0.024*(R[v]+50.0))/(1.-(exp((-50.0-R[v])/5.0)));
        W[hBeta]  = (-0.0091*(R[v]+75.0))/(1.-(exp((R[v]+75.0)/5.0)));
        W[hInf]   = 1./(1.+exp((R[v]+65.0)/6.2));
        W[hTau]   = 1./(R[hAlpha]+R[hBeta]);
    };

    template<class T>
    static inline void cnrn_states(T& W){
        T const & R = W;
        cnrn_rates<T>(W);
        W[m] += (1.-exp(-0.1/R[mTau]))*(R[mInf]-R[m]);
        W[h] += (1.-exp(-0.1/R[hTau]))*(R[hInf]-R[h]);
    }

    template<class T>
    struct f_compute{
        void operator()(T& S ){
           cnrn_states(S);
        }
    };
}

typedef  cyme::vector<Na::channel<float>, memory::AoSoA> Vec_f_AoSoA_Na;
typedef  cyme::vector<Na::channel<double>, memory::AoSoA> Vec_d_AoSoA_Na;

typedef boost::mpl::vector<Vec_f_AoSoA_Na,Vec_d_AoSoA_Na> vector_list;

template<class T>
T relative_error();

template<>
float relative_error(){return 0.1;}

template<>
double relative_error(){return 0.001;}

template<class T1, class T2>
void f_init(T1& block_a, T2& block_b){
    for(size_t i=0; i<block_a.size(); ++i)
        for(size_t j=0; j<block_a.size_block(); ++j){
            typename T1::value_type random = 10*drand48();
            block_a(i,j) = random;
            block_b(i,j) = random;
        }
}

template<class T1, class T2>
void f_check(T1& block_a, T2& block_b){
    for(size_t i=0; i<block_a.size(); ++i)
        for(size_t j=0; j<block_a.size_block(); ++j)
            BOOST_REQUIRE_CLOSE(block_a(i,j),block_b(i,j),relative_error<typename T1::value_type>());
}

#ifdef _OPENMP
template<typename Iterator, typename Functor>
Functor
omp_for_each(Iterator first, Iterator last, Functor f) {
    #pragma omp parallel for private(f)
    for(Iterator it=first; it<last; ++it)
        f(*it);
    return f;
}
#endif

struct test_case{

    template <class T>
    void operator()(T const&){
        typedef typename T::storage_type storage_type;
        typedef typename storage_type::value_type value_type;
        const std::size_t N(0xffff);
        T Vec_AoSoA_Na(N,0); // vector AoSoA from the boost mpl
        cyme::vector<Na::channel<value_type>, memory::AoS> Vec_AoS_Na(N,0); // AoS - serial version
        f_init(Vec_AoSoA_Na,Vec_AoS_Na);
        std::for_each(Vec_AoSoA_Na.begin(), Vec_AoSoA_Na.end(), Na::f_compute<storage_type>() ); //AoSoS compute
        std::for_each(Vec_AoS_Na.begin(), Vec_AoS_Na.end(), Na::f_compute<typename cyme::vector<Na::channel<value_type>, memory::AoS>::storage_type>() ); //AoS compute
        f_check(Vec_AoSoA_Na,Vec_AoS_Na); //check with an epsilon
    }
};

BOOST_AUTO_TEST_CASE(Na_test){
     boost::mpl::for_each<vector_list>(test_case());
}
