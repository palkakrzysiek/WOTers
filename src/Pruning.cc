#include "Pruning.h"

Pruning::Pruning(int l) : length(l) {}

void Pruning::perform(Image &image)
{
  int w = image.get_surface()->w;
  int h = image.get_surface()->h;
  image.perform_operation(new Binarize());
  Image previousImage(image);

  // remove ends of the lines
  int i, j, k, l;
  for (l = 0; l < length; l++) {
    for (i = 9; i < 17; i++) {
      Image workingCopy(image);
      workingCopy.perform_operation(new HMT(i));
      for (j = 1; j < w - 1; j++) {
        for (k = 1; k < h - 1; k++) {
          uint8_t r2, g2, b2;
          SDL_GetRGB(workingCopy.get_pixel(j, k), workingCopy.get_surface()->format,
              &r2, &g2, &b2);
          if (r2 == FG) {
            image.set_pixel(j, k, SDL_MapRGB(image.get_surface()->format,
                  BG, BG, BG));
          }
        }
      }
    }
  }
  // find endpoints
  Image endpoints(image);
  for (l = 0; l < length; l++) {
    for (j = 1; j < w - 1; j++) { // clear endpoints
      for (k = 1; k < h - 1; k++) {
        endpoints.set_pixel(j, k, SDL_MapRGB(endpoints.get_surface()->format,
              BG, BG, BG));
      }
    }
    for (i = 18; i < 25; i++) {
      Image workingCopy(image);
      workingCopy.perform_operation(new HMT(i));
      for (j = 1; j < w - 1; j++) {
        for (k = 1; k < h - 1; k++) {
          uint8_t r1, g1, b1;
          uint8_t r2, g2, b2;
          SDL_GetRGB(endpoints.get_pixel(i, j), endpoints.get_surface()->format,
              &r1, &g1, &b1);
          SDL_GetRGB(workingCopy.get_pixel(j, k), workingCopy.get_surface()->format,
              &r2, &g2, &b2);
          if (r2 == FG) { // if it is endpoint
            endpoints.set_pixel(j, k, SDL_MapRGB(endpoints.get_surface()->format,
                  FG, FG, FG));
          }
        }
      }
    }

    // enlarge endpoints
    endpoints.perform_operation(new Dilation(17));
    // find product with original image
    for (j = 1; j < w - 1; j++) {
      for (k = 1; k < h - 1; k++) {
        uint8_t r1, g1, b1;
        uint8_t r2, g2, b2;
        SDL_GetRGB(endpoints.get_pixel(j, k), endpoints.get_surface()->format,
            &r1, &g1, &b1);
        SDL_GetRGB(previousImage.get_pixel(j, k), previousImage.get_surface()->format,
            &r2, &g2, &b2);
        if (r1 == FG && r2 == FG) {
          image.set_pixel(j, k, SDL_MapRGB(image.get_surface()->format,
                FG, FG, FG));
        }
      }
    }


  }


}
