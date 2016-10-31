//
// Created by Liferov Ilia (liferili) on 5/28/16.
//

#ifndef SEMESTRALNI_PRACE_STRINGHELPER_H
#define SEMESTRALNI_PRACE_STRINGHELPER_H

#include <string>
#include <fstream>
#include <algorithm>
#include "Error.h"
#include "Format.h"
/**
 * constant string that contains whitespaces
 */
const string WHITESPACES=" \t\n\r\f\v";

using namespace std;

/**
 * Contains few methods for working with strings
 */
class StringHelper {
private:
    /**
     * It is a helper thus private constructor for it.
     */
    StringHelper(){};
    /**
     * Helping method for trimmming whitespaces. Performs left trim.
     * @param s string that should be trimmed
     * @param t string with characters that should be trimmed (here whitespaces)
     * @return reference to the string that has been trimmed
     */
    static string &leftTrim(string &s);
    /**
     * Helping method for trimmming whitespaces. Performs right trim.
     * @param s string that should be trimmed
     * @param t string with characters that should be trimmed (here whitespaces)
     * @return reference to the string that has been trimmed
     */
    static string &rightTrim(string &s);
    /**
     * Counts length of substring that should be printed according to the line length
     * @param str source string
     * @param beg index from where substring should begins
     * @param rowLength line length
     * @return returns substring length
     */
    static int textTokenLength(const string& str, int beg, int rowLength);
public:
    /**
     * Performs right and left trim of given characters (constant WHITESPACES here) with the string
     * @param s string that should be trimmed
     * @return reference to the string that has been trimmed
     */
    static string &trim(string &s);
    /**
     * Converts given string to lowercase
     * @param s string that should be converted
     * @return reference to the string that has been converted
     */
    static string& toLower(string& s);
    /**
     * Performs formatted print according to the line length and spaces that source string contains.
     * @param ofile output file stream for printing
     * @param str source string
     * @param format printing format
     * @return number of characters that is engaged on the last line
     */
    static int formattedPrint(ofstream &ofile, const string &str, Format &format);
};


#endif //SEMESTRALNI_PRACE_STRINGHELPER_H
