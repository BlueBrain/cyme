/*
 * CYME, License
 * 
 * Timothee Ewart - Swiss Federal Institute of technology in Lausanne 
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef CYME_SIMD_VEC_IPP
#define CYME_SIMD_VEC_IPP

namespace numeric{

    template<class T, memory::simd O>
    vec_simd<T,O>::vec_simd(const typename simd_trait<T,O>::value_type a){
        this->xmm = _mm_load1<typename simd_trait<T,O>::value_type,O>(this->xmm,a);
    }

    template<class T, memory::simd O>
    vec_simd<T,O>::vec_simd(){
    }

    template<class T, memory::simd O>
    vec_simd<T,O>::vec_simd(typename simd_trait<T,O>::const_pointer a){
        this->xmm = _mm_load<typename simd_trait<T,O>::value_type,O>(this->xmm,a);
    }

    template<class T, memory::simd O>
    vec_simd<T,O>::vec_simd(typename simd_trait<T,O>::register_type x){
        this->xmm = x;
    }

    template<class T, memory::simd O>
    vec_simd<T,O>& vec_simd<T,O>::operator()(){
        return *this;
    }

    template<class T, memory::simd O>
    const vec_simd<T,O>& vec_simd<T,O>::operator()() const{
        return *this;
    }

    template<class T, memory::simd O>
    vec_simd<T,O>& vec_simd<T,O>::operator *=(const vec_simd<T,O>& rhs){
        this->xmm = _mm_mul<typename simd_trait<T,O>::value_type,O>(this->xmm,rhs.xmm);
        return *this;
    }

    template<class T, memory::simd O>
    vec_simd<T,O>& vec_simd<T,O>::operator /=(const vec_simd<T,O>& rhs){
        this->xmm = _mm_div<typename simd_trait<T,O>::value_type,O>(this->xmm,rhs.xmm);
        return *this;
    }

    template<class T, memory::simd O>
    vec_simd<T,O>& vec_simd<T,O>::operator +=(const vec_simd<T,O>& rhs){
        this->xmm = _mm_add<typename simd_trait<T,O>::value_type,O>(this->xmm,rhs.xmm);
        return *this;
    }

    template<class T, memory::simd O>
    vec_simd<T,O>& vec_simd<T,O>::operator -=(const vec_simd<T,O>& rhs){
        this->xmm = _mm_sub<typename simd_trait<T,O>::value_type,O>(this->xmm,rhs.xmm);
        return *this;
    }

    template<class T, memory::simd O>
    void vec_simd<T,O>::store(typename simd_trait<T,O>::pointer a) const{
        _mm_store<value_type,O>(this->xmm,a);
    } 

    template<class T, memory::simd O>
    vec_simd<T,O>& vec_simd<T,O>::neg(){
       this->xmm = _mm_neg<typename simd_trait<T,O>::value_type,O>(this->xmm);
       return *this;
    } 


    template<class T,memory::simd O>
    vec_simd<T,O> cast(const vec_simd<int,O>& rhs){
        vec_simd<T,O> nrv;
        nrv.xmm = _mm_cast<typename simd_trait<T,O>::value_type,O>(rhs.xmm); // TO change a day no time this week
        return nrv;
    }

    template<class T, memory::simd O>
    vec_simd<int,O> floor(vec_simd<T,O> &rhs){
        vec_simd<int,O> nrv;
        nrv.xmm = _mm_floor<typename simd_trait<T,O>::value_type,O>(rhs.xmm);
        return nrv;
    }

    template<class T,memory::simd O>
    vec_simd<T,O> twok(const vec_simd<int,O>& rhs){
        vec_simd<T,O> nrv;
        nrv.xmm = _mm_twok<typename simd_trait<T,O>::value_type,O>(rhs.xmm); // TO change a day no time this week 
        return nrv;
    }

    template<class T, memory::simd O>
    vec_simd<T,O> min(const vec_simd<T,O>& lhs, const vec_simd<T,O>& rhs){
        vec_simd<T,O> nrv;
        nrv.xmm = _mm_min<typename simd_trait<T,O>::value_type,O>(lhs.xmm,rhs.xmm);
        return nrv;
    }

    template<class T, memory::simd O>
    vec_simd<T,O> max(const vec_simd<T,O>& lhs, const vec_simd<T,O>& rhs){
        vec_simd<T,O> nrv;
        nrv.xmm = _mm_max<typename simd_trait<T,O>::value_type,O>(lhs.xmm,rhs.xmm);
        return nrv;
    }

#ifdef __FMA__
    template<class T, memory::simd O>
    void vec_simd<T,O>::ma(const vec_simd& lhs, const vec_simd& rhs){
        this->xmm = _mm_fma<typename simd_trait<T,O>::value_type,O>(this->xmm,lhs.xmm,rhs.xmm);
    }

    template<class T, memory::simd O>
    void vec_simd<T,O>::ms(const vec_simd& lhs, const vec_simd& rhs){
        this->xmm = _mm_fms<typename simd_trait<T,O>::value_type,O>(this->xmm,lhs.xmm,rhs.xmm);
    }

    template<class T, memory::simd O>
    void vec_simd<T,O>::nma(const vec_simd& lhs, const vec_simd& rhs){
        this->xmm = _mm_nfma<typename simd_trait<T,O>::value_type,O>(this->xmm,lhs.xmm,rhs.xmm);
    }

    template<class T, memory::simd O>
    void vec_simd<T,O>::nms(const vec_simd& lhs, const vec_simd& rhs){
        this->xmm = _mm_nfms<typename simd_trait<T,O>::value_type,O>(this->xmm,lhs.xmm,rhs.xmm);
    }
#endif

} //end namespace

#endif

