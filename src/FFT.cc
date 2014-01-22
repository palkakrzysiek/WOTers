#include "FreqDomain.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <utility>      // std::move (objects)

typedef std::complex<double> complex_type;

void FreqDomain::FFT(bool inverse)
{
  int w = cimg->getWidth();
  int h = cimg->getHeight();
  int i, j;

  if (inverse) {
    cimg->swap_squares();
  }

  if ((w<2 || w&(w-1)) || (h<2 || h&(h-1))) {
    std::cerr << "width and height must be power of 2";
    exit(1);
  }

  //std::cout << "\n>>>>>>>>>>>>>\n";
  //for (int abc = 0; abc < h; abc++) {
    //std::cout << lineH[abc] << " ";
  //}

  std::vector<std::complex<double>> lineH(h);
  for (i = 0; i < w; i++) { // 1d fft for horizontal lines
    for (j = 0; j < h; j++) {
      lineH[j] = cimg->get_pixel(i, j);
    }
    this->fft1d(&lineH, inverse);
    for (j = 0; j < h; j++) {
      cimg->set_pixel(i, j, lineH[j]);
    }
  }

  std::vector<std::complex<double>> lineW(w);
  for (i = 0; i < h; i++) { // 1d fft for vertical lines
    for (j = 0; j < w; j++) {
      lineW[j] = cimg->get_pixel(j, i);
    }
    this->fft1d(&lineW, inverse);
    for (j = 0; j < w; j++) {
      cimg->set_pixel(j, i, lineW[j]);
    }
  }

  if (!inverse) {
    cimg->swap_squares();
  } else {
    cimg->updateImage();
  }


}
