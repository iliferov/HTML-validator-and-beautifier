//
// Created by Liferov Ilia (liferili) on 6/5/16.
//

#include "StringHelper.h"

using namespace std;

string & StringHelper::leftTrim(string &s) {
    s.erase(0, s.find_first_not_of(WHITESPACES));
    return s;
}

string &StringHelper::rightTrim(string &s) {
    s.erase(s.find_last_not_of(WHITESPACES) + 1);
    return s;
}

int StringHelper::textTokenLength(const string &str, int beg, int rowLength) {
    int i;
    for(i=beg+rowLength; i>beg; i--)
        if (str.substr(i,1)==" " || str.substr(i,1)=="\n" || str.substr(i,1)=="\t") break;
    if (i==beg){
        int j;
        for(j=beg+rowLength; j<(int)str.length(); j++)
            if (str.substr(j,1)==" " || str.substr(j,1)=="\n" || str.substr(j,1)=="\t") break;
        return j-beg;
    }
    else{
        return i-beg;
    }
}

string &StringHelper::trim(string &s) {
    return leftTrim(rightTrim(s));
}

string &StringHelper::toLower(string &s) {
    transform(s.begin(), s.end(), s.begin(),
              [](unsigned char c) { return std::tolower(c); });
    return s;
}

int StringHelper::formattedPrint(ofstream &ofile, const string &str, Format &format) {
    int left=str.length(), beg=0;
    while(true){
        if (format.getCurLength()==format.getLength())
            for(auto i=0; i<format.getCurIndent(); i++)
                if (!ofile.put(' ')) {ofile.close(); throw Error("Failed to write to file");}
        //dividing source string into pieces according to line length and spaces
        if (left>format.getCurLength()){
            int substrLength=textTokenLength(str, beg, format.getCurLength());
            if (!ofile.write(str.substr(beg, substrLength).c_str(), substrLength)) {ofile.close(); throw Error("Failed to write to file");}
            left-=substrLength+1;
            beg+=substrLength+1;
            format.resetCurLength();
            if (!ofile.put('\n')) {ofile.close(); throw Error("Failed to write to file");}
        }
            //printing the rest
        else{
            if (left<0){
                left*=-1;
                break;
            }
            if (!ofile.write(str.substr(beg, left).c_str(), left)) {ofile.close(); throw Error("Failed to write to file");}
            format.resetCurLength();
            break;
        }
    }
    return left;
}
