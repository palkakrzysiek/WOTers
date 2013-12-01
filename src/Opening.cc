#include "Opening.h"

void Opening::perform(Image &image)
{
    image.perform_operation(new Erosion());
    image.perform_operation(new Dilation());
}
