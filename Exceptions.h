#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stack>
#include <string>
#include "TokenType.h"

using std::stack;
using std::string;

class MissingOpeningP
{
  private:
    string errorMessage = "Missing Openning Parenthesis \n";
  public:
    string GetErrorMessage()
    {
      return errorMessage;
    }
}; // exit code: 1


class DanglingOpeningP
{
  private:
    string errorMessage = "Dangling Openning Parenthesis \n";
  public:
    string GetErrorMessage()
    {
      return errorMessage;
    }
}; // exit code: 2


class VacuousExpression
{
  private:
    string errorMessage = "Vacuous Expression \n";
  public:
    string GetErrorMessage()
    {
      return errorMessage;
    }
}; // exit code: 3


class DivisionByZero
{
  private:
    string errorMessage = "Division By Zero \n";
  public:
    string GetErrorMessage()
    {
      return errorMessage;
    }
}; // exit code: 4


class DanglingOperator
{
  private:
    string errorMessage = "Dangling Operator \n";
  public:
    string GetErrorMessage()
    {
      return errorMessage;
    }
};// exit code: 5


class MissingOperator
{
  private:
    string errorMessage = "Missing Operator \n";
  public:
    string GetErrorMessage()
    {
      return errorMessage;
    }
}; // exit code: 6

#endif