#include "Image.h"
#include "BrightnessTransformation.h"
#include <sys/time.h>
#include <cstdint>
#include <iostream>
#include <iomanip>

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
  
  uint64_t timer = now();
  img.apply_transformation(new BrightnessTransformation(0.5));
  timer = now() - timer;

  cout << setprecision(4) << (double)timer/1e6 << " s" << endl;

  img.save();

  return 0;
}
