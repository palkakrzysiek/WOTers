#include "Image.h"
#include <cmath>

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

void Image::save(const std::string &filename)
{
  SDL_SaveBMP(image, filename);
}

// function setting individual pixel value
// depends on image format (bytes per pixel)
void Image::set_pixel(int x, int y, uint32_t pixel)
{
  int bpp = image->format->BytesPerPixel;
  uint8_t *p = (uint8_t *) image->pixels + y * image->pitch + x * bpp;

  switch (bpp)
  {
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
      if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
      {
          p[0] = (pixel >> 16) & 0xff;
          p[1] = (pixel >> 8) & 0xff;
          p[2] = pixel & 0xff;
      } 
      else 
      {
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
uint32_t Image::get_pixel(int x, int y)
{
  int bpp = image->format->BytesPerPixel;
  uint8_t *p = (uint8_t *) image->pixels + y * image->pitch + x * bpp;

  switch (bpp)
  {
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

    default:
      return 0;
  }
}

void Image::apply_transformation(Transformation *t)
{
  printf("Before transform\n");
  t->transform(*this);
  delete t;
}
