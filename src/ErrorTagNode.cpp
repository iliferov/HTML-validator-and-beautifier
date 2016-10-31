//
// Created by Liferov Ilia (liferili) on 5/31/16.
//


#include "Format.h"
#include "ErrorTagNode.h"
#include "StringHelper.h"
#include <fstream>

void ErrorTagNode::print(Format &format, ofstream &ofile, HtmlElementCollection &collection)const {
    int engaged=StringHelper::formattedPrint(ofile, this->content, format);
    if (format.isInlineOpen()){
        format.setCurLength(format.getLength()-engaged);
    }
    if (!ofile.put('\n')) {ofile.close(); throw Error("Failed to write to file");}
}

ErrorTagNode::ErrorTagNode(const string &str, int line) :TreeNode("undefined", line){content=str;}

string ErrorTagNode::getType() const {return this->nodeType;}

int ErrorTagNode::getLineNumber()const {return this->line;}

