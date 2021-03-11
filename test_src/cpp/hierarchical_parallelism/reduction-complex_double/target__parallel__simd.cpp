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
  if ( (std::signbit(std::real(x)) != std::signbit(std::real(gold))) or (std::signbit(std::imag(x)) != std::signbit(std::imag(gold))) )
  {
    x = std::abs(gold) - std::abs(x);
  }
  return std::abs(gold) * (1-tol) <= std::abs(x) && std::abs(x) <= std::abs(gold) * (1 + tol);
}
void test_target__parallel__simd() {
  const int N0 { 32768 };
  const complex<double> expected_value { N0 };
  complex<double> counter_parallel{};
  #pragma omp target map(tofrom: counter_parallel)
  #pragma omp parallel
  {
    #pragma omp simd
    for (int i0 = 0 ; i0 < N0 ; i0++ )
    {
      counter_parallel = counter_parallel + complex<double> { double { 1. } / omp_get_num_threads() };
    }
  }
  if (!almost_equal(counter_parallel, expected_value, 0.1)) {
    std::cerr << "Expected: " << expected_value << " Got: " << counter_parallel << std::endl;
    std::exit(112);
  }
}
int main()
{
    test_target__parallel__simd();
}
