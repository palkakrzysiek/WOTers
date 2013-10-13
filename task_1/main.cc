#include "Image.h"
#include "Parser.h"
#include "Transformations.h"
#include <sys/time.h>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>

using namespace std;

int main(int argc, char** argv)
{
 
    using namespace std;

    Parser p(argc, argv);

    Image img(p.getFilename());
    Transformation *t = nullptr;

    if (p.setBrightness())
    {
        t = new BrightnessTransformation(p.getBrightnessValue()/100.0);
    }

    assert(t != nullptr);
    img.apply_transformation(t);

    img.save(p.getOutFilename());
        
    return 0;
}
