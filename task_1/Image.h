#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <cstdio>
#include <cstdint>

class Image
{
public:
  Image(const std::string &filename);
  ~Image();

  const SDL_Surface *get_surface();

private:
  SDL_Surface *image;

  void set_pixel(int x, int y, uint32_t value);
  uint32_t get_pixel(int x, int y);

public:
  void save();

  void brightness(double by_percent);
  void contrast(double by_percent);
  void negative();

  void hflip();
  void vflip();
  void dflip();
  void shrink(double by_percent);
  void enlarge(double by_percent);

  void alpha();
  void cmean();

  void mse();
  void pmse();
  void snr();
  void psnr();
  void md();

};

#endif
