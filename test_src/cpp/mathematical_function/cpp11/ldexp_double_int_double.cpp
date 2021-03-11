#include <cmath>
#include <iomanip>
#include <limits>
#include <iostream>
#include <cstdlib>
using namespace std;
bool almost_equal(double x, double y, int ulp) {
     return std::fabs(x-y) <= std::numeric_limits<double>::epsilon() * std::fabs(x+y) * ulp ||  std::fabs(x-y) < std::numeric_limits<double>::min();
}
void test_ldexp(){
    const int PROB_SIZE = 10;
   double in0 { 0.42 };
   int in1 { 1 };
   double out2_host {};
   double out2_device {};
    for (int i= 0;  i < PROB_SIZE ; i++) {
    out2_host +=  ldexp( in0, in1);
   }
   #pragma omp target map(tofrom: out2_device )    reduction(+: out2_device)
    for (int i= 0;  i < PROB_SIZE; i++)
    {
     out2_device +=  ldexp( in0, in1);
    }
   if ( !almost_equal(out2_host,out2_device, 4) ) {
        std::cerr << std::setprecision (std::numeric_limits<double>::max_digits10 ) << "Host: " << out2_host << " GPU: " << out2_device << std::endl;
        std::exit(112);
    }
}
int main()
{
    test_ldexp();
}
