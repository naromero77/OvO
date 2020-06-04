#include <iostream>
#include <limits>
#include <cmath>
#include <vector>
#include <algorithm>
bool almost_equal(float x, float y, int ulp) {
     return std::fabs(x-y) <= std::numeric_limits<float>::epsilon() * std::fabs(x+y) * ulp ||  std::fabs(x-y) < std::numeric_limits<float>::min();
}
void test_target__parallel_for__simd(){
  const int N_i = 64;
  const int N_j = 64;
  const int size = N_i*N_j;
  std::vector<float> A(size);
  std::vector<float> B(size);
  std::generate(B.begin(), B.end(), std::rand);
  float *pA = A.data();
  float *pB = B.data();
#pragma omp target   map(from: pA[0:N_i*N_j]) map(to: pB[0:N_i*N_j]) 
#pragma omp parallel for 
    for (int i = 0 ; i < N_i ; i++ )
    {
#pragma omp simd 
    for (int j = 0 ; j < N_j ; j++ )
    {
pA[ j+i*N_j ] = pB [ j+i*N_j ];
    } 
    } 
for (int i = 0 ;  i < size ; i++) {
    if ( !almost_equal(A[i],B[i],1) ) {
         std::cerr << "Expected: " << B[i] << " Got: " << A[i] << std::endl;
        std::exit(112);
    }
}
}
int main()
{
    test_target__parallel_for__simd();
}