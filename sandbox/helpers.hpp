/*
 * Cyme - helpers.hpp, Copyright (c), 2014,
 * Timothee Ewart - Swiss Federal Institute of technology in Lausanne,
 * timothee.ewart@epfl.ch,
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3.0 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.
 */

#pragma once

#include <sstream>
#include <vector>
#include <chrono>

template <typename T>
struct name {
    static const std::string print() { return "unknown"; }
};

template <>
struct name<float> {
    static const std::string print() { return "float"; }
};

template <>
struct name<double> {
    static const std::string print() { return "double"; }
};

template <typename T>
struct name<cyme::vector<T, cyme::AoS>> {
    static const std::string print() {
        std::stringstream s;
        s << "cyme::vector<" << name<T>::print() << ",\tAoS>";
        return s.str();
    }
};

template <typename T>
struct name<cyme::vector<T, cyme::AoSoA>> {
    static const std::string print() {
        std::stringstream s;
        s << "cyme::vector<" << name<T>::print() << ",\tAoSoA>";
        return s.str();
    }
};

template <class T>
void average(std::vector<double> &v_time) {
    double sum = std::accumulate(v_time.begin(), v_time.end(), 0.0);
    double mean = sum / v_time.size();
    double sq_sum = std::inner_product(v_time.begin(), v_time.end(), v_time.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / v_time.size() - mean * mean);
    std::cout << "\t" << name<T>::print() << "\tmean " << mean << " [s], stdev " << stdev << std::endl;
}

// wrapper around std::chrono timers
class timer {
  public:
    typedef std::chrono::duration<double> duration_type;
    typedef std::chrono::system_clock::time_point point_type;
    void tic() { start_ = std::chrono::system_clock::now(); }
    double toc() {
        sec_ = std::chrono::system_clock::now() - start_;
        return sec_.count();
    }

  private:
    point_type start_;
    duration_type sec_;
};
