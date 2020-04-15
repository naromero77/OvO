
#include <cmath>

#include <limits>
#include <iostream>

using namespace std;

 
bool almost_equal(double x, double y, int ulp) {

     return std::fabs(x-y) <= std::numeric_limits<double>::epsilon() * std::fabs(x+y) * ulp ||  std::fabs(x-y) < std::numeric_limits<double>::min();

}


void test_modf(){
   
   double in0 {  0.42 };
   

   
   double out1_host;
   double out1_device;
   
   double out2_host;
   double out2_device;
   

    out2_host =  modf( in0, &out1_host);
   
   #pragma omp target map(from: out1_device, out2_device )
   {
     out2_device =  modf( in0, &out1_device);
   }

   
   if ( !almost_equal(out1_host,out1_device,1) ) {
        std::cerr << "Host: " << out1_host << " GPU: " << out1_device << std::endl;
        throw std::runtime_error( "modf give incorect value when offloaded");
    }
    
   if ( !almost_equal(out2_host,out2_device,1) ) {
        std::cerr << "Host: " << out2_host << " GPU: " << out2_device << std::endl;
        throw std::runtime_error( "modf give incorect value when offloaded");
    }
    
}

int main()
{
    test_modf();
}