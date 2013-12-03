#include "Opening.h"

Opening::Opening(int m) : mask(m) {}

void Opening::perform(Image &image)
{
    image.perform_operation(new Erosion(mask));
    image.perform_operation(new Dilation(mask));
}
