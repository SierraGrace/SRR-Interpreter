#include "Token.h"

Token::Token(TokenType type, std::string value) : type(type), value(value) {
    //PrintToken();
}

void Token::PrintToken()
{
    if (this->type == END) { std::cout << "End token\n"; }

    std::cout << "Token type: " << this->type << std::endl
         << "Token value: " << this->value << std::endl << std::endl;
}