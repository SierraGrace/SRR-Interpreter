#include <iostream>
#include <string>

using std::cout, std::endl, std::string;

enum TokenType {
    STRING,
    NUMBER,

    ASSIGN,
    PLUS,
    MINUS,

    SEMICOLON,

    END
};

class Token {
public:
    TokenType type;
    string value;

    Token(TokenType type, string value) : type(type), value(value) {
        cout << "Token type: " << this->type << endl
             << "Token value: " << this->value << endl << endl;
    }
};

class Lexer {
public:
    string input;
    int size;

    int position = 0;

    Lexer(const string &input) : input(input) { this->size = input.size(); }

    Token GetNextToken (int index = 0) {

        if (index >= input.size()) { position++; return Token(END, ""); }

        char current = input[index];

        while (index < input.size() && isspace(input[index])) {
            position++;
            index++;

            current = input[index];
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
                position++;
                return Token(SEMICOLON, ";");
        }

        if (isalpha(current)) {
            return Token(STRING, GetStringToken(this->input, index));
        }
        if (isdigit(current)) {
            return Token(NUMBER, GetNumberToken(this->input, index));
        }
    }

    string GetStringToken(string &input, int index) {
        string tokenValue = "";

        for (int i = index; i < input.size(); i++) {
            if(isalpha(input[i])) { tokenValue.push_back(input[i]); }

            if(i + 1 >= input.size()) { break; }
            if (!isalpha(input[i + 1])) { break; }
        }

        position += tokenValue.size();
        return tokenValue;
    }

    string GetNumberToken(string &input, int index) {
        string tokenValue = "";

        for (int i = index; i < input.size(); i++) {
            if(isdigit(input[i])) { tokenValue.push_back(input[i]); }

            if(i + 1 >= input.size()) { break; }
            if (!isdigit(input[i + 1])) { break; }
        }

        position += tokenValue.size();
        return tokenValue;
    }

    void Tokenize() {
        while (position <= input.size()) {
            GetNextToken(position);
        }
    }
};

int main() {
    string code = "int a = 15 + 30;";

    Lexer lexer(code);
    lexer.Tokenize();

    return 0;
}