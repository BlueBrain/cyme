#include <iostream>

#include "memory/block.hpp"

int main(){

    memory::block<double,8, 15, memory::AoS> a;
    memory::block<double,8, 15, memory::AoSoA> b;

    a(7,4) = 3.14;
    b(7,4) = 3.14;


    std::cout << "sdgags" << std::endl;
}
