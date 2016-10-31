//
// Created by Liferov Ilia (liferili) on 5/25/16.
//

#include "HtmlElementCollection.h"
#include "ElementsFileError.h"
#include "PairHtmlElement.h"
#include "SingleHtmlElement.h"
#include <string>
#include <set>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

bool readTag(int& lineNumber, string& name, string& tagFormat, bool& paired, ifstream& inFile, set<string>& attributes, set<string>& children){
    string tmp, substr;
    bool waitForAttributes=false, waitForChildren=false, success=false;

    attributes.clear();
    children.clear();

    //reading html elements file line by line and constructing elements
    while(getline(inFile, tmp)){
        lineNumber++;
        if (tmp=="" || tmp.substr(0,2)=="//") continue;
        istringstream iss(tmp);
        //reading name of the element and format
        if (waitForAttributes==false && waitForChildren==false){
            vector<string> tmpVec;
            while (getline(iss,substr,';')){
                tmpVec.push_back(substr);
            }
            if (tmpVec.size()!=3
                || tmpVec[0].find_first_of(" ,./\\:\'\"][}{><&?!@#$%*()_-=+")!=tmpVec[0].npos
                || (tmpVec[1]!="inline" && tmpVec[1]!="block")
                || (tmpVec[2]!="required" && tmpVec[2]!="forbidden")) throw ElementsFileError("wrong format. line: "+to_string(lineNumber));
            name=tmpVec[0];
            tagFormat=tmpVec[1];
            paired=tmpVec[2]=="required";
            waitForAttributes=true;
            waitForChildren=false;
        }
            //reading element`s attributes
        else if (waitForAttributes==true && waitForChildren==false){
            while(getline(iss,substr,' ')){
                auto it=attributes.insert(substr);
                if (!it.second) throw ElementsFileError("duplicate attribute \""+substr+"\". line: "+to_string(lineNumber));
            }
            if (!paired) return true;
            waitForAttributes=false;
            waitForChildren=true;
        }
            //reading element`s children
        else if (waitForAttributes==false && waitForChildren==true){
            while(getline(iss,substr,' ')){
                auto it=children.insert(substr);
                if (!it.second) throw ElementsFileError("duplicate child \""+substr+"\". line: "+to_string(lineNumber));
            }
            success=true;
        }
        if (success) break;
    }
    if (success) return true;
    else if (waitForAttributes==true && waitForChildren==false) throw ElementsFileError(" missing attributes of element \""+name + "\". line: "+to_string(lineNumber));
    else if (waitForAttributes==false && waitForChildren==true) throw ElementsFileError(" missing children of element \""+name + "\". line: "+to_string(lineNumber));
    return false;
}

HtmlElementCollection::HtmlElementCollection(Format &format) {
    int lineNumber=0;
    ifstream inFile;
    string name, tagFormat;
    bool paired, block;
    set<string> attributes, children;

    inFile.open(format.getHtmlElemsFileName());
    if (!inFile.good()) throw ElementsFileError("Cannot open file \""+format.getHtmlElemsFileName()+"\"");

    //parsing html elements file, creating elements and pushing them to the elements dictionary
    while(readTag(lineNumber, name, tagFormat, paired, inFile, attributes, children)){
        block=tagFormat=="block";
        if (paired){
            shared_ptr<PairHtmlElement> elemPtr (new PairHtmlElement(name, block, children, attributes));
            this->elementCollection[name]=elemPtr;
        }
        else{
            shared_ptr<SingleHtmlElement> elemPtr (new SingleHtmlElement(name, block, attributes));
            this->elementCollection[name]=elemPtr;
        }
    }
    if (this->elementCollection.empty()) throw ElementsFileError("file is empty!");
}
