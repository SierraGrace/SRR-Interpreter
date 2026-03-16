#include "Parser.h"

void Parser::GetTokenList() {
    while(lexer.position < lexer.size) {
        tokens.push_back(lexer.GetNextToken());
    }
}

void Parser::AnalyzeTokenList() {

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

    std::cout << "Left: " << leftNumber->Evaluate() << std::endl;
    std::cout << "Right: " << rightNumber->Evaluate() << std::endl;

    BinaryExpression *newExpr = new BinaryExpression(leftNumber, _operator, rightNumber);
    std::cout << "Result is: " << newExpr->Evaluate();
}