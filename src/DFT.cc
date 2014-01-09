#include "DFT.h"
#include <cmath>
#include <complex>
#include <algorithm>

void DFT::perform(Image &image)
{
  int w = image.get_surface()->w;
  int h = image.get_surface()->h;

  Image copy(image);

  std::complex<double> imaginary_unit(0.0, 1.0);

  int i, j;

  // first 1D iteration
  # pragma omp parallel for private(j)
  for (i = 0; i < w; ++i)
  {
    for (j = 0; j < h; ++j)
    {
      uint8_t r, g, b;
      std::complex<double> r2, g2, b2;

      for (int k = 0; k < w; ++k)
      {
        SDL_GetRGB(image.get_pixel(k, j), image.get_surface()->format,
                   &r, &g, &b);

        std::complex<double> e = std::exp(imaginary_unit * std::complex<double>(-2.0 *
                                          M_PI * (double) i * k / w));

        r2 += std::complex<double>(r, 0.0) * e;
        g2 += std::complex<double>(g, 0.0) * e;
        b2 += std::complex<double>(b, 0.0) * e;
      }

      copy.set_pixel(i, j, SDL_MapRGB(copy.get_surface()->format,
                     trunc(std::abs(r2)),
                     trunc(std::abs(g2)),
                     trunc(std::abs(b2))));
    }
  }

  image = std::move(copy);
  Image copy2(copy);

  // second  1D operation
# pragma omp parallel for private(i)
  for (j = 0; j < h; ++j)
  {
    for (i = 0; i < w; ++i)
    {
      uint8_t r, g, b;
      std::complex<double> r2, g2, b2;

      for (int k = 0; k < h; ++k)
      {
        SDL_GetRGB(copy2.get_pixel(i, k), copy2.get_surface()->format,
                   &r, &g, &b);

        std::complex<double> e = std::exp(imaginary_unit * std::complex<double>(-2.0 *
                                          M_PI * (double) j * k / h));

        r2 += std::complex<double>(r, 0.0) * e;
        g2 += std::complex<double>(g, 0.0) * e;
        b2 += std::complex<double>(b, 0.0) * e;
      }

      copy2.set_pixel(i, j, SDL_MapRGB(copy2.get_surface()->format,
                     trunc(std::abs(r2)),
                     trunc(std::abs(g2)),
                     trunc(std::abs(b2))));
    }
  }

  image = std::move(copy);
}
