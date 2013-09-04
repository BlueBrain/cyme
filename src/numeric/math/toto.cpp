#include <iostream>
#include "math.hpp"
#include "pow.hpp"

int main(){
    double a[2];
    double b[2] = {1,2};
    b = numeric::pow<numeric::vec<double>,3>(a);
}
