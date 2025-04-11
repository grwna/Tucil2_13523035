#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "header/processing.hpp"
#include "lib/gif.h"

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
        stbi_write_jpg(path.c_str(), img.width, img.height, img.channels, img.data, 85);
    }
}
void create_gif(string path, Quadtree& tree, const Image& img, int max_depth){
    int w = img.width;
    int h = img.height;

    try {
        GifWriter writer;
        uint32_t delay = 50;
        bool dither = false;
        if (path.rfind(";;;;;", 0) == 0) {
            path.erase(0, 5);
            dither = true;
        }
        
        if (!GifBegin(&writer, path.c_str(), w, h, delay, 8, dither)) {
            __throw_runtime_error;
        }

        vector<uint8_t> rgb_buffer(static_cast<size_t>(w) * h * 3);
        vector<uint8_t> rgba_buffer(static_cast<size_t>(w) * h * 4);

        Image frame;
        frame.width = w;
        frame.height = h;
        frame.channels = 3;
        frame.data = rgb_buffer.data();

        for (int d = 0; d <= max_depth; ++d) {
            fill(rgb_buffer.begin(), rgb_buffer.end(), 0);
            tree.draw_to_depth(frame, 0, d);

            for (size_t i = 0, j = 0; i < rgb_buffer.size(); i += 3, j += 4) {
                rgba_buffer[j + 0] = rgb_buffer[i + 0];
                rgba_buffer[j + 1] = rgb_buffer[i + 1];
                rgba_buffer[j + 2] = rgb_buffer[i + 2];
                rgba_buffer[j + 3] = 255;
            }

            if (!GifWriteFrame(&writer, rgba_buffer.data(), w, h, delay, 8, dither)) {
                break;
            }
        }
        GifEnd(&writer);
        cout << endl;
        clr("GIF saved successfully to " + path, 10);
    } catch (const exception& e){
        clr("Failed to save GIF!", 196);
    }
}

// TODO: Validation
void compression(string in_path, string out_path, string gif_path, int mode, double threshold, int min_block){
    Image img = read_image_file(in_path);

    if (img.data == nullptr) {
        clr(string(15, '='), 196);
        clr("Failed to read image file!", 196);
        clr(string(15, '='), 196);
        return;
    }
    
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
            if (threshold) threshold = 0.8 + (0.2 * threshold);
            break;
        default:
            error_func = nullptr;
            break;
    }

    auto start_time = chrono::high_resolution_clock::now();
    Quadtree tree = Quadtree(0, 0, img.width, img.height);
    tree.build(img, min_block, threshold, error_func);
    int max_depth = tree.get_depth();
    tree.draw_to_depth(img, 0, max_depth);
    auto execution_time_object = chrono::high_resolution_clock::now() - start_time;
    double execution_time = chrono::duration<double, std::milli>(execution_time_object).count();    // in ms
    
    try {
        create_file(out_path);
        save_image_file(img, out_path);
        
        
        cout << "\033[2J\033[H";
        clr("Compressed image saved successfully to " + out_path, 10);
        clr("Execution time: " + to_string(execution_time) + " ms", 10);
        
        if (gif_path != "null"){
            start_time = chrono::high_resolution_clock::now();
            cout << "Creating GIF...";
            create_gif(gif_path, tree, img, max_depth);
            execution_time_object = chrono::high_resolution_clock::now() - start_time;
            execution_time = chrono::duration<double, std::milli>(execution_time_object).count();    // in ms
            clr("Execution time: " + to_string(execution_time) + " ms", 227);
            cout << endl;
        }
        
        cout << endl;
        clr("Parameters:", 227);
        clr("Error Method: " + to_string(mode) , 227);
        clr("Threshold: " + to_string(threshold), 227);
        clr("Minimum Block Size: " + to_string(min_block), 227); 
        cout << endl;

        try {
            uintmax_t input_file_size = filesystem::file_size(in_path);
            uintmax_t output_file_size = filesystem::file_size(out_path);
            double compression_percent = (1 - ((double)output_file_size/(double)input_file_size)) * 100;
            clr("Original Size: " + to_string(input_file_size) + " Bytes", 69);
            clr("Compressed Size: " + to_string(output_file_size) + " Bytes", 69);
            clr("Compression Percentage: " + to_string(compression_percent) + "%", 69);
            
        } catch (const exception e){
            clr("Error reading file size!", 196); 
            cout << endl;
        }

        clr("Depth of Tree: " + to_string(max_depth), 69);
        clr("Amount of Nodes: " + to_string(tree.get_node_count()), 69);
    }
    catch (const exception &e){
        clr("Failed to save file!", 196);
    }

}

