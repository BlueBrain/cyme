#include <iostream>
#include <algorithm>
#include <numeric>

#include <boost/chrono.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>

#include "cyme/cyme.hpp"

//#include "iacaMarks.h"
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
    static inline void cnrn_rates(T& C){
//      cyme::serial<typename T::value_type, memory::AoSoA> tmp(exp((C[v]+35.0f)/9.0f));
//      C[mAlpha] = (0.182*(C[v]+35.0))/(1.-(1./tmp()));
//      C[mBeta]  = (-0.124*(C[v]+35.0))/(1.-tmp());
        C[mAlpha] = (0.182*(C[v]+35.0))/(1.-(exp((-35.0-C[v])/9.0)));
        C[mBeta]  = (-0.124*(C[v]+35.0))/(1.-(exp((C[v]+35.0)/9.0)));
        C[mInf]   = C[mAlpha]/(C[mAlpha]+C[mBeta]);
        C[mTau]   = 1./(C[mAlpha]+C[mBeta]);
        C[hAlpha] = (0.024*(C[v]+50.0))/(1.-(exp((-50.0-C[v])/5.0)));
        C[hBeta]  = (-0.0091*(C[v]+75.0))/(1.-(exp((C[v]+75.0)/5.0)));
        C[hInf]   = 1./(1.+exp((C[v]+65.0)/6.2));
        C[hTau]   = 1./(C[hAlpha]+C[hBeta]);
    };

    template<class T>
    static inline void cnrn_states(T& C){
        cnrn_rates<T>(C);
        C[m] += (1.-exp(-0.1/C[mTau]))*(C[mInf]-C[m]);
        C[h] += (1.-exp(-0.1/C[hTau]))*(C[hInf]-C[h]);
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
//2567
template<class T>
const std::string name();

template<>
const std::string name<float>(){return "float";}

template<>
const std::string name<double>(){return "double";}

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
    for(Iterator it=first; it<last; ++it) {
        f(*it);
    }

    return f;
}
#endif

template<class T>
void average(std::vector<double> &v_time){
        double sum = std::accumulate(v_time.begin(), v_time.end(), 0.0);
        double mean = sum / v_time.size();
        double sq_sum = std::inner_product(v_time.begin(), v_time.end(), v_time.begin(), 0.0);
        double stdev = std::sqrt(sq_sum / v_time.size() - mean * mean);
        std::cout << name<T>()  << " mean " << mean << " [s], stdev " << stdev << std::endl;
}

struct test_case{

    template <class T>
    void operator()(T const&){
        int limit = 10;
        typedef typename T::storage_type storage_type;
        typedef typename storage_type::value_type value_type;
        const std::size_t N(0xffffff);
        T v(N,0);

#ifdef _OPENMP
        omp_for_each(v.begin(), v.end(), f_init<T>() );
#else
        std::for_each(v.begin(), v.end(), f_init<T>() );
#endif

        std::vector<double> v_time(limit,0);

        for(int i=0; i < limit; ++i){
            boost::chrono::system_clock::time_point start =  boost::chrono::system_clock::now();
#ifdef _OPENMP
            omp_for_each(v.begin(), v.end(), Na::f_compute<storage_type>() );
#else
            std::for_each(v.begin(), v.end(), Na::f_compute<storage_type>() );
#endif
            boost::chrono::duration<double>  sec = boost::chrono::system_clock::now() - start;
            v_time[i] = sec.count();
        }
        average<value_type>(v_time);
    }
};

int main(){
     boost::mpl::for_each<vector_list>(test_case());
}
