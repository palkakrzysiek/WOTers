#include "Closing.h"

void Closing::perform(Image &image)
{
    image.perform_operation(new Dilation());
    image.perform_operation(new Erosion());
}
