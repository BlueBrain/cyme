
#pragma once

#include <vector>
#include "memory/detail/simd.h"
#include "memory/allocator.hpp"
#include "memory/detail/storage.hpp"


namespace test{

template<class T, memory::order O>
class vector{};

template<class T>
class vector<T,memory::AoS>{
    typedef typename T::value_type value_type;
    typedef std::vector<memory::storage<value_type,T::value_size,memory::AoS>, memory::Allocator<memory::storage<value_type,T::value_size,memory::AoS> > > base_type;
    typedef typename base_type::iterator iterator;
    //to do
private:
    base_type data;
};


template<class T>
class vector<T,memory::AoSoA>{
public:
    const static memory::order order_value = memory::AoSoA;
    typedef std::size_t size_type;
    typedef typename    T::value_type value_type;
    typedef value_type&                                               reference;
    typedef const value_type&                                         const_reference;
    static const size_type  storage_width = memory::unroll_factor::N*memory::__GETSIMD__()/sizeof(value_type)*T::value_size;
    typedef memory::storage<value_type,storage_width,memory::AoSoA>  storage_type;
    typedef std::vector<
                        storage_type,
                        memory::Allocator<storage_type>
                       > base_type;
    typedef typename base_type::iterator iterator;
    
    vector(const size_t size=0, value_type value=value_type())
        :data(size/(memory::unroll_factor::N*memory::__GETSIMD__()/sizeof(T))+1,value),size_cyme(size){
    }
    
    iterator begin(){
        return this->data.begin();
    }

    iterator end(){
        return this->data.end();
    }

    storage_type& operator [](int i){
        return this->data[i];
    }

    const storage_type& operator [](int i) const{
        return this->data[i];
    }
    
    static inline size_type size_block() {
        return T::value_size;
    }

    inline size_type size() {
        return this->data.size();
    }
    
    inline reference operator()(size_type i, size_type j){
           // nothing on i as the original size is destroyed in the constructor
           // BOOST_ASSERT_MSG( i < size(), "out of range: block_v AoS i" );
            BOOST_ASSERT_MSG(     j < T::value_size, "out of range: block_v AoSoA j" );
            // Please tune me ! (does it exist an alternative to this ? ^_^
            return this->data[(i*T::value_size+j)/storage_width] //(i)
            (j*(memory::unroll_factor::N*memory::__GETSIMD__()/sizeof(value_type)) + i%(memory::unroll_factor::N*memory::__GETSIMD__()/sizeof(value_type)));      //(j)
    }

        inline const_reference operator()(size_type i, size_type j) const{
           // nothing on i as the original size is destroyed in the constructor
            BOOST_ASSERT_MSG(     j < T::value_size, "out of range: block_v AoSoA j" );
            // Please tune me ! (does it exist an alternative to this ? ^_^
            return this->data[(i*T::value_size+j)/(T::value_size*memory::unroll_factor::N*memory::__GETSIMD__()/sizeof(value_type))] //(i)
            (j*(memory::unroll_factor::N*memory::__GETSIMD__()/sizeof(value_type)) + i%(memory::unroll_factor::N*memory::__GETSIMD__()/sizeof(value_type)));      //(j)
    }

private:
    base_type data;
    size_type size_cyme;
};

}