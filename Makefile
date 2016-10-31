EXECUTABLE=liferili
CXX=g++
CXXFLAGS=-std=c++11 -Wall -pedantic -Wno-long-long -O0 -ggdb
OUTPUTHTML=output.html

all: compile

run: compile
	./$(EXECUTABLE) -i examples/input.html -o $(OUTPUTHTML) -c examples/cfg

compile: $(EXECUTABLE)

doc: src/main.cpp src/ArgumentsParser.h src/ErrorTagNode.h src/HtmlErrorList.h src/TextNode.h src/CommentNode.h src/Format.h src/PairHtmlElement.h src/TopNode.h src/ConfigError.h src/HtmlDOM.h src/PairTagNode.h src/TreeNode.h src/DoctypeNode.h src/HtmlElementCollection.h src/SingleHtmlElement.h src/ElementsFileError.h src/HtmlElement.h src/SingleTagNode.h src/Error.h src/HtmlError.h src/StringHelper.h
	doxygen Doxyfile

$(EXECUTABLE): objs/main.o objs/ArgumentsParser.o objs/CommentNode.o objs/DoctypeNode.o objs/ErrorTagNode.o objs/Format.o objs/HtmlDOM.o objs/HtmlElementCollection.o objs/HtmlElement.o objs/HtmlError.o objs/HtmlErrorList.o objs/PairHtmlElement.o objs/PairTagNode.o objs/SingleHtmlElement.o objs/SingleTagNode.o objs/StringHelper.o objs/TextNode.o objs/TopNode.o
	$(CXX) $(CXXFLAGS) $^ -o $@



objs/ArgumentsParser.o: src/ArgumentsParser.cpp src/ArgumentsParser.h src/ConfigError.h src/Error.h | objs
	$(CXX) $(CXXFLAGS) -c $< -o $@

objs/CommentNode.o: src/CommentNode.cpp src/CommentNode.h src/Format.h src/ArgumentsParser.h \
 src/TreeNode.h src/HtmlErrorList.h src/HtmlError.h src/HtmlElementCollection.h \
 src/HtmlElement.h src/Error.h src/StringHelper.h | objs
	$(CXX) $(CXXFLAGS) -c $< -o $@

objs/DoctypeNode.o: src/DoctypeNode.cpp src/DoctypeNode.h src/TreeNode.h src/Format.h \
 src/ArgumentsParser.h src/HtmlErrorList.h src/HtmlError.h src/HtmlElementCollection.h \
 src/HtmlElement.h src/Error.h src/StringHelper.h | objs
	$(CXX) $(CXXFLAGS) -c $< -o $@

objs/ErrorTagNode.o: src/ErrorTagNode.cpp src/Format.h src/ArgumentsParser.h \
 src/ErrorTagNode.h src/TreeNode.h src/HtmlErrorList.h src/HtmlError.h \
 src/HtmlElementCollection.h src/HtmlElement.h src/Error.h src/StringHelper.h | objs
	$(CXX) $(CXXFLAGS) -c $< -o $@

objs/Format.o: src/Format.cpp src/Format.h src/ArgumentsParser.h src/ConfigError.h | objs
	$(CXX) $(CXXFLAGS) -c $< -o $@

objs/HtmlDOM.o: src/HtmlDOM.cpp src/HtmlDOM.h src/Format.h src/ArgumentsParser.h src/TreeNode.h \
 src/HtmlErrorList.h src/HtmlError.h src/HtmlElementCollection.h src/HtmlElement.h \
 src/TopNode.h src/Error.h src/PairTagNode.h src/DoctypeNode.h src/SingleTagNode.h \
 src/CommentNode.h src/TextNode.h src/ErrorTagNode.h src/StringHelper.h | objs
	$(CXX) $(CXXFLAGS) -c $< -o $@

objs/HtmlElementCollection.o: src/HtmlElementCollection.cpp \
 src/HtmlElementCollection.h src/HtmlElement.h src/Format.h src/ArgumentsParser.h \
 src/ElementsFileError.h src/PairHtmlElement.h src/SingleHtmlElement.h | objs
	$(CXX) $(CXXFLAGS) -c $< -o $@

objs/HtmlElement.o: src/HtmlElement.cpp src/HtmlElement.h | objs
	$(CXX) $(CXXFLAGS) -c $< -o $@

objs/HtmlError.o: src/HtmlError.cpp src/HtmlError.h | objs
	$(CXX) $(CXXFLAGS) -c $< -o $@

objs/HtmlErrorList.o: src/HtmlErrorList.cpp src/HtmlErrorList.h src/HtmlError.h | objs
	$(CXX) $(CXXFLAGS) -c $< -o $@

objs/main.o: src/main.cpp src/HtmlDOM.h src/Format.h src/ArgumentsParser.h src/TreeNode.h \
 src/HtmlErrorList.h src/HtmlError.h src/HtmlElementCollection.h src/HtmlElement.h \
 src/TopNode.h src/Error.h src/PairTagNode.h | objs
	$(CXX) $(CXXFLAGS) -c $< -o $@

objs/PairHtmlElement.o: src/PairHtmlElement.cpp src/PairHtmlElement.h src/HtmlElement.h | objs
	$(CXX) $(CXXFLAGS) -c $< -o $@

objs/PairTagNode.o: src/PairTagNode.cpp src/PairTagNode.h src/Format.h src/ArgumentsParser.h \
 src/TreeNode.h src/HtmlErrorList.h src/HtmlError.h src/HtmlElementCollection.h \
 src/HtmlElement.h src/StringHelper.h src/Error.h | objs
	$(CXX) $(CXXFLAGS) -c $< -o $@

objs/SingleHtmlElement.o: src/SingleHtmlElement.cpp src/SingleHtmlElement.h \
 src/HtmlElement.h | objs
	$(CXX) $(CXXFLAGS) -c $< -o $@

objs/SingleTagNode.o: src/SingleTagNode.cpp src/SingleTagNode.h src/Format.h \
 src/ArgumentsParser.h src/TreeNode.h src/HtmlErrorList.h src/HtmlError.h \
 src/HtmlElementCollection.h src/HtmlElement.h src/Error.h src/StringHelper.h | objs
	$(CXX) $(CXXFLAGS) -c $< -o $@

objs/StringHelper.o: src/StringHelper.cpp src/StringHelper.h src/Error.h src/Format.h \
 src/ArgumentsParser.h | objs
	$(CXX) $(CXXFLAGS) -c $< -o $@

objs/TextNode.o: src/TextNode.cpp src/TextNode.h src/Format.h src/ArgumentsParser.h src/TreeNode.h \
 src/HtmlErrorList.h src/HtmlError.h src/HtmlElementCollection.h src/HtmlElement.h \
 src/Error.h src/StringHelper.h | objs
	$(CXX) $(CXXFLAGS) -c $< -o $@

objs/TopNode.o: src/TopNode.cpp src/TopNode.h src/TreeNode.h src/Format.h src/ArgumentsParser.h \
 src/HtmlErrorList.h src/HtmlError.h src/HtmlElementCollection.h src/HtmlElement.h \
 src/Error.h src/PairTagNode.h | objs
	$(CXX) $(CXXFLAGS) -c $< -o $@

objs/:
	mkdir objs

clean:
	rm -rf $(EXECUTABLE) $(OUTPUTHTML) objs/ doc/ 2>/dev/null
