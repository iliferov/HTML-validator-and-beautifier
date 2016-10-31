//
// Created by Liferov Ilia (liferili) on 5/25/16.
//

#ifndef SEMESTRALNI_PRACE_ERROR_H
#define SEMESTRALNI_PRACE_ERROR_H

#include <exception>
#include <string>

using namespace std;

/**
 * Represents general error.
 */
class Error : public exception {
public:
    /**
     * Constructs error.
     * @param str error message
     * @return error message
     */
    Error(const string &str):message(str){};
    /**
     * Getter for error message
     * @return error message
     */
    virtual const char *what(void) const noexcept{
        return message.c_str();
    };
private:
    /**
     * error message
     */
    string message;
};


#endif //SEMESTRALNI_PRACE_ERROR_H
