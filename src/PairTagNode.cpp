//
// Created by Liferov Ilia (liferili) on 5/12/16.
//

#include <sstream>
#include "PairTagNode.h"
#include "StringHelper.h"
#include "Error.h"
#include <fstream>

void PairTagNode::validate(HtmlElementCollection &elements, HtmlErrorList &errors)const {
    //validating attributes
    set<string> setOfNames;
    for(auto i:this->attributes){
        istringstream iss(i);
        string attrName;
        getline(iss, attrName,'=');
        attrName= StringHelper::trim(attrName);
        auto it=setOfNames.insert(attrName);
        if (!it.second){
            string messageError="Duplicate specification of attribute \""+attrName+"\". Tag \""+ tagName +"\" is open at line: "+to_string(this->getLineNumber());
            errors.pushError(HtmlError(messageError, this->line));
        }
    }
    for(auto i:setOfNames){
        string forCheck=i;
        StringHelper::toLower(forCheck);
        string thisTagName=tagName;
        StringHelper::toLower(thisTagName);

        if (!elements.elementCollection[thisTagName]->checkAttribute(forCheck)){
            string messageError="There is no attribute \""+i+"\". Tag \""+ tagName +"\" is open at line: "+to_string(this->getLineNumber());
            errors.pushError(HtmlError(messageError, this->line));
        }
    }

    //validating children
    for(auto i:this->children){
        if (i->getType()=="text"){
            string forCheck="text";
                string thisTagName=tagName;
                StringHelper::toLower(thisTagName);
                if (!elements.elementCollection[thisTagName]->checkChild(forCheck)){
                    string messageError="Character data is not allowed inside element \""+tagName+"\"";
                    errors.pushError(HtmlError(messageError, i->getLineNumber()));
                }
        }
        else if (i->getType()=="doctype"){
            string message="DOCTYPE is allowed only at the top of the document";
            errors.pushError(HtmlError(message,i->getLineNumber()));
        }
        else if (i->getType()=="pair" || i->getType()=="single"){
            string forCheck= i->getType();
            StringHelper::toLower(forCheck);
            string thisTagName=tagName;
            StringHelper::toLower(thisTagName);
            if (!elements.elementCollection[thisTagName]->checkChild(forCheck)){
                string message="Element \""+ i->getType()+"\" is not allowed inside the element \""+ tagName +"\"";
                errors.pushError(HtmlError(message, i->getLineNumber()));
            }
        }
    }

    for(auto i:this->children)
        i->validate(elements, errors);
}

void PairTagNode::print(Format &format, ofstream &ofile, HtmlElementCollection &collection)const {
    string forSearch = this->tagName;
    auto it = collection.elementCollection.find(StringHelper::toLower(forSearch));

    string oTag;
    oTag += ("<" + this->tagName);
    for (auto i:attributes) {
        StringHelper::trim(i);
        oTag += (" " + (i));
    }
    oTag += ">";

    if (it->second->isBlock()) {
        StringHelper::formattedPrint(ofile, oTag, format);
        if (!ofile.put('\n')){ofile.close(); throw Error("Failed to write to file");}

        format.incCurIndent();
        for (auto i:this->children)
            i->print(format, ofile, collection);
        format.decCurIndent();

        if (this->closingTag != "") {
            string cTag;
            cTag += ("<" + this->closingTag + ">");
            StringHelper::formattedPrint(ofile, cTag, format);
            if (!ofile.put('\n')){ofile.close(); throw Error("Failed to write to file");}
        }
    }
    else {
        int engaged=StringHelper::formattedPrint(ofile, oTag, format);
        format.openInline();
        if (format.isInlineOpen()){
            format.setCurLength(format.getLength()-engaged);
        }

        for (auto i:this->children)
            i->print(format, ofile, collection);

        if (this->closingTag != "") {
            ofile.seekp(-1, ofile.cur); //eating last '\n'
            string cTag;
            cTag += ("<" + this->closingTag + ">");
            int engaged2=StringHelper::formattedPrint(ofile, cTag, format);
            format.closeInline();
            if (format.isInlineOpen()){
                format.setCurLength(format.getLength()-engaged2);
            }
            if (!ofile.put('\n')) {ofile.close(); throw Error("Failed to write to file");}
        }
    }
}

PairTagNode::PairTagNode(const string &name, int line, vector<string> &vec) :TreeNode("pair", line){
    this->closingTag="";
    this->tagName=name;
    if (vec.size()>1){
        for(auto i=vec.begin()+1;i!=vec.end();i++)
            attributes.push_back(*i);
    }
}

string PairTagNode::getTagName() {return tagName;}

void PairTagNode::setClosingTag(string &str) {closingTag=str;}

string PairTagNode::getType() const {return this->nodeType;}

int PairTagNode::getLineNumber()const {return this->line;}

void PairTagNode::pushChild(shared_ptr<TreeNode> child) {children.push_back(child);}
