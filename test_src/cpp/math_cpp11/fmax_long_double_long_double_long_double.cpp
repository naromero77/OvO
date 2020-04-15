
#include <cmath>

#include <limits>
#include <iostream>

using namespace std;

 
bool almost_equal(long double x, long double y, int ulp) {

     return std::fabs(x-y) <= std::numeric_limits<long double>::epsilon() * std::fabs(x+y) * ulp ||  std::fabs(x-y) < std::numeric_limits<long double>::min();

}


void test_fmax(){
   
   long double in0 {  0.42 };
   
   long double in1 {  0.42 };
   

   
   long double out2_host;
   long double out2_device;
   

    out2_host =  fmax( in0, in1);
   
   #pragma omp target map(from: out2_device )
   {
     out2_device =  fmax( in0, in1);
   }

   
   if ( !almost_equal(out2_host,out2_device,1) ) {
        std::cerr << "Host: " << out2_host << " GPU: " << out2_device << std::endl;
        throw std::runtime_error( "fmax give incorect value when offloaded");
    }
    
}

int main()
{
    test_fmax();
}