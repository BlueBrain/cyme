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

#ifndef CYME_EXP_HPP
#define CYME_EXP_HPP

#include <math.h>  

#include "math/remez.hpp"

namespace numeric{
    //the classical exp and Pade exp are into the git revision: c0788dfd49424fe9abc2809896efdd81fe03ffd4 
    template<class T, std::size_t n>
    struct helper_remez_exp{
        static inline T exp(T const& a){
//          return pow<T,n>(a)*T(coeff_remez<T,n>::coeff()) + helper_remez_exp<T,n-1>::exp(a); // classic implementation very slow as pow is recalculating
//          for every iteration, not optimium as 20 is hardcoded
#ifdef __FMA__
            return muladd(helper_remez_exp<T,n-1>::exp(a),a,T(coeff_remez<T,coeff_remez_number::value-n>::coeff()));
#else
            return T(coeff_remez<T,coeff_remez_number::value-n>::coeff()) + helper_remez_exp<T,n-1>::exp(a)*a;
#endif
        }
    };

    template<class T>
    struct helper_remez_exp<T,0>{
        static inline T exp(T const& a){
            return T(coeff_remez<T,coeff_remez_number::value>::coeff());
        }
    };

    template<class T, std::size_t n>
    struct Remez_exp{
        /** fn template<std::size_t T, std::size_t n> Pade_exp  
            \brief clean wrapper of the Pade approximat method 
        */
        static inline T exp(T const& a){
            return helper_remez_exp<T,n>::exp(a);
        }
    };


    template<class T, std::size_t n>
    struct Vendor_exp{
        static inline T exp(T const& a){
            return exp_v(a);            
        }
    };    

    /** \class template<std::size_t T, std::size_t n, class Solver> exp  
        \brief final wrapper for the exp, pade approximant with n = 14 (maximum value before pb), remez calculate with n=20
    */
    template<class T, std::size_t n = coeff_remez_number::value, class Solver = Vendor_exp<T,n> >
    struct Helper_exp{
        static inline T exp(T const& a){
             return Solver::exp(a);
        }
    };


} //end namespace 

#endif 
