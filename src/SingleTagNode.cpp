//
// Created by Liferov Ilia (liferili) on 5/12/16.
//

#include <sstream>
#include "SingleTagNode.h"
#include "StringHelper.h"
#include <fstream>

using namespace std;

void SingleTagNode::validate(HtmlElementCollection &elements, HtmlErrorList &errors)const {
    set<string> setOfNames;
    for(auto i:this->attributes) {
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
}

void SingleTagNode::print(Format &format, ofstream &ofile, HtmlElementCollection &collection)const {
    //constructing open tag
    string oTag;
    oTag+=("<"+this->tagName);
    for (auto i:attributes){
        StringHelper::trim(i);
        oTag+=(" "+(i));
    }
    oTag+=">";
    //printing it
    int engaged=StringHelper::formattedPrint(ofile, oTag, format);
    if (format.isInlineOpen()){
        format.setCurLength(format.getLength()-engaged);
    }
    if (!ofile.put('\n')){ofile.close(); throw Error("Failed to write to file");}
}

SingleTagNode::SingleTagNode(const string &name, int line, vector<string> &vec) :TreeNode("single", line){
    this->tagName=name;
    if (vec.size()>1){
        for(auto i=vec.begin()+1;i!=vec.end();i++)
            attributes.push_back(*i);
    }
}

string SingleTagNode::getType() const {return this->nodeType;}

int SingleTagNode::getLineNumber() const {return this->line;}



