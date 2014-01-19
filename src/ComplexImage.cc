#include "ComplexImage.h"

ComplexImage::ComplexImage(uint16_t width, uint16_t height)
 : width_(width),
   height_(height),
   data_(width_*height_)
{
}

ComplexImage::ComplexImage(Image *im) {
  orgimg = im;
  int w = orgimg->get_surface()->w;
  int h = orgimg->get_surface()->h;
  width_ = w;
  height_ = h;
  data_.reserve(width_*height_);
  int i, j;

# pragma omp parallel for private(j)
  for (i = 0; i < w; i++) {
    for (j = 0; j < h; j++) {
      uint8_t r, g, b;
      SDL_GetRGB(orgimg->get_pixel(i, j), orgimg->get_surface()->format,
                 &r, &g, &b);
      this->set_pixel(i, j, static_cast<double>(r), 0.0);
    }
  }
}

void ComplexImage::set_pixel(uint16_t x, uint16_t y, double real, double imaginary)
{
  data_[y * height_ + x].real(real);
  data_[y * height_ + x].imag(imaginary);
}

void ComplexImage::set_pixel(uint16_t x, uint16_t y, const complex_type &cplx_number)
{
  data_[y * height_ + x].real(cplx_number.real());
  data_[y * height_ + x].imag(cplx_number.imag());
}

ComplexImage::complex_type ComplexImage::get_pixel(uint16_t x, uint16_t y) const
{
  const complex_type &pixel = data_[y * height_ + x];

  return complex_type(pixel.real(), pixel.imag());
}

void ComplexImage::swap_squares () {
  int h_mid = height_ / 2;
  int w_mid = width_ / 2;
  int x, y;

# pragma omp parallel for private(y)
  for (x = 0; x < w_mid ; x++) {
    for (y = 0; y < h_mid; y++) {
      std::swap(data_[y * height_ + x], data_[(y + h_mid) * height_ + (x + w_mid)]);
      std::swap(data_[y * height_ + (x + w_mid)], data_[(y + h_mid) * height_ + x]);
    }
  }
}

void ComplexImage::save_magnitude_image(const char* filename) const {

  Image image(width_, height_, 24);
  int i, j, mag;
  i = j = mag = 0;

  double maxabs = 0.0;

# pragma omp parallel for private(j) shared(maxabs)
  for (i = 0; i < width_; i++) {
    for (j = 0; j < height_; j++) {
      auto temp = std::abs(this->get_pixel(i, j));
      if (temp > maxabs) {
#       pragma omp critical
        {
          if (temp > maxabs) {
            maxabs = temp;
          }
        }
      }
    }
  }

  const double logconstant = static_cast<double>(255) / std::log(1 + maxabs);

# pragma omp parallel for private(j)
  for (i = 0; i < width_; i++) {
    for (j = 0; j < height_; j++) {
      uint8_t val = trunc(logconstant * std::log(1 + std::abs(this->get_pixel(i, j))));
      image.set_pixel(i, j, SDL_MapRGB(image.get_surface()->format,
                         val, val, val));
    }
  }

  image.save(filename);
}

void ComplexImage::save_phase_shift_image(const char* filename) const {

  Image image(width_, height_, 24);
  int i, j;
  i = j = 0;

# pragma omp parallel for private(j)
  for (i = 0; i < width_; i++) {
    for (j = 0; j < height_; j++) {
      uint8_t arg = trunc(std::log(std::arg(this->get_pixel(i, j)) / 2 / M_PI * 255));
      image.set_pixel(i, j, SDL_MapRGB(image.get_surface()->format,
                         arg, arg, arg));
    }
  }

  image.save(filename);
}

void ComplexImage::updateImage() {
  int i, j;

# pragma omp parallel for private(j)
  for (i = 0; i < width_; i++) {
    for (j = 0; j < height_; j++) {
      uint8_t r = static_cast<uint8_t>(this->get_pixel(i, j).real());
      orgimg->set_pixel(i, j, SDL_MapRGB(orgimg->get_surface()->format,
            r, r, r));
    }
  }
}
