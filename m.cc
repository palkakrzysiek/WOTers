#include "Image.h"
#include "Operations.h"
#include <sys/time.h>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>

using namespace std;

static uint64_t now() {
  struct timeval tv;

  if (gettimeofday(&tv, NULL))
    abort();

  return tv.tv_sec * 1000000ULL + tv.tv_usec;
}

int main(int argc, char const *argv[])
{
  Image img(argv[1]);

  Image filtered(argv[2]);
  uint64_t result = 0;

  uint64_t timer = now();
  // img.perform_operation(new MeanSquareError(&filtered, &result));
  img.perform_operation(new AlphaTrimmedMeanFilter(6));
  timer = now() - timer;

  printf("%llu\n", result);

  printf("%gs\n", (double)timer/1e6);

  img.save("out.bmp");

  return 0;
}
