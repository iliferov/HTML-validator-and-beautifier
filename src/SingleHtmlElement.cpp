//
// Created by Liferov Ilia (liferili) on 6/5/16.
//

#include "SingleHtmlElement.h"

using namespace std;

SingleHtmlElement::SingleHtmlElement(string name, bool block, set <string> &attributes) :HtmlElement(name, block, attributes){}

bool SingleHtmlElement::isBlock() const {return this->block;}

bool SingleHtmlElement::checkChild(const string &child)const {return false;}

bool SingleHtmlElement::checkAttribute(const string &attribute)const {
    auto it=this->attributes.find(attribute);
    return !(it == this->attributes.end());
}

bool SingleHtmlElement::isPaired()const {return false;}
