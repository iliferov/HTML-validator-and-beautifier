//
// Created by Liferov Ilia (liferili) on 5/27/16.
//

#include "CommentNode.h"
#include "StringHelper.h"

void CommentNode::print(Format &format, ofstream &ofile, HtmlElementCollection &collection)const {
    string comment;
    comment+=("<"+this->content+">");
    int engaged=StringHelper::formattedPrint(ofile, comment, format);
    if (format.isInlineOpen()){
        format.setCurLength(format.getLength()-engaged);
    }
    if (!ofile.put('\n')) {ofile.close(); throw Error("Failed to write to file");}
}

CommentNode::CommentNode(const string &str, int line) :TreeNode("comment", line){content=str;}

string CommentNode::getType() const {return this->nodeType;}

int CommentNode::getLineNumber() const {return this->line;}

