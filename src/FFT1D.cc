#include <complex>
#include <vector>
#include "FreqDomain.h"

void FreqDomain::fft1d(std::vector<std::complex<double>> *in, bool inverse) {
  //std::vector<std::complex<double>> vecCopy(in);

  auto bInverse = [](unsigned int input, int max)->unsigned int{
  unsigned int output = 0;
  unsigned int n = log2(max);
  unsigned int i = 0;
  for (i = 0; i < n; i++)
    if ((input >> i) & 0x1)
      output |=  (0x1 << (n - 1 - i));
  return output;
  };


  const auto J = std::complex<double>(0, 1);
  const double twoPi = 2.0 * M_PI;
  const auto eConst = static_cast<double>((inverse?1:-1)) * J * twoPi;
  int N = (*in).size();
  int i, j, k, delta, twiddle_factor;
  std::complex<double> W_N, W, t_0, t_1;

  delta = N/2; // distance between top and bootom part of "butterfly's wing"
  W_N = std::exp(eConst / static_cast<double>(N));
  for (i = 1; i <= log2(N) ; i++) { // for every stage
    for (j = 0; j < delta; j++) { // for every twiddle
      // how to find twiddle_num
      // http://www.dsprelated.com/showcode/232.php
      twiddle_factor = j * std::pow(2, i-1);
      W = std::pow(W_N, twiddle_factor);
      for (k = 0; k < N; k += 2*delta) { // for every butterfly operation with the same twiddle
        t_0 = (*in)[j+k] + (*in)[j+k+delta];
        t_1 = ((*in)[j+k] - (*in)[j+k+delta]) * W;
        (*in)[j+k] = t_0;
        (*in)[j+k+delta] = t_1;
      }
    }
    delta /= 2;
  }
  if (inverse) {
    for (i = 0; i < N; i++) {
      (*in)[i] /= N;
    }
  }
  // permute vector
  int r;
  for (i = 0; i < N; i++) {
    r = bInverse(i, N);
    if (r > i) {
      std::swap((*in)[r], (*in)[i]);
    }
  }
}
