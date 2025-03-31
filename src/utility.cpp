#include "header/utility.hpp"

void trim(string &str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos) {
        str.clear(); // Empty string
        return;
    }
    size_t last = str.find_last_not_of(" \t\n\r");
    str = str.substr(first, last - first + 1);
}

void create_file(string path){
    filesystem::path p(path);
    filesystem::create_directories(p.parent_path());

    ofstream file(path);
    if (!file.is_open()) {
        cerr << "Error creating file: " << path << endl;
    } else {
        file.close();
    }
}

bool validate_threshold(int mode, int threshold){
    switch (mode){
        case 1:
            return (threshold >= 0 && threshold <= pow(255,2));
        case 2:
        case 3:
            return (threshold >= 0 && threshold <= 255);
        case 4:
            return (threshold >= 0 && threshold <= 8);
        case 5:
            return (threshold >= -1 && threshold <= 1);
        default:
            return false;
    }
}