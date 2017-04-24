# HTML-validator-and-beautifier
Simple HTML validator and beautifier with some bugs and undone things. You can generate documentation via doxygen. (Doxyfile config is included)
 <pre>
 Simple html code formatter and validator.
 Configuration file and file with html elements are required. (both files formats below)

 Mandatory arguments:
      -i
         specifies input file

      -o
         specifies output file

      -c
         specifies configuration file

 Optional arguments:
      -q
         quiet mode
         Causes most warning and diagnostic messages to be
         suppressed.
         Note: if enabled html document validation will not happen

 ---------------------------------------------------------------------------------------

 Configuration file and file with html elements support C++ style
 comments (Comment line begins with two common slashes).

 Configuration file format:
 variable=value (ex. indent=4)

 Mandatory variables:
      indent (unsigned integer value)
             preferred indent in output file

      length (unsigned integer value)
             preferred row length in output file

      elements (string value)
             name of file that contains html elements

 ---------------------------------------------------------------------------------------

 Html elements file must contains described elements.

 1.name of the element;tag format{inline | block};closed tag{required | forbidden}
 2.allowed attribures
 3.allowed children (Only if closed tag is required! Else leave it empty.)

 Example of the description:
 //-----------------------------------//
 body;block;required
 lang onload title id xml:lang dir
 h3 pre h6 ol div ul h2 h5 blockquote h1
 //-----------------------------------//*
 ---------------------------------------------------------------------------------------

 Errors will be printed to std:out

 </pre>
