#ifndef LEXER_H
#define LEXER_H

#include <string>
#include "Token.h"

class Lexer {
public:
    std::string input;
    int size;

    int position = 0;

    Lexer(const std::string &input) : input(input) { this->size = input.size(); };

    Token GetNextToken();

    std::string GetStringToken(std::string &input, int index);
    std::string GetNumberToken(std::string &input, int index);

    void Tokenize();
};

#endif
