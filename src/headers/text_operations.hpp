#ifndef TEXT_OPERATIONS_MODULE_HPP
#define TEXT_OPERATIONS_MODULE_HPP

#include <stdio.h>

/*
 * Checks if a character is a letter
 */
inline bool isLetter(char ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

/*
 * Checks if a character is a digit
 */
inline bool isDigit(char ch)
{
    return ch >= '0' && ch <= '9';
}

/*
 * Checks if a character ends a line
 */
inline bool isEndOfLine(int ch)
{
    return ch == '\n' || ch == EOF;
}

/*
 * Checks if a charcter is a space
 */
inline bool isSpace(int ch)
{
    return ch == '\t' || ch == ' ' || ch == '\r' || isEndOfLine(ch);
}

/*
 * Checks if a string is an integer number
 */
bool isNumber(const char *str);

/*
 * Converts a string to an integer number
 */
int str2int(const char *str);

/*
 * Converts a string to a float number
 */
double str2double(const char *str);

#endif
