//
// Created by Liferov Ilia (liferili) on 5/12/16.
//

#ifndef SEMESTRALNI_PRACE_HTML_H
#define SEMESTRALNI_PRACE_HTML_H

#include <iostream>
#include <list>
#include <memory>
#include <vector>
#include "Format.h"
#include "TreeNode.h"
#include "HtmlElementCollection.h"
#include "TopNode.h"
#include "HtmlError.h"
#include "Error.h"
#include "HtmlErrorList.h"

using namespace std;

/**
 * Represents html DOM tree.
 */
class HtmlDOM {
protected:
    /**
     * pointer to the top node
     */
    shared_ptr<TopNode> top;
public:
    /**
     * Creates html DOM tree.
     * @param inputFileName input file name
     * @param htmlElements collection of html elements
     * @param errors list of errors
     */
    void createDOM(string inputFileName, const HtmlElementCollection& htmlElements, HtmlErrorList& errors);
    /**
     * Validates html document.
     * @param elements collection of html elements
     * @param errors list of errors
     */
    void validateDocument(HtmlElementCollection &elements, HtmlErrorList &errors)const;
    /**
     * Prints html document
     * @param ofileName output file name
     * @param format printing format
     * @param collection collection of html elements
     */
    void printHtmlDocument(const string &ofileName, Format &format, HtmlElementCollection& collection) const;
};


#endif //SEMESTRALNI_PRACE_HTML_H
