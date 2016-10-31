//
// Created by Liferov Ilia (liferili) on 5/12/16.
//

#ifndef SEMESTRALNI_PRACE_PRINTFORMAT_H
#define SEMESTRALNI_PRACE_PRINTFORMAT_H

#include <iostream>
#include <list>
#include <memory>
#include <stack>
#include "ArgumentsParser.h"

using namespace std;

/**
 * Provides printing format.
 */
class Format {
protected:
    /**
     * specified line length
     */
    int length;
    /**
     * current line length (is used while printing)
     */
    int currentLength;
    /**
     * specified indent
     */
    int indent;
    /**
     * current indent (is used while printing)
     */
    int currentIndent;
    /**
     * name of the file that contains information about html elements
     */
    string htmlElemsFile;
    /**
     * stack of opened inlines (is used while printing)
     */
    stack<bool> inlineStack;
public:
    /**
     * Constructs instance of class.
     * @param parser parser where appropriate settings stores
     */
    Format(ArgumentsParser& parser);
    /**
     * Getter for specified line length.
     * @return specified line length.
     */
    int getLength()const;
    /**
     * Getter for current line length.
     * @return current line length
     */
    int getCurLength()const;
    /**
     * Resets current line length.
     */
    void resetCurLength();
    /**
     * Setter for current line length.
     * @param val prefered value
     */
    void setCurLength(int val);
    /**
     * Getter for specified indent.
     * @return specified indent.
     */
    int getIndent()const;
    /**
     * Getter for current indent.
     * @return current indent
     */
    int getCurIndent()const;
    /**
     * Increments current indent by one indent length.
     */
    void incCurIndent();
    /**
     * Decrements current indent by one indent length.
     */
    void decCurIndent();
    /**
     * Opens inline. Pushing it to inline stack.
     */
    void openInline();
    /**
     * Closes inline. Poping it from inline stack.
     */
    void closeInline();
    /**
     * Checks whether inline is open.
     * @return TRUE if inline is open
     */
    bool isInlineOpen()const;
    /**
     * Getter for name of the file that contains information about html elements
     * @return name of the file
     */
    string getHtmlElemsFileName()const;
};


#endif //SEMESTRALNI_PRACE_PRINTFORMAT_H
