#include "Image.h"

Image::Image(const std::string &filename)
{
  image = IMG_Load(filename.c_str());
  if (image == nullptr)
  {
    fprintf(stderr, "Error: %s\n", IMG_GetError());
  }
}

Image::~Image()
{
  // SDL_DestorySurface(image);
}

const SDL_Surface *Image::get_surface()
{
  return image;
}
