# ifndef _ERROR_HPP
# define _ERROR_HPP

#include "quadtree.hpp"
#include <cmath>

// Explanation for each methods: https://docs.google.com/document/d/1N_ENR9VQI9XdOTtVinCBd7vVqb2tbeclMInyARlmVcs
double variance(const Image& img, const Region& region, const vector<uint8_t>& mean);

double mean_absolute_deviation(const Image& img, const Region& region, const vector<uint8_t>& mean);

double max_pixel_difference(const Image& img, const Region& region, const vector<uint8_t>& mean);

double entropy(const Image& img, const Region& region, const vector<uint8_t>& mean);

double ssim(const Image& img, const Region& region, const vector<uint8_t>& mean);

# endif