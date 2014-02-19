#include "Resize.h"
#include <SDL.h>

Resize::Resize(const std::tuple<double, int, int> &value)
  : scale_x(std::get<0>(value)),
    scale_y(scale_x),
    width(std::get<1>(value)),
    height(std::get<2>(value)),
    keep_ratio(false)
{
}

void Resize::perform(Image &image)
{
  // calculating sizes and scales
  if (width > 0 && height > 0)
  {
    scale_x = ((double) width/image.get_surface()->w);

    if (keep_ratio)
    {
      height = scale_x * image.get_surface()->h;
      scale_y = scale_x;
    }
    else
    {
      scale_y = ((double) height/image.get_surface()->h);
      height = scale_y * image.get_surface()->h;
    }
  }
  else
  {
    width = scale_x * image.get_surface()->w;
    height = scale_y * image.get_surface()->h;
  }

  // creating empty SDL_Surface of new size
  SDL_Surface *sptr = SDL_CreateRGBSurface(image.get_surface()->flags,
                                           width,
                                           height,
                                           image.get_surface()->format->BitsPerPixel,
                                           image.get_surface()->format->Rmask,
                                           image.get_surface()->format->Gmask,
                                           image.get_surface()->format->Bmask,
                                           image.get_surface()->format->Amask);

  if (sptr == nullptr)
  {
    fprintf(stderr, "Error: %s\n", SDL_GetError());
    exit(1);
  }

  // when depth is 8 SDL_CreateRGBSurface allocates empty palette
  // which SDL_ConvertSurface considers an error causing
  // segmentation fault

  // manually copying the palette
  if (image.get_surface()->format->BitsPerPixel <= 8)
  {
    SDL_SetPaletteColors(sptr->format->palette,
                         &*image.get_surface()->format->palette->colors,
                         0,
                         image.get_surface()->format->palette->ncolors);
  }

  Image resized(sptr);

  int i, j;

# pragma omp parallel for private(i)
  for (j = 0; j < height; ++j)
  {
    for (i = 0; i < width; ++i)
    {
      resized.set_pixel(i, j, image.get_pixel(i/scale_x, j/scale_y));
    }
  }

  // replacing previous image with the resized one
  image = std::move(resized);
}
