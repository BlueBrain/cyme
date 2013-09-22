/*
 * CoreBluron, License
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

#ifndef COREBLURON_STORAGE_IPP 
#define COREBLURON_STORAGE_IPP
namespace memory{
    template <class T, std::size_t Size>
    storage<T, Size, AoS>::storage(){
        memset((void*)&this->data[0],T(),Size*sizeof(T)); // memset works only for char, T() return 0 so ok
    }

    template <class T, std::size_t Size>
    storage<T, Size, AoS>::storage(value_type value){
        for(size_type i=0; i<Size; ++i) 
            this->data[i] = value;
    }

    template <class T, std::size_t Size>
    typename storage<T, Size, AoS>::reference storage<T, Size, AoS>::operator()(size_type i){
        return data[i];
    }

    template <class T, std::size_t Size>
    typename storage<T, Size, AoS>::const_reference storage<T, Size, AoS>::operator()(size_type i) const{
          return data[i];
    }

    template <class T, std::size_t Size>
    typename storage<T, Size, AoS>::reference storage<T, Size, AoS>::operator[](size_type i){
             return operator()(i);
    }

    template <class T, std::size_t Size>
    typename storage<T, Size, AoS>::const_reference storage<T, Size, AoS>::operator[](size_type i) const{
             return operator()(i);
    }
    
    template <class T, std::size_t Size>
    storage<T, Size, AoSoA>::storage(){
        memset((void*)&this->data[0],T(),Size*sizeof(T)); // memset works only for char, T() return 0 so ok
    }

    template <class T, std::size_t Size>
    storage<T, Size, AoSoA>::storage(value_type value){
        for(size_type i=0; i<Size; ++i) 
            this->data[i] = value;
    }

    template <class T, std::size_t Size>
    typename storage<T, Size, AoSoA>::reference storage<T, Size, AoSoA>::operator()(size_type i){
        return data[i];
    }

    template <class T, std::size_t Size>
    typename storage<T, Size, AoSoA>::const_reference storage<T, Size, AoSoA>::operator()(size_type i) const{
        return data[i];
    }

    template <class T, std::size_t Size>
    numeric::Vec<T,memory::__GETSIMD__()> storage<T, Size, AoSoA>::operator[](size_type i){
        return numeric::Vec<T,memory::__GETSIMD__()>(&data[i*stride<T,AoSoA>::helper_stride()]);
    }

    template <class T, std::size_t Size>
    const numeric::Vec<T,memory::__GETSIMD__()> storage<T, Size, AoSoA>::operator[](size_type i) const{
        std::cout << " read " << std::endl;
        return numeric::Vec<T,memory::__GETSIMD__()>(&data[i*stride<T,AoSoA>::helper_stride()]);
    }

} //end namespace
#endif 
