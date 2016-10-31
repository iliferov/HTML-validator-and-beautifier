//
// Created by Liferov Ilia (liferili) on 5/27/16.
//

#include "DoctypeNode.h"
#include "StringHelper.h"
#include <fstream>

void DoctypeNode::print(Format &format, ofstream &ofile, HtmlElementCollection &collection)const {
    string doctype;
    doctype+=("<"+this->content+">");
    int engaged=StringHelper::formattedPrint(ofile, doctype, format);
    if (format.isInlineOpen()){
        format.setCurLength(format.getLength()-engaged);
    }
    if (!ofile.put('\n')) {ofile.close(); throw Error("Failed to write to file");}
}

DoctypeNode::DoctypeNode(const string &str, int line) :TreeNode("doctype", line){content=str;}

string DoctypeNode::getType() const {return this->nodeType;}

int DoctypeNode::getLineNumber() const {return this->line;}

