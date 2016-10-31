//
// Created by Liferov Ilia (liferili) on 5/12/16.
//

#include "TextNode.h"
#include "StringHelper.h"
#include <fstream>

void TextNode::print(Format &format, ofstream &ofile, HtmlElementCollection &collection)const {
    int engaged=StringHelper::formattedPrint(ofile, this->content, format);
    if (format.isInlineOpen()){
        format.setCurLength(format.getLength()-engaged);
    }
    if (!ofile.put('\n')){ofile.close(); throw Error("Failed to write to file");}
}

TextNode::TextNode(const string &str, int line) :TreeNode("text", line){content=str;}

string TextNode::getType() const {return this->nodeType;}

int TextNode::getLineNumber() const {return this->line;}

