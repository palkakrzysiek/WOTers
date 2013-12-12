#include "Erosion.h"
#include "StructuralElements.h"


Erosion::Erosion(int m) : mask(m) {}

void Erosion::perform(Image &image)
{
  int w = image.get_surface()->w;
  int h = image.get_surface()->h;

  Image workingCopy(image);

  int i, j, k, l;
  uint8_t r, g, b;

//# pragma omp parallel for private(i)
// it does not work with parallel processing
  for (j = 1; j < h - 1; ++j) {
    for (i = 1; i < w - 1; ++i) {
      SDL_GetRGB(image.get_pixel(i, j), image.get_surface()->format,
          &r, &g, &b);
      //if (r == BG){
        //workingCopy.set_pixel(i, j, SDL_MapRGB(workingCopy.get_surface()->format,
              //BG, BG, BG)); // just assume, check in next nested loops
      //}
      //else {
        //workingCopy.set_pixel(i, j, SDL_MapRGB(workingCopy.get_surface()->format,
              //FG, FG, FG)); // just assume, check in next nested loops
      //}
      //printf("%d\n", r);
      if (r == BG) {
        for (k = -1; k <= 1; ++k) {
          for (l = -1; l <= 1; ++l) {
            //SDL_GetRGB(image.get_pixel(i+k, j+l), image.get_surface()->format,
            //&r, &g, &b);
            if (STRUCTURAL_ELEMENT[mask][k+1][l+1] == ACTIVE) {
              workingCopy.set_pixel(i+k, j+l, SDL_MapRGB(workingCopy.get_surface()->format,
                    BG, BG, BG));
            }
          }
        }
      }

    }
  }

  image = std::move(workingCopy);
}

