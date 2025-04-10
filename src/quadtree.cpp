#include "header/quadtree.hpp"

Quadtree::Quadtree(int x, int y, int width, int height) : 
    region({x, y, width, height}), isLeaf(true){
    for (int i = 0; i < 4; i++) children[i] = nullptr;
    this->region.pixel_count = (long long)region.width * region.height; // untuk gambar berdimensi sangat besar, menggunakan long-long 

}

Quadtree::~Quadtree(){
    for (int i = 0; i < 4; i++){
        delete children[i];
    }
}

int Quadtree::get_depth() {
    if (isLeaf) {
        return 0;
    } else {
        int max_child_depth = 0;
        for (int i = 0; i < 4; ++i) {
             max_child_depth = max(max_child_depth, children[i]->get_depth());
        }
        return 1 + max_child_depth;
    }
}

long long Quadtree::get_node_count() {
    long long count = 1; // Current node
    if (!isLeaf) {
        for (int i = 0; i < 4; ++i) {
            count += children[i]->get_node_count(); 
        }
    }
    return count;
}

vector<uint8_t> Quadtree::calculate_mean_color(const Image& img, const Region& region){
    vector<uint8_t> mean(img.channels, 0);
    vector<long long> pixel_sum(img.channels, 0);

    for (int y = region.y; y < region.y + region.height; ++y) {
        for (int x = region.x; x < region.x + region.width; ++x) {
            for (int c = 0; c < img.channels; ++c) {
                pixel_sum[c] += img.data[(y * img.width + x) * img.channels + c];
            }
        }
    }
    for (int c = 0; c < img.channels; ++c) mean[c] = (uint8_t)(pixel_sum[c] / (double)region.pixel_count);

    return mean;
}

void Quadtree::build(const Image& img, int min_block, double threshold, function<double(const Image&, const Region&, const vector<uint8_t>&, int)>error_func){
    this->mean_color = calculate_mean_color(img, region);
    double error = (error_func(img, region, mean_color, 0) + error_func(img, region, mean_color, 1) + error_func(img, region, mean_color, 2)) /3.0;
    
    int half_width = region.width / 2;
    int half_height = region.height / 2;

    if ((img.mode == 5 && error <= threshold) || region.width <= min_block || region.height <= min_block || error <= threshold) {
        isLeaf = true;
        return;
    }

    isLeaf = false;

    children[0] = new Quadtree(region.x, region.y, half_width, half_height);
    children[1] = new Quadtree(region.x + half_width, region.y, half_width, half_height);
    children[2] = new Quadtree(region.x, region.y + half_height, half_width, half_height);
    children[3] = new Quadtree(region.x + half_width, region.y + half_height, half_width, half_height);

    for (int i = 0; i < 4; ++i) {
        children[i]->build(img, min_block, threshold, error_func);
    }
}

void Quadtree::draw_to_depth(Image& img, int curr_depth, int limit_depth){
    if (isLeaf || curr_depth == limit_depth) {
        for (int y = region.y; y < region.y + region.height; ++y) {
            uint8_t* row_ptr = &img.data[(y * img.width + region.x) * img.channels];
            for (int x = 0; x < region.width; ++x) {
                for (int c = 0; c < img.channels; ++c) {
                    row_ptr[x * img.channels + c] = mean_color[c];
                }
            }
        }
        return;
    }

    if (!isLeaf && curr_depth < limit_depth) {
        for (int i = 0; i < 4; ++i) {
            children[i]->draw_to_depth(img, curr_depth + 1, limit_depth);
        }
    }
}

