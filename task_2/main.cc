#include "Histogram.h"

int main(int argc, char *argv[])
{
  Image image(argv[1]);
  Histogram histogram(image);

  histogram.save_as_image(Histogram::Channel::G, "histogram.bmp");

  return 0;
}
