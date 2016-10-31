//
// Created by Liferov Ilia (liferili) on 5/27/16.
//

#ifndef SEMESTRALNI_PRACE_HTMLERROR_H
#define SEMESTRALNI_PRACE_HTMLERROR_H

#include <string>
#include <iostream>

using namespace std;

/**
 * Represents html document error.
 */
class HtmlError {
private:
    /**
     * line where error takes place
     */
    int line;
    /**
     * error message
     */
    string content;
public:
    /**
     * Constructs html document error.
     * @param content error message
     * @param line line where error takes place
     */
    HtmlError(const string& content, int line);
    /**
     * Getter for line where error takes place.
     * @return line number
     */
    int getLine()const;
    /**
     * Prints html document error to std:out
     */
    void print()const;
};


#endif //SEMESTRALNI_PRACE_HTMLERROR_H
