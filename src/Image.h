#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <SDL.h>
#include <string>
#include <cstdint>

#include "Operation.h"

class Operation;

// wrapper class for SDL_Surface
// simplifies operations on surfaces
class Image
{
public:
  // constructors

  Image(int width, int height, int bpp);

  Image(const std::string &filename);
  
  // copy constructors
  Image(Image &other);
  const Image& operator=(Image &other);

  // move constructors
  Image(Image &&other);
  Image(SDL_Surface *surface);
  const Image& operator=(Image &&other);

  ~Image();

  const SDL_Surface *get_surface();

  // pixel operations
  void set_pixel(int x, int y, uint32_t value);
  uint32_t get_pixel(int x, int y);

  // applying transformations
  void perform_operation(Operation *t);

  void save(const std::string& filename);

private:
  SDL_Surface *surface = nullptr;

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
