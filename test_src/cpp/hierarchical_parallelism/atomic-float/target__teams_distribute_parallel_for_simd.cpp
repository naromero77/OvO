#include <iostream>
#include <cstdlib>
#include <cmath>
bool almost_equal(float x, float gold, float tol) {
  return gold * (1-tol) <= x && x <= gold * (1 + tol);
}
void test_target__teams_distribute_parallel_for_simd() {
  const int N0 { 32768 };
  const float expected_value { N0 };
  float counter_N0{};
  #pragma omp target map(tofrom: counter_N0)
  #pragma omp teams distribute parallel for simd
  for (int i0 = 0 ; i0 < N0 ; i0++ )
  {
    #pragma omp atomic update
    counter_N0 = counter_N0 + 1. ;
  }
  if (!almost_equal(counter_N0, expected_value, 0.1)) {
    std::cerr << "Expected: " << expected_value << " Got: " << counter_N0 << std::endl;
    std::exit(112);
  }
}
int main()
{
    test_target__teams_distribute_parallel_for_simd();
}
