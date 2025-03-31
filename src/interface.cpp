#include "header/interface.hpp"

void interface(){
    int choice;
    while (true) {
        cls();
        cout << string(15, '=') << " Welcome to Tucil 2 " << string(15, '=') << endl;
        wait_for_input();
        cout << "Image Compression Using Quadtree" << endl << endl;
        cout << "1. Start" << endl;
        cout << "2. Help" << endl;
        cout << "3. Exit" << endl;
        cout << endl << "Select and option: ";
        input(choice);
        if (choice == 1){main_program();}
        else if (choice == 2){help();}
        else if (choice == 3){exit(0);}
        else {
            input_error();
            continue;
        }
    }
}

void main_program(){
    string input_path;
    string output_path;
    int mode;
    double threshold;
    int min_block;

    while (true){
        cls();
        cout << "Enter the absolute path of the image (make sure the file exists)" << endl;
        cout << "Default: 'io/input/{image}.{ext}'" << endl << endl;
        cout << ">> ";
        input(input_path);
        trim(input_path);
        if (input_path.find("/") == string::npos && input_path.find("\\") == string::npos){ // Default input_path
            input_path = "io/input/" + input_path;
        }
        cout << input_path << endl;
        if (!filesystem::exists(input_path) || !regex_match(input_path, image_regex)){
            cout << "File doesn't exist or doesnt have a valid file extension!" << endl;
            input_error();
            continue;}
        break;
    }

    while (true){
        cls();
        cout << "Pick the Error Measurement Methods" << endl;
        cout << "1. Variance" << endl;
        cout << "2. Mean Absolute Deviation" << endl;
        cout << "3. Max Pixel Difference" << endl;
        cout << "4. Entropy" << endl;
        cout << "5. Structural Similarity Index (SSIM)" << endl;
        cout << ">> ";
        if (!input(mode) || (mode < 1 || mode > 5)){
            input_error();
            continue;}
        break;
    }

    while (true){
        cls();
        cout << "Enter threshold" << endl << endl;
        cout << "Valid threshold ranges" << endl;
        cout << "Variance:                 [0, 65025]" << endl;
        cout << "Mean Absolute Difference: [0, 255]" << endl;
        cout << "Max Pixel Difference:     [0, 255]" << endl;
        cout << "Entropy:                  [0, 8]" << endl;
        cout << "SSIM:                     [-1, 1]" << endl;
        cout << ">> ";
        // TODO: Validate double
        if (!input(threshold)) threshold = -999;
        if (!validate_threshold(mode, threshold)){
            input_error();
            continue;
        }
        break;
    }
    
    while (true){
        cls();
        cout << "Enter minimum block size" << endl;
        cout << ">> ";
        if (!input(min_block)){
            input_error();
            continue;
        }
        break;
    }

    while (true){
        cls();
        cout << "Enter the absolute path of where to save the image" << endl;
        cout << "Default: 'io/output/{image}.{ext}'" << endl << endl;
        cout << ">> ";
        input(output_path);
        trim(output_path);
        if (output_path.find("/") == string::npos && output_path.find("\\") == string::npos){ // Default input_path
            output_path = "io/output/" + output_path;
        }
        if (!regex_match(output_path, image_regex)){
            cout << "Invalid path and/or filename!" << endl;
            input_error();
            continue;}
        create_file(output_path);
        break;
    }

    compression(input_path, output_path, mode, threshold, min_block);
    cout << "saved successfully to " << output_path << endl;
    wait_for_input();
}

void help(){
    cout << "Display Help" << endl;
    wait_for_input();
}

void wait_for_input(){
    cout << "Press enter to continue...";
    cin.sync();
    cin.get();
    cls();
}

void cls(){
    cout << "\033[2J\033[H";
}

void input_error(){
    
    cout << endl;
    clr(string(15, '='), 9);
    clr("Invalid input!", 9);
    clr(string(15, '='), 9);
    cout << endl;
    
    // Clear buffer
    cin.clear();

    wait_for_input();
}