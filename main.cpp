#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Lexer.h"
#include "Parser.h"

using std::cout, std::endl, std::string;

std::string ReadFile(std::string filename) {
    std::ifstream file(filename);

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

int main() {
    std::string sourceCode = ReadFile("..//main.srr");

    Lexer lexer(sourceCode);
    Parser parser(lexer);

    parser.GetTokenList();
    parser.AnalyzeTokenList();

    return 0;
}
