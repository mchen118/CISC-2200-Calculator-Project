#ifndef EXPRESSIONTYPE_H
#define EXPRESSIONTYPE_H

#include <queue>
#include "TokenType.h"
#include "Exceptions.h"

using std::queue;
using std::string;
using std::stack;

class ExpressionType
{
  public:
    ExpressionType();
    
    queue<TokenType> GetExpression() const;
    
    void StringToInfix(string str);
    void InfixToPostfix(const ExpressionType& infix);
    double EvaluatePostfix() const;

    void PrintExpression() const;
    
  private:
    void CheckForOP(stack <TokenType>& tokenStack);
    void OutputRemaining(stack <TokenType>& tokenStack);
    void CheckExpression() const;
    void BinaryOperation(stack <double>& doubleStack, TokenType token) const;
    void CheckStack(stack <double> doubleStack) const;
    
    queue<TokenType> expression;
};


#endif