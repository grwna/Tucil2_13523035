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

bool validate_int(int var) {
    stringstream ss;
    ss << var;
    int temp;
    ss >> temp;
    return !ss.fail() && ss.eof();
}