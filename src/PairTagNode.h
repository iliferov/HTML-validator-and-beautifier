//
// Created by Liferov Ilia (liferili) on 5/12/16.
//

#ifndef SEMESTRALNI_PRACE_PAIRTAGNODE_H
#define SEMESTRALNI_PRACE_PAIRTAGNODE_H

#include <iostream>
#include <list>
#include <memory>
#include <vector>
#include "Format.h"
#include "TreeNode.h"

using namespace std;
/**
 * Html DOM tree that represents html element that requires closing tag.
 */
class PairTagNode: public TreeNode {
protected:
    /**
     * name of the html element
     */
    string tagName;
    /**
     * closing tag of the html element
     */
    string closingTag;
    /**
     * founded attributes of the html element
     */
    vector<string> attributes;
    /**
     * founded children of the html element
     */
    vector<shared_ptr<TreeNode>> children;
public:
    /**
     * Constructing node.
     * @param name name of the element
     * @param line number of line where element appeared
     * @param vec array with html element`s arguments
     */
    PairTagNode(const string& name, int line, vector<string>& vec);
    /**
     * Setter for closing tag
     * @param str closing tag
     */
    void setClosingTag(string& str);
    /**
     * Getter for html element name
     * @return
     */
    virtual string getTagName();
    string getType()const;
    virtual void validate(HtmlElementCollection &elements, HtmlErrorList &errors)const;
    virtual void print(Format &format, ofstream &ofile, HtmlElementCollection &collection)const;
    virtual int getLineNumber()const;
    void pushChild(shared_ptr<TreeNode> child);
};


#endif //SEMESTRALNI_PRACE_PAIRTAGNODE_H
