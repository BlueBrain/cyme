/*
 * Cyme - test_print.cpp, Copyright (c), 2014,
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

 #include <iostream>
 #include <vector>

 #include <cyme/cyme.h>

 #include <boost/chrono.hpp>

 #include <boost/function.hpp>
 #include <boost/bind.hpp>

 #include <boost/accumulators/accumulators.hpp>
 #include <boost/accumulators/statistics/stats.hpp>
 #include <boost/accumulators/statistics/mean.hpp>
 #include <boost/accumulators/statistics/variance.hpp>

 #include <boost/mpl/for_each.hpp>
 #include <boost/mpl/vector.hpp>
 #include <boost/mpl/push_back.hpp>
 #include <functional>

 #include <algorithm>
int main(){
	cyme::vec_simd <float, cyme::vmx,1> a;
	std::cout<<"Printing vec_simd returns: "<<a<<std::endl;
}

