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
        clr("Enter the absolute path of the image (make sure the file exists)", 227);
        clr("Entering just the name of the file will use the default path instead", 227);
        cout << endl;
        clr("Default: 'io/input/{image}.{ext}'", 227);
        cout << endl;
        clr(">> ", 230, false);
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
            clr("Pick the Error Measurement Methods", 227);
            clr("1. Variance", 227);
            clr("2. Mean Absolute Deviation", 227);
            clr("3. Max Pixel Difference", 227);
            clr("4. Entropy", 227);
            clr("5. Structural Similarity Index (SSIM)", 227);
            cout << endl;
            clr(">> ", 230, false);
        if (!input(mode) || (mode < 1 || mode > 5)){
            input_error();
            continue;}
        range = get_threshold_range(mode);
        break;
    }

    // Target Compression
    while (true){
        cls();
        clr("Enter Target Compression Percentage",227);
        cout << endl;
        clr("Range: 0 - 1",227);
        clr("Enter 0 to disable this feature",227) ;
        cout << endl;
        clr(">> ", 230, false);
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
            clr("Enter threshold",227); 
            cout << endl;
            clr("Valid threshold ranges",227);
            clr("Variance:                 [0, 2250]",227);
            clr("Mean Absolute Difference: [0, 50]",227);
            clr("Max Pixel Difference:     [0, 250]",227);
            clr("Entropy:                  [0, 8]",227);
            clr("SSIM:                     [0, 1]",227);
            cout << endl;
            clr(">> ", 230, false);
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
            clr("Enter minimum block size", 227); 
            cout << endl;
            clr(">> ", 230, false);
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
        clr("Enter the absolute path of where to save the image", 227);
        clr("Entering just the name of the file will use the default path instead", 227);
        cout << endl;
        clr("Default: 'io/output/{image}.{ext}'", 227);
        cout << endl;
        clr(">> ", 230, false);
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
        clr("Save compression to GIF? (y/n)", 227);
        cout << endl;
        clr(">> ", 230, false);
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
            clr("Enable dithering for GIF? (y/n)", 227);
            clr("Dithering: Better quality but bigger file size and slower creation", 227); 
            cout << endl;
            clr(">> ", 230, false);
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
            clr("Enter the absolute path of where to save the GIF", 227);
            clr("Entering just the name of the file will use the default path instead", 227);
            cout << endl;
            clr("Default: 'io/output/{name}.gif'", 227);
            cout << endl;
            clr(">> ", 230, false);
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