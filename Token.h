#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>

enum TokenType {
    STRING,
    NUMBER,

    ASSIGN,
    PLUS,
    MINUS,

    SEMICOLON,
    ENDLINE,

    UNDEFINED,
    END
};

class Token {
public:
    TokenType type;
    std::string value;

    Token() {}
    Token(TokenType type, std::string value);

    void PrintToken();
};

#endif
