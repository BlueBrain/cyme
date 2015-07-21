/*
 * Cyme - expr_vec.hpp, Copyright (c), 2014,
 * Timothee Ewart - Swiss Federal Institute of technology in Lausanne,
 * timothee.ewart@epfl.ch,
 * All rights reserved.
 * This file is part of Cyme <https://github.com/BlueBrain/cyme>
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

/**
 * @file cyme/core/expression/expr_vec.hpp
 * Defines vertex class, rvec and wvec vector class
 *
 *  This uses template expressions to parse a series of basic operations into a tree at compile time.
 *  Effort was made to limit the number of local copies.
 *  Directly inspired (copy/paste and modify ^_^) from
 *  'C++ Templates: The Complete Guide' (Josuttis, Vandevoorde), Chapter XVIII
 *  To summarize every mathematical operations are transformed in a vertex
 *  during the compilation, every vertex has a corresponding SIMD wrapper
 *
 *
 * helper traits class to select how to refer to an ''expression template vertex''
 * - in general: by reference
 * - for scalars: by value
 */

#ifndef CYME_EXPR_VEC_HPP
#define CYME_EXPR_VEC_HPP

#include <iostream>

namespace cyme{
    /** \cond */
    //forward declarations
    template<class T, cyme::simd O, int N>
    class vec_scalar;

    //forward declarations
    template<class T,cyme::simd O, int N>
    struct vec_simd;

    //forward declarations
    template<class T,cyme::simd O, int N, int M>
    forceinline vec_simd<T,O,N> pow(const vec_simd<T,O,N>& lhs);
    /** \endcond */

    /** Primary vertex */
    template<class T, cyme::simd O, int N>
    struct vec_traits{
        typedef T const& value_type;
    };

    /** Partial specialization of the primary vertex for scalar */
    template<class T, cyme::simd O, int N>
    struct vec_traits< vec_scalar<T,O,N>, O, N>{
        typedef vec_scalar<T,O,N> value_type;
    };

    /** abs vertex in the DAG from abs(a) */
    template<class T, cyme::simd O, int N, class OP1>
    class vec_abs{
        typename vec_traits<OP1,O,N>::value_type op1;

    public:
        forceinline vec_abs(OP1 const& a):op1(a){
        }

        forceinline vec_simd<T,O,N> operator()() const{
            return abs(op1());
        }
    };

    /** sin vertex in the DAG from sin(a) */
    template<class T, cyme::simd O, int N, class OP1>
    class vec_sin{
        typename vec_traits<OP1,O,N>::value_type op1;

    public:
        forceinline vec_sin(OP1 const& a):op1(a){
        }

        forceinline vec_simd<T,O,N> operator()() const{
            return sin(op1());
        }
    };

    /** sqrt vertex in the DAG from sqrt(a) */
    template<class T, cyme::simd O, int N, class OP1>
    class vec_sqrt{
        typename vec_traits<OP1,O,N>::value_type op1;

    public:
        forceinline vec_sqrt(OP1 const& a):op1(a){
        }

        forceinline vec_simd<T,O,N> operator()() const{
            return sqrt(op1());
        }
    };

    /** exp vertex in the DAG from exp(a) */
    template<class T, cyme::simd O, int N, class OP1>
    class vec_exp{
        typename vec_traits<OP1,O,N>::value_type op1;

    public:
        forceinline vec_exp(OP1 const& a):op1(a){
        }

        forceinline vec_simd<T,O,N> operator()() const{
            return exp(op1());
        }
    };

    /** exp2 vertex in the DAG from exp2(a) */
    template<class T, cyme::simd O, int N, class OP1>
    class vec_exp2{
        typename vec_traits<OP1,O,N>::value_type op1;

    public:
        forceinline vec_exp2(OP1 const& a):op1(a){
        }

        forceinline vec_simd<T,O,N> operator()() const{
            return exp2(op1());
        }
    };

    /** exp10 vertex in the DAG from exp10(a) */
    template<class T, cyme::simd O, int N, class OP1>
    class vec_exp10{
        typename vec_traits<OP1,O,N>::value_type op1;

    public:
        forceinline vec_exp10(OP1 const& a):op1(a){
        }

        forceinline vec_simd<T,O,N> operator()() const{
            return exp10(op1());
        }
    };

    /** log vertex in the DAG from log(a) */
    template<class T, cyme::simd O, int N, class OP1>
    class vec_log{
        typename vec_traits<OP1,O,N>::value_type op1;

