//
// Created by Liferov Ilia (liferili) on 5/25/16.
//

#ifndef SEMESTRALNI_PRACE_SINGLEHTMLELEMENT_H
#define SEMESTRALNI_PRACE_SINGLEHTMLELEMENT_H

#include "HtmlElement.h"

/**
 * Represents html element that does not require closing tag with its properties (allowed attributes and children; format of element: block/inline, paired/single).
 */
class SingleHtmlElement: public HtmlElement {
public:
    /**
     * Constructs the html element that does not require closing tag.
     * @param name name of the html element
     * @param block format: block/inline. TRUE if block
     * @param attributes set of allowed attributes
     */
    SingleHtmlElement(string name, bool block, set<string>& attributes);
    bool isBlock()const;
    bool checkChild(const string& child)const;
    bool checkAttribute(const string& attribute)const;
    bool isPaired()const;
};


#endif //SEMESTRALNI_PRACE_SINGLEHTMLELEMENT_H
