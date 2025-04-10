#ifndef _UTILITY_HPP
#define _UTILITY_HPP

#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <cmath>
#include <vector>
using namespace std;

/**
 * @brief Trims leading and trailing whitespaces from input
 * 
 * @param str string to be trimmed 
 */
void trim(string &str);

/**
 * @brief Reads input and save it to var, then clear buffer
 * 
 * @param var variable to save to 
 */
template<class T>
bool input(T &var) {
    string line;
    if (getline(cin, line)) {
        istringstream iss(line);
        if (iss >> var) {
            return true;
        }
    }
    cin.clear();
    return false;
}

/**
 * @brief Prints word in ANSI escape color
 * 
 * This functions outputs given word(s) with specified ANSI Color Codes.
 * Supports 256-color ANSI escape characters 
 * 
 * @param word The text to be printed
 * @param code ANSI Color Codes (0-255) see 256-ansi-table.png in doc/img
 * @param endl If true, appends newline at the end of word
 */
template<class T>
void clr(const T& word, int code, bool enln = true) {
    cout << "\033[38;5;" << code << "m" << word << "\033[0m";
    if (enln) cout << endl;
}

/**
 * @brief Create a file and all parent directory (if not exists)
 *  
 * @param Absolute path to file
 */
void create_file(const string path);

/**
 * @brief Validate an input variable as valid integer or not
 * 
 * @param var variable to check
 * @return true if input is a valid integer,
 * @return false if input is not valid integer
 */
bool validate_int(int var);

/**
 * @brief Get the threshold range for the corresponding error method
 * 
 * @param mode 
 * @return A "tuple" vector for min range and max range 
 */
vector<int> get_threshold_range(int mode);

/**
 * @brief Validate threshold value
 * 
 * @param range range of error calculation mode
 * @param threshold the threshold to validate
 * @return true if valid 
 */
bool validate_threshold(vector<int> range, int threshold);

#endif
