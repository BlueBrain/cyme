#include <iostream>
#include <algorithm>
#include <numeric>

#include <boost/chrono.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>

#include "cyme/cyme.hpp"

//#include "iacaMarks.h"
namespace ProbAMPANMDA_EMS{
    enum properties {
        tau_r_AMPA, tau_d_AMPA, tau_r_NMDA, tau_d_NMDA, A_AMPA, B_AMPA, A_NMDA, B_NMDA, e, mg, i, i_AMPA, i_NMDA, g_AMPA, g_NMDA, g, v, _g
    };

    template<class T>
    struct synapse{
        typedef T value_type;
        static const int value_size = 18;
    };

    template<class T>
    static inline void cnrn_state(T& S){
        S[A_AMPA] += (1.-exp(-0.1/S[tau_r_AMPA]))*(-S[A_AMPA]);
        S[B_AMPA] += (1.-exp(-0.1/S[tau_d_AMPA]))*(-S[B_AMPA]);
        S[A_NMDA] += (1.-exp(-0.1/S[tau_r_NMDA]))*(-S[A_NMDA]);
        S[B_NMDA] += (1.-exp(-0.1/S[tau_d_NMDA]))*(-S[B_NMDA]);
    }

    template<class T>
    static inline  cyme::serial<typename T::value_type,T::MemoryOrder> cnrn_current( T& S,typename T::value_type t){
        typedef typename T::value_type value_type;
        S[v] = t;
        cyme::serial<value_type,T::MemoryOrder> gmax(1.1); // my value
        cyme::serial<value_type,T::MemoryOrder> mggate(1.0/(1.0+exp(-0.062*S[v])*(S[mg]/3.57)));
        S[g_AMPA] = gmax() * (S[B_AMPA] - S[A_AMPA]);
        S[g_NMDA] = gmax() * (S[B_NMDA] - S[A_NMDA]) * mggate();
        S[g] = S[g_AMPA] + S[g_NMDA];
        S[i_AMPA] = S[g_AMPA]*(S[v]-S[e]);
        S[i_NMDA] = S[g_NMDA]*(S[v]-S[e]);
        S[i] = S[i_AMPA]+S[i_NMDA];
        return cyme::serial<value_type,T::MemoryOrder>(S[i]);
    }

    template<class T>
    static inline void cnrn_cur(T& S){
        typedef typename T::value_type value_type; //basic float or double
        value_type _v = drand48(); // _v voltage fron a node random number
        value_type _nd_area=3.1;
        cyme::serial<value_type,T::MemoryOrder> tmp  = cnrn_current<T>(S,_v + 0.001);
        cyme::serial<value_type,T::MemoryOrder> tmp2 = cnrn_current<T>(S,_v);
        S[_g] = (tmp()-tmp2())/0.001*(1.e2/_nd_area);
    }

    template<class T>
    struct f_compute_1{
        void operator()(T& S ){
           cnrn_state(S);
        }
    };

    template<class T>
    struct f_compute_2{
        void operator()(T& S ){
           cnrn_cur(S);
        }
    };
}

typedef  cyme::vector<ProbAMPANMDA_EMS::synapse<float>, memory::AoS> Vec_f_AoS_ProbAMPANMDA_EMS;
typedef  cyme::vector<ProbAMPANMDA_EMS::synapse<float>, memory::AoSoA> Vec_f_AoSoA_ProbAMPANMDA_EMS;
typedef  cyme::vector<ProbAMPANMDA_EMS::synapse<double>, memory::AoS> Vec_d_AoS_ProbAMPANMDA_EMS;
typedef  cyme::vector<ProbAMPANMDA_EMS::synapse<double>, memory::AoSoA> Vec_d_AoSoA_ProbAMPANMDA_EMS;

typedef boost::mpl::vector<Vec_f_AoS_ProbAMPANMDA_EMS, Vec_f_AoSoA_ProbAMPANMDA_EMS,Vec_d_AoS_ProbAMPANMDA_EMS, Vec_d_AoSoA_ProbAMPANMDA_EMS> vector_list;

template<class T>
struct f_init{
    void operator()(typename T::storage_type& S ){
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
void average(std::vector<T> &v_time){
        T sum = std::accumulate(v_time.begin(), v_time.end(), 0.0);
        T mean = sum / v_time.size();
        T sq_sum = std::inner_product(v_time.begin(), v_time.end(), v_time.begin(), 0.0);
        T stdev = std::sqrt(sq_sum / v_time.size() - mean * mean);
        std::cout << "float: " << sizeof(T) << "[Byte], "  << " mean " << mean << " [s], stdev " << stdev << std::endl;
}

struct test_case_1{
    template <class T>
    void operator()(T const&){
        int limit = 10;
        typedef typename T::storage_type storage_type;
        const std::size_t N(0xfffff);
        T v(N,0);

#ifdef _OPENMP
        omp_for_each(v.begin(), v.end(), f_init<T>() );
#else
        std::for_each(v.begin(), v.end(), f_init<T>() );
#endif

        std::vector<double> v_time(limit,0);

        for(int j=0; j < limit; ++j){
            boost::chrono::system_clock::time_point start =  boost::chrono::system_clock::now();
#ifdef _OPENMP
            omp_for_each(v.begin(), v.end(), ProbAMPANMDA_EMS::f_compute_1<storage_type>() );
#else
            std::for_each(v.begin(), v.end(), ProbAMPANMDA_EMS::f_compute_1<storage_type>() );
#endif
            boost::chrono::duration<double>  sec = boost::chrono::system_clock::now() - start;
            v_time[j] = sec.count();
        }
        average<double>(v_time);
    }
};


struct test_case_2{
    template <class T>
    void operator()(T const&){
        int limit = 10;
        typedef typename T::storage_type storage_type;
        const std::size_t N(0xfffff);
        T v(N,0);

#ifdef _OPENMP
        omp_for_each(v.begin(), v.end(), f_init<T>() );
#else
        std::for_each(v.begin(), v.end(), f_init<T>() );
#endif

        std::vector<double> v_time(limit,0);

        for(int j=0; j < limit; ++j){
            boost::chrono::system_clock::time_point start =  boost::chrono::system_clock::now();
#ifdef _OPENMP
            omp_for_each(v.begin(), v.end(), ProbAMPANMDA_EMS::f_compute_2<storage_type>() );
#else
            std::for_each(v.begin(), v.end(), ProbAMPANMDA_EMS::f_compute_2<storage_type>() );
#endif
            boost::chrono::duration<double>  sec = boost::chrono::system_clock::now() - start;
            v_time[j] = sec.count();
        }
        average<double>(v_time);
    }
};


int main(){
     std::cout << " cnrn_state " << std::endl;
     boost::mpl::for_each<vector_list>(test_case_1());
     std::cout << " cnrn_current " << std::endl;
     boost::mpl::for_each<vector_list>(test_case_2());
}
