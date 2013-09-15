#include <iostream>

#include "numeric/math/math.hpp"
#include "memory/block.hpp"

#include <stdlib.h>


#define TYPE float
#define N 3
#define M 2
#define ORDER T::order


int main(){
   srand(-1);
     memory::block<TYPE,M,N,memory::AoS> block_a;
     memory::block<TYPE,M,N,memory::AoSoA> block_b;

     TYPE test_a[M][N], res_a[M][N];
     TYPE test_b[M][N], res_b[M][N];

     for(int i=0; i<N; ++i)
         for(int j=0; j<M; ++j){
            long random = rand()%100;
            block_a(i,j) = random;
            block_b(i,j) = random;
     //       test_a[i][j] = random;
     //       test_b[i][j] = random;
         }
    std::cout << " hello " << std::endl;

    typename memory::block<TYPE,M,N,memory::AoS>::iterator it_AoS = block_a.begin();
    for(; it_AoS != block_a.end(); ++it_AoS)
         numeric::add<TYPE>((*it_AoS)[0],(*it_AoS)[1]);

    typename memory::block<TYPE,M,N,memory::AoSoA>::iterator it_AoSoA = block_b.begin();
    for(; it_AoSoA != block_b.end(); ++it_AoSoA)
         numeric::add<TYPE>((*it_AoSoA)[0],(*it_AoSoA)[1]);
   
    for(int i=0; i<N ; ++i)
        for(int j=0; j<M; ++j){
           test_a[0][j] += test_b[1][j];
 std::cout <<   block_a(i,j)  << " " << block_b(i,j) << std::endl;
//           res_a[i][j] = block_a(i,j);
//           res_b[i][j] = block_b(i,j);
        }

    int block_b_bool = memcmp((void*)res_a, (void*)res_b, M*N*sizeof(TYPE));
    int block_a_bool = memcmp((void*)res_b, (void*)test_a, M*N*sizeof(TYPE));

    std::cout << block_b_bool << " " << block_a_bool << std::endl;

}
