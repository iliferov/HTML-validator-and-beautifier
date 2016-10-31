//
// Created by Liferov Ilia (liferili) on 5/27/16.
//

#include "TopNode.h"

void TopNode::validate(HtmlElementCollection& elements, HtmlErrorList& errors)const {
    //checking document for a doctype
    auto iter=children.begin();
    for (;iter!=children.end();iter++)
        if ((*iter)->getType()=="doctype") break;

    if (iter==children.end()){
        string errorMessage="No DOCTYPE found";
        errors.pushError(HtmlError(errorMessage, 1));
    }
    else if (iter!=children.begin()){
        string errorMessage="DOCTYPE is allowed only at the top of the document";
        errors.pushError(HtmlError(errorMessage, (*iter)->getLineNumber()));
    }

    //validating children
    for(auto i:children)
        i->validate(elements, errors);
}

void TopNode::print(Format &format, ofstream &ofile, HtmlElementCollection& collection)const {
    for(auto i:children)
        i->print(format, ofile, collection);
}

int TopNode::getLineNumber()const {return this->line;}



