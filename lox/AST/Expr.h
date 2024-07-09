#ifndef Expr_H
#define Expr_H

#include <memory>
#include <string>
#include <vector>

using namespace std;

class Expr {
  public:
    virtual ~Expr() = default;
};

class Binary : public Expr {
  public:
    Binary(shared_ptr<Expr> left, string operatorToken,
           shared_ptr<Expr> right) {
        this->left = left;
        this->operatorToken = operatorToken;
        this->right = right;
    }
    shared_ptr<Expr> left;
    string operatorToken;
    shared_ptr<Expr> right;
};

class Grouping : public Expr {
  public:
    Grouping(shared_ptr<Expr> expression) { this->expression = expression; }
    shared_ptr<Expr> expression;
};

class Literal : public Expr {
  public:
    Literal(string value) { this->value = value; }
    string value;
};

class Unary : public Expr {
  public:
    Unary(string operatorToken, shared_ptr<Expr> right) {
        this->operatorToken = operatorToken;
        this->right = right;
    }
    string operatorToken;
    shared_ptr<Expr> right;
};

#endif
