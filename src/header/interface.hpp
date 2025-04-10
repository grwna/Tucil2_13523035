#ifndef _INTERFACE_HPP
#define _INTERFACE_HPP

#include <filesystem>
#include <regex>
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

#endif