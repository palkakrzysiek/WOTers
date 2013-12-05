#include "Histogram.h"
#include <cstring>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>

Histogram::Histogram(Image &image)
{
  int w = image.get_surface()->w;
  int h = image.get_surface()->h;

  n_pixels = w * h;
  grayscale = (image.get_surface()->format->BitsPerPixel <= 8) ? true : false;

  int i, j;

  for (j = 0; j < h; ++j)
  {
    for (i = 0; i < w; ++i)
    {
      uint8_t r, g, b, a;

      SDL_GetRGBA(image.get_pixel(i, j), image.get_surface()->format,
                  &r, &g, &b, &a);

      ++pixels_r[r];
      ++pixels_g[g];
      ++pixels_b[b];
      ++pixels_a[a];
    }
  }
}

void Histogram::print_channel(Channel c)
{
  if (c == ALL)
  {
    print_channel(R);
    print_channel(G);
    print_channel(B);
    return;
  }

  uint32_t *ptr = pixels_r;

  if (c == R)
    ptr = pixels_r;
  else if (c == G)
    ptr = pixels_g;
  else if (c == B)
    ptr = pixels_b;
  else if (c == A)
    ptr = pixels_a;

  // printf("%f\n", (double) ptr[0] / n_pixels);

  for (int i = 0; i < 256; ++i)
    printf("[%d] = %u\n", i, ptr[i]);
}

double Histogram::cmean(Channel c)
{
  if (c == ALL)
    return (cmean(R) + cmean(G) + cmean(B)) / 3.0;

  uint32_t *ptr = pixels_r;

  if (c == R)
    ptr = pixels_r;
  else if (c == G)
    ptr = pixels_g;
  else if (c == B)
    ptr = pixels_b;
  else if (c == A)
    ptr = pixels_a;

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
  if (c == ALL)
    return (cvariance(R) + cvariance(G) + cvariance(B)) / 3.0;

  uint32_t *ptr = pixels_r;

  if (c == R)
    ptr = pixels_r;
  else if (c == G)
    ptr = pixels_g;
  else if (c == B)
    ptr = pixels_b;
  else if (c == A)
    ptr = pixels_a;

  double result = 0.0;
  double mean = cmean(c);

# pragma omp parallel for reduction(+:result)
  for (int i = 0; i < 256; ++i)
  {
    result += (double) (i - mean) * (i - mean) * ptr[i];
  }

  result /= n_pixels;

  return result;
}

double Histogram::cstdev(Channel c)
{
  if (c == ALL)
    return (cstdev(R) + cstdev(G) + cstdev(B)) / 3.0;

  return sqrt(cvariance(c));
}

double Histogram::cvarcoi(Channel c)
{
  if (c == ALL)
    return (cvarcoi(R) + cvarcoi(G) + cvarcoi(B)) / 3.0;

  return cstdev(c) / cmean(c);
}

double Histogram::cvarcoii(Channel c)
{
  if (c == ALL)
    return (cvarcoii(R) + cvarcoii(G) + cvarcoii(B)) / 3.0;

  uint32_t *ptr = pixels_r;

  if (c == R)
    ptr = pixels_r;
  else if (c == G)
    ptr = pixels_g;
  else if (c == B)
    ptr = pixels_b;
  else if (c == A)
    ptr = pixels_a;

  double result = 0.0;

# pragma omp parallel for reduction(+:result)
  for (int i = 0; i < 256; ++i)
  {
    result += pow(ptr[i], 2);
  }

  result /= pow(n_pixels, 256);

  return result;
}

double Histogram::casyco(Channel c)
{
  if (c == ALL)
    return (casyco(R) + casyco(G) + casyco(B)) / 3.0;

  uint32_t *ptr = pixels_r;

  if (c == R)
    ptr = pixels_r;
  else if (c == G)
    ptr = pixels_g;
  else if (c == B)
    ptr = pixels_b;
  else if (c == A)
    ptr = pixels_a;

  double mean = cmean(c);
  double stddev = cstdev(c);

  double result = 0.0;

# pragma omp parallel for reduction(+:result)
  for (int i = 0; i < 256; ++i)
  {
    result += pow(i - mean, 3) * ptr[i];
  }

  result /= n_pixels;
  result *= 1.0 / pow(stddev, 3);

  return result;
}

double Histogram::cflatco(Channel c)
{
  if (c == ALL)
    return (cflatco(R) + cflatco(G) + cflatco(B)) / 3.0;

  uint32_t *ptr = pixels_r;

  if (c == R)
    ptr = pixels_r;
  else if (c == G)
    ptr = pixels_g;
  else if (c == B)
    ptr = pixels_b;
  else if (c == A)
    ptr = pixels_a;

  double mean = cmean(c);
  double stddev = cstdev(c);

  double result = 0.0;

# pragma omp parallel for reduction(+:result)
  for (int i = 0; i < 256; ++i)
  {
    result += pow(i - mean, 4) * ptr[i] - 3.0;
  }

  result /= n_pixels;
  result *= 1.0 / pow(stddev, 4);

  return result;
}

double Histogram::centropy(Channel c)
{
  if (c == ALL)
    return (centropy(R) + centropy(G) + centropy(B)) / 3.0;

  uint32_t *ptr = pixels_r;

  if (c == R)
    ptr = pixels_r;
  else if (c == G)
    ptr = pixels_g;
  else if (c == B)
    ptr = pixels_b;
  else if (c == A)
    ptr = pixels_a;

  double result = 0.0;

# pragma omp parallel for reduction(+:result)
  for (int i = 0; i < 256; ++i)
  {
    double tmp = ((double)ptr[i]) * log2((double) ((double)ptr[i]) / ((double)n_pixels));

    if (!isinf(tmp) && !isnan(tmp))
    {
      result += tmp;
    }
  }

  result *= -1.0;
  result /= (double) n_pixels;
  return result;
}

void Histogram::save_as_image(Channel c, const std::string &filename)
{
  uint32_t *ptr = pixels_r;

  Image image(768, 520, 24);
  int8_t dr = 0, dg = 0, db = 0;

  if (grayscale)
  {
    ptr = pixels_r;
    dr = -1;
    dg = -1;
    db = -1;
  }
  else if (c == ALL)
  {
    save_as_image(R, "R.bmp");
    save_as_image(G, "G.bmp");
    save_as_image(B, "B.bmp");
    return;
  }
  else if (c == R)
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

  int i, j;

  int w = image.get_surface()->w;
  int h = image.get_surface()->h;

  uint32_t max = *std::max_element(ptr, ptr + 256);
  double f = (double) max / (h - 15);

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

const uint32_t* Histogram::get_r()
{
  return pixels_r;
}

const uint32_t* Histogram::get_g()
{
  return pixels_g;
}

const uint32_t* Histogram::get_b()
{
  return pixels_b;
}

const uint32_t* Histogram::get_a()
{
  return pixels_a;
}
