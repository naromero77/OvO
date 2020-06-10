#include <iostream>
#include <cstdlib>
bool almost_equal(float x, float gold, float tol) {
        return gold * (1-tol) <= x && x <= gold * (1 + tol);
}
void test_target__teams_distribute_parallel_for__simd(){
 const int N0 = 512;
 const int N1 = 512;
 float counter{};
#pragma omp target map(tofrom: counter)
#pragma omp teams distribute parallel for reduction(+: counter)
      for (int i0 = 0 ; i0 < N0 ; i0++ )
      {
#pragma omp simd reduction(+: counter)
      for (int i1 = 0 ; i1 < N1 ; i1++ )
      {
counter += float { 1.0f };
    }
    }
if ( !almost_equal(counter,float { N0*N1 }, 0.1)  ) {
    std::cerr << "Expected: " << N0*N1 << " Got: " << counter << std::endl;
    std::exit(112);
}
}
int main()
{
    test_target__teams_distribute_parallel_for__simd();
}
