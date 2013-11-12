#ifndef _RALEIGH_FPDF_H__
#define _RALEIGH_FPDF_H__

#include "Operation.h"
#include "Histogram.h"

class RaleighFPDF : public Operation
{
public:
  RaleighFPDF(Histogram::Channel c, double a);

  void perform(Image &image);

private:
  double alpha;
  Histogram::Channel channel;

};

#endif