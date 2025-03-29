#ifndef _UTILITY_HPP
#define _UTILITY_HPP

#include <string>
#include <iostream>
#include <limits>
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
void input(T &var){
    cin >> var;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

#endif
