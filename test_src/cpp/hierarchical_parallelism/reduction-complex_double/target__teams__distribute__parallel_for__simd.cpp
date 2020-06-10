#include <iostream>
#include <cstdlib>
#include <cmath>
#include <complex>
using namespace std;
bool almost_equal(complex<double> x, complex<double> gold, float tol) {
        return abs(gold) * (1-tol) <= abs(x) && abs(x) <= abs(gold) * (1 + tol);
}
#pragma omp declare reduction(+: complex<double>: omp_out += omp_in)
void test_target__teams__distribute__parallel_for__simd(){
 const int N0 = 64;
 const int N1 = 64;
 const int N2 = 64;
 complex<double> counter{};
#pragma omp target map(tofrom: counter)
#pragma omp teams reduction(+: counter)
#pragma omp distribute
      for (int i0 = 0 ; i0 < N0 ; i0++ )
      {
#pragma omp parallel for reduction(+: counter)
      for (int i1 = 0 ; i1 < N1 ; i1++ )
      {
#pragma omp simd reduction(+: counter)
      for (int i2 = 0 ; i2 < N2 ; i2++ )
      {
counter += complex<double> { 1.0f };
    }
    }
    }
if ( !almost_equal(counter,complex<double> { N0*N1*N2 }, 0.1)  ) {
    std::cerr << "Expected: " << N0*N1*N2 << " Got: " << counter << std::endl;
    std::exit(112);
}
}
int main()
{
    test_target__teams__distribute__parallel_for__simd();
}
