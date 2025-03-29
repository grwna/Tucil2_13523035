#include "header/processing.hpp"

cv::Mat read_image_file(string path){
    cv::Mat img = cv::imread(path, cv::IMREAD_COLOR_RGB);
    return img;
}

void save_image_file(const cv::Mat &img, string path){
    cv::imwrite(path, img);
}

vector<uint8_t> matrix_to_vector(const cv::Mat &img){
    int width = img.cols;
    int height = img.rows;
    std::vector<uint8_t> img_vec(width * height * 3); // Allocate for RGB

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            img_vec[(y * width + x) * 3 + 0] = img.at<cv::Vec3b>(y, x)[0]; // Red
            img_vec[(y * width + x) * 3 + 1] = img.at<cv::Vec3b>(y, x)[1]; // Green
            img_vec[(y * width + x) * 3 + 2] = img.at<cv::Vec3b>(y, x)[2]; // Blue
        }
    }
    return img_vec;
}

cv::Mat vector_to_matrix(const vector<uint8_t> img_vec, int width, int height, int channels){
    cv::Mat image(height, width, CV_8UC3); // Unsigned 8 bit, 3 Channels
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            image.at<cv::Vec3b>(y, x)[0] = img_vec[(y * width + x) * 3 + 0]; // Red
            image.at<cv::Vec3b>(y, x)[1] = img_vec[(y * width + x) * 3 + 1]; // Green
            image.at<cv::Vec3b>(y, x)[2] = img_vec[(y * width + x) * 3 + 2]; // Blue
        }
    }
    return image;
}