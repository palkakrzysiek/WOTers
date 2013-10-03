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
