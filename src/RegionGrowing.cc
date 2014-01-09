#include "RegionGrowing.h"

RegionGrowing::RegionGrowing(int s, int h)
  : seedVal(s), thresholdMargin(h)
{
}

void RegionGrowing::perform(Image &image)
{

  // bool grayscale = (image.get_surface()->format->BitsPerPixel <= 8) ? true : false;
  std::queue<Point> points;

  if (!image.grayscale()) {
    image.perform_operation(new ConvertToGrayscale());
  }

  if (thresholdMargin == -1) {
    Histogram hist(image);
    thresholdMargin = std::abs(static_cast<long long>(seedVal - hist.cmean(Histogram::Channel::ALL)));
  }

  int w = image.get_surface()->w;
  int h = image.get_surface()->h;

  Image outimg(image);
  uint8_t r, g, b;
  int i, j;
  for (i = 0; i < w; i++) {
    for (j = 0; j < h; j++) {
      SDL_GetRGB(image.get_pixel(i, j), image.get_surface()->format,
          &r, &g, &b);
      if (seedVal == r) {
        Point p;
        p.x = i, p.y = j;
        points.push(p);
        outimg.set_pixel(i, j, SDL_MapRGB(outimg.get_surface()->format,
              FG, FG, FG));
      }
      else {
        outimg.set_pixel(i, j, SDL_MapRGB(outimg.get_surface()->format,
              BG, BG, BG));
      }
    }
  }

  while (!points.empty()) {
    Point p = points.front();
    points.pop();
    for (i = p.x - 1; i <= p.x + 1; i++) {
      for (j = p.y -1; j <= p.y + 1; j++) {
        if ((i >= 0) && (i < w) && (j >= 0) && (j < h)) {
          uint8_t r2, g2, b2;
          SDL_GetRGB(outimg.get_pixel(i, j), outimg.get_surface()->format,
              &r, &g, &b);
          SDL_GetRGB(image.get_pixel(i, j), image.get_surface()->format,
              &r2, &g2, &b2);
          // if this pixel hasn't been already checked
          // and have value within accepted range
          if ((r != FG) && (std::abs(r2 - seedVal) <= thresholdMargin)) {
            Point p2;
            p2.x = i, p2.y = j;
            points.push(p2);
            outimg.set_pixel(i, j, SDL_MapRGB(outimg.get_surface()->format,
                FG, FG, FG));
          }
        }
      }
    }
  }


  image = std::move(outimg);
}
