//
// Created by Liferov Ilia (liferili) on 6/6/16.
//

#include "HtmlError.h"

HtmlError::HtmlError(const string &content, int line) {this->content=content;this->line=line;}

int HtmlError::getLine() const {return this->line;}

void HtmlError::print() const {
    cout << "line: " << this->line << ". " << content << endl << endl;
}
