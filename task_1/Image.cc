#include "Image.h"

Image::Image(const std::string &filename)
{
  image = IMG_Load(filename.c_str());
  if (image == nullptr)
  {
    fprintf(stderr, "Error: %s\n", IMG_GetError());
    exit(1);
  }
}

Image::~Image()
{
}

const SDL_Surface *Image::get_surface()
{
  return image;
}

void Image::save()
{
  SDL_SaveBMP(image, "out.bmp");
}

void Image::set_pixel(int x, int y, uint32_t pixel)
{
    int bpp = image->format->BytesPerPixel;
    uint8_t *p = (uint8_t *)image->pixels + y * image->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(uint16_t *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(uint32_t *)p = pixel;
        break;
    }
}

uint32_t Image::get_pixel(int x, int y)
{
    int bpp = image->format->BytesPerPixel;
    uint8_t *p = (uint8_t *)image->pixels + y * image->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *(uint8_t *)p;
        break;

    case 2:
        return *(uint16_t *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(uint32_t *)p;
        break;
    }
}

void Image::negative()
{
  uint16_t *pixels = (uint16_t*) image->pixels;

  for (int i = 0; i < image->w; ++i)
  {
    for (int j = 0; j < image->h; ++j)
    {
      set_pixel(i, j, ~get_pixel(i, j));
    }
  }
}
