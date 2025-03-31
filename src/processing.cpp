#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "header/processing.hpp"

Image read_image_file(string path){
    Image img;
    img.data = stbi_load(path.c_str(), &img.width, &img.height, &img.channels, 3);
    img.type = filesystem::path(path).extension().string();
    img.channels = 3; // Only RGB
    return img;
}

void save_image_file(Image img, string path){
    if (img.type == ".png"){
        stbi_write_png(path.c_str(), img.width, img.height, img.channels, img.data, img.width * img.channels);
    } 
    else if (img.type == ".jpg" || img.type == ".jpeg"){
        stbi_write_jpg(path.c_str(), img.width, img.height, img.channels, img.data, img.width * img.channels);
    }
}

// TODO: Validation
void compression(string in_path, string out_path, int mode, double threshold, int min_block){
    Image img = read_image_file(in_path);
    img.mode = mode;

    typedef double (*ErrorFunc)(const Image&, const Region&, const vector<uint8_t>&, int);
    function<double(const Image&, const Region&, const vector<uint8_t>&, int)> error_func;

    switch (mode){
        case 1:
            error_func = (ErrorFunc) variance;
            break;
        case 2:
            error_func = (ErrorFunc) mean_absolute_deviation;
            break;
        case 3:
            error_func = (ErrorFunc) max_pixel_difference;
            break;
        case 4:
            error_func = (ErrorFunc) entropy;
            break;
        case 5:
            error_func = (ErrorFunc) ssim;
            break;
        default:
            error_func = nullptr;
            break;
    }

    Quadtree tree = Quadtree(0, 0, img.width, img.height);
    tree.build(img, min_block, threshold, error_func);
    tree.draw(img);
    save_image_file(img, out_path);
}