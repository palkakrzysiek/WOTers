#include "Image.h"
#include "Transformations.h"
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
  Image img(argv[2]);

  Transformation *t = nullptr;

  string o = argv[1];

  if (o == "b")
    t = new BrightnessTransformation(0.5);
  else if (o == "c") 
    t = new ContrastTransformation(0.5);
  else if (o == "n")
    t = new NegativeTransformation();
  else if (o == "h")   
    t = new HorizontalFlip();
  else if (o == "v")
    t = new VerticalFlip();
  else if (o == "d")
    t = new DiagonalFlip();
  else if(o == "r")
    t = new Resize(350, 1280, false);
  
  assert(t != nullptr);
  
  uint64_t timer = now();
  img.apply_transformation(t);
  timer = now() - timer;

  printf("%gs\n", (double)timer/1e6);

  img.save("out.bmp");

  return 0;
}
