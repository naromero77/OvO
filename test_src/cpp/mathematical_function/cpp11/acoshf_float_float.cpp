#include <cmath>
#include <iomanip>
#include <limits>
#include <iostream>
#include <cstdlib>
using namespace std;
bool almost_equal(float x, float y, int ulp) {
     return std::fabs(x-y) <= std::numeric_limits<float>::epsilon() * std::fabs(x+y) * ulp ||  std::fabs(x-y) < std::numeric_limits<float>::min();
}
void test_acoshf(){
    const int PROB_SIZE = 10;
   float x { 4.42 };
   float o_host {};
   float o_device {};
    for (int i= 0;  i < PROB_SIZE ; i++) {
    o_host +=  acoshf( x);
   }
   #pragma omp target map(tofrom: o_device )    reduction(+: o_device)
    for (int i= 0;  i < PROB_SIZE; i++)
    {
     o_device +=  acoshf( x);
    }
   if ( !almost_equal(o_host,o_device, 4) ) {
        std::cerr << std::setprecision (std::numeric_limits<float>::max_digits10 ) << "Host: " << o_host << " GPU: " << o_device << std::endl;
        std::exit(112);
    }
}
int main()
{
    test_acoshf();
}
