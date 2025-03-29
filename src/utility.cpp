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