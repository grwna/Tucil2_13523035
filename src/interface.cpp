#include "header/interface.hpp"

void interface(){
    int choice;
    while (true) {
        cls();
        cout << endl << endl;
        clr(welcome_banner, 196);
        wait_for_input();

        while(true){
            clr("  ---------------------------------- ", 227);
            clr(" | Image Compression Using Quadtree |", 227);
            clr("  ---------------------------------- ", 227);
            clr(sleepy_cat, 227);
            cout << "Select an option: ";
            input(choice);
            if (choice == 1){main_program();}
            else if (choice == 2){exit(0);}
            else {
                input_error();
                continue;
            }
        }
    }
}

void main_program(){
    string input_path;
    string output_path;
    string gif_path = "null";
    int mode;
    double threshold;
    int min_block;
    double target;
    vector<int> range;
    string gif;

    // Input File Path
    while (true){
        cls();
        cout << "Enter the absolute path of the image (make sure the file exists)" << endl;
        cout << "Entering just the name of the file will use the default path instead" << endl;
        cout << "Default: 'io/input/{image}.{ext}'" << endl << endl;
        cout << ">> ";
        input(input_path);
        trim(input_path);
        if (input_path.find("/") == string::npos && input_path.find("\\") == string::npos){ // Default input_path
            input_path = "io/input/" + input_path;
        }
        if (!filesystem::exists(input_path) || !regex_match(input_path, image_regex)){
            cout << endl;
            clr("File doesn't exist or doesnt have a valid file extension!", 196);
            input_error();
            continue;}
        break;
    }

    // Error Methods
    while (true){
        cls();
        cout << "Pick the Error Measurement Methods" << endl;
        cout << "1. Variance" << endl;
        cout << "2. Mean Absolute Deviation" << endl;
        cout << "3. Max Pixel Difference" << endl;
        cout << "4. Entropy" << endl;
        cout << "5. Structural Similarity Index (SSIM)" << endl << endl;
        cout << ">> ";
        if (!input(mode) || (mode < 1 || mode > 5)){
            input_error();
            continue;}
        range = get_threshold_range(mode);
        break;
    }

    // Target Compression
    while (true){
        cls();
        cout << "Enter Target Compression Percentage" << endl;
        cout << "Range: 0 - 1" << endl;
        cout << "Enter 0 to disable this feature" << endl << endl;
        cout << ">> ";
        if(!input(target) || target < 0 || target > 1){
            input_error();
            continue;
        }
        if (target){
            threshold = (double)(range[1]-range[0]) * target;
            min_block = 0;
        }
        break;
    }

    if (!target){
        // Threshold
        while (true){
            cls();
            cout << "Enter threshold" << endl << endl;
            cout << "Valid threshold ranges" << endl;
            cout << "Variance:                 [0, 2250]" << endl;
            cout << "Mean Absolute Difference: [0, 50]" << endl;
            cout << "Max Pixel Difference:     [0, 250]" << endl;
            cout << "Entropy:                  [0, 8]" << endl;
            cout << "SSIM:                     [0, 1]" << endl << endl;
            cout << ">> ";
            if (!input(threshold)) threshold = -999;  // If input fails, let validate_threshold 'throw' the error
            if (!validate_threshold(range, threshold)){
                input_error();
                continue;
            }
            break;
        }
        
        // Min Block Size
        while (true){
            cls();
            cout << "Enter minimum block size" << endl << endl;
            cout << ">> ";
            if (!input(min_block)){
                input_error();
                continue;
            }
            break;
        }
    }

    // Output File Path
    while (true){
        cls();
        cout << "Enter the absolute path of where to save the image" << endl;
        cout << "Entering just the name of the file will use the default path instead" << endl;
        cout << "Default: 'io/output/{image}.{ext}'" << endl << endl;
        cout << ">> ";
        input(output_path);
        trim(output_path);
        if (output_path.find("/") == string::npos && output_path.find("\\") == string::npos){
            output_path = "io/output/" + output_path;
        }
        if (!regex_match(output_path, image_regex)){
            cout << endl;
            clr("Invalid path and/or filename!",196);
            input_error();
            continue;
        }
        if (input_path == output_path){
            cout << endl;
            clr("Output path cannot be the same as Input path", 196);
            input_error();
            continue;
        }
        break;
    }

    // GIF
    while (true){
        cls();
        cout << "Save compression to GIF? (y/n)" << endl << endl;
        cout << ">> ";
        input(gif);
        if (gif != "y" && gif != "Y" && gif != "n" && gif != "N"){
            cout << endl;
            clr("Enter y or n!", 196);
            input_error();
            continue;
        }
        break;
    }
    
    // GIF PATH
    if (gif == "y" || gif == "Y"){
        while(true){
            cls();
            cout << "Enable dithering for GIF? (y/n)" << endl;
            cout << "Dithering: Better quality but bigger file size and slower creation" << endl << endl;
            cout << ">> ";
            input(gif);
            if (gif != "y" && gif != "Y" && gif != "n" && gif != "N"){
                cout << endl;
                clr("Enter y or n!", 196);
                input_error();
                continue;
            }
            if (gif == "y" || gif == "Y"){
                gif = ";;;;;";
            } else {
                gif = "";
            }
            break;
        }

        while(true){
            cls();
            cout << "Enter the absolute path of where to save the GIF" << endl;
            cout << "Entering just the name of the file will use the default path instead" << endl;
            cout << "Default: 'io/output/{name}.gif'" << endl << endl;
            cout << ">> ";
            input(gif_path);
            trim(gif_path);
            if (gif_path.find("/") == string::npos && gif_path.find("\\") == string::npos){
                gif_path = "io/output/" + gif_path;
            }
            if (!regex_match(gif_path, gif_regex)){
                cout << endl;
                clr("Invalid path and/or filename!", 196);
                input_error();
                continue;
            }
            gif_path = gif + gif_path;
            break;
        }
    }

    cls();
    cout << "Processing..";
    compression(input_path, output_path, gif_path, mode, threshold, min_block);
    wait_for_input();
}

void wait_for_input(){
    cout << endl << "Press enter to continue...";
    cin.sync();
    cin.get();
    cls();
}

void cls(){
    cout << "\033[2J\033[H";
}

void input_error(){
    
    cout << endl;
    clr(string(15, '='), 196);
    clr("Invalid input!", 196);
    clr(string(15, '='), 196);
    cout << endl;
    
    // Clear buffer
    cin.clear();

    wait_for_input();
}