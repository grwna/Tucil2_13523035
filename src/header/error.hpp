# ifndef _ERROR_HPP
# define _ERROR_HPP

#include "quadtree.hpp"
#include <cmath>

// Explanation for each methods: https://docs.google.com/document/d/1N_ENR9VQI9XdOTtVinCBd7vVqb2tbeclMInyARlmVcs
double variance(const Image& img, const Region& region, const vector<uint8_t>& mean, int ch_idx);

double mean_absolute_deviation(const Image& img, const Region& region, const vector<uint8_t>& mean, int ch_idx);

double max_pixel_difference(const Image& img, const Region& region, const vector<uint8_t>& mean, int ch_idx);

double entropy(const Image& img, const Region& region, const vector<uint8_t>& mean, int ch_idx);

/**
 * @brief Helper functionf or entropy, calculates the entropy for a channel
 * 
 * @param counts The occurence of every pixel for one channel
 * @param pixel_count Amount of pixels in a block
 * @return Entropy for one channel
 */
double calculate_entropy(const vector<int>& counts, long long pixel_count);

double ssim(const Image& img, const Region& region, const vector<uint8_t>& mean, int ch_idx);

# endif