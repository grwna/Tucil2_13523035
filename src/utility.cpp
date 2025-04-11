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

vector<int> get_threshold_range(int mode){
    switch (mode){
        case 1:
            return {0, 2250};
        case 2:
            return {0,50};
        case 3:
            return {0,250};
        case 4:
            return {0,8};
        case 5:
            return {-1,1};
        default:
            return {0,0};
    }
}

bool validate_threshold(vector<int> range, int threshold){
    return threshold >= range[0] && threshold <= range[1];
}