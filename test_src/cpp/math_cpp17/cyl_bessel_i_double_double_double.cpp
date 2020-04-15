
#include <cmath>

#include <limits>
#include <iostream>

using namespace std;

 
bool almost_equal(double x, double y, int ulp) {

     return std::fabs(x-y) <= std::numeric_limits<double>::epsilon() * std::fabs(x+y) * ulp ||  std::fabs(x-y) < std::numeric_limits<double>::min();

}


void test_cyl_bessel_i(){
   
   double in0 {  0.42 };
   
   double in1 {  0.42 };
   

   
   double out2_host;
   double out2_device;
   

    out2_host =  cyl_bessel_i( in0, in1);
   
   #pragma omp target map(from: out2_device )
   {
     out2_device =  cyl_bessel_i( in0, in1);
   }

   
   if ( !almost_equal(out2_host,out2_device,1) ) {
        std::cerr << "Host: " << out2_host << " GPU: " << out2_device << std::endl;
        throw std::runtime_error( "cyl_bessel_i give incorect value when offloaded");
    }
    
}

int main()
{
    test_cyl_bessel_i();
}