#include "ContraharmonicMeanFilter.h"
#include <cmath>

const int sqareSize = 1; // size of "borders"

ContraharmonicMeanFilter::ContraharmonicMeanFilter(double q)
  : order(q) { }

void ContraharmonicMeanFilter::perform(Image &image) {
    int w = image.get_surface()->w;
    int h = image.get_surface()->h;

    // create a copy of the image
    Image filtered(image);

    int i, j;
    i = j = 0;

# pragma omp parallel for private(j)  
    for (i = 0; i < w - 1; i++) {
        for (j = 0; j < h - 1; j++) {
            double sum1[4] {0};
            double sum2[4] {0};
            uint8_t rgba[4] {0};
            double result[4] {0};
            
            // for every pixel
            for (int k = -sqareSize; k < sqareSize; k++){
                for (int l = -sqareSize; l < sqareSize; l++){
                    // sum appropriate powers
                    // in case of pixels on borders -- don't copy them
                    // to obtain for example 9x9 mask, just use only those
                    // pixels that already exist
                    if (i + k >= 0 && j + l >= 0 && i + k < w && j + l < h) {
                        SDL_GetRGBA(image.get_pixel(i + k, j + l), image.get_surface()->format, &rgba[0], &rgba[1], &rgba[2], &rgba[3]);
                        for (int o = 0; o < 4; o++){
                            sum1[o] += std::pow(rgba[o], order + 1);
                            sum2[o] += std::pow(rgba[o], order);
                        }
                    }
                }
            }
            for (int o = 0; o < 4; o++){
                result[o] = sum1[o] / sum2[o];
            }
            filtered.set_pixel(i, j, SDL_MapRGBA(filtered.get_surface()->format,
                        trunc(result[0]), trunc(result[1]), trunc(result[2]), trunc(result[3])));
        }
    }
    image = std::move(filtered);


}
