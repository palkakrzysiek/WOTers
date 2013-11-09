#include "Histogram.h"

int main(int argc, char *argv[])
{
  Image image(argv[1]);
  Histogram histogram(image);
  printf("mean: %g\n", histogram.cmean(Histogram::Channel::R));
  printf("variance: %g\n", histogram.cvariance(Histogram::Channel::R));
  printf("stddev: %g\n", histogram.cstdev(Histogram::Channel::R));
  printf("varcoi: %g\n", histogram.cvarcoi(Histogram::Channel::R));
  printf("asyco: %g\n", histogram.casyco(Histogram::Channel::R));
  // printf("varcoii: %g\n", histogram.cvarcoii(Histogram::Channel::R));
  printf("entropy: %g\n", histogram.centropy(Histogram::Channel::R));
  // histogram.save_as_image(Histogram::Channel::B, "histogram.bmp");
  // histogram.print_channel(Histogram::Channel::B);
  return 0;
}
