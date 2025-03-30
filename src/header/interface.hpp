#ifndef _INTERFACE_HPP
#define _INTERFACE_HPP

#include <filesystem>
#include <regex>
#include "utility.hpp"
#include "processing.hpp"

const regex image_regex(".*\\.(jpg|jpeg|png)$", regex::icase);

/* The main menu for the interface */
void interface(void);

/* The main application flow */
void main_program();

/* Help menu, explains how to use the program */
void help(void);

/* Waits for user to press Enter key, then clears terminal */
void wait_for_input(void);

/* Clears terminal and put cursor to the top left */
void cls(void);

/* Display alert for invalid input */
void input_error(void);

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

#endif