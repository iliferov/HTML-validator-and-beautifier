//
// Created by Liferov Ilia (liferili) on 5/13/16.
//

#include "ArgumentsParser.h"
#include "ConfigError.h"
#include "Error.h"
#include <map>
#include<string>

using namespace std;


ArgumentsParser::ArgumentsParser() {
    args["-i"]="\0";
    args["-o"]="\0";
    args["-c"]="\0";
    args["-q"]="\0";
}

void ArgumentsParser::setArgs(int argCount, char **argArray) {
    bool waitForValue=false;
    string tmpString;
    string lastOption;

    //pasing each main argument
    for(auto i=1;i!=argCount; i++){
        tmpString=argArray[i];
        //reading argument`s value
        if (waitForValue){
            auto it=args.find(lastOption);
            if (it!=args.end()) args[lastOption]=tmpString;
            waitForValue=false;
        }
            //reading argument
        else{
            auto it=args.find(tmpString);
            if (it!=args.end()) lastOption=tmpString;
            else throw Error("Unknown option!");
            if (lastOption!="-q") waitForValue=true;
            else args["-q"]="1";
        }
    }

    //checking if any mandatory argument is missing
    for(auto i:args)
        if (i.second=="\0" && i.first!="-q") throw Error("Missing input, output or config file!");
}

string ArgumentsParser::getIFileName()const {
    return args.at("-i");
}

string ArgumentsParser::getOFileName()const {
    return args.at("-o");
}

bool ArgumentsParser::getQuietMode()const {
    return !(args.at("-q") == "\0");
}

string ArgumentsParser::getCfgFileName()const {
    return args.at("-c");
}













