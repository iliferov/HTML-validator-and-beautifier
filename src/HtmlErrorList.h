//
// Created by Liferov Ilia (liferili) on 5/27/16.
//

#ifndef SEMESTRALNI_PRACE_ERRORLIST_H
#define SEMESTRALNI_PRACE_ERRORLIST_H


#include <list>
#include "HtmlError.h"
#include <algorithm>

using namespace std;

/**
 * Represents list of html document errors.
 */
class HtmlErrorList {
private:
    /**
     * there are errors ordered by line number
     */
    vector<HtmlError> errors;
public:
    /**
     * Pushes html document error
     * @param error error that should be pushed
     */
    void pushError(const HtmlError& error);
    /**
     * Prints all errors to std:out
     */
    void printErrors()const;
};


#endif //SEMESTRALNI_PRACE_ERRORLIST_H
