#pragma once

#include <vector>
#include <sstream>

template<typename T>
struct name {
    static const std::string print() {
        return "unknown";
    }
};

template<>
struct name<float> {
    static const std::string print() {
        return "float";
    }
};

template<>
struct name<double> {
    static const std::string print() {
        return "double";
    }
};

template<typename T>
struct name<cyme::vector<T, memory::AoS> > {
    static const std::string print() {
        std::stringstream s;
        s << "cyme::vector<" << name<T>::print() << ",\tAoS>";
        return s.str();
    }
};

template<typename T>
struct name<cyme::vector<T, memory::AoSoA> > {
    static const std::string print() {
        std::stringstream s;
        s << "cyme::vector<" << name<T>::print() << ",\tAoSoA>";
        return s.str();
    }
};

template<class T>
void average(std::vector<double> &v_time){
        double sum = std::accumulate(v_time.begin(), v_time.end(), 0.0);
        double mean = sum / v_time.size();
        double sq_sum = std::inner_product(v_time.begin(), v_time.end(), v_time.begin(), 0.0);
        double stdev = std::sqrt(sq_sum / v_time.size() - mean * mean);
        std::cout << "\t" << name<T>::print()  << "\tmean " << mean << " [s], stdev " << stdev << std::endl;
}

// wrapper around boost::chrono timers
class timer {
    public:
    typedef boost::chrono::duration<double> duration_type;
    typedef boost::chrono::system_clock::time_point point_type;
    void tic() {
        start_ = boost::chrono::system_clock::now();
    }
    double toc() {
        sec_ = boost::chrono::system_clock::now() - start_;
        return sec_.count();
    }

    private:
    point_type start_;
    duration_type sec_;
};