    public:
        forceinline vec_log(OP1 const& a):op1(a){
        }

        forceinline vec_simd<T,O,N> operator()() const{
            return log(op1());
        }
    };

    /** log2 vertex in the DAG from log2(a) */
    template<class T, cyme::simd O, int N, class OP1>
    class vec_log2{
        typename vec_traits<OP1,O,N>::value_type op1;

    public:
        forceinline vec_log2(OP1 const& a):op1(a){
        }

        forceinline vec_simd<T,O,N> operator()() const{
            return log2(op1());
        }
    };

    /** log10 vertex in the DAG from log10(a) */
    template<class T, cyme::simd O, int N, class OP1>
    class vec_log10{
        typename vec_traits<OP1,O,N>::value_type op1;

    public:
        forceinline vec_log10(OP1 const& a):op1(a){
        }

        forceinline vec_simd<T,O,N> operator()() const{
            return log10(op1());
        }
    };

    /** pow vertex in the DAG from pow(a,n), integer exponent only */
    template<class T, cyme::simd O, int N, class OP1, int M>
    class vec_pow{
        typename vec_traits<OP1,O,N>::value_type op1;

    public:
        forceinline vec_pow(OP1 const& a):op1(a){
        }

        forceinline vec_simd<T,O,N> operator()() const{
            return pow<T,O,N,M>(op1());
        }
    };

    /** add vertex in the DAG from a+b */
    template<class T, cyme::simd O, int N, class OP1, class OP2>
    class vec_add{
        typename vec_traits<OP1,O,N>::value_type op1;
        typename vec_traits<OP2,O,N>::value_type op2;

    public:
        forceinline vec_add(OP1 const& a, OP2 const& b):op1(a), op2(b){
        }

        forceinline vec_simd<T,O,N> operator()() const{
            return op1() + op2();
        }
    };

    /** sub vertex in the DAG from a-b */
    template<class T, cyme::simd O, int N, class OP1, class OP2>
    class vec_sub{
        typename vec_traits<OP1,O,N>::value_type op1;
        typename vec_traits<OP2,O,N>::value_type op2;

    public:
        forceinline vec_sub(OP1 const& a, OP2 const& b):op1(a), op2(b){
        }

        forceinline vec_simd<T,O,N> operator()() const{
            return op1() - op2();
        }
    };

    /** negate vertex in the DAG from -a

    Contrary to other class it is a structure, I did an optimization in case
    I get multiple negate e.g. -(-(a)) the vertex is transformed to a.
    For this I need to get the original operator (op1)
    */
    template<class T, cyme::simd O, int N, class OP1>
    struct vec_neg{
        typename vec_traits<OP1,O,N>::value_type op1;

    public:
        forceinline vec_neg(OP1 const& a):op1(a){
        }

        forceinline vec_simd<T,O,N> operator()() const{
            return neg(op1());
        }
    };

    /** mul vertex in the DAG from a*b */
    template<class T, cyme::simd O, int N, class OP1, class OP2>
    class vec_mul{
        typename vec_traits<OP1,O,N>::value_type op1;
        typename vec_traits<OP2,O,N>::value_type op2;
    public:

        forceinline vec_simd<T,O,N> operator()() const{
            return op1() * op2();
        }

        forceinline vec_mul(OP1 const& a, OP2 const& b):op1(a), op2(b){
        }

        //fma/s only
        forceinline const typename vec_traits<OP1,O,N>::value_type& getop1() const{
             return op1;
        }

        //fma/s only
        forceinline const typename vec_traits<OP2,O,N>::value_type& getop2() const{
             return op2;
        }
    };

    /** fma vertex in the DAG from a*b+c
    \warning Experimental, I may not catch all FMA
    */
    template<class T, cyme::simd O, int N, class OP1, class OP2, class OP3>
    class vec_muladd{
        typename vec_traits<OP1,O,N>::value_type op1;
        typename vec_traits<OP2,O,N>::value_type op2;
        typename vec_traits<OP3,O,N>::value_type op3;

    public:

        forceinline vec_simd<T,O,N> operator()() const{
            return muladd(op1(),op2(),op3());
        }

        forceinline vec_muladd(vec_mul<T,O,N,OP1,OP2> const& a, OP3 const& b):op1(a.getop1()), op2(a.getop2()), op3(b){}
    };

