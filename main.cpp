#include <iostream>
#include <string>
#include <vector>

using std::cout, std::endl, std::string;

enum TokenType {
    STRING,
    NUMBER,

    ASSIGN,
    PLUS,
    MINUS,

    SEMICOLON,

    UNDEFINED,
    END
};

class Token {
public:
    TokenType type;
    string value;

    Token() {}

    Token(TokenType type, string value) : type(type), value(value) {
        //PrintToken();
    }

    void PrintToken() {
        if (this->type == END) { cout << "End token\n"; }

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

    Token GetNextToken () {

        if (position >= input.size()) { position++; return Token(END, ""); }

        char current = input[position];

        while (position < input.size() && isspace(input[position])) {
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
                position++;
                return Token(SEMICOLON, ";");
            default:
                position++;
                return Token(UNDEFINED, "");
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
            GetNextToken();
        }
    }
};

class Expression {
public:
    virtual ~Expression() = default;
    virtual int Evaluate() = 0;
};

class NumberExpression : public Expression {
public:
    int value;

    NumberExpression(int value) : value(value) {}

    int Evaluate() override { return value; }
};

class BinaryExpression : public Expression {
public:
    Token _operator;

    Expression *LeftNode;
    Expression *RightNode;

    BinaryExpression(Expression *LeftNode, Token _operator, Expression *RightNode)
        : LeftNode(LeftNode), _operator(_operator), RightNode(RightNode) {}

    int Evaluate() override {
        if (_operator.type == PLUS) {
            return LeftNode->Evaluate() + RightNode->Evaluate();
        }
        if (_operator.type == MINUS) {
            return LeftNode->Evaluate() - RightNode->Evaluate();
        }
    }
};

class Parser {
public:
    Lexer lexer;

    Parser(Lexer lexer) : lexer(lexer) {}

    std::vector<Token> tokens;

    Token current;

    void GetTokenList() {
        while(lexer.position < lexer.size) {
            tokens.push_back(lexer.GetNextToken());
        }
    }

    void AnalyzeTokenList() {

        NumberExpression *leftNumber = nullptr;
        NumberExpression *rightNumber = nullptr;

        Token _operator;

        for (int i = 0; i < tokens.size(); i++) {
            current = tokens[i];

            if (current.type == NUMBER && leftNumber == nullptr) {
                leftNumber = new NumberExpression(stoi(current.value));
            }

            if (current.type == PLUS || current.type == MINUS) {
                _operator = current;
            }

            if (i != 0 && current.type == NUMBER && leftNumber != nullptr && rightNumber == nullptr) {
                rightNumber = new NumberExpression(stoi(current.value));
            }
        }

        cout << "Left: " << leftNumber->Evaluate() << endl;
        cout << "Right: " << rightNumber->Evaluate() << endl;

        BinaryExpression *newExpr = new BinaryExpression(leftNumber, _operator, rightNumber);
        cout << "Result is: " << newExpr->Evaluate();
    }
};

int main() {
    string code = "90 + 25";

    Lexer lexer(code);
    Parser parser(lexer);

    parser.GetTokenList();
    parser.AnalyzeTokenList();

    return 0;
}
