#include <iostream>
//#include <cstdint>
#include <emmintrin.h>

template<std::size_t n>
inline std::size_t factorial(){
    return n*factorial<n-1>();
}

template<>
inline std::size_t factorial<0>(){
    return 1;
}

template <typename T> struct simd_trait{};

template <>
struct simd_trait<float>{
    typedef float  value_type; 
    typedef __m128 register_type;
};

template <>
struct simd_trait<double>{
    typedef double value_type; 
    typedef __m128d register_type;
};

template<class T>
inline typename simd_trait<T>::register_type _mm_load1(typename simd_trait<T>::register_type xmm0, const typename simd_trait<T>::value_type a);

template<class T>
inline typename simd_trait<T>::register_type _mm_load(typename simd_trait<T>::register_type xmm0, const typename simd_trait<T>::value_type* a);

template<class T>
inline typename simd_trait<T>::register_type _mm_mul(typename simd_trait<T>::register_type xmm0, typename simd_trait<T>::register_type xmm1);

template<class T>
inline typename simd_trait<T>::register_type _mm_div(typename simd_trait<T>::register_type xmm0, typename simd_trait<T>::register_type xmm1);

template<class T>
inline typename simd_trait<T>::register_type _mm_add(typename simd_trait<T>::register_type xmm0, typename simd_trait<T>::register_type xmm1);


template<>
inline typename simd_trait<double>::register_type _mm_load1<double>(typename simd_trait<double>::register_type xmm0, const typename simd_trait<double>::value_type a){
    return (xmm0 =_mm_load1_pd(&a)); 
}

template<>
inline typename simd_trait<double>::register_type _mm_load<double>(typename simd_trait<double>::register_type xmm0, const typename simd_trait<double>::value_type* a){
    return (xmm0 =_mm_load_pd(a)); 
}

template<>
inline typename simd_trait<double>::register_type _mm_mul<double>(typename simd_trait<double>::register_type xmm0, typename simd_trait<double>::register_type xmm1){
    return (xmm0 = _mm_mul_pd(xmm0, xmm1));
};

template<>
inline typename simd_trait<double>::register_type _mm_div<double>(typename simd_trait<double>::register_type xmm0, typename simd_trait<double>::register_type xmm1){
    return (xmm0 = _mm_div_pd(xmm0, xmm1));
};

template<>
inline typename simd_trait<double>::register_type _mm_add<double>(typename simd_trait<double>::register_type xmm0, typename simd_trait<double>::register_type xmm1){
    return (xmm0 = _mm_add_pd(xmm0, xmm1));
};


template<>
typename simd_trait<float>::register_type _mm_load1<float>(typename simd_trait<float>::register_type xmm0, const typename simd_trait<float>::value_type a){
    return (xmm0 =_mm_load1_ps(&a)); 
}

template<>
typename simd_trait<float>::register_type _mm_load<float>(typename simd_trait<float>::register_type xmm0, const typename simd_trait<float>::value_type* a){
    return (xmm0 =_mm_load_ps(a)); 
}

template<>
inline typename simd_trait<float>::register_type _mm_mul<float>(typename simd_trait<float>::register_type xmm0, typename simd_trait<float>::register_type xmm1){
    return (xmm0 = _mm_mul_ss(xmm0, xmm1));
};

template<>
inline typename simd_trait<float >::register_type _mm_div<float>(typename simd_trait<float>::register_type xmm0, typename simd_trait<float>::register_type xmm1){
    return (xmm0 = _mm_div_ps(xmm0, xmm1));
};

template<>
inline typename simd_trait<float>::register_type _mm_add<float>(typename simd_trait<float>::register_type xmm0, typename simd_trait<float>::register_type xmm1){
    return (xmm0 = _mm_add_ps(xmm0, xmm1));
};

template<class T>
struct vec{
    typedef typename simd_trait<T>::value_type value_type;
    typedef typename simd_trait<T>::register_type register_type;

    explicit vec(const value_type a){ xmm = _mm_load1<value_type>(xmm,a);}
    vec(const value_type* a){ xmm = _mm_load<value_type>(xmm,a);} 

    vec& operator *=(const vec& rhs){
        xmm = _mm_mul<value_type>(xmm, rhs.xmm);
        return *this;
    }
    
    vec& operator /=(const vec& rhs){
        xmm = _mm_div<value_type>(xmm, rhs.xmm);
        return *this;
    }
    
    vec& operator +=(const vec& rhs){
        xmm = _mm_add<value_type>(xmm, rhs.xmm);
        return *this;
    }

    register_type xmm;
};

template<class T>
vec<T> operator* (const vec<T>& lhs, const vec<T>& rhs){
    // named return value optimization
    vec<T> nrv(lhs);
    nrv *= rhs;
    return nrv;
}

template<class T>
vec<T> operator/ (const vec<T>& lhs, const vec<T>& rhs){
    // named return value optimization
    vec<T> nrv(lhs);
    nrv /= rhs;
    return nrv;
}

template<class T>
vec<T> operator+ (const vec<T>& lhs, const vec<T>& rhs){
    // named return value optimization
    vec<T> nrv(lhs);
    nrv += rhs;
    return nrv;
}

template<class T>
std::ostream& operator<< (std::ostream& os, vec<T> const & v){
     T a[2] = {0,0};
    _mm_store_pd(a,v.xmm);
    os  << a[0] << " " << a[1];
    return os;
}

template<std::size_t n>
inline vec<double> pow(vec<double> const& v){
    return v*pow<n-1>(v);
}

template<>
inline vec<double> pow<0>(vec<double> const& v){
    return vec<double>(1);
}

template<std::size_t n>
inline vec<double> exp(vec<double> const& v){
    return pow<n>(v)/vec<double>(factorial<n>())+exp<n-1>(v);
};

template<>
inline vec<double> exp<0>(vec<double> const& v){
    return vec<double>(1);
};



int main(int argc, char* argv[]){
    double array[2];
    array[0] = atof(argv[1]);
    array[1] = atof(argv[2]);
    vec<double> v(array);
    vec<double> v1(2);
    v1 = exp<20>(v);
    std::cout << array[0] <<  " " << array[1] << " " << std::endl;
    std::cout << v << std::endl;
    std::cout << v1 << std::endl;
}
