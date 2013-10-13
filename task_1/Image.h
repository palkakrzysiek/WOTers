#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <cstdio>
#include <cstdint>

#include "Transformation.h"

class Transformation;

// wrapper class for SDL_Surface
// simplifies operations on images
class Image
{
public:
  // constructors
  Image(const std::string &filename);
  Image(Image &other);
  Image(SDL_Surface *surface);
  const Image& operator=(Image &other);
  const Image& operator=(SDL_Surface *surface);

  ~Image();

  const SDL_Surface *get_surface();

  // pixel operations
  void set_pixel(int x, int y, uint32_t value);
  uint32_t get_pixel(int x, int y);

  // applying transformations
  void apply_transformation(Transformation *t);

  void save(const std::string& filename);

private:
  SDL_Surface *image;

  // void brightness(double by_percent);
  // void contrast(double by_percent);
  // void negative();

  // void hflip();
  // void vflip();
  // void dflip();
  // void shrink(double by_percent);
  // void enlarge(double by_percent);

  // void alpha();
  // void cmean();

  // void mse();
  // void pmse();
  // void snr();
  // void psnr();
  // void md();

};

#endif
