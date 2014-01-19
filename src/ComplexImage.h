#ifndef __COMPLEX_IMAGE_H__
#define __COMPLEX_IMAGE_H__

#include <complex>
#include <memory>
#include <vector>
#include <cmath>
#include "Image.h"

class ComplexImage
{
public:
  typedef std::complex<double> complex_type;

  ComplexImage(uint16_t width, uint16_t height);
  explicit ComplexImage(Image *);

  uint16_t get_width() const;
  uint16_t get_height() const;

  void set_pixel(uint16_t x, uint16_t y, double real, double imaginary);
  void set_pixel(uint16_t x, uint16_t y, const complex_type &cplx_number);

  complex_type get_pixel(uint16_t x, uint16_t y) const;

  void swap_squares();
  void updateImage();

  Image get_real_image() const;
  Image get_imaginary_image() const;
  void save_magnitude_image(const char*) const;
  void save_phase_shift_image(const char*) const;

  int getWidth() {return width_;}
  int getHeight() {return height_;}

private:
  uint16_t width_, height_;

  std::vector<complex_type> data_;
  Image *orgimg;
};

#endif
