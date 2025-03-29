#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "header/processing.hpp"

Image read_image_file(string path){
    Image img;
    img.data = stbi_load(path.c_str(), &img.width, &img.height, &img.channels, 3);
    img.type = filesystem::path(path).extension().string();
    return img;
}

void save_image_file(Image img, string path){
    if (img.type == "png"){
        stbi_write_png(path.c_str(), img.width, img.height, img.channels, img.data, img.width * img.channels);
    } 
    else if (img.type == "jpg" || img.type == "jpeg"){
        stbi_write_jpg(path.c_str(), img.width, img.height, img.channels, img.data, img.width * img.channels);
    }
}