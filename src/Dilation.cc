#include "Dilation.h"
#include "StructuralElements.h"

void Dilation::perform(Image &image)
{
  int w = image.get_surface()->w;
  int h = image.get_surface()->h;

  Image workingCopy(image);

  int i, j, k, l;

# pragma omp parallel for private(i)
  for (j = 1; j < h - 1; ++j) {
    for (i = 1; i < w - 1; ++i) {
    uint8_t r, g, b;
      SDL_GetRGB(image.get_pixel(i, j), image.get_surface()->format,
          &r, &g, &b);
      if (r == WHITE){ // don't check empty pixels
        continue;
      }

      for (k = -1; k <= 1; ++k) {
        for (l = -1; l <= 1; ++l) {
          SDL_GetRGB(image.get_pixel(i+k, j+l), image.get_surface()->format,
              &r, &g, &b);
          if (STRUCTURAL_ELEMENT[8][k+1][l+1] == ACTIVE) {
            workingCopy.set_pixel(i+k, j+l, SDL_MapRGB(workingCopy.get_surface()->format,
                  BLACK, BLACK, BLACK));
          }
        }
      }
    }
  }

  image = std::move(workingCopy);
}
