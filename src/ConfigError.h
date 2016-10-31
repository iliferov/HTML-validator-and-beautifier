//
// Created by Liferov Ilia (liferili) on 5/13/16.
//

#ifndef SEMESTRALNI_PRACE_EXCEPTION_H
#define SEMESTRALNI_PRACE_EXCEPTION_H

#include <exception>
#include <string>

using namespace std;

/**
 * Represents configuration file error.
 */
class ConfigError : public exception {
public:
    /**
     * Constructs error.
     * @param str error message
     * @return error message
     */
    ConfigError(const string &str):message(str){};
    /**
     * Getter for error message
     * @return error message
     */
    virtual const char *what(void) const noexcept{
        return (base+message).c_str();
    };
private:
    /**
     * Contains base of the configuration file error ("Configuration file: ")
     */
    string base="Configuration file: ";
    /**
     * error message
     */
    string message;
};


#endif //SEMESTRALNI_PRACE_EXCEPTION_H
