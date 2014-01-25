#include "FreqDomain.h"
using std::pow;
void FreqDomain::lowPass(double r) {
  int i, j, w, h;
  std::complex<double> current, mask;
  w = cimg->getWidth();
  h = cimg->getHeight();
  for (i = 0; i < w; i++) {
    for (j = 0; j < h; j++) {
      if (pow(i - w/2,2) + pow(j - h/2, 2) > r*r) {
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
      if (pow(i - w/2,2) + pow(j - h/2, 2) < r*r && !(i == w/2 && j == h/2)) {
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
      if ((pow(i - w/2,2) + pow(j - h/2, 2) < r1*r1 && !(i == w/2 && j == h/2)) ||
          (pow(i - w/2,2) + pow(j - h/2, 2) > r2*r2)) {
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
      if ((pow(i - w/2,2) + pow(j - h/2, 2) > r1*r1) &&
          (pow(i - w/2,2) + pow(j - h/2, 2) < r2*r2)) {
        cimg->set_pixel(i, j, 0, 0);
      }
    }
  }
}

void FreqDomain::directed(double an, double ra) {
  int i, j, w, h;
  w = cimg->getWidth();
  h = cimg->getHeight();
  int angle = an;
  int range = ra;
  //angle = (((angle+180)%360) - 180);
  angle = (angle+180) % 360;
  range = (range%360);
  int carg, csym;
  for (i = 0; i < w; i++) {
    for (j = 0; j < h; j++) {
      carg = (M_PI+std::arg(std::complex<double>(i - w/2, h - j - h/2)))/M_PI*180;
      //carg %= 360;
      csym = (carg + 180);



      if ( !((angle - range)%360 < carg%360 && carg%360 < (angle + range)%360) &&
           !((angle - range)%360 < csym%360 && csym%360 < (angle + range)%360) &&
           !(i == w/2 && j == h/2) ) {
        cimg->set_pixel(i, j, 0, 0);
      }
    }
  }
}


//void FreqDomain::directed(double an, double ra) {
  //int i, j, w, h;
  //w = cimg->getWidth();
  //h = cimg->getHeight();
  //int angle = an;
  //int range = ra;
  //angle = (((angle+180)%360) - 180);
  //range = (range%180);
  //int carg, csym;
  //for (i = 0; i < w; i++) {
    //for (j = 0; j < h; j++) {
      //carg = (M_PI+std::arg(std::complex<double>(i - w/2, h - j - h/2)))/M_PI*180;
      //csym = (carg + 180) % 180;
      //if ( !((angle - range)%180 < carg && carg < (angle + range)%180) &&
           //!((angle - range)%180 < csym && csym < (angle + range)%180) &&
           //!(i == w/2 && j == h/2)) {
        //cimg->set_pixel(i, j, 0, 0);
      //}
    //}
  //}
//}






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
