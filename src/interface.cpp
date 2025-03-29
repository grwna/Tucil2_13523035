#include "header/interface.hpp"

void interface(){
    cls();
    cout << string(15, '=') << " Welcome to Tucil 2 " << string(15, '=') << endl;
    wait_for_input();

    int choice;
    while (true) {
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
        }
    }
}

void main_program(){
    string path;
    int choice;
    int threshold;
    int min_block;

    while (true){
        cout << "Enter the absolute path of the image (make sure the file exists)" << endl;
        cout << "Default: 'io/input/{image}.{ext}'" << endl << endl;
        cout << ">>";
        input(path);
        trim(path);
        if (path.find("/") == string::npos || path.find("\\") == string::npos){ // Default path
            path = "io/input/";
        }
        else if (!filesystem::exists(path) || !regex_match(path, image_regex)){
            input_error();
            continue;}
        break;
    }

    while (true){
        cout << "Pick the Error Measurement Methods" << endl;
        cout << "1. Variance" << endl;
        cout << "2. Mean Absolute Deviation (MAD)" << endl;
        cout << "3. Max Pixel Difference" << endl;
        cout << "4. Entropy" << endl;
        cout << "5. Structural Similarity Index (SSIM)" << endl;
        input(choice);
        if (choice < 1 || choice > 5){
            input_error();
            continue;}
        break;
    }

    while (true){
        cout << "Enter threshold";
        input(threshold);
    }
    
    while (true){
        cout << "Enter minimum block size";
        input(min_block);
    }


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
    wait_for_input();
}