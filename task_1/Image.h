#include <SDL_Image.h>

class Image
{
public:
  Image(const char *filename);
  ~Image();

private:
  SDL_Surface *image;

};
