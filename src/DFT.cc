#include "FreqDomain.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <utility>      // std::move (objects)

void FreqDomain::DFT(bool inverse)
{
  int w = cimg->getWidth();
  int h = cimg->getHeight();
  printf("%d, %d\n", w, h);
  int i, j, k, l;
  uint8_t r, g, b;
  std::complex<double> currentFreq;
  const auto J = std::complex<double>(0, 1);
  const double demdiv = 1.0 / (w*h);
  const double twoPi = 2.0 * M_PI;
  const auto eConst = static_cast<double>((inverse?1:-1)) * J * twoPi;
  ComplexImage temp(w, h);

  if (inverse) {
    cimg->swap_squares();
  }

  for (i = 0; i < w; i++) {
    for (j = 0; j < h; j++) {
      currentFreq = std::complex<double>(0, 0);
      //printf("%f\n", std::abs(cimg->get_pixel(i, j)));
      for (k = 0; k < w; k++) {
        for (l = 0; l < h; l++) {
          currentFreq += cimg->get_pixel(k, l) *
                         exp(eConst * static_cast<double>(static_cast<double>(i)*k/w + static_cast<double>(j)*l/h));
        }
      }

      if (!inverse) {
        currentFreq *= demdiv;
      }
      temp.set_pixel(i, j, currentFreq);
    }
  }
  *cimg = std::move(temp);
    if (!inverse) {
    cimg->swap_squares();
    cimg->save_magnitude_image("mag.bmp");
    cimg->save_phase_shift_image("pshift.bmp");
  } else {
    cimg->updateImage();
  }

}
