//
// Created by Liferov Ilia (liferili) on 5/25/16.
//

#ifndef SEMESTRALNI_PRACE_ELEMENTSFILEERROR_H
#define SEMESTRALNI_PRACE_ELEMENTSFILEERROR_H

#include <exception>
#include <string>

using namespace std;


/**
 * Represents html elemetns file error.
 */
class ElementsFileError : public exception {
private:
    /**
     * Contains base of the html elemetns file error ("Html elements file error: ")
     */
    string base="Html elements file error: ";
    /**
     * error message
     */
    string message;
public:
    /**
     * Constructs error.
     * @param str error message
     * @return error message
     */
    ElementsFileError(const string &str):message(str){};
    /**
     * Getter for error message
     * @return error message
     */
    virtual const char *what(void) const noexcept{
        return (base+message).c_str();
    };
};


#endif //SEMESTRALNI_PRACE_ELEMENTSFILEERROR_H
