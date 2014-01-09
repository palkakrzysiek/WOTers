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
  bool areAllCorrect = 0;

  for (i = 1; i < w - 1; ++i) {
    for (j = 1; j < h - 1; ++j) {
      areAllCorrect = true;
      workingCopy.set_pixel(i, j, SDL_MapRGB(workingCopy.get_surface()->format,
            BG, BG, BG)); // just assume, check in next nested loops
      for (k = -1; k <= 1; ++k) {
        for (l = -1; l <= 1; ++l) {
          SDL_GetRGB(image.get_pixel(i+k, j+l), image.get_surface()->format,
          &r, &g, &b);
          if (STRUCTURAL_ELEMENT[mask][k+1][l+1] == ACTIVE && r != FG) {
            areAllCorrect = false;
          }
        }
      }

      if (areAllCorrect) {
        workingCopy.set_pixel(i, j, SDL_MapRGB(workingCopy.get_surface()->format,
              FG, FG, FG));
      } else {
        workingCopy.set_pixel(i, j, SDL_MapRGB(workingCopy.get_surface()->format,
              BG, BG, BG));
      }

    }
  }

  image = std::move(workingCopy);
}

