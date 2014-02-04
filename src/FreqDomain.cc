#include "FreqDomain.h"
using std::pow;
void FreqDomain::lowPass(double r) {
  int i, j, w, h;
  std::complex<double> current, mask;
  w = cimg->getWidth();
  h = cimg->getHeight();
  for (i = 0; i < w; i++) {
    for (j = 0; j < h; j++) {
      if (pow(i - w/2, 2) + pow(j - h/2, 2) > r*r) {
        cimg->set_pixel(i, j, 0, 0);
      }
    }
  }
}
void FreqDomain::highPass(double r) {
  int i, j, w, h;
  std::complex<double> current, mask;
  w = cimg->getWidth();
  h = cimg->getHeight();
  for (i = 0; i < w; i++) {
    for (j = 0; j < h; j++) {
      if (pow(i - w/2, 2) + pow(j - h/2, 2) < r*r && !(i == w/2 && j == h/2)) {
        cimg->set_pixel(i, j, 0, 0);
      }
    }
  }
}

void FreqDomain::bandPass(double r1, double r2) {
  int i, j, w, h;
  std::complex<double> current, mask;
  w = cimg->getWidth();
  h = cimg->getHeight();
  for (i = 0; i < w; i++) {
    for (j = 0; j < h; j++) {
      if ((pow(i - w/2, 2) + pow(j - h/2, 2) < r1*r1 && !(i == w/2 && j == h/2)) ||
          (pow(i - w/2, 2) + pow(j - h/2, 2) > r2*r2)) {
        cimg->set_pixel(i, j, 0, 0);
      }
    }
  }
}

void FreqDomain::bandCut(double r1, double r2) {
  int i, j, w, h;
  std::complex<double> current, mask;
  w = cimg->getWidth();
  h = cimg->getHeight();
  for (i = 0; i < w; i++) {
    for (j = 0; j < h; j++) {
      if ((pow(i - w/2, 2) + pow(j - h/2, 2) > r1*r1) &&
          (pow(i - w/2, 2) + pow(j - h/2, 2) < r2*r2)) {
        cimg->set_pixel(i, j, 0, 0);
      }
    }
  }
}

void FreqDomain::directed(double angle, double range) {

  // http://stackoverflow.com/questions/9505862/shortest-distance-between-two-degree-marks-on-a-circle
  auto distance = [](double first, double second)->double{
      return 180.0 - std::fabs(std::fmod(std::fabs(first - second), 360.0) - 180.0);
  };

  int i, j, w, h;
  w = cimg->getWidth();
  h = cimg->getHeight();

  double carg;
  for (i = 0; i < w; i++) {
    for (j = 0; j < h; j++) {
      carg = (M_PI+std::arg(std::complex<double>(i - w/2, h - j - h/2)))/M_PI*180;
      if ( !(distance(carg, angle) < range) &&
           // for symmetry
           !(distance(carg, angle + 180.0) < range) &&
           !(i == w/2 && j == h/2) ) {
        cimg->set_pixel(i, j, 0, 0);
      }
    }
  }
}

void FreqDomain::phaseModify(int l, int k) {
  int n, m, w, h;
  const auto J = std::complex<double>(0, 1);
  w = cimg->getWidth();
  h = cimg->getHeight();
  for (n = 0; n < w; n++) {
    for (m = 0; m < h; m++) {
      cimg->set_pixel(n, m,
      cimg->get_pixel(n, m) * std::exp(J * (
        (static_cast<double>(-1) * n * k * 2 * M_PI/w)+
        (static_cast<double>(-1) * m * l * 2 * M_PI/h)+
        static_cast<double>(k+l) * M_PI
        )));
    }
  }
}
