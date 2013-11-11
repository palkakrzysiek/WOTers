#ifndef _RALEIGH_FPDF_H__
#define _RALEIGH_FPDF_H__

#include "Operation.h"
#include "Histogram.h"

class RaleightFPDF : public Operation
{
public:
  RaleightFPDF(Image *o, double a, double *r);

  void perform(Image &image);

private:
  Image *other;
  double alpha;
  double *result;

};

#endif