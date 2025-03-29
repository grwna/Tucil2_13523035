#ifndef PROCESSING_HPP
#define _PROCESSING_HPP

#include <opencv2/opencv.hpp>
#include <vector>
#include <stdint.h>
using namespace std;

/**
 * @brief Read the RGB pixel data from an image file
 * 
 * Note: Alpha channel values are not preserved during this step
 * 
 * @param path Full path to image file 
 * @return OpenCV Matrix Object containing RGB values from the image file
 */
cv::Mat read_image_file(string path);

/**
 * @brief Save an OpenCV Matrix object to an image
 * 
 * @param img 
 * @param path 
 */
void save_image_file(const cv::Mat &img, string path);

/**
 * @brief Turns a Matrix into a 1 dimensional vector
 * 
 * @param img An OpenCV Matrix object of an image 
 * @return Pixels of the image formatted as a 1 dimensional vector 
 */
vector<uint8_t> matrix_to_vector(const cv::Mat& img);

/**
 * @brief Turns a 1 dimensional vector into an OpenCV Matrix object
 * 
 * @param img_vec 1 dimensional vector of image's pixels
 * @param width Width of the image
 * @param height Height of the image
 * @param channels Number of channels in the image (3 for this program)
 * @return OpenCV Matrix object
 */
cv::Mat vector_to_matrix(const vector<uint8_t> img_vec, int width, int height, int channels = 3);

#endif