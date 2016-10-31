//
// Created by Liferov Ilia (liferili) on 5/12/16.
//

#ifndef SEMESTRALNI_PRACE_TEXTNODE_H
#define SEMESTRALNI_PRACE_TEXTNODE_H

#include <iostream>
#include <list>
#include <memory>
#include "Format.h"
#include "TreeNode.h"
#include "Error.h"

using namespace std;
/**
 * Html DOM tree node that represents character data.
 */
class TextNode: public TreeNode {
protected:
    /**
     * contains character data
     */
    string content;
public:
    /**
     * Constructs character data node of html DOM tree.
     * @param str character data
     * @param line line where character data appeared
     */
    TextNode(const string& str, int line);
    string getType()const;
    void validate(HtmlElementCollection &elements, HtmlErrorList &errors)const{};
    int getLineNumber()const;
    void print(Format &format, ofstream &ofile, HtmlElementCollection &collection)const;
};


#endif //SEMESTRALNI_PRACE_TEXTNODE_H
