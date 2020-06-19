#include <iostream>
#include <cstdlib>
#include <cmath>
#include <complex>
using std::complex;
#ifdef _OPENMP
#include <omp.h>
#else
int omp_get_num_teams() {return 1;}
int omp_get_num_threads() {return 1;}
#endif
bool almost_equal(complex<double> x, complex<double> gold, float tol) {
  return std::abs(gold) * (1-tol) <= std::abs(x) && std::abs(x) <= std::abs(gold) * (1 + tol);
}
void test_target__teams__parallel__simd() {
  const int N0 { 262144 };
  const complex<double> expected_value { N0 };
  #pragma omp declare reduction(+: complex<double>: omp_out += omp_in)
  complex<double> counter_teams{};
  #pragma omp target map(tofrom: counter_teams)
  #pragma omp teams reduction(+: counter_teams)
  {
    complex<double> counter_parallel{};
    #pragma omp parallel reduction(+: counter_parallel)
    {
      complex<double> counter_N0{};
      #pragma omp simd reduction(+: counter_N0)
      for (int i0 = 0 ; i0 < N0 ; i0++ )
      {
        counter_N0 = counter_N0 +  1. ;
      }
      counter_parallel = counter_parallel + complex<double> { counter_N0.real() / omp_get_num_threads() };
    }
    counter_teams = counter_teams + complex<double> { counter_parallel.real() / omp_get_num_teams() };
  }
  if (!almost_equal(counter_teams, expected_value, 0.1)) {
    std::cerr << "Expected: " << expected_value << " Got: " << counter_teams << std::endl;
    std::exit(112);
  }
}
int main()
{
    test_target__teams__parallel__simd();
}