
#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>

#include <cyme/cyme.h>
#include "helpers.hpp"

int main() {

    //    int v = -3;           // we want to find the absolute value of v
    //    unsigned int r;  // the result goes here
    //    int const mask = v >> (sizeof(int) * 8  - 1); // CHAR_BIT is the number of bits per byte (normally 8).
    //    r = (v + mask) ^ mask;

    double data[8] __attribute__((aligned(16))) = {-1, 1, -1, 1, -1, 1, -1, 1};

    cyme::vec<int, cyme::sse, 4> a;

    cyme::vec<double, cyme::sse, 4> b(data);
    cyme::vec<double, cyme::sse, 4> zero;

    cyme::vec<double, cyme::sse, 4> mask;
    mask = b > zero;

    a = cyme::cyme_cast<int>(mask);

    return 0;
}
