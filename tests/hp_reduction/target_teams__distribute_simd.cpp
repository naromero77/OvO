#include <cassert>

void test_target_teams__distribute_simd(){

 // Input and Outputs
 
 const int L = 5;

int counter = 0;

// Main program

#pragma omp target teams  reduction(+:counter)   defaultmap(tofrom:scalar) 

{

#pragma omp distribute simd  reduction(+:counter)  

    for (int i = 0 ; i < L ; i++ )

{


counter++;

 }  } 

// Validation
assert( counter == L );

}
int main()
{
    test_target_teams__distribute_simd();
}