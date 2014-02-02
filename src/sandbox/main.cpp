#include <iostream>
#include <algorithm>
#include <boost/chrono.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>

#include "cyme/cyme.hpp"

#include "iacaMarks.h"

template<class T>
struct synapse{
    typedef T value_type;
    static const int value_size = 18;
};

template<class T>
static inline void cnrn_rates(typename T::storage_type& S){
    S[8]  = (0.182*(S[16]+35.0)) / (1.-(exp((-35.0 - S[16])/9.0)));
    S[9]  = (-0.124*(S[16]+35.0))/ (1.-(exp((S[16]+35.0)/9.0)));
    S[6]  = S[8]/(S[8]+S[9]);
    S[7]  = 1./(S[8]+S[9]);
    S[12] = (0.024*(S[16]+50.0))  /(1.-(exp((-50.0 -S[16])/5.0)));
    S[13] = (-0.0091*(S[16]+75.0))/(1.-(exp((S[16]+75.0)/5.0)));
    S[10] = 1./(1.+exp((S[16]+65.0)/6.2));
    S[11] = 1./(S[12]+S[13]);
};

template<class T>
static inline void cnrn_states(typename T::storage_type& S){
    typedef typename T::value_type value_type; //basic float or double
    cnrn_rates<T>(S);
    IACA_START
    S[3] += (1.-exp(0.1*(-1./S[7] )))*((S[6] /S[7]) /(1./S[7]) -S[3]);
    S[4] += (1.-exp(0.1*(-1./S[11])))*((S[10]/S[11])/(1./S[11])-S[4]);
    IACA_END
}

template<class T>
struct f_compute{
    void operator()(typename T::storage_type& S ){
       cnrn_states<T>(S); 
    }
};

template<class T>
struct f_init{
    void operator()(typename T::storage_type& S ){
        for(int i=0;i <T::size_block(); ++i)
            S[i] = drand48();
    }
};

typedef  cyme::vector<synapse<float>, memory::AoS> Vec_f_AoS;
typedef  cyme::vector<synapse<float>, memory::AoSoA> Vec_f_AoSoA;
typedef  cyme::vector<synapse<double>, memory::AoS> Vec_d_AoS;
typedef  cyme::vector<synapse<double>, memory::AoSoA> Vec_d_AoSoA; 

typedef  cyme::array<synapse<float>, 128,memory::AoS> Ar_f_AoS;
typedef  cyme::array<synapse<float>, 128,memory::AoSoA> Ar_f_AoSoA;
typedef  cyme::array<synapse<double>, 128,memory::AoS> Ar_d_AoS;
typedef  cyme::array<synapse<double>, 128,memory::AoSoA> Ar_d_AoSoA;


typedef boost::mpl::vector< Vec_f_AoS, Vec_f_AoSoA, Vec_d_AoS, Vec_d_AoSoA > vector_list;
//typedef boost::mpl::vector< Ar_f_AoS, Ar_f_AoSoA, Ar_d_AoS, Ar_d_AoSoA > vector_list;

//typedef boost::mpl::vector<Vec_d_AoSoA > vector_list;

struct test_case{

    template <class T>
    void operator()(T const&){

        T v(0xffffff,0);
        std::for_each(v.begin(), v.end(), f_init<T>() );
        
        boost::chrono::system_clock::time_point start =  boost::chrono::system_clock::now();
            std::for_each(v.begin(), v.end(), f_compute<T>() );
        boost::chrono::duration<double>  sec = boost::chrono::system_clock::now() - start;
        
        std::cout << "float: " << sizeof(typename T::value_type) << "[Byte], "  << " sec " << sec.count() << std::endl;
    }
};


int main(int argc, char* argv[]){
     boost::mpl::for_each<vector_list>(test_case());
}
