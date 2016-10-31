//
// Created by Liferov Ilia (liferili) on 6/5/16.
//

#include "PairHtmlElement.h"

using namespace std;

PairHtmlElement::PairHtmlElement(string name, bool block, set <string> &children, set <string> &attributes) :HtmlElement(name, block, attributes){this->children=children;}

bool PairHtmlElement::isBlock() const {return this->block;}

bool PairHtmlElement::checkChild(const string &child)const {
    auto it=this->children.find(child);
    return !(it==this->children.end());
}

bool PairHtmlElement::checkAttribute(const string &attribute)const {
    auto it=this->attributes.find(attribute);
    return !(it == this->attributes.end());
}

bool PairHtmlElement::isPaired()const {return true;}
