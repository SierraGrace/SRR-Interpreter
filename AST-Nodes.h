#ifndef AST_NODES_H
#define AST_NODES_H

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

#endif
