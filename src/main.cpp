#include <iostream>
#include "HtmlDOM.h"

using namespace std;

/**
 * @mainpage Html formatter and validator
 * <pre>
 * Simple html code formatter and validator.
 * Configuration file and file with html elements are required. (both files formats below)
 *
 * Mandatory arguments:
 *      -i
 *         specifies input file
 *
 *      -o
 *         specifies output file
 *
 *      -c
 *         specifies configuration file
 *
 * Optional arguments:
 *      -q
 *         quiet mode
 *         Causes most warning and diagnostic messages to be
 *         suppressed.
 *         Note: if enabled html document validation will not happen
 *
 * ---------------------------------------------------------------------------------------
 *
 * Configuration file and file with html elements support C++ style
 * comments (Comment line begins with two common slashes).
 *
 * Configuration file format:
 * variable=value (ex. indent=4)
 *
 * Mandatory variables:
 *      indent (unsigned integer value)
 *             preferred indent in output file
 *
 *      length (unsigned integer value)
 *             preferred row length in output file
 *
 *      elements (string value)
 *             name of file that contains html elements
 *
 * ---------------------------------------------------------------------------------------
 *
 * Html elements file must contains described elements.
 *
 * 1.name of the element;tag format{inline | block};closed tag{required | forbidden}
 * 2.allowed attribures
 * 3.allowed children (Only if closed tag is required! Else leave it empty.)
 *
 * Example of the description:
 * //-----------------------------------//
 * body;block;required
 * lang onload title id xml:lang dir
 * h3 pre h6 ol div ul h2 h5 blockquote h1
 * //-----------------------------------//
 *
 * ---------------------------------------------------------------------------------------
 *
 * Errors will be printed to std:out
 *
 * </pre>
 */

int main(int argc, char* argv[]) {
    try {
        //parsing application arguments
        ArgumentsParser argumentsParser;
        argumentsParser.setArgs(argc, argv);

        //creating print format class
        Format format(argumentsParser);

        //creating html elements dictionary
        HtmlElementCollection htmlElementCollection(format);


        HtmlDOM dom;
        HtmlErrorList errorList;

        //creating the document object model tree
        dom.createDOM(argumentsParser.getIFileName(), htmlElementCollection, errorList);
        //printing the html document according to printing format
        dom.printHtmlDocument(argumentsParser.getOFileName(), format, htmlElementCollection);
        if (!argumentsParser.getQuietMode()){
            //validating the html document if it is needed
            dom.validateDocument(htmlElementCollection, errorList);
            //printing document errors to std:out
            errorList.printErrors();
        };
    }
    catch (const exception& e){
        cout << e.what() << endl;
        return 0;
    }
    return 0;
}
