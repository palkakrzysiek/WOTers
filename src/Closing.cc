#include "Closing.h"

Closing::Closing(int m) : mask(m) {}

void Closing::perform(Image &image)
{
    image.perform_operation(new Dilation(mask));
    image.perform_operation(new Erosion(mask));
}
