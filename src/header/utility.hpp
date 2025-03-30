#ifndef _UTILITY_HPP
#define _UTILITY_HPP

#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <cmath>
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
 * @brief Validate threshold value
 * 
 * @param mode error calculation mode
 * @param threshold the threshold to validate
 * @return true if valid 
 */
bool validate_threshold(int mode, int threshold);

#endif
