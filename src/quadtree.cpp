#include "header/quadtree.hpp"

Quadtree::Quadtree(int x, int y, int width, int height) : 
    region({x, y, width, height}), isLeaf(true){
    for (int i = 0; i < 4; i++) children[i] = nullptr;
}

Quadtree::~Quadtree(){
    for (int i = 0; i < 4; i++){
        delete children[i];
    }
}

vector<uint8_t> Quadtree::calculate_mean_color(const Image& img, const Region& region){
    vector<uint8_t> mean(img.channels, 0);
    long long pixelCount = (long long)region.width * region.height; // Avoids overflow 

    for (int y = region.y; y < region.y + region.height; ++y) {
        for (int x = region.x; x < region.x + region.width; ++x) {
            for (int c = 0; c < img.channels; ++c) {
                mean[c] += img.data[(y * img.width + x) * img.channels + c];
            }
        }
    }

    for (int c = 0; c < img.channels; ++c) {
        mean[c] = (uint8_t)(mean[c] / pixelCount);
    }

    return mean;
}

void Quadtree::build(const Image& img, int min_block, double threshold, function<double(const Image&, const Region&, const vector<uint8_t>&)>error_func){
    mean_color = calculate_mean_color(img, region);
    double error = error_func(img, region, mean_color);

    if (region.width <= min_block || region.height <= min_block || error <= threshold) { // Base case
        isLeaf = true;
        return;
    }

    isLeaf = false;
    int halfWidth = region.width / 2;
    int halfHeight = region.height / 2;

    // Recursion
    children[0] = new Quadtree(region.x, region.y, halfWidth, halfHeight);
    children[1] = new Quadtree(region.x + halfWidth, region.y, halfWidth, halfHeight);
    children[2] = new Quadtree(region.x, region.y + halfHeight, halfWidth, halfHeight);
    children[3] = new Quadtree(region.x + halfWidth, region.y + halfHeight, halfWidth, halfHeight);

    for (int i = 0; i < 4; ++i) {
        children[i]->build(img, min_block, threshold, error_func);
    }
}

void Quadtree::draw(Image& img) {
    if (isLeaf) {
        for (int y = region.y; y < region.y + region.height; ++y) {
            for (int x = region.x; x < region.x + region.width; ++x) {
                for (int c = 0; c < img.channels; ++c) {
                    img.data[(y * img.width + x) * img.channels + c] = mean_color[c];
                }
            }
        }
        return;
    }

    for (int i = 0; i < 4; ++i) children[i]->draw(img);
    
}