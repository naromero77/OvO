#include <iostream>
#include <cmath>
#include <stdexcept>
bool almost_equal(float x, float gold, float tol) {
        return gold * (1-tol) <= x && x <= gold * ( 1+tol );
}
void test_target_teams_distribute__parallel__loop__simd(){
 // Input and Outputs
 const int L = 64;
 const int M = 64;
 const int N = 64;
float counter{};
// Main program
#pragma omp target teams distribute  reduction(+: counter)   map(tofrom:counter) 
    for (int i = 0 ; i < L ; i++ )
{
#pragma omp parallel  reduction(+: counter)  
{
#pragma omp loop  
    for (int j = 0 ; j < M ; j++ )
{
#pragma omp simd  reduction(+: counter)  
    for (int k = 0 ; k < N ; k++ )
{
counter += float { 1.0f };
    }
    }
    }
    }
// Validation
if ( !almost_equal(counter,float { L*M*N }, 0.1)  ) {
    std::cerr << "Expected: " << L*M*N << " Got: " << counter << std::endl;
    throw std::runtime_error( "target_teams_distribute__parallel__loop__simd give incorect value when offloaded");
}
}
int main()
{
    test_target_teams_distribute__parallel__loop__simd();
}
