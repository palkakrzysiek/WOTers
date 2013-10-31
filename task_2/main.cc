#include "Histogram.h"

int main(int argc, char *argv[])
{
  Image image(argv[1]);
  Histogram histogram(image);
  printf("%g\n", histogram.cmean(Histogram::Channel::R));
  histogram.save_as_image(Histogram::Channel::B, "histogram.bmp");
  histogram.print_channel(Histogram::Channel::B);
  return 0;
}
