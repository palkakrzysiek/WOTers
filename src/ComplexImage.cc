#include "ComplexImage.h"

ComplexImage::ComplexImage(uint16_t width, uint16_t height)
 : width_(width),
   height_(height),
   data_(width_*height_)
{
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
  auto &pixel = data_[y * height_ + x];

  return complex_type(pixel.real(), pixel.imag());
}
