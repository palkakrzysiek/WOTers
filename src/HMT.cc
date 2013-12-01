#include "HMT.h"
#include "StructuralElements.h"

HMT::HMT(int m)
  : mask(m)
{
}

void HMT::perform(Image &image)
{
  int w = image.get_surface()->w;
  int h = image.get_surface()->h;

  Image workingCopy(image);

  int i, j, k, l;

  for (j = 1; j < h - 1; ++j) {
    for (i = 1; i < w - 1; ++i) {
    uint8_t r, g, b;
      SDL_GetRGB(image.get_pixel(i, j), image.get_surface()->format,
          &r, &g, &b);

    workingCopy.set_pixel(i, j, SDL_MapRGB(workingCopy.get_surface()->format,
                BLACK, BLACK, BLACK)); // just assume, check in next loops

      for (k = -1; k <= 1; ++k) {
        for (l = -1; l <= 1; ++l) {
          SDL_GetRGB(image.get_pixel(i+k, j+l), image.get_surface()->format,
              &r, &g, &b);
          if ((STRUCTURAL_ELEMENT[mask][k+1][l+1] == ACTIVE && r != BLACK) ||
              (STRUCTURAL_ELEMENT[mask][k+1][l+1] == INACTIVE && r != WHITE)) {
            workingCopy.set_pixel(i, j, SDL_MapRGB(workingCopy.get_surface()->format,
                  WHITE, WHITE, WHITE));
          }
        }
      }
    }
  }

  image = std::move(workingCopy);
}
