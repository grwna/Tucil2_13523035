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

    double pixel_count = (double) region.pixel_count;
    var_R /= pixel_count;
    var_G /= pixel_count;
    var_B /= pixel_count;

    return (var_R + var_G + var_B) / 3.0;
}

double mean_absolute_deviation(const Image& img, const Region& region, const vector<uint8_t>& mean){
    double mad_R = 0;
    double mad_G = 0;
    double mad_B = 0;
    for (int y = region.y; y < region.y + region.height; ++y) {
        for (int x = region.x; x < region.x + region.width; ++x) {
            mad_R += abs(img.data[(y * img.width + x) * img.channels + 0] - mean[0]);
            mad_G += abs(img.data[(y * img.width + x) * img.channels + 1] - mean[1]);
            mad_B += abs(img.data[(y * img.width + x) * img.channels + 2] - mean[2]);
        }
    }
    
    double pixel_count = (double) region.pixel_count;
    mad_R /= pixel_count;
    mad_G /= pixel_count;
    mad_B /= pixel_count;

    return (mad_R + mad_G + mad_B) / 3.0;
}

double max_pixel_difference(const Image& img, const Region& region, const vector<uint8_t>& mean) {
    int max_vals[3] = {0, 0, 0};
    int min_vals[3] = {255, 255, 255};

    for (int y = region.y; y < region.y + region.height; ++y) {
        for (int x = region.x; x < region.x + region.width; ++x) {
            for (int c = 0; c < 3; ++c) {
                int val = img.data[(y * img.width + x) * img.channels + c];
                max_vals[c] = max(max_vals[c], val);
                min_vals[c] = min(min_vals[c], val);
            }
        }
    }

    return (double)(max_vals[0] - min_vals[0] + max_vals[1] - min_vals[1] + max_vals[2] - min_vals[2] / 3.0);
}

double entropy(const Image& img, const Region& region, const vector<uint8_t>& mean){
    // Kemunculan masing2 nilai di masing2 channel
    vector<int> countsR(256, 0), countsG(256, 0), countsB(256, 0);
    double entropyR, entropyG, entropyB;

    for (int y = region.y; y < region.y + region.height; ++y) {
        for (int x = region.x; x < region.x + region.width; ++x) {
            int r = img.data[(y * img.width + x) * img.channels + 0];
            int g = img.data[(y * img.width + x) * img.channels + 1];
            int b = img.data[(y * img.width + x) * img.channels + 2];

            countsR[r]++;
            countsG[g]++;
            countsB[b]++;
        }
    }

    entropyR = calculate_entropy(countsR, region.pixel_count);
    entropyG = calculate_entropy(countsG, region.pixel_count);
    entropyB = calculate_entropy(countsB, region.pixel_count);

    return (entropyR + entropyG + entropyB) / 3.0;
}

double calculate_entropy(const vector<int>& counts, long long pixel_count){
    double probability;
    double channel_entropy = 0;
    for (int i = 0; i < 256; i++){
        if (counts[i] > 0){
            probability = counts[i] / (double) pixel_count;
            channel_entropy -= probability * log2(probability);
        }
    }
    return channel_entropy;
}

double ssim(const Image& img, const Region& region, const vector<uint8_t>& mean){
    // Variansi = 0, karena blok monoton

    const double C1 = pow(0.01 * 255,2);
    const double C2 = pow(0.03 * 255,2);

    double ssim_sum = 0;
    vector<double> weigths = {0.2989, 0.5870, 0.1140};  // Luminance Weighting 
    // vector<double> weigths = {1/3, 1/3, 1/3};  // equal

    for (int i = 0; i < img.channels; i++){
        ssim_sum += (2 * pow(mean[i],2) + C1 * C2) / (2 * pow(mean[i],2) + C1 * C2);
    }

    return  ;
}