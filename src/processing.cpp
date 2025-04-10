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
        stbi_write_jpg(path.c_str(), img.width, img.height, img.channels, img.data, 85);
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
        cout << "Compressed image saved successfully to " << out_path << endl;
        cout << "Execution time: " << execution_time << " ms" << endl << endl;

        cout << "Parameters:" << endl;
        cout << "Error Method: " << mode << endl;
        cout << "Threshold: " << threshold << endl;
        cout << "Minimum Block Size: " << min_block << endl << endl;

        try {
            uintmax_t input_file_size = filesystem::file_size(in_path);
            uintmax_t output_file_size = filesystem::file_size(out_path);
            double compression_percent = (1 - ((double)output_file_size/(double)input_file_size)) * 100;
            cout << "Original Size: " << input_file_size << " Bytes" << endl;
            cout << "Compressed Size: " << output_file_size << " Bytes" << endl;
            cout << "Compression Percentage: " << compression_percent << "%" << endl;
            
        } catch (const exception e){
            cout << "Error reading file size!" << endl;
        }

        cout << "Depth of Tree: " << tree.get_depth() << endl;
        cout << "Amount of Nodes: " << tree.get_node_count() << endl;
    }
    catch (const exception &e){
        cout << "Failed to save file!" << endl;
    }
}

