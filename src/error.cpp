#include "header/error.hpp"

double variance(const Image& img, const Region& region, const vector<uint8_t>& mean) {
    double var_R = 0;
    double var_G = 0;
    double var_B = 0;

    for (int y = region.y; y < region.y + region.height; ++y) {
        for (int x = region.x; x < region.x + region.width; ++x) {
            var_R += pow(img.data[(y * img.width + x) * img.channels + 0] - mean[0], 2);
            var_G += pow(img.data[(y * img.width + x) * img.channels + 1] - mean[1], 2);
            var_B += pow(img.data[(y * img.width + x) * img.channels + 2] - mean[2], 2);
        }
    }

    var_R /= region.pixel_count;
    var_G /= region.pixel_count;
    var_B /= region.pixel_count;

    return (var_R + var_G + var_B) / 3.0;
}