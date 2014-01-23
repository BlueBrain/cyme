#include <iostream>
#include <algorithm>
#include <boost/chrono.hpp>

#include "cyme/cyme.hpp"

//#include "iacaMarks.h"

template<class T>
struct synapse{
    typedef T value_type;
    static const int value_size = 18;
};

template<class T>
struct f_compute{
    void operator()(typename T::storage_type& S ){
         S[0] = exp(S[1])*S[2]+exp(S[3])/1.2;
    }
};

template<class T>
struct f_init{
    void operator()(typename T::storage_type& S ){
        for(int i=0;i <T::size_block(); ++i)
            S[i] = drand48();
    }
};

int main(int argc, char* argv[]){

    typedef  cyme::vector<synapse<float>, memory::AoSoA> my_vector;
    my_vector b(0xfffff,0);
    std::for_each(b.begin(), b.end(), f_init<my_vector>() );

    boost::chrono::system_clock::time_point start =  boost::chrono::system_clock::now();
        std::for_each(b.begin(), b.end(), f_compute<my_vector>() );
    boost::chrono::duration<double>  sec = boost::chrono::system_clock::now() - start;

    std::cout << " sec " << sec.count() << std::endl;
}

// C++11 version 
// std::for_each(b.begin(), b.end(), [](my_vector::storage_type& S){S[0] = exp(S[1])*S[2]+S[3]/1.2; } );
