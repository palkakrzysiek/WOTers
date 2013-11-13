#include "RaleighFPDF.h"
#include <cmath>
#include <algorithm>

    RaleighFPDF::RaleighFPDF(Histogram::Channel c, double a)
: channel(c),
    alpha(a)
{
}

void RaleighFPDF::perform(Image &image)
{
    int w = image.get_surface()->w;
    int h = image.get_surface()->h;

    Image improved(image);
    Histogram hist(image);

    int g_min = 0;


    // precompute new intensity values
    double newVal[3][256] {};
    double tempVal[3] = {0};
    int i, j, k;
    for (i = 0; i <= 255; i++) { // 255 operations
        tempVal[0] = hist.get_r()[i];
        tempVal[1] = hist.get_g()[i];
        tempVal[2] = hist.get_b()[i];

        for (j = i; j <= 255 ; j++) {
            for (k = 0; k < 3; k++) { // 3 * (255 - 0) / 2 * 255 operations
                newVal[k][j] += tempVal[k];
            }
        }

        for (k = 0; k < 3; k++) { // 3 operations
            newVal[k][i] /= w * h; // 1 operation
            newVal[k][i] = 1 / newVal[k][i]; // 1 operation
            newVal[k][i] = log(newVal[k][i]); // 1 operation
            newVal[k][i] = 2 * alpha * alpha * newVal[k][i]; // 3 operations
             //newVal > 0
            newVal[k][i] = sqrt(newVal[k][i]); // 1 operation
            newVal[k][i] = g_min + newVal[k][i]; // 1 operation

        }
    }

    uint8_t rgb[3] {};
    
    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++){
            SDL_GetRGB(image.get_pixel(i, j), image.get_surface()->format,
                    &rgb[0], &rgb[1], &rgb[2]);

            if (channel == Histogram::Channel::R || 
                channel == Histogram::Channel::ALL) {
                rgb[0] = trunc(newVal[0][255-rgb[0]]); 
            }
            if (channel == Histogram::Channel::G || 
                channel == Histogram::Channel::ALL) {
                rgb[1] = trunc(newVal[1][255-rgb[1]]); 
            }
            if (channel == Histogram::Channel::B || 
                channel == Histogram::Channel::ALL) {
                rgb[2] = trunc(newVal[2][255-rgb[2]]); 
            }

            improved.set_pixel(i, j, SDL_MapRGB(improved.get_surface()->format,
                        rgb[0], rgb[1], rgb[2]));
        }
    }
    image = std::move(improved);
}
