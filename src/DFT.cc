#include "FreqDomain.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <utility>      // std::move (objects)

typedef std::complex<double> complex_type;

void FreqDomain::DFT(bool inverse)
{
  int w = cimg->getWidth();
  int h = cimg->getHeight();
  int i, j;
  const auto J = std::complex<double>(0, 1);
  const double demdiv = 1.0 / (w*h);
  const double twoPi = 2.0 * M_PI;
  const auto eConst = static_cast<double>((inverse?1:-1)) * J * twoPi;
  ComplexImage temp(orgimg);

  if (inverse) {
    cimg->swap_squares();
  }

# pragma omp parallel for private(j)
  for (i = 0; i < w; i++) {
    for (j = 0; j < h; j++) {
      complex_type currentFreq = std::complex<double>(0, 0);
      for (int k = 0; k < w; k++) {
        for (int l = 0; l < h; l++) {
          currentFreq += cimg->get_pixel(k, l) *
                         exp(eConst * (static_cast<double>(i)*k/w + static_cast<double>(j)*l/h));
        }
      }

      if (inverse) {
        currentFreq *= demdiv;
      }

      temp.set_pixel(i, j, currentFreq);
    }
  }

  *cimg = std::move(temp);

  if (!inverse) {
    cimg->swap_squares();
  } else {
    cimg->updateImage();
  }

}
