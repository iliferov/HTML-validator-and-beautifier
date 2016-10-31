//
// Created by Liferov Ilia (liferili) on 5/12/16.
//


#include "Format.h"
#include "ArgumentsParser.h"
#include "ConfigError.h"
#include<string>
#include <fstream>

using namespace std;

void correctInt(string option, string str){
    for(auto i:str){
        if (!(i>=48 && i<=57)) throw ConfigError("Configuration file: wrong value of option \""+option+"\"");
    }
}

map<string,string> parseConfiguration(ifstream& file){
    string tmp;
    string optionStr;
    string valueStr;

    map<string,string> options;
    options["indent"]="\0";
    options["length"]="\0";
    options["elements"]="\0";

    //reading cofiguration file line by line and parsing the application settings
    while(getline(file, tmp)){
        if (tmp=="" || tmp.substr(0,2)=="//") continue;
        auto pos=tmp.find("=");
        if (pos==string::npos) throw ConfigError("no such parameter \""+tmp+"\"");
        optionStr=tmp.substr(0, pos);
        valueStr=tmp.substr(pos+1, tmp.size());
        if (options.find(optionStr)==options.end()) throw ConfigError("no such parameter \""+optionStr+"\"");
        else if (options.find(optionStr)->second!="\0") throw ConfigError("duplicate parameter \""+optionStr+"\"");
        options[optionStr]=valueStr;
    }

    //checking if any mandatory application setting if missing
    for(auto i:options)
        if (i.second=="\0") throw ConfigError("Wrong format. missing \""+i.first+"\"");

    return options;
}

Format::Format(ArgumentsParser &parser) {
    ifstream inFile;
    map<string,string> options;

    inFile.open(parser.getCfgFileName());
    if (!inFile.good()) throw ConfigError("Cannot open file "+parser.getCfgFileName());
    options=parseConfiguration(inFile);

    correctInt("indent",options["indent"]);
    correctInt("length",options["length"]);

    this->length=stoi(options["length"]);
    this->indent=stoi(options["indent"]);
    this->currentIndent=0;
    this->currentLength=this->length;
    this->htmlElemsFile=options["elements"];
}

int Format::getLength() const {return length;}

int Format::getCurLength() const {return currentLength;}

void Format::resetCurLength() {currentLength=length;}

void Format::setCurLength(int val) {currentLength=val;}

int Format::getIndent() const {return indent;}

int Format::getCurIndent() const {return currentIndent;}

void Format::decCurIndent() {
    if (currentIndent<=indent) currentIndent=0;
    else currentIndent-=indent;
}

void Format::incCurIndent() {
    currentIndent+=indent;
}

void Format::openInline() {inlineStack.push(true);}

void Format::closeInline() {if (!inlineStack.empty()) inlineStack.pop();}

string Format::getHtmlElemsFileName() const {return htmlElemsFile;}

bool Format::isInlineOpen() const {return !inlineStack.empty();}





