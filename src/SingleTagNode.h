//
// Created by Liferov Ilia (liferili) on 5/12/16.
//

#ifndef SEMESTRALNI_PRACE_SINGLETAGNODE_H
#define SEMESTRALNI_PRACE_SINGLETAGNODE_H

#include <iostream>
#include <list>
#include <memory>
#include "Format.h"
#include "TreeNode.h"
#include "Error.h"

using namespace std;

/**
 * Html DOM tree that represents html element that does not require closing tag.
 */
class SingleTagNode: public TreeNode {
protected:
    /**
     * name of the html element
     */
    string tagName;
    /**
     * founded attibutes of the html element
     */
    vector<string> attributes;
public:
    /**
     * Constructs node.
     * @param name name of the element
     * @param line number of line where element appeared
     * @param vec array with element`s arguments
     */
    SingleTagNode(const string& name, int line, vector<string>& vec);
    void validate(HtmlElementCollection &elements, HtmlErrorList &errors)const;
    string getType()const;
    int getLineNumber()const;
    void print(Format &format, ofstream &ofile, HtmlElementCollection &collection)const;
};


#endif //SEMESTRALNI_PRACE_SINGLETAGNODE_H
