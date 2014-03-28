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

#ifndef CYME_SIMD_LOG_HPP
#define CYME_SIMD_LOG_HPP


namespace numeric{
    /**
        \brief my implementation of the logarithm, not done yet
    */
    template<class T, memory::simd O, int N, std::size_t n> // Remez, series ...
    struct my_log{
        static forceinline vec_simd<T,O,N> log(vec_simd<T,O,N> x){
            T tmp[N*O/sizeof(T)] __attribute__((aligned(static_cast<int>(O)))); // temporary fix until I develop my own version
            x.store(tmp);
            for(int i=0; i<N*O/sizeof(T); ++i)
                tmp[i] = std::log(tmp[i]);
            std::cout << " you're using system log, not efficient, Code me ! (simd_log.hpp) " << std::endl;
            return vec_simd<T,O,N>(tmp);
        }
    };

    /**
     \brief Vendor implementation of the logarithm
     */
    template<class T, memory::simd O, int N, std::size_t n>
    struct Vendor_log{
        static forceinline vec_simd<T,O,N> log(vec_simd<T,O,N> const& a){
            return log_v(a); /* call vendor wrapper */
        }
    };

    /**
     \brief Selector for the log
    */
    template<class T, memory::simd O, int N, std::size_t n = 0, class Solver = my_log<T,O,N,n> > // my_log (to do) ou vendor
    struct Selector_log{
         static forceinline vec_simd<T,O,N> log(vec_simd<T,O,N> x){
               x = Solver::log(x);
               return x;
         }
    };

    /**
        \brief final wrapper for the log
    */
    template<class T,memory::simd O, int N>
    forceinline vec_simd<T,O,N> log(const vec_simd<T,O,N>& rhs){
        return Selector_log<T,O,N>::log(rhs);
    }
}
#endif
