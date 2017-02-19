
#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>

#include <cyme/cyme.h>
#include "helpers.hpp"

int main() {

    cyme::vec<float> a(6.);
    cyme::vec<float> b(5.);

    if ((a < b).is_empty())
        std::cout << " full of 0 ";
    else
        std::cout << " I do not know ";

    cyme::vec<float> c;
    c = min(a, b);

    return 0;
}
