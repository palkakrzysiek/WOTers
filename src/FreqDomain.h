#ifndef SRC_FREQDOMAIN_H_
#define SRC_FREQDOMAIN_H_

#include "ComplexImage.h"
#include "Image.h"
#include <complex>

class FreqDomain {
public:
  explicit FreqDomain(Image *o) : orgimg(o), cimg(new ComplexImage(o)) {}
  ~FreqDomain() {delete cimg;}
  void fft1d(std::vector<std::complex<double>> *, bool inverse);
  void DFT(bool inverse = false);
  void IDFT() {this->DFT(true);}
  void FFT(bool inverse = false);
  void IFFT() {this->FFT(true);}
  void save_magnitude_spectrum(const char* c) {cimg->save_magnitude_image(c);}
  void save_phase_shift_spectrum(const char* c) {cimg->save_phase_shift_image(c);}

private:
  Image *orgimg;
  ComplexImage *cimg;
};

#endif  // SRC_FREQDOMAIN_H_
