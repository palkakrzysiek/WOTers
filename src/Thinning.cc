#include "Thinning.h"

void Thinning::perform(Image &image)
{
  // New image = Old - Old HMT B(n)
  int w = image.get_surface()->w;
  int h = image.get_surface()->h;
  // it works only for monochromatic images
  image.perform_operation(new Binarize());

  Image previousImage(image);

  // just for debugging
  int loopCouter = 0;

  bool doContinue = true;
  while (doContinue) {
    loopCouter++;
    int i, j, k;
    int counter = 0;
    // for 8 different structural elements
    for (i = 0; i < 8; i++) {
      Image workingCopy(image);
      workingCopy.perform_operation(new HMT(i));
      // subtrat values of original images from result of HMT
      for (j = 1; j < w - 1; j++) {
        for (k = 1; k < h - 1; k++) {
          uint8_t r2, g2, b2;
          SDL_GetRGB(workingCopy.get_pixel(j, k), workingCopy.get_surface()->format,
              &r2, &g2, &b2);
          // if current pixel in image with result of HMT have foreground
          // color, than set value of original image to background color
          if (r2 == FG) {
            image.set_pixel(j, k, SDL_MapRGB(image.get_surface()->format,
                  BG, BG, BG));
          }
        }
      }
    }

    // counter of differences
    counter = 0;
    // compare previous state of image, with that after subtracting of results
    // of 8 HMT operations
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
      // if they are the same, do not continue
    if (counter == 0)
      doContinue = false;
    previousImage = image;
  }


}
