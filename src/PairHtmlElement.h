//
// Created by Liferov Ilia (liferili) on 5/25/16.
//

#ifndef SEMESTRALNI_PRACE_PAIRHTMLELEMENT_H
#define SEMESTRALNI_PRACE_PAIRHTMLELEMENT_H


#include "HtmlElement.h"

/**
 * Represents html element that requires closing tag with its properties (allowed attributes and children; format of element: block/inline, paired/single).
 */
class PairHtmlElement: public HtmlElement {
protected:
    /**
     * set of allowed children
     */
    set<string> children;
public:
    /**
     * Constructs the html element that requires closing tag.
     * @param name name of the html element
     * @param block format: block/inline. TRUE if block
     * @param children set of allowed children
     * @param attributes set of allowed attributes
     */
    PairHtmlElement(string name, bool block, set<string>& children, set<string>& attributes);
    bool isBlock()const;
    bool checkChild(const string& child)const;
    bool checkAttribute(const string& attribute)const;
    bool isPaired()const;
};

#endif //SEMESTRALNI_PRACE_PAIRHTMLELEMENT_H
