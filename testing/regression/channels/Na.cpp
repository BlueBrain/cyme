#include <iostream>
#include <algorithm>
#include <numeric>

#include <boost/chrono.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>

#include "cyme/cyme.hpp"
#include "helpers.hpp"

namespace Na{
    enum properties {
        m, h, mInf, mTau, mAlpha, mBeta, hInf, hTau, hAlpha, hBeta, v
    };

    template<class T>
    struct channel{
        typedef T value_type;
        static const int value_size = 11;
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

typedef  cyme::vector<Na::channel<float>, memory::AoS> Vec_f_AoS_Na;
typedef  cyme::vector<Na::channel<float>, memory::AoSoA> Vec_f_AoSoA_Na;
typedef  cyme::vector<Na::channel<double>, memory::AoS> Vec_d_AoS_Na;
typedef  cyme::vector<Na::channel<double>, memory::AoSoA> Vec_d_AoSoA_Na;

typedef boost::mpl::vector<Vec_f_AoS_Na,Vec_f_AoSoA_Na,Vec_d_AoS_Na,Vec_d_AoSoA_Na> vector_list;

template<typename T>
struct name<Na::channel<T> > {
    static const std::string print() {
        std::stringstream s;
        s << "Na::channel<" << name<T>::print()
          << " by " << Na::channel<T>::value_size
          << ">";
        return s.str();
    }
};

template<class T>
struct f_init{
    void operator()(typename T::storage_type& S){
      for(std::size_t i=0;i <T::size_block(); ++i)
          S[i] = drand48();
    }
};

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
        int limit = 4;
        typedef typename T::storage_type storage_type;
        typedef typename storage_type::value_type value_type;
        const std::size_t N(0xffff);
        T v(N,0);

#ifdef _OPENMP
        omp_for_each(v.begin(), v.end(), f_init<T>() );
#else
        std::for_each(v.begin(), v.end(), f_init<T>() );
#endif

        std::vector<double> v_time(limit,0);

        timer t;
        for(int i=0; i < limit; ++i){
            t.tic();
#ifdef _OPENMP
            omp_for_each(v.begin(), v.end(), Na::f_compute<storage_type>() );
#else
            std::for_each(v.begin(), v.end(), Na::f_compute<storage_type>() );
#endif
            v_time[i] = t.toc();
        }
        average<T>(v_time);
    }
};

int main(){
     boost::mpl::for_each<vector_list>(test_case());
     return 0;
}
