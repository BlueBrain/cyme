
#include <iostream>

#include "cyme/cyme.hpp"

//#include "iacaMarks.h"

#include <boost/chrono.hpp>

#include <algorithm>

template<class T>
struct synapse{
    typedef T value_type;
    static const int value_size = 18;
};

template<class Ba>
void init(Ba& block_a){
    for(int i=0; i<block_a.size(); ++i)
        for(int j=0; j<block_a.size_block(); ++j){
            typename Ba::value_type random = -100*drand48();
            block_a(i,j) = random;
        }
}

template<class T>
struct functor{
    void operator()(typename T::storage_type& S ){
         S[0] = exp(S[1])*S[2]+S[3]/1.2;
    }
};


int main(int argc, char* argv[]){

    typedef  cyme::vector<synapse<float>, memory::AoSoA> my_vector;
    my_vector b(0xfffff,0);

    init(b);

    boost::chrono::system_clock::time_point start =  boost::chrono::system_clock::now();
    std::for_each(b.begin(), b.end(), functor<my_vector>() );
    std::fill(b.begin(), b.end(),3.0 );
    std::generate(b.begin(), b.end(), std::rand );


// C++11 version - std::for_each(b.begin(), b.end(), [](my_vector::storage_type& S){S[0] = exp(S[1])*S[2]+S[3]/1.2; } );


    boost::chrono::duration<double>  sec = boost::chrono::system_clock::now() - start;
    std::cout << " sec " << sec.count() << std::endl;

}
