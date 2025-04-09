#ifndef _PROCESSING_HPP
#define _PROCESSING_HPP

#include "../lib/stb_image.h"
#include "../lib/stb_image_write.h"
#include "quadtree.hpp"
#include "error.hpp"
#include <chrono>
#include <filesystem>

/**
 * @brief Read the RGB pixel data from an image file
 * 
 * Note: Alpha channel values are not preserved during this step
 * 
 * @param path Full path to image file 
 * @return Image struct that contains  matrix containing RGB values from the image file and dimensions
 */
Image read_image_file(string path);

/**
 * @brief Save an RGB matrix to an image
 * 
 * @param img 
 * @param path 
 */
void save_image_file(const Image img, string path);

/**
 * Handles the entire proccess of compression, to be used in the interface
 * NOTE: Execution Time and File Size calculations are done here 
 * 
 * @param in_path  The path to the input image file.
 * @param out_path The path to save the compressed image file.
 * @param mode     The error measurement  mode.
 * @param threshold The threshold value for the compression algorithm 
 * @param min_block The minimum block size for quadtree subdivision.
 */
void compression(string in_path, string out_path, int mode, double threshold, int min_block);

#endif