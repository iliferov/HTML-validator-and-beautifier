//
// Created by Liferov Ilia (liferili) on 5/12/16.
//

#include <fstream>
#include <sstream>
#include <deque>
#include "HtmlDOM.h"
#include "DoctypeNode.h"
#include "PairTagNode.h"
#include "SingleTagNode.h"
#include "CommentNode.h"
#include "TextNode.h"
#include "ErrorTagNode.h"
#include <algorithm>
#include "StringHelper.h"

using namespace std;

//factory method. chooses type of tree node, creates it and pushes it to the html DOM tree
void AddTag(string& tag, int line, deque<shared_ptr<PairTagNode>>& nodeStack, const HtmlElementCollection& htmlElements, HtmlErrorList& errors){
    if (tag.substr(0,1)!="/"){ //if it is a opening tag
        if (tag.substr(tag.length()-1,1)=="/") tag=tag.substr(0,tag.length()-1);
        string checker=tag.substr(0,9);
        StringHelper::toLower(checker);
        if (checker =="!doctype "){ // if it is a doctype
            shared_ptr<DoctypeNode> ptr (new DoctypeNode(tag,line));
            (*nodeStack.begin())->pushChild(ptr);
        }
        else if (tag.length()>=5 && ((tag.substr(0,3)=="!--" && tag.substr(tag.length()-2,2)=="--")
                || (tag.substr(0,4)=="!--[" && tag.substr(tag.length()-1,1)=="]")
                || (tag.substr(0,2)=="![" && tag.substr(tag.length()-3,3)=="]--"))){ // if it is a (conditional) comment
            shared_ptr<CommentNode> ptr (new CommentNode(tag, line));
            (*nodeStack.begin())->pushChild(ptr);
        }
        else{
            //parsing element`s string to name and attributes
            vector<string> tokens;
            istringstream iss(tag);
            string tmp, token;
            getline(iss,tmp,' ');
            tokens.push_back(tmp);
            while(getline(iss,tmp,' ')){
                token+=tmp;
                iss.seekg(-2,iss.cur);
                if (iss.peek()=='"'){
                    tokens.push_back(tmp);
                    token.clear();
                }
                else token+=" ";
                iss.seekg(2,iss.cur);
            }
            if (token!="") tokens.push_back(token);
            //----------------------------------------------

            if (tokens.empty()){ //tag is empty <>
                errors.pushError(HtmlError("Empty tag", line));
                string tagToText="<"+tag+">";
                shared_ptr<ErrorTagNode> ptr (new ErrorTagNode(tagToText, line));
                (*nodeStack.begin())->pushChild(ptr);
            }
            else{ //tag is not empty
                string forSearch=tokens[0];
                StringHelper::toLower(forSearch);

                auto it=htmlElements.elementCollection.find(forSearch);
                if (it==htmlElements.elementCollection.end()){ //undefined tag, pushing it into DOM as ErrorTag
                    string errorMessage="Undefined tag \""+tokens[0]+"\"";
                    errors.pushError(HtmlError(errorMessage, line));
                    string tagToText="<"+tag+">";
                    shared_ptr<ErrorTagNode> ptr (new ErrorTagNode(tagToText, line));
                    (*nodeStack.begin())->pushChild(ptr);
                }
                else{
                    if (it->second->isPaired()){ //element requires closing tag
                        shared_ptr<PairTagNode> ptr (new PairTagNode(tokens[0], line, tokens));
                        (*nodeStack.begin())->pushChild(ptr);
                        nodeStack.push_front(ptr);
                    }
                    else{ //element doesnt require closing tag
                        shared_ptr<SingleTagNode> ptr(new SingleTagNode(tokens[0], line, tokens));
                        (*nodeStack.begin())->pushChild(ptr);
                    }
                }
            }
        }
    }
    else{ //if it is a closing tag
        string closingTag=tag.substr(1,tag.length()-1);
        string lastInStack=(*nodeStack.begin())->getTagName();
        StringHelper::toLower(closingTag);
        StringHelper::toLower(lastInStack);

        if (closingTag==lastInStack){ // exact match with the top of the stack
            (*nodeStack.begin())->setClosingTag(tag);
            nodeStack.pop_front();
        }
        else{
            auto it=htmlElements.elementCollection.find(closingTag);
            if (it==htmlElements.elementCollection.end()){ //if closing tag is undefined. Just pushing it into DOM as ErrorTag
                string errorMessage="Undefined tag \"\\"+tag.substr(1,tag.length())+"\"";
                errors.pushError(HtmlError(errorMessage,line));
                string tagToText="<"+tag+">";
                shared_ptr<ErrorTagNode> ptr (new ErrorTagNode(tagToText, line));
                (*nodeStack.begin())->pushChild(ptr);
            }
            else{ //known tag. Checking if it was opened somewhere earlier
                auto stackIterator=nodeStack.begin();
                for(; stackIterator!=nodeStack.end(); stackIterator++){
                    string name=(*stackIterator)->getTagName();
                    StringHelper::toLower(name);
                    if (name==closingTag) break;
                }
                if (stackIterator!=nodeStack.end()){ //appropriate tag is not the last in stack
                    string errorMessage;
                    int cnt=0;
                    for(auto i=nodeStack.begin(); i!=stackIterator; i++){
                        errorMessage="Closing tag for element \""+(*i)->getTagName()+"\"(opened on line: "+to_string((*i)->getLineNumber())+") expected";
                        errors.pushError(HtmlError(errorMessage, line));
                        cnt++;
                    }
                    for(auto i=0; i<cnt; i++)
                        nodeStack.pop_front();
                    (*nodeStack.begin())->setClosingTag(tag);
                    nodeStack.pop_front();
                }
                else{ //tag has not been opened
                    string errorMessage="End tag for element \""+tag.substr(1,tag.length())+"\" which is not open";
                    errors.pushError(HtmlError(errorMessage,line));
                    string tagToText="<"+closingTag+">";
                    shared_ptr<ErrorTagNode> ptr (new ErrorTagNode(tagToText, line));
                    (*nodeStack.begin())->pushChild(ptr);
                }
            }
        }
    }
}