    /** fma vertex in the DAG from a*b+c*d
    \warning Althoug the following version requests less operation (one FMA and one mul), it is slower of 2 cycles,
    because the two multiplications are done in parallel
    */
    template<class T, cyme::simd O, int N, class OP1, class OP2, class OP3, class OP4>
    class vec_mul_add_mul{
        typename vec_traits<OP1,O,N>::value_type op1;
        typename vec_traits<OP2,O,N>::value_type op2;
        typename vec_traits<OP3,O,N>::value_type op3;
        typename vec_traits<OP4,O,N>::value_type op4;

    public:

        forceinline vec_simd<T,O,N> operator()() const{
        // return muladd(op1(),op2(),op3()*op4()); // FMA version to replug when FMA ops become faster
            return op1()*op2()+op3()*op4();
        }

        forceinline vec_mul_add_mul(vec_mul<T,O,N,OP1,OP2> const& a, vec_mul<T,O,N,OP3,OP4> const& b):
            op1(a.getop1()), op2(a.getop2()), op3(b.getop1()), op4(b.getop2()){}
    };

    /** fms vertex in the DAG from a*b-c*d
    \warning Althoug the following version requests less operation (one FMA and one mul), it is slower of 2 cycles,
    because the two multiplications are done in parallel
    */
    template<class T, cyme::simd O, int N, class OP1, class OP2, class OP3, class OP4>
    class vec_mul_sub_mul{
        typename vec_traits<OP1,O,N>::value_type op1;
        typename vec_traits<OP2,O,N>::value_type op2;
        typename vec_traits<OP3,O,N>::value_type op3;
        typename vec_traits<OP4,O,N>::value_type op4;

    public:

        forceinline vec_simd<T,O,N> operator()() const{
        // return mulsub(op1(),op2(),op3()*op4()); // FMA version to replug when FMA ops become faster
            return op1()*op2()-op3()*op4();
        }

        forceinline vec_mul_sub_mul(vec_mul<T,O,N,OP1,OP2> const& a, vec_mul<T,O,N,OP3,OP4> const& b):
            op1(a.getop1()), op2(a.getop2()), op3(b.getop1()), op4(b.getop2()){}
    };

    /** fms vertex in the DAG from a*b-c
    \warning it is experimental, I may not capture all FMA
    */
    template<class T, cyme::simd O, int N, class OP1, class OP2, class OP3>
    class vec_mulsub{
        typename vec_traits<OP1,O,N>::value_type op1;
        typename vec_traits<OP2,O,N>::value_type op2;
        typename vec_traits<OP3,O,N>::value_type op3;

    public:

        forceinline vec_simd<T,O,N> operator()() const{
            return mulsub(op1(),op2(),op3());
        }

        forceinline vec_mulsub(vec_mul<T,O,N,OP1,OP2> const& a, OP3 const& b):
            op1(a.getop1()), op2(a.getop2()), op3(b){}
    };


    /** fms vertex in the DAG from a-b*c
    \warning it is experimental, I may not capture all FMA
    */
    template<class T, cyme::simd O, int N, class OP1, class OP2, class OP3>
    class vec_negate_muladd{
        typename vec_traits<OP1,O,N>::value_type op1;
        typename vec_traits<OP2,O,N>::value_type op2;
        typename vec_traits<OP3,O,N>::value_type op3;

    public:

        forceinline vec_simd<T,O,N> operator()() const{
            return negatemuladd(op1(),op2(),op3()); // -a*b+c <=> c - a*b
        }

        forceinline vec_negate_muladd(vec_mul<T,O,N,OP1,OP2> const& a, OP3 const& b):
            op1(a.getop1()), op2(a.getop2()), op3(b){}
    };


    /** div vertex in the DAG from a/b

    I made a distinction between operands specially if b is scalar
    */
    template<class T, cyme::simd O, int N, class OP1, class OP2>
    class vec_div{
        typename vec_traits<OP1,O,N>::value_type op1;
        typename vec_traits<OP2,O,N>::value_type op2;
    public:

        forceinline vec_simd<T,O,N> operator()() const{
            return op1() / op2();
        }

        forceinline vec_div(OP1 const& a, OP2 const& b):op1(a), op2(b){}
    };

    /** scalar vertex */
    template<class T, cyme::simd O, int N>
    class vec_scalar{
    public:
        explicit forceinline vec_scalar(T const& a):s(a){
        }

