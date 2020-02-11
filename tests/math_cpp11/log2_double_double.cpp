#include <cassert>

#include <cmath>
#include <limits>
#include <iomanip>
#include <iostream>
#include <type_traits>
#include <algorithm>

// Some function, like "assoc_laguerre" need to be called with "std::" 
using namespace std;
 
template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
    almost_equal(T x, T y, int ulp)
{
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::fabs(x-y) <= std::numeric_limits<T>::epsilon() * std::fabs(x+y) * ulp
        // unless the result is subnormal
        || std::fabs(x-y) < std::numeric_limits<T>::min();
}

template<class T>
typename std::enable_if<std::numeric_limits<T>::is_integer, bool>::type
    almost_equal(T x, T y, int ulp)
{
    return x == y ;
} 

void test_log2(){
   
   double x = 0.42;
   

   double o_host = log2( x);

   double o_gpu ; 
   #pragma omp target defaultmap(tofrom:scalar)
   {
   o_gpu = log2( x);
   }

   auto bo = almost_equal(o_host,o_gpu,1) ;
   if ( bo != true ) {
        std::cerr.precision(std::numeric_limits<double>::digits);
        std::cerr << "Host: " << o_host << " GPU: " << o_gpu << std::endl;
        assert ( bo );
    }
}

int main()
{
    test_log2();
}
