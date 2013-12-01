#ifndef _RALEIGH_FPDF_H__
#define _RALEIGH_FPDF_H__

#include "Operation.h"
#include "Histogram.h"

class RaleighFPDF : public Operation
{
public:
  RaleighFPDF(Histogram::Channel c, const std::pair<int, int> &minmax);

  void perform(Image &image);

private:
  int g_min, g_max;
  Histogram::Channel channel;

};

#endif