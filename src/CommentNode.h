//
// Created by Liferov Ilia (liferili) on 5/27/16.
//

#ifndef SEMESTRALNI_PRACE_COMMENTNODE_H
#define SEMESTRALNI_PRACE_COMMENTNODE_H

#include <iostream>
#include <list>
#include <memory>
#include <vector>
#include "Format.h"
#include "TreeNode.h"
#include "Error.h"

using namespace std;

/**
 * Html DOM tree node that represents html comment (or conditional comment)
 */
class CommentNode: public TreeNode {
protected:
    /**
     * content of the html comment
     */
    string content;
public:
    /**
     * Constructs comment node of html DOM tree.
     * @param str comment content
     * @param line line where comment appeared
     */
    CommentNode(const string& str, int line);
    string getType()const;
    void validate(HtmlElementCollection &elements, HtmlErrorList &errors)const{};
    int getLineNumber()const;
    void print(Format &format, ofstream &ofile, HtmlElementCollection &collection)const;
};


#endif //SEMESTRALNI_PRACE_COMMENTNODE_H
