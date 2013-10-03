#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <cstdio>

class Image
{
public:
  Image(const std::string &filename);
  ~Image();

  const SDL_Surface *get_surface();

private:
  SDL_Surface *image;

};

#endif
