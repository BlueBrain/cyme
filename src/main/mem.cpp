#include <iostream>

#include "memory/block.hpp"

int main(){

    memory::block<double,5, 5, memory::AoS> a;
    memory::block<double,5, 5, memory::AoSoA> b;

    a(2,3) = 3.14;
    b(2,3) = 3.14;


    std::cout << "sdgags" << std::endl;
}
