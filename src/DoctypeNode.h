//
// Created by Liferov Ilia (liferili) on 5/27/16.
//

#ifndef SEMESTRALNI_PRACE_DOCTYPENODE_H
#define SEMESTRALNI_PRACE_DOCTYPENODE_H


#include "TreeNode.h"
#include "Error.h"

/**
 * Html DOM tree node that represents doctype.
 */
class DoctypeNode : public TreeNode {
protected:
    /**
     * content of the html doctype
     */
    string content;
public:
    /**
     * Constructs doctype node of html DOM tree.
     * @param str doctype content
     * @param line line where comment appeared
     */
    DoctypeNode(const string& str, int line);
    void validate(HtmlElementCollection &elements, HtmlErrorList &errors)const{};
    string getType()const;
    int getLineNumber()const;
    void print(Format &format, ofstream &ofile, HtmlElementCollection &collection)const;
};


#endif //SEMESTRALNI_PRACE_DOCTYPENODE_H
