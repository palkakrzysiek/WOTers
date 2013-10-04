#include "Image.h"

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    fprintf(stderr, "usage\n");
    return 1;
  }

  Image img(argv[1]);
  // img.negative();
  img.brightness(0.5);
  img.save();

  return 0;
}
