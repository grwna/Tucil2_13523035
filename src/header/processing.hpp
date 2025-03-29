#ifndef _PROCESSING_HPP
#define _PROCESSING_HPP

#include "../lib/stb_image.h"
#include "../lib/stb_image_write.h"
#include <vector>
#include <string>
#include <cstdint>
#include <filesystem>
using namespace std;

/** @brief Represents an image.*/
struct Image {
    /* Image data. */
    uint8_t* data;
    /* Image width. */
    int width;
    /* Image height. */
    int height;
    /* Number of channels. */
    int channels;
    /* Filetype of the image */
    string type;
  };

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

#endif