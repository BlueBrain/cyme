#include <iostream>

#include "numeric/math/math.hpp"
#include "memory/block.hpp"

#include <stdlib.h>

int main(){

    memory::block<float,5, 3, memory::AoS> a;
    memory::block<float,5, 3, memory::AoSoA> b;

    srand(-1);

    for(int i=0; i< 3;++i)
       for(int j=0; j< 5;++j){
           a(i,j) = rand()%100;
           b(i,j) = a(i,j) ;
       }
    /*
   memory::block<float,5,3,memory::AoS>::iterator it_AoS = a.begin();
   for(; it_AoS != a.end(); ++it_AoS){
        numeric::add<float>((*it_AoS)[0],(*it_AoS)[1]);
        numeric::div<float>((*it_AoS)[2],(*it_AoS)[4]);
        numeric::div<float>((*it_AoS)[0],(*it_AoS)[2]);
   }
   */
   memory::block<float,5,3,memory::AoSoA>::iterator it_AoSoA = b.begin();
   for(; it_AoSoA != b.end(); ++it_AoSoA){
        numeric::div<float>((*it_AoSoA)[0],(*it_AoSoA)[1]);
        numeric::div<float>((*it_AoSoA)[2],(*it_AoSoA)[4]);
        numeric::div<float>((*it_AoSoA)[0],(*it_AoSoA)[2]);
   }
/*
    for(int i=0; i< 3;++i)
       for(int j=0; j< 5;++j){
           std::cout << a(i,j) << " " <<  b(i,j) << std::endl;
       }

*/

std::cout << " fini " << std::endl;

 //   memory::block<float,3,3,memory::AoS>::iterator itAoS1 =  a.begin();
 
  //  memory::block<float,2,3,memory::AoSoA>::iterator it1 =  b.begin();


 //   numeric::add<float,3>((*itAoS1)[0],(*itAoS1)[1]);
 //   numeric::mul<float,3>((*itAoS1)[0],(*itAoS1)[1]);


}
