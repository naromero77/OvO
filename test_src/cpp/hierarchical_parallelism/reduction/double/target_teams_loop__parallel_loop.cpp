#include <iostream>
#include <cmath>
#include <stdexcept>
bool almost_equal(double x, double gold, float tol) {
        return gold * (1-tol) <= x && x <= gold * ( 1+tol );
}
void test_target_teams_loop__parallel_loop(){
 // Input and Outputs
 const int L = 4096;
 const int M = 64;
double counter{};
// Main program
#pragma omp target teams loop  reduction(+: counter)   map(tofrom:counter) 
    for (int i = 0 ; i < L ; i++ )
{
#pragma omp parallel loop  reduction(+: counter)  
    for (int j = 0 ; j < M ; j++ )
{
counter += double { 1.0f };
    }
    }
// Validation
if ( !almost_equal(counter,double { L*M }, 0.1)  ) {
    std::cerr << "Expected: " << L*M << " Got: " << counter << std::endl;
    throw std::runtime_error( "target_teams_loop__parallel_loop give incorect value when offloaded");
}
}
int main()
{
    test_target_teams_loop__parallel_loop();
}
