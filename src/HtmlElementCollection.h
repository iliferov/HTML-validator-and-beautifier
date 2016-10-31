//
// Created by Liferov Ilia (liferili) on 5/25/16.
//

#ifndef SEMESTRALNI_PRACE_HTMLELEMENTS_H
#define SEMESTRALNI_PRACE_HTMLELEMENTS_H

#include "HtmlElement.h"
#include "Format.h"
#include <string>
#include <map>

using namespace std;

/**
 * Represents collection of html elements with necessary information (allowed children and attributes; format of html element: block/inline, single/paired)
 */
class HtmlElementCollection {
public:
    /**
     * Dictionary with lowercase name of html element as a key and HtmlElement as a value.
     */
    map<string,shared_ptr<HtmlElement>> elementCollection;
    /**
     * Performs parsing html elements file and fills in dictionary with appropriate html elements
     * @param format printing format (contains html elements file name)
     */
    HtmlElementCollection(Format& format);
};


#endif //SEMESTRALNI_PRACE_HTMLELEMENTS_H
