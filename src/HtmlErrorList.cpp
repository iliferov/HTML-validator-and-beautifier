//
// Created by Liferov Ilia (liferili) on 6/5/16.
//
#include "HtmlErrorList.h"

using namespace std;

void HtmlErrorList::pushError(const HtmlError &error) {
    auto it=lower_bound(errors.begin(), errors.end(), error, [](const HtmlError &a, const HtmlError &b){return a.getLine()<b.getLine();});
    errors.insert(it,error);
}

void HtmlErrorList::printErrors()const {
    if (this->errors.empty()){
        cout << "Validating is done without errors!" << endl;
    }
    else{
        cout << "Errors: " << endl << endl;
        for(auto i : this->errors){
            i.print();
        }
    }
}
