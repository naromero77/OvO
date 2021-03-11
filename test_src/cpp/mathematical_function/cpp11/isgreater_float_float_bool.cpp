#include <cmath>
#include <iomanip>
#include <limits>
#include <iostream>
#include <cstdlib>
using namespace std;
void test_isgreater(){
    const int PROB_SIZE = 10;
   float in0 { 0.42 };
   float in1 { 0.42 };
   bool out2_host {};
   bool out2_device {};
    for (int i= 0;  i < PROB_SIZE ; i++) {
    out2_host +=  isgreater( in0, in1);
   }
   #pragma omp target map(tofrom: out2_device )    reduction(+: out2_device)
    for (int i= 0;  i < PROB_SIZE; i++)
    {
     out2_device +=  isgreater( in0, in1);
    }
   if ( out2_host != out2_device ) {
        std::cerr << std::setprecision (std::numeric_limits<bool>::max_digits10 ) << "Host: " << out2_host << " GPU: " << out2_device << std::endl;
        std::exit(112);
    }
}
int main()
{
    test_isgreater();
}
