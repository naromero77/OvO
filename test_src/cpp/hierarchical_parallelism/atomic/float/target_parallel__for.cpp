#include <iostream>
#include <cmath>
#include <stdexcept>
#
bool almost_equal(float x, float gold, float tol) {
        return gold * (1-tol) <= x && x <= gold * ( 1+tol );
}
void test_target_parallel__for(){
 // Input and Outputs
 const int L = 262144;
float counter{};
// Main program
#pragma omp target parallel  map(tofrom:counter) 
{
#pragma omp for 
    for (int i = 0 ; i < L ; i++ )
{
#pragma omp atomic update
counter += float { 1 };
    } 
    } 
// Validation
if ( !almost_equal(counter,float { L }, 0.1)  ) {
    std::cerr << "Expected: " << L << " Got: " << counter << std::endl;
    throw std::runtime_error( "target_parallel__for give incorect value when offloaded");
}
}
int main()
{
    test_target_parallel__for();
}
