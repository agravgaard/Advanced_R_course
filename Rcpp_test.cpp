#include <Rcpp.h>

/* GCC can do parallel stl if you link to tbb:
 * registerPlugin("tbb", plugin = function() {
       list(env = list(PKG_CXXFLAGS="",
                       PKG_LIBS="-ltbb"))
   }
   )
 */
// [[Rcpp::plugins(cpp2a, openmp, tbb)]]
#include <execution>

// This is a simple example of exporting a C++ function to R. You can
// source this function into an R session using the Rcpp::sourceCpp 
// function (or via the Source button on the editor toolbar). Learn
// more about Rcpp at:
//
//   http://www.rcpp.org/
//   http://adv-r.had.co.nz/Rcpp.html
//   http://gallery.rcpp.org/
//

// [[Rcpp::export]]
Rcpp::NumericVector timesTwo(Rcpp::NumericVector x) {
  return x * 2;
}

// [[Rcpp::export]]
bool is_odd(int i) {
  return i % 2 == 1;
}

// [[Rcpp::export]]
void copy_vec(const Rcpp::NumericVector& x) {
  auto y = x;
  y[0] = 100;
}

// [[Rcpp::export]]
auto test_parstl(Rcpp::NumericVector& x){
  std::transform(std::execution::par, x.begin(), x.end(), x.begin(), [](auto val){ return std::sqrt(val); });
  return x;
}

// You can include R code blocks in C++ files processed with sourceCpp
// (useful for testing and development). The R code will be automatically 
// run after the compilation.
//


/*** R
timesTwo(42)

x <- c(1., 2., 3.)
copy_vec(x)
x

test_parstl(x)
*/