        forceinline vec_simd<T,O,N> operator()() const{
            return s;
        }

    private:
        vec_simd<T,O,N> const s; // value of the scalar
    };

    /** read vector used during the construction of the DAG, rhs only !

    This class is an "interface" between the iterator and the computation
    vector class (SIMD register). During compilation, the DAG is created.
    The tree is built on the read only vector consequently.
    rvec is called only with the const [] operators of the
    class storage.

    If the user utilises rvec like and lhs and rhs, it should be very careful
    because the results will be note save. You need a wvec for that.

    \remark constrary the wrec I do not keep trace of the pointer of the input.
    I do not want generate a tree with a useless pointer.
    */
    template<class T, cyme::simd O, int N = cyme::unroll_factor::N, class Rep = vec_simd<T,O,N> >
    class rvec{
    public:
        typedef T value_type;
        typedef value_type* pointer;
        typedef value_type const* const_pointer;
        typedef Rep base_type;

        /** default constructor nothing special */
        forceinline explicit rvec():expr_rep(){
        }

        /** constructor rhs of the operator= I do not save the pointer, as I read only the cyme on this side */
        forceinline explicit rvec(Rep const& rb):expr_rep(rb){
        }

        /** constructor lhs of the operator= */
        forceinline explicit rvec(const_pointer rb):expr_rep(rb){
        }

        /** constructor for a given value */
        forceinline explicit rvec(value_type a):expr_rep(a){
        }

        /**
        operator= creates the tree and execute in normal condition
        The tree is built at the compilation, the full tree is stored in rhs argument.
        The execution of the tree is performed when we call the operator()
        */
        template<class T2, cyme::simd O2, int N2, class Rep2>
        forceinline rvec& operator= (rvec<T2,O2,N2,Rep2 > const& rhs){
            rep() = rhs.rep()();
            return *this;
        }

        /**
        operator+=, creates the tree and execute in normal condition
        The tree is built at the compilation, the full tree is stored in rhs argument.
        The execution of the tree is performed when we call the operator()
        */
        template<class T2, cyme::simd O2, int N2, class Rep2>
        forceinline rvec& operator+= (rvec<T2,O2,N2,Rep2 > const& rhs){
            rep() += rhs.rep()();
            return *this;
        }

        /**
        operator-=, creates the tree and execute in normal condition
        The tree is built at the compilation, the full tree is stored in rhs argument.
        The execution of the tree is performed when we call the operator()
        */
        template<class T2, cyme::simd O2, int N2, class Rep2>
        forceinline rvec& operator-= (rvec<T2,O2,N2,Rep2 > const& rhs){
            rep() -= rhs.rep()();
            return *this;
        }

        /**
        operator*=, creates the tree and execute in normal condition
        The tree is built at the compilation, the full tree is stored in rhs argument.
        The execution of the tree is performed when we call the operator()
        */
        template<class T2, cyme::simd O2, int N2, class Rep2>
        forceinline rvec& operator*= (rvec<T2,O2,N2,Rep2 > const& rhs){ rep() *= rhs.rep()();
            return *this;
        }

        /**
        operator/=, creates the tree and execute in normal condition
        \warning the division is the system one not my version
        */
        template<class T2, cyme::simd O2, int N2, class Rep2>
        forceinline rvec& operator/= (rvec<T2,O2,N2,Rep2 > const& rhs){
            rep() /= rhs.rep()();
            return *this;
        }

        /** Get the vector class, read only */
        forceinline Rep const& rep() const{
            return expr_rep;
        }

        /** Get the vector class, writable */
        forceinline Rep& rep(){
            return expr_rep;
        }

	/**
  	Use print function from Rep
 	*/
	forceinline void print(std::ostream &out) const{
	    expr_rep.print(out);
	}

    private:
        /** Composition with cyme::vec_simd */
        Rep expr_rep;
    };

    /** write vector used during the construction of the DAG, lhs only !

    This class is an "interface" between the iterator and the computation
    vector class (SIMD register). During compilation, the DAG is created.
    The tree is built on the read only vector consequently.
    rvec is called only with the non-const [] operators of the class storage.

    \remark The wrec keep trace of the pointer of the input.
    */
    template<class T, cyme::simd O, int N = cyme::unroll_factor::N, class Rep = vec_simd<T,O,N> >
    class wvec{
        public:
        typedef rvec<T,O,N,Rep> V;
        typedef T value_type;
        typedef value_type* pointer;
        typedef Rep base_type;

