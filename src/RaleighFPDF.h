#ifndef _RALEIGH_FPDF_H__
#define _RALEIGH_FPDF_H__

#include "Operation.h"
#include "Histogram.h"

class RaleighFPDF : public Operation
{
public:
  RaleighFPDF(double a);

  void perform(Image &image);

private:
  double alpha;

};

#endif