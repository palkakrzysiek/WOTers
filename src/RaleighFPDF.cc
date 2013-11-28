#include "RaleighFPDF.h"
#include <cmath>
#include <algorithm>
#include <cstdio>

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

    uint8_t g_min, g_max;
    printf("gmin: ");
    scanf("%u", &g_min);
    printf("gmax: ");
    scanf("%u", &g_max);

    // precompute new intensity values
    double newVal[3][256] = {};
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
                alpha = 0.0;
                uint64_t H_0;

                if (tempVal[k] == 0)
                    H_0 = 1;
                else
                    H_0 = tempVal[k];

                alpha = 0.0;
                alpha = g_max - g_min;
                alpha *= alpha;
                alpha /= 2.0 * log((double) w * h / H_0);

                newVal[k][i] = g_min + sqrt(-2.0 * alpha * alpha * log(newVal[k][i]));

        }
    }

#   pragma omp parallel for private(j)
    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            uint8_t rgb[3] = {};

            SDL_GetRGB(image.get_pixel(i, j), image.get_surface()->format,
                       &rgb[0], &rgb[1], &rgb[2]);

            if (channel == Histogram::Channel::R ||
                channel == Histogram::Channel::ALL) {
                rgb[0] = trunc(newVal[0][rgb[0]]);
            }
            if (channel == Histogram::Channel::G ||
                channel == Histogram::Channel::ALL) {
                rgb[1] = trunc(newVal[1][rgb[1]]);
            }
            if (channel == Histogram::Channel::B ||
                channel == Histogram::Channel::ALL) {
                rgb[2] = trunc(newVal[2][rgb[2]]);
            }

            improved.set_pixel(i, j, SDL_MapRGB(improved.get_surface()->format,
                        rgb[0], rgb[1], rgb[2]));
        }
    }

    // uint64_t H_0;

//     if (tempVal[0] == 0)
//         H_0 = 1;
//     else
//         H_0 = tempVal[0];

//     alpha = 0.0;
//     alpha = g_max - g_min;
//     alpha *= alpha;
//     alpha /= 2.0 * log((double) w * h / H_0);

// #   pragma omp parallel for private(j)
//     for (i = 0; i < w; i++) {
//         for (j = 0; j < h; j++) {
//             for (k = 0; k < 3; ++k)
//             {


//                 newVal[]
//             }
//         }
//     }

    // for (i = 0; i < w; i++) {
    //     for (j = 0; j < h; j++) {
    //         improved.set(i, j,)
    //     }
    // }


    image = std::move(improved);
}
