#include <iostream>
#include <cstdlib>
#include <cmath>
#include <complex>
using std::complex;
#ifdef _OPENMP
#include <omp.h>
#else
int omp_get_num_threads() {return 1;}
#endif
bool almost_equal(complex<double> x, complex<double> gold, float tol) {
  return std::abs(gold) * (1-tol) <= std::abs(x) && std::abs(x) <= std::abs(gold) * (1 + tol);
}
#pragma omp declare reduction(+: complex<double>: omp_out += omp_in)
void test_target_parallel() {
  const complex<double> expected_value { 1 };
  complex<double> counter_parallel{};
  #pragma omp target parallel map(tofrom: counter_parallel) reduction(+: counter_parallel)
  {
    counter_parallel = counter_parallel + complex<double> { double { 1. } / omp_get_num_threads() };
  }
  if (!almost_equal(counter_parallel, expected_value, 0.1)) {
    std::cerr << "Expected: " << expected_value << " Got: " << counter_parallel << std::endl;
    std::exit(112);
  }
}
int main()
{
    test_target_parallel();
}
