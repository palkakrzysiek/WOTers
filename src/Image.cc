#include "Image.h"
#include <SDL_image.h>
#include <cstdio>
#include <utility>

// create empty image
Image::Image(int width, int height, int bpp)
{
  // uint32_t rmask, gmask, bmask, amask;

  // if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
  // {
  //   rmask = 0xff000000;
  //   gmask = 0x00ff0000;
  //   bmask = 0x0000ff00;
  //   amask = 0x000000ff;
  // }
  // else
  // {
  //   amask = 0xff000000;
  //   bmask = 0x00ff0000;
  //   gmask = 0x0000ff00;
  //   rmask = 0x000000ff;
  // }

  // surface = SDL_CreateRGBSurface(0, width, height, bpp, rmask, gmask, bmask, amask);
  surface = SDL_CreateRGBSurface(0, width, height, bpp, 0, 0, 0, 0);

  if (surface == nullptr)
  {
    fprintf(stderr, "Error: %s\n", IMG_GetError());
    exit(1);
  }
}

// create image from file
Image::Image(const std::string &filename)
{
  surface = IMG_Load(filename.c_str());
  if (surface == nullptr)
  {
    fprintf(stderr, "Error: %s\n", IMG_GetError());
    exit(1);
  }
}

// copying constructor
Image::Image(Image &other)
{
  surface = SDL_ConvertSurface((SDL_Surface *) other.get_surface(),
                             other.get_surface()->format,
                             other.get_surface()->flags);
}

// copying assignment operator
const Image& Image::operator=(Image &other)
{
  if (surface != nullptr)
  {
    SDL_FreeSurface(surface);
  }

  surface = SDL_ConvertSurface((SDL_Surface *) other.get_surface(),
                             other.get_surface()->format,
                             other.get_surface()->flags);

  return *this;
}

// move constructor
Image::Image(Image &&other)
{
  surface = other.surface;
  other.surface = nullptr;
}

// moving surface
Image::Image(SDL_Surface *other)
{
  surface = other;
  other = nullptr;
}

// move assignment operator
const Image& Image::operator=(Image &&other)
{
  if (surface != nullptr)
  {
    SDL_FreeSurface(surface);
  }

  surface = other.surface;
  other.surface = nullptr;

  return *this;
}

Image::~Image()
{
  if (surface != nullptr)
  {
    SDL_FreeSurface(surface);
  }
}

const SDL_Surface *Image::get_surface()
{
  return surface;
}

void Image::save(const std::string &filename)
{
  if (surface != nullptr)
  {
    SDL_SaveBMP(surface, filename.c_str());
  }
}

// function setting individual pixel value
// depends on surface format (bytes per pixel)
void Image::set_pixel(int x, int y, uint32_t pixel)
{
  int bpp = surface->format->BytesPerPixel;

  // finding address of the pixel
  uint8_t *p = (uint8_t *) surface->pixels + y * surface->pitch + x * bpp;

  switch (bpp)
  {
    // 8 bit
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
// depends on surface format (bytes per pixel)
uint32_t Image::get_pixel(int x, int y)
{
  int bpp = surface->format->BytesPerPixel;

  // finding address of the pixel
  uint8_t *p = (uint8_t *) surface->pixels + y * surface->pitch + x * bpp;

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

void Image::perform_operation(Operation *t)
{
  t->perform(*this);
  delete t;
}

bool Image::grayscale() const
{
  return surface->format->BitsPerPixel <= 8;
}

