//
// Created by Liferov Ilia (liferili) on 5/13/16.
//

#ifndef SEMESTRALNI_PRACE_ARGUMENTSPARSER_H
#define SEMESTRALNI_PRACE_ARGUMENTSPARSER_H

#include <map>
#include<string>

using namespace std;


/**
 * Performs parsing of application arguments and
 * stores extracted application settings.
 */
class ArgumentsParser {
protected:
    /**
     * dictionary of the application arguments
     */
    map<string,string> args;
public:
    /**
     * Constructs empty instance of class. (empty argument storage).
     */
    ArgumentsParser();
    /**
     * Performs parsing arguments and saving extracted application settings.
     * @param argCount number of arguments
     * @param argArray pointer to array of C-strings
     */
    void setArgs(int argCount, char * argArray[]);
    /**
     * Getter for input file name.
     * @return input file name
     */
    string getIFileName()const;
    /**
     * Getter for output file name.
     * @return output file name
     */
    string getOFileName()const;
    /**
     * Getter for quiet mode.
     * @return TRUE if quiet mode is enabled
     */
    bool getQuietMode()const;
    /**
     * Getter for config file name.
     * @return config file name
     */
    string getCfgFileName()const;
};


#endif //SEMESTRALNI_PRACE_ARGUMENTSPARSER_H
