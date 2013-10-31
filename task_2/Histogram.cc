#include "Histogram.h"
#include <cstring>
#include <cassert>
#include <cmath>
#include <algorithm>

Histogram::Histogram(Image &image)
{
  int w = image.get_surface()->w;
  int h = image.get_surface()->h;

  n_pixels = w * h;

  int i, j;

// # pragma omp parallel for default(shared) private(i)
  for (j = 0; j < h; ++j)
  {
    for (i = 0; i < w; ++i)
    {
      uint8_t r, g, b, a;

      SDL_GetRGBA(image.get_pixel(i, j), image.get_surface()->format,
                  &r, &g, &b, &a);

// #     pragma omp flush(pixels_r[r])
      ++pixels_r[r];

// #     pragma omp flush(pixels_g[g])
      ++pixels_g[g];

// #     pragma omp flush(pixels_b[b])
      ++pixels_b[b];

// #     pragma omp flush(pixels_a[a])
      ++pixels_a[a];
      // printf("%hu, %hu, %hu, %hu\n", r, g, b, a);
    }
  } 
}

void Histogram::print_channel(Channel c)
{
  // std::map<uint8_t, uint64_t> *ptr;

  // if (c == R)
  //   ptr = &pixels_r;
  // else if (c == G)
  //   ptr = &pixels_g;
  // else if (c == B)
  //   ptr = &pixels_b;
  // else if (c == A)
  //   ptr = &pixels_a;

  // for (const auto &i : *ptr)
  //   printf("[%hu] = %llu\n", i.first, i.second);
  for (auto i : pixels_r)
    printf("%llu\n", i);
}

double Histogram::cmean(Channel c)
{
  // int w = image.get_surface()->w;
  // int h = image.get_surface()->h;

  uint64_t *ptr = nullptr;

  if (c == R)
    ptr = pixels_r;
  else if (c == G)
    ptr = pixels_g;
  else if (c == B)
    ptr = pixels_b;
  else if (c == A)
    ptr = pixels_a;

  assert(ptr != nullptr);

  double result = 0.0;

# pragma omp parallel for reduction(+:result)
  for (int i = 0; i < 256; ++i)
  {
    result += (double) i * ptr[i];
  }

  result /= n_pixels;

  return result;
}

double Histogram::cvariance(Channel c)
{
  uint64_t *ptr = nullptr;

  if (c == R)
    ptr = pixels_r;
  else if (c == G)
    ptr = pixels_g;
  else if (c == B)
    ptr = pixels_b;
  else if (c == A)
    ptr = pixels_a;

  assert(ptr != nullptr);

  double result = 0.0;
  double m = cmean(c);

# pragma omp parallel for reduction(+:result)
  for (int i = 0; i < 256; ++i)
  {
    result += (i - m) * (i - m) * ptr[i];
  }

  result /= n_pixels;

  return result;
}

double Histogram::cstdev(Channel c)
{
  return sqrt(cvariance(c));
}

double Histogram::cvarcoi(Channel c)
{
  return cstdev(c) / cmean(c);
}

double Histogram::casyco(Channel c)
{
  uint64_t *ptr = nullptr;

  if (c == R)
    ptr = pixels_r;
  else if (c == G)
    ptr = pixels_g;
  else if (c == B)
    ptr = pixels_b;
  else if (c == A)
    ptr = pixels_a;

  assert(ptr != nullptr);

  double mean = cmean(c);

  double result = 0.0;

# pragma omp parallel for reduction(+:result)
  for (int i = 0; i < 256; ++i)
  {
    result += pow(i - mean, 3) * ptr[i];
  }

  result /= n_pixels;
  mean = (1.0 / pow(cstdev(c), 3)) * result;

  return mean;
}

void Histogram::save_as_image(Channel c, const std::string &filename)
{
  uint64_t *ptr = nullptr;

  Image image(768, 510, 24);
  int8_t dr = 0, dg = 0, db = 0; 

  if (c == R)
  {
    ptr = pixels_r;
    dr = 1;
  }
  else if (c == G)
  {
    ptr = pixels_g;
    dg = 1;
  }
  else if (c == B)
  {
    ptr = pixels_b;
    db = 1;
  }
  else if (c == A)
  {
    ptr = pixels_a;
    dr = -1;
    dg = -1;
    db = -1;
  }

  assert(ptr != nullptr);

  int i, j;

  int w = image.get_surface()->w;
  int h = image.get_surface()->h;

  uint64_t max = *std::max_element(ptr, ptr + 256);
  double f = (double) max / (h - 5);
  printf("%f\n", f);

# pragma omp parallel for private(i)
  for (j = 0; j < h; ++j)
  {
    for (i = 0; i < w; ++i)
    {
      image.set_pixel(i, j, 0xffffff);
    }
  }
  
# pragma omp parallel for private(j)
  for (i = 0; i < w; ++i)
  {
    if (ptr[i / 3] > 0)
    {
      for (j = 0; j < (ptr[i / 3] / f); ++j)
      {
        image.set_pixel(i, h - j - 1, SDL_MapRGB(image.get_surface()->format,
                        Operation::trunc((i / 3) * dr),
                        Operation::trunc((i / 3) * dg),
                        Operation::trunc((i / 3) * db)));
      }
    }
  }

  image.save(filename);
}
