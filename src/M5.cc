#include "M5.h"
#include "StructuralElements.h"

void M5::perform(Image &image)
{
  int w = image.get_surface()->w;
  int h = image.get_surface()->h;
  Image workingCopy(image);
  Image previousImage(image);

  bool doContinue = true;
  int loopCouter = 0;
  while (doContinue) {
    loopCouter++;
    int i, j, k;
    int counter = 0;
    for (i = 0; i < 8; i++) {
      workingCopy.perform_operation(new HMT(i+1));
      for (j = 1; j < w - 1; j++) {
        for (k = 1; k < h - 1; k++) {
          uint8_t r2, g2, b2;
          SDL_GetRGB(workingCopy.get_pixel(j, k), workingCopy.get_surface()->format,
              &r2, &g2, &b2);
          if (r2 == BLACK) {
            image.set_pixel(j, k, SDL_MapRGB(image.get_surface()->format,
                  WHITE, WHITE, WHITE));
          }
        }
      }
      workingCopy = image;
    }

    for (i = 1; i < w - 1; i++) {
      for (j = 1; j < h - 1; j++) {
        uint8_t r1, g1, b1;
        uint8_t r2, g2, b2;
        SDL_GetRGB(image.get_pixel(i, j), image.get_surface()->format,
            &r1, &g1, &b1);
        SDL_GetRGB(previousImage.get_pixel(i, j), previousImage.get_surface()->format,
            &r2, &g2, &b2);
        if (r1 != r2) {
          counter++;
        }
      }
    }
    printf("Loop: %d, %d differences.\n", loopCouter, counter);
    if (counter == 0)
      doContinue = false;
    previousImage = image;
  }


}
