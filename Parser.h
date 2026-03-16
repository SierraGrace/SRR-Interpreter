#ifndef PARSER_H
#define PARSER_H

#include <vector>

#include "Token.h"
#include "Lexer.h"
#include "AST-Nodes.h"

class Parser {
public:
    Lexer lexer;

    Parser(Lexer lexer) : lexer(lexer) {}

    std::vector<Token> tokens;

    Token current;
    void GetTokenList();
    void AnalyzeTokenList();
};

#endif
