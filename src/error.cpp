#include "header/error.hpp"

double variance(const Image& img, const Region& region, const vector<uint8_t>& mean, int ch_idx) {
    double var = 0;
    for (int y = region.y; y < region.y + region.height; ++y) {
        for (int x = region.x; x < region.x + region.width; ++x) {
            var += pow(img.data[(y * img.width + x) * img.channels + ch_idx] - mean[ch_idx], 2);
        }
    }
    return var / (double) region.pixel_count;
}

double mean_absolute_deviation(const Image& img, const Region& region, const vector<uint8_t>& mean, int ch_idx){
    double mad = 0;
    for (int y = region.y; y < region.y + region.height; ++y) {
        for (int x = region.x; x < region.x + region.width; ++x) {
            mad += abs(img.data[(y * img.width + x) * img.channels + ch_idx] - mean[ch_idx]);
        }
    }
    return mad / (double) region.pixel_count;
}

double max_pixel_difference(const Image& img, const Region& region, const vector<uint8_t>& mean, int ch_idx) {
    int max_vals = 0;
    int min_vals = 255;
    for (int y = region.y; y < region.y + region.height; ++y) {
        for (int x = region.x; x < region.x + region.width; ++x) {
            int val = img.data[(y * img.width + x) * img.channels + ch_idx];
            max_vals = max(max_vals, val);
            min_vals = min(min_vals, val);
        }
    }
    return max_vals - min_vals;
}

double entropy(const Image& img, const Region& region, const vector<uint8_t>& mean, int ch_idx){
    // Kemunculan masing2 nilai di masing2 channel
    vector<int> counts(256, 0);
    double entropy;
    for (int y = region.y; y < region.y + region.height; ++y) {
        for (int x = region.x; x < region.x + region.width; ++x) {
            int pix_val = img.data[(y * img.width + x) * img.channels + ch_idx];

            counts[pix_val]++;
        }
    }
    return calculate_entropy(counts, region.pixel_count);;
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

double ssim(const Image& img, const Region& region, const vector<uint8_t>& mean, int ch_idx){
    const double C1 = pow(0.01 * 255,2);
    const double C2 = pow(0.03 * 255,2);

    double ssim_sum = 0;
    vector<double> weigths = {0.2989, 0.5870, 0.1140};  // Luminance Weighting 
    // vector<double> weigths = {1/3, 1/3, 1/3};  // equal
    double var_x = variance(img, region, mean, ch_idx);
    return weigths[ch_idx] * (C2 / (var_x * C2));
}