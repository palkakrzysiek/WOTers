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
        {
            return p[0] << 16 | p[1] << 8 | p[2];
        }
        else
        {
            return p[0] | p[1] << 8 | p[2] << 16;
        }
        
        break;

    case 4:
        return *(uint32_t *)p;
        break;
    }
}

void Image::brightness(double by_percent)
{
  for (int i = 0; i < image->w; ++i)
  {
    for (int j = 0; j < image->h; ++j)
    {
      uint8_t r, g, b;
      SDL_GetRGB(get_pixel(i, j), image->format, &r, &g, &b);

      int by = by_percent * 0xff;

      if (r + by > 0xff)
      {
        r = 0xff;
      }
      else if (r + by < 0)
      {
        r = 0;
      }
      else
      {
        r += by;
      }

      if (g + by > 0xff)
      {
        g = 0xff;
      }
      else if (g + by < 0)
      {
        g = 0;
      }
      else
      {
        g += by;
      }

      if (b + by > 0xff)
      {
        b = 0xff;
      }
      else if (b + by < 0)
      {
        b = 0;
      }
      else
      {
        b += by;
      }

      set_pixel(i, j, SDL_MapRGB(image->format, r, g, b));
    }
  }
}


void Image::contrast(double by_percent)
{
  double c = by_percent * 255;

  double f = ((259.0 * (c + 255.0)) / (255.0 * (259.0 - c)));
  printf("f: %g\n", f);

  for (int i = 0; i < image->w; ++i)
  {
    for (int j = 0; j < image->h; ++j)
    {
      uint8_t r, g, b;
      SDL_GetRGB(get_pixel(i, j), image->format, &r, &g, &b);

      if (((r - 0x80) * f) + 0x80 > 0xff)
      {
        r = 0xff;
      }
      else if (((r - 0x80) * f) + 0x80 < 0)
      {
        r = 0;
      }
      else
      {
        r = ((r - 0x80) * f) + 0x80;
      }

      if (((g - 0x80) * f) + 0x80 > 0xff)
      {
        g = 0xff;
      }
      else if (((g - 0x80) * f) + 0x80 < 0)
      {
        g = 0;
      }
      else
      {
        g = ((g - 0x80) * f) + 0x80;
      }

      if (((b - 0x80) * f) + 0x80 > 0xff)
      {
        b = 0xff;
      }
      else if (((b - 0x80) * f) + 0x80 < 0)
      {
        b = 0;
      }
      else
      {
        b = ((b - 0x80) * f) + 0x80;
      }

      set_pixel(i, j, SDL_MapRGB(image->format, r, g, b));
    }
  }
}

void Image::negative()
{
  for (int i = 0; i < image->w; ++i)
  {
    for (int j = 0; j < image->h; ++j)
    {
      set_pixel(i, j, ~get_pixel(i, j));
    }
  }
}
