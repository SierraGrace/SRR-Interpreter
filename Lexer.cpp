#include "Lexer.h"

Token Lexer::GetNextToken () {

    if (position >= input.size()) { position++; return Token(END, ""); }

    char current = input[position];

    if (current == '\n') {
        position++;
        return Token(ENDLINE, "\\n");
    }

    while (position < input.size() && (input[position] == ' ' || input[position] == '\t')) {
        position++;
        current = input[position];
    }

    if (isalpha(current)) {
        return Token(STRING, GetStringToken(this->input, position));
    }
    if (isdigit(current)) {
        return Token(NUMBER, GetNumberToken(this->input, position));
    }

    switch (current) {
        case '+':
            position++;
            return Token(PLUS, "+");
        case '-':
            position++;
            return Token(MINUS, "-");
        case '=':
            position++;
            return Token(ASSIGN, "=");
        case ';':
            std::cout << "ENDLINE TOKEN\n";
            position++;
            return Token(SEMICOLON, ";");
        default:
            position++;
            return Token(UNDEFINED, "");
    }
}

std::string Lexer::GetStringToken(std::string &input, int index) {
    std::string tokenValue = "";

    for (int i = index; i < input.size(); i++) {
        if(isalpha(input[i])) { tokenValue.push_back(input[i]); }

        if(i + 1 >= input.size()) { break; }
        if (!isalpha(input[i + 1])) { break; }
    }

    position += tokenValue.size();
    return tokenValue;
}

std::string Lexer::GetNumberToken(std::string &input, int index) {
    std::string tokenValue = "";

    for (int i = index; i < input.size(); i++) {
        if(isdigit(input[i])) { tokenValue.push_back(input[i]); }

        if(i + 1 >= input.size()) { break; }
        if (!isdigit(input[i + 1])) { break; }
    }

    position += tokenValue.size();
    return tokenValue;
}

void Lexer::Tokenize() {
    while (position <= input.size()) {
        GetNextToken();
    }
}