#ifndef _COMPRESSION_HPP
#define _COMPRESSION_HPP

#include "processing.hpp"
#include "quadtree.hpp"
#include <filesystem>

/**
 * @brief Handles the entire proccess of compression, to be used in the interface
 * 
 * @param in_path  The path to the input image file.
 * @param out_path The path to save the compressed image file.
 * @param mode     The error measurement  mode.
 * @param threshold The threshold value for the compression algorithm 
 * @param min_block The minimum block size for quadtree subdivision.
 */
void compression(string in_path, string out_path, int mode, int threshold, int min_block);

#endif