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
  SDL_FreeSurface(image);
}

const SDL_Surface *Image::get_surface()
{
  return image;
}

void Image::save()
{
  SDL_SaveBMP(image, "out.bmp");
}

// function setting individual pixel value
// depends on image format (bytes per pixel)
// tak naprawdę to nie do końca rozumiem jak (i dlaczego tak) działa
// znalazłem w internecie
void Image::set_pixel(int x, int y, uint32_t pixel, SDL_Surface *surface = nullptr)
{
  if (surface == nullptr)
    surface = image;

  int bpp = surface->format->BytesPerPixel;
  uint8_t *p = (uint8_t *) surface->pixels + y * surface->pitch + x * bpp;

  switch (bpp) {
    // 8
    case 1:
      *p = pixel;
      break;

    // 16 bit
    case 2:
      *(uint16_t *) p = pixel;
      break;

    // 24 bit
    case 3:
      if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
          p[0] = (pixel >> 16) & 0xff;
          p[1] = (pixel >> 8) & 0xff;
          p[2] = pixel & 0xff;
      } else {
          p[0] = pixel & 0xff;
          p[1] = (pixel >> 8) & 0xff;
          p[2] = (pixel >> 16) & 0xff;
      }
      break;

    // 32 bit
    case 4:
      *(uint32_t *) p = pixel;
      break;
  }
}

// function getting individual pixel value
// depends on image format (bytes per pixel)
// tak naprawdę to nie do końca rozumiem jak (i dlaczego tak) działa
// znalazłem w internecie
uint32_t Image::get_pixel(int x, int y, SDL_Surface *surface = nullptr)
{
  if (surface == nullptr)
    surface = image;

  int bpp = surface->format->BytesPerPixel;
  uint8_t *p = (uint8_t *)surface->pixels + y * surface->pitch + x * bpp;

  switch (bpp) {
    // 8 bit
    case 1:
      return *(uint8_t *)p;
      break;

    // 16 bit
    case 2:
      return *(uint16_t *)p;
      break;

    // 24 bit
    case 3:
      if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
      {
          return p[0] << 16 | p[1] << 8 | p[2];
      }
      else
      {
          return p[0] | p[1] << 8 | p[2] << 16;
      }
        
      break;

    // 32 bit
    case 4:
      return *(uint32_t *)p;
      break;
  }
}

void Image::brightness(double by_percent)
{ 
  // birghtness can be changed from -255 to 255
  int by = by_percent * 0xff;

  uint8_t r, g, b;

  // change value of each individual pixel color
  // also check that color value is in range [0, 255]
  for (int i = 0; i < image->w; ++i)
  {
    for (int j = 0; j < image->h; ++j)
    {
      SDL_GetRGB(get_pixel(i, j), image->format, &r, &g, &b);

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

      // setting new pixel value
      set_pixel(i, j, SDL_MapRGB(image->format, r, g, b));
    }
  }
}


void Image::contrast(double by_percent)
{
  // contrast change varies from -255 to 255
  // thus c must be in range [-1.0, 1.0]
  double c = by_percent * 255;

  // calculate contrast factor
  double f = ((259.0 * (c + 255.0)) / (255.0 * (259.0 - c)));

  uint8_t r, g, b;

  // change contrast of each individual pixel color
  // also check that color value is in range [0, 255]
  for (int i = 0; i < image->w; ++i)
  {
    for (int j = 0; j < image->h; ++j)
    {
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

      // setting new pixel value
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

void Image::hflip()
{
  // iterate through the lines of image
  for (int j = 0; j < image->h; ++j)
  {
    for (int i = 0; i < image->w/2; ++i)
    {
      // assign the values of last pixels in the line of image
      // to the first pixel values of temp
      uint32_t temp = get_pixel(i, j);
      set_pixel(i, j, get_pixel(image->w - 1 - i, j));
      set_pixel(image->w - 1 - i, j, temp);
    }
  }
}

void Image::vflip()
{
  // iterate through the lines of image
  for (int i = 0; i < image->w; ++i)
  {
    for (int j = 0; j < image->h/2; ++j)
    {
      // assign the values of last pixels in the line of image
      // to the first pixel values of temp
      uint32_t temp = get_pixel(i, j);
      set_pixel(i, j, get_pixel(i, image->h - 1 - j));
      set_pixel(i, image->h - 1 - j, temp);
    }
  }

}

void Image::dflip()
{
  hflip();
  vflip();
}
