//
// Created by Liferov Ilia (liferili) on 5/27/16.
//

#ifndef SEMESTRALNI_PRACE_TOPNODE_H
#define SEMESTRALNI_PRACE_TOPNODE_H


#include <vector>
#include "TreeNode.h"
#include "Error.h"
#include "PairTagNode.h"
#include "HtmlElementCollection.h"

/**
 * Html DOM tree node that represents html document.
 */
class TopNode: public PairTagNode {
public:
    /**
     * Constructs top node of html DOM tree.
     * @param line line where node appeared
     * @param vec array with arguments
     */
    TopNode(int line, vector<string>& vec):PairTagNode("top",line, vec){};
    void validate(HtmlElementCollection& elements, HtmlErrorList& errors)const;
    void print(Format &format, ofstream &ofile, HtmlElementCollection& collection)const;
    int getLineNumber()const;
};


#endif //SEMESTRALNI_PRACE_TOPNODE_H
