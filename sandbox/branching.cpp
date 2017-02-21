
#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>

#include <cyme/cyme.h>
#include "helpers.hpp"

int main() {

    cyme::vec<float> a(6.);
    cyme::vec<int> b(5.);

    b = cyme::cyme_cast<int>(a);


    return 0;
}
