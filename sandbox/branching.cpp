
#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>

#include <cyme/cyme.h>
#include "helpers.hpp"

int main() {

    int data[8] __attribute__((aligned(32))) = {-1, 1, -2, 3, 4, 5, 6, 7};

    cyme::vec<double> a;

    cyme::vec<int> b(data);
    cyme::vec<int> zero;

    cyme::vec<int> mask;
    mask = b > zero;

    a = cyme::cyme_cast<double>(mask);

    return 0;
}
