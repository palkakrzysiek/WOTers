#ifndef __REGION_GROWING__
#define __REGION_GROWING__

#include "Operation.h"
#include "Histogram.h"
#include "ConvertToGrayscale.h"
#include "StructuralElements.h"
#include <queue>

struct Point {
    int x;
    int y;
};


class RegionGrowing : public Operation {
    public:
        RegionGrowing(int reg, int th);
        void perform(Image &image);
    private:
        int seedVal;
        int thresholdMargin;
};

#endif
