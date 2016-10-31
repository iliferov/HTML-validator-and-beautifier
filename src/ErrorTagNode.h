//
// Created by Liferov Ilia (liferili) on 5/28/16.
//

#ifndef SEMESTRALNI_PRACE_UNDEFINEDTAGNODE_H
#define SEMESTRALNI_PRACE_UNDEFINEDTAGNODE_H


#include <iostream>
#include <list>
#include <memory>
#include "Format.h"
#include "TreeNode.h"
#include "Error.h"

using namespace std;

/**
 * Html DOM tree node that represents undefined html element.
 */
class ErrorTagNode: public TreeNode {
protected:
    /**
     * content of the undefined html element
     */
    string content;
public:
    /**
     * Constructs undefined element node of html DOM tree.
     * @param str undefined element content
     * @param line line where undefined element appeared
     */
    ErrorTagNode(const string& str, int line);
    string getType()const;
    void validate(HtmlElementCollection &elements, HtmlErrorList &errors)const{};
    int getLineNumber()const;
    void print(Format &format, ofstream &ofile, HtmlElementCollection &collection)const;
};

#endif //SEMESTRALNI_PRACE_UNDEFINEDTAGNODE_H
