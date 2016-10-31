//
// Created by Liferov Ilia (liferili) on 5/12/16.
//

#ifndef SEMESTRALNI_PRACE_TREENODE_H
#define SEMESTRALNI_PRACE_TREENODE_H

#include <iostream>
#include <list>
#include <memory>
#include <vector>
#include "Format.h"
#include "HtmlErrorList.h"
#include "HtmlElementCollection.h"

using namespace std;

/**
 * Represents any node of html DOM tree (abstract class).
 */

class TreeNode {
protected:
    /**
     * type of the node
     */
    string nodeType;
    /**
     * number of line where html element appeared
     */
    int line;
public:
    /**
     * Constructs any node of html DOM tree.
     * @param type type of the node
     * @param line number of line where html element appeared
     */
    TreeNode(const string& type, int line){nodeType=type;this->line=line;};
    /**
     * Getter for node type.
     * @return type of node
     */
    virtual string getType()const=0;
    /**
     * Validates node`s arguments and children.
     * @param elements collection of html elements (checking possible arguments and children)
     * @param errors list of errors
     */
    virtual void validate(HtmlElementCollection &elements, HtmlErrorList &errors)const=0;
    /**
     * Prints node with appropriate format.
     * @param format printing format
     * @param ofile output file stream
     * @param collection collection of html elements (checking format of html element)
     */
    virtual void print(Format &format, ofstream &ofile, HtmlElementCollection &collection)const=0;
    /**
     * Appends child node.
     * @param child child that should be appended
     */
    virtual void pushChild(shared_ptr<TreeNode> child){};
    /**
     * Getter for line where html element appeared
     * @return number of line
     */
    virtual int getLineNumber()const=0;
};

#endif //SEMESTRALNI_PRACE_TREENODE_H