//creates text node and pushes it to the html DOM tree
void AddText(string& text, int line, deque<shared_ptr<PairTagNode>>& nodeStack){
    StringHelper::trim(text);
    if (text!=" " && text!="\n" && text!=""){ //we dont need empty I suppose
        shared_ptr<TextNode> ptr (new TextNode(text, line));
        (*nodeStack.begin())->pushChild(ptr);
    }
}

//helping function. deletes spaces from string
void DeleteSpaces(string& src){
    if (src.length()>=5 && ((src.substr(0,3))!="!--" || (src.substr(src.length()-2,2))!="--")){
        auto it= unique(src.begin(), src.end(), [](char l, char r){return (l==r) && (l==' ');});
        src.erase(it,src.end());
    }
}

void HtmlDOM::createDOM(string inputFileName, const HtmlElementCollection& htmlElements, HtmlErrorList& errors) {
    ifstream inFile(inputFileName);
    if (!inFile.good()) throw Error("Cannot open input file \""+inputFileName+"\".");

    bool readingTag=false;
    int lineNumber=0;
    string tmp, tag, text, piece;

    //creating the TOP node (represents the whole html document)
    deque<shared_ptr<PairTagNode>> nodeStack;
    vector<string> shame;
    shared_ptr<TopNode> top (new TopNode(lineNumber, shame));
    this->top=top;
    nodeStack.push_front(top);

    //parsing input file into tags nad character data
    while(getline(inFile,tmp)){
        lineNumber++;
        istringstream tmpLine(tmp);
        while (1) {
            if (readingTag) {
                getline(tmpLine, piece, '>');
                if (tmpLine.eof()) {
                    tag += piece;
                    break;
                }
                else {
                    tag += piece;
                    DeleteSpaces(tag);
                    AddTag(tag, lineNumber, nodeStack, htmlElements, errors);
                    tag.clear();
                    readingTag = false;
                }
            }
            else {
                getline(tmpLine, piece, '<');
                if (tmpLine.eof()) {
                    text += piece;
                    break;
                }
                else {
                    text += piece;
                    DeleteSpaces(text);
                    if (!text.empty()) AddText(text, lineNumber, nodeStack);
                    text.clear();
                    readingTag = true;
                }
            }
        }
    }
    //check the stack if there are any elements that should be closed
    while(nodeStack.size()!=1){
        string errorMessage="Missing closing tag for \""+(*nodeStack.begin())->getTagName()+"\". Tag opens on line "+to_string((*nodeStack.begin())->getLineNumber());
        errors.pushError(HtmlError(errorMessage, lineNumber));
        nodeStack.pop_front();
    }
    inFile.close();
}

void HtmlDOM::validateDocument(HtmlElementCollection &elements, HtmlErrorList &errors)const {
    this->top->validate(elements, errors);
}

void HtmlDOM::printHtmlDocument(const string &ofileName, Format &format, HtmlElementCollection& collection) const {
    ofstream ofile(ofileName);
    if (!ofile.good()) throw Error("Cannot open output file \""+ofileName+"\"");
    cout << "Printing formatted document to \""+ofileName+"\" ..." << endl;
    this->top->print(format, ofile, collection);
    cout << "Done!" << endl << endl;
}









