#include "Image.h"

int main()
{
  // IMG_Init();

  Image img("img.bmp");
  printf("%d\n", img.get_surface()->format->BitsPerPixel);

  IMG_Quit();

  return 0;
}
