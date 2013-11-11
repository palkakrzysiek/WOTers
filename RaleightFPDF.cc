#include "RaleightFPDF.h"
#include <cmath>
#include <algorithm>

RaleightFPDF::RaleightFPDF(Image *o, double a, double *r)
  : other(o),
    alpha(a),
    result(r)
{

}

void RaleightFPDF::perform(Image &image)
{
  Histogram f(*other);
  Histogram g(image);

  uint64_t g_min = *std::min_element(g.get_r(), g.get_r() + 256);

  double sum = 0.0;

# pragma omp parallel for reduction(+:sum)
  for (int i = 0; i < 256; ++i)
  {
    /* code */
  }

  *result = g_min;
}
