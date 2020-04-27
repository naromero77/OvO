#include <iostream>
#include <cmath>
#include <stdexcept>
bool almost_equal(double x, double gold, float tol) {
    return gold * (1-tol) <= x && x <= gold * ( 1+tol );
}
void test_target_teams__distribute_simd(){
 const int L = 262144;
double counter{};
#pragma omp target teams  map(tofrom:counter) 
    {
double partial_counter{};
#pragma omp distribute simd  reduction(+: counter)  
    for (int i = 0 ; i < L ; i++ )
    {
partial_counter += double { 1.0f };
   } 
#pragma omp atomic update
counter += partial_counter;
   } 
if ( !almost_equal(counter,double { L }, 0.1)  ) {
    std::cerr << "Expected: " << L << " Got: " << counter << std::endl;
    throw std::runtime_error( "target_teams__distribute_simd give incorect value when offloaded");
}
}
int main()
{
    test_target_teams__distribute_simd();
}
