//
// Created by Liferov Ilia (liferili) on 5/25/16.
//

#ifndef SEMESTRALNI_PRACE_HTMLELEMENT_H
#define SEMESTRALNI_PRACE_HTMLELEMENT_H

#include <string>
#include <set>

using namespace std;

/**
 * Represents any html element with its properties (allowed attributes and children; format of element: block/inline, paired/single).
 */
class HtmlElement {
protected:
    /**
     * name of html element
     */
    string name;
    /**
     * format: block/inline. TRUE if block
     */
    bool block;
    /**
     * set of allowed attributes
     */
    set<string> attributes;
public:
    /**
     * Constructs the html element.
     * @param name name of the html element
     * @param block format: block/inline. TRUE if block
     * @param attributes set of allowed attributes
     */
    HtmlElement(string name, bool block, set<string>& attributes);
    /**
     * Getter for format: block/inline.
     * @return TRUE if block
     */
    virtual bool isBlock()const=0;
    /**
     * Validates child of the html element.
     * @param child name of the child that should be validated
     * @return TRUE of child is allowed
     */
    virtual bool checkChild(const string& child)const=0;
    /**
     * Validates attibute of the html element.
     * @param attribute name of the attribute that should be validated
     * @return
     */
    virtual bool checkAttribute(const string& attribute)const=0;
    /**
     * Getter for format: paired/single.
     * @return TRUE if paired
     */
    virtual bool isPaired ()const=0;
};


#endif //SEMESTRALNI_PRACE_HTMLELEMENT_H