        /*** Constructor lhs of the operator=, I save the data into the cyme after the computation */
        forceinline explicit wvec(pointer rb):data_pointer(rb),expr_rep(rb){
        }

        /**
        RAII for the store. Altough, we do not allocate cyme, we allocate a SIMD register.
        If not rewrite this command after the tree creation into the +=, *=, etc ....
        */
        ~wvec(){
            expr_rep.store(data_pointer); //store the SIMD register into main cyme
        }

        /**
        operator= initializes the wvec to a given value. The full vector has
        the same value.
        */
        forceinline wvec& operator= (value_type a){
            rvec<T,O,N,Rep> v(a);
            expr_rep() = v.rep()();
            return *this;
        }

        /**
        operator= creates the tree and execute in normal condition
        The tree is built at the compilation, the full tree is stored in rhs argument.
        The execution of the tree is performed when we call the operator()
        we call the operator(). The datas are saved when the destructor is called.
        */
        template<class T2, cyme::simd O2, int N2, class Rep2>
        forceinline wvec& operator= (rvec<T2,O2,N2,Rep2> const& rhs){
            expr_rep() = rhs.rep()();
            return *this;
        }

        /**
        operator+= creates the tree and execute in normal condition
        The tree is built at the compilation, the full tree is stored in rhs argument.
        The execution of the tree is performed when we call the operator()
        we call the operator(). The datas are saved when the destructor is called.
        */
        template<class T2, cyme::simd O2, int N2, class Rep2>
        forceinline wvec& operator+= (rvec<T2,O2,N2,Rep2 > const& rhs){
            expr_rep() += rhs.rep()();
            return *this;
        }

        /**
        operator-= creates the tree and execute in normal condition
        The tree is built at the compilation, the full tree is stored in rhs argument.
        The execution of the tree is performed when we call the operator()
        we call the operator().The datas are saved when the destructor is called.
        */
        template<class T2, cyme::simd O2, int N2, class Rep2>
        forceinline wvec& operator-= (rvec<T2,O2,N2,Rep2 > const& rhs){
            expr_rep() -= rhs.rep()();
            return *this;
        }

        /**
        operator*= creates the tree and execute in normal condition
        The tree is built at the compilation, the full tree is stored in rhs argument.
        The execution of the tree is performed when we call the operator()
        we call the operator().The datas are saved when the destructor is called.
        */
        template<class T2, cyme::simd O2, int N2, class Rep2>
        forceinline wvec& operator*= (rvec<T2,O2,N2,Rep2 > const& rhs){
            expr_rep() *= rhs.rep()();
            return *this;
        }

        /**
        operator/= creates the tree and execute in normal condition
        The tree is built at the compilation, the full tree is stored in rhs argument.
        The execution of the tree is performed when we call the operator()
        we call the operator().The datas are saved when the destructor is called.
        */
        template<class T2, cyme::simd O2, int N2, class Rep2>
        forceinline wvec& operator/= (rvec<T2,O2,N2,Rep2 > const& rhs){
            expr_rep() /= rhs.rep()(); //basic register copy no three
            return *this;
        }

        /**
        Get the vector class, read only
        */
        forceinline Rep const& rep() const{
            return expr_rep;
        }
        /**
        Get the vector class, write only
        */
        forceinline Rep& rep(){
            return expr_rep;
        }

	/**
  	Use print function from Rep
  	*/
	forceinline void print(std::ostream &out) const{
	    expr_rep.print(out);
	}

    private:
        /** Pointer to save the data */
        pointer data_pointer;
        /** Composition with cyme::vec_simd */
        Rep expr_rep;
    };
 }

#include "cyme/core/expression/expr_vec_ops.ipp"
#ifdef __FMA__
#include "cyme/core/expression/expr_vec_fma.ipp"
#endif

/** Ostream operators for rvec and wvec*/
/**wvec*/
template<class T, cyme::simd O, int N, class Rep>
forceinline std::ostream &operator<<(std::ostream &out, const cyme::wvec<T,O,N,Rep> &vec){
	vec.print(out);
	return out;
}

/**rvec*/
template<class T, cyme::simd O, int N, class Rep>
forceinline std::ostream &operator<<(std::ostream &out, const cyme::rvec<T,O,N,Rep> &vec){
	vec.print(out);
	return out;
}
#endif
