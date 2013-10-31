#include "Histogram.h"

int main(int argc, char *argv[])
{
  Image image(argv[1]);
  Histogram histogram(image);

  histogram.print_channel(Histogram::Channel::B);

  return 0;
}
