#include "Histogram.h"

int main(int argc, char *argv[])
{
  Image image(argv[1]);
  Histogram histogram(image);

  return 0;
}
