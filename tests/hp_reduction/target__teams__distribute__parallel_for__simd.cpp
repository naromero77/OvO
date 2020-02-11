#include <cassert>

void test_target__teams__distribute__parallel_for__simd(){

 // Input and Outputs
 
 const int L = 5;
 const int M = 6;
 const int N = 7;

int counter = 0;

// Main program

#pragma omp target   defaultmap(tofrom:scalar) 

{

#pragma omp teams  reduction(+:counter)  

{

#pragma omp distribute  

    for (int i = 0 ; i < L ; i++ )

{

#pragma omp parallel for  reduction(+:counter)  

    for (int j = 0 ; j < M ; j++ )

{

#pragma omp simd  reduction(+:counter)  

    for (int k = 0 ; k < N ; k++ )

{


counter++;

 }  }  }  }  } 

// Validation
assert( counter == L*M*N );

}
int main()
{
    test_target__teams__distribute__parallel_for__simd();
}