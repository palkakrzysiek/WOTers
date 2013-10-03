#include "Image.h"

int main(int argc, char *argv[])
{
  Image img("img.bmp");
  printf("%d\n", img.get_surface()->format->BitsPerPixel);

  return 0;
}
