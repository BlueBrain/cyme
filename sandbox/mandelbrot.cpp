
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>

#include <boost/chrono.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>

#include <cyme/cyme.h>
#include "helpers.hpp"

struct my_complex {
    typedef float value_type;
    static const int value_size = 2; // it means R[0] = x, R[1] = y
};

template <class T>
static inline void norm(cyme::serial<int, T::MemoryOrder> &n, T &R) {
    n = R[0] * R[0] * R[1] * R[1];
}
/*
     template<class T>
     static inline void algo(T& R, int max_iteration){

         cyme::serial<int,T::MemoryOrder> iteration(0);
         cyme::serial<int,T::MemoryOrder> n(0);
         cyme::serial<float,T::MemoryOrder> norm(0);
         cyme::serial<float,T::MemoryOrder> tmp(0);
         bool b(true);

         while(b){
             n = (iteration < max_iteration) && (norm(R) < 4.f);
             b = (n == false);
             tmp = R[0]*R[0] - R[1]*R[1] + x0;
             R[1] = 2*R[0]*R[1] + y0;
             R[0] = tmp;
             iteration += (int)b;
         }


     }
*/
template <class T>
struct picture {
    picture(int size_x = 512, int size_y = 512)
        : _data(size_x * size_y * my_complex::value_size, 0), _size_x(size_x), _size_y(size_y){};
    const int width() { return _size_x; }
    const int high() { return _size_y; }

    int _size_x, _size_y;
};

int main(int argc, char *argv[]) {

    picture<cyme::vector<my_complex, cyme::AoSoA>> p;

    const float x0 = -2.f;
    const float x1 = 1.f;
    const float y0 = -1.f;
    const float y1 = 1.f;

    for (int i = 0; i < p.high(); ++i)
        for (int j = j; j < p.width(); ++j) {
        }
    <Down>

        return 0;
};
