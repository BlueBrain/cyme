/*
 * Cyme - main_s.cpp, Copyright (c), 2014,
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

#include <algorithm>
#include <iostream>
#include <numeric>

#include <boost/chrono.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>

#include "helpers.hpp"
#include <cyme/cyme.h>

namespace ProbAMPANMDA_EMS {
enum properties {
    tau_r_AMPA,
    tau_d_AMPA,
    tau_r_NMDA,
    tau_d_NMDA,
    A_AMPA,
    B_AMPA,
    A_NMDA,
    B_NMDA,
    e,
    mg,
    i,
    i_AMPA,
    i_NMDA,
    g_AMPA,
    g_NMDA,
    g,
    v,
    _g
};

template <class T>
struct synapse {
    typedef T value_type;
    static const int value_size = 18;
};

template <class T>
static inline void cnrn_state(T &W) {
    T const &R = W;
    W[A_AMPA] += (1. - exp(-0.1 / R[tau_r_AMPA])) * (-R[A_AMPA]);
    W[B_AMPA] += (1. - exp(-0.1 / R[tau_d_AMPA])) * (-R[B_AMPA]);
    W[A_NMDA] += (1. - exp(-0.1 / R[tau_r_NMDA])) * (-R[A_NMDA]);
    W[B_NMDA] += (1. - exp(-0.1 / R[tau_d_NMDA])) * (-R[B_NMDA]);
}

template <class T>
static inline cyme::serial<typename T::value_type, T::MemoryOrder> cnrn_current(T &W, typename T::value_type t) {
    T const &R = W;
    typedef typename T::value_type value_type;
    W[v] = t;
    cyme::serial<value_type, T::MemoryOrder> gmax(1.1); // my value
    cyme::serial<value_type, T::MemoryOrder> mggate(1.0 / (1.0 + exp(-0.062 * R[v]) * (R[mg] / 3.57)));
    W[g_AMPA] = gmax() * (R[B_AMPA] - R[A_AMPA]);
    W[g_NMDA] = gmax() * (R[B_NMDA] - R[A_NMDA]) * mggate();
    W[g] = R[g_AMPA] + R[g_NMDA];
    W[i_AMPA] = R[g_AMPA] * (R[v] - R[e]);
    W[i_NMDA] = R[g_NMDA] * (R[v] - R[e]);
    W[i] = R[i_AMPA] + R[i_NMDA];
    return cyme::serial<value_type, T::MemoryOrder>(R[i]);
}

template <class T>
static inline void cnrn_cur(T &W) {
    typedef typename T::value_type value_type; // basic float or double
    value_type _v = drand48();                 // _v voltage fron a node random number
    value_type _nd_area = 3.1;
    cyme::serial<value_type, T::MemoryOrder> tmp = cnrn_current<T>(W, _v + 0.001);
    cyme::serial<value_type, T::MemoryOrder> tmp2 = cnrn_current<T>(W, _v);
    W[_g] = (tmp() - tmp2()) / 0.001 * (1.e2 / _nd_area);
}

template <class T>
struct f_compute_1 {
    void operator()(T &S) { cnrn_state(S); }
};

template <class T>
struct f_compute_2 {
    void operator()(T &S) { cnrn_cur(S); }
};
}

typedef cyme::vector<ProbAMPANMDA_EMS::synapse<float>, memory::AoS> Vec_f_AoS_ProbAMPANMDA_EMS;
typedef cyme::vector<ProbAMPANMDA_EMS::synapse<float>, memory::AoSoA> Vec_f_AoSoA_ProbAMPANMDA_EMS;
typedef cyme::vector<ProbAMPANMDA_EMS::synapse<double>, memory::AoS> Vec_d_AoS_ProbAMPANMDA_EMS;
typedef cyme::vector<ProbAMPANMDA_EMS::synapse<double>, memory::AoSoA> Vec_d_AoSoA_ProbAMPANMDA_EMS;

typedef boost::mpl::vector<Vec_f_AoS_ProbAMPANMDA_EMS, Vec_f_AoSoA_ProbAMPANMDA_EMS, Vec_d_AoS_ProbAMPANMDA_EMS,
                           Vec_d_AoSoA_ProbAMPANMDA_EMS>
    vector_list;

template <typename T>
struct name<ProbAMPANMDA_EMS::synapse<T>> {
    static const std::string print() {
        std::stringstream s;
        s << "ProbAMPANMDA_EMS::synapse<" << name<T>::print() << "\tby " << ProbAMPANMDA_EMS::synapse<T>::value_size
          << ">";
        return s.str();
    }
};

template <class T>
struct f_init {
    void operator()(typename T::storage_type &S) {
        for (std::size_t i = 0; i < T::size_block(); ++i)
            S[i] = drand48();
    }
};

#ifdef _OPENMP
template <typename Iterator, typename Functor>
Functor omp_for_each(Iterator first, Iterator last, Functor f) {
#pragma omp parallel for private(f)
    for (Iterator it = first; it < last; ++it) {
        f(*it);
    }

    return f;
}
#endif

struct test_case_1 {
    template <class T>
    void operator()(T const &) {
        int limit = 5;
        typedef typename T::storage_type storage_type;
        const std::size_t N(0xfffff);
        T v(N, 0);

#ifdef _OPENMP
        omp_for_each(v.begin(), v.end(), f_init<T>());
#else
        std::for_each(v.begin(), v.end(), f_init<T>());
#endif

        std::vector<double> v_time(limit, 0);

        timer t;
        for (int j = 0; j < limit; ++j) {
            t.tic();
#ifdef _OPENMP
            omp_for_each(v.begin(), v.end(), ProbAMPANMDA_EMS::f_compute_1<storage_type>());
#else
            std::for_each(v.begin(), v.end(), ProbAMPANMDA_EMS::f_compute_1<storage_type>());
#endif
            v_time[j] = t.toc();
        }
        average<T>(v_time);
    }
};

struct test_case_2 {
    template <class T>
    void operator()(T const &) {
        int limit = 5;
        typedef typename T::storage_type storage_type;
        const std::size_t N(0xfffff);
        T v(N, 0);

#ifdef _OPENMP
        omp_for_each(v.begin(), v.end(), f_init<T>());
#else
        std::for_each(v.begin(), v.end(), f_init<T>());
#endif

        std::vector<double> v_time(limit, 0);

        timer t;
        for (int j = 0; j < limit; ++j) {
            t.tic();
#ifdef _OPENMP
            omp_for_each(v.begin(), v.end(), ProbAMPANMDA_EMS::f_compute_2<storage_type>());
#else
            std::for_each(v.begin(), v.end(), ProbAMPANMDA_EMS::f_compute_2<storage_type>());
#endif
            v_time[j] = t.toc();
        }
        average<T>(v_time);
    }
};

int main() {
    std::cout << " cnrn_state " << std::endl;
    boost::mpl::for_each<vector_list>(test_case_1());
    std::cout << " cnrn_current " << std::endl;
    boost::mpl::for_each<vector_list>(test_case_2());
}
