#include <queue>
#include <stack>
#include <string>
#include <iostream>
#include "TokenType.h"
#include "ExpressionType.h"
#include "Exceptions.h"

using namespace std;


/*
  Default constructor
*/
ExpressionType::ExpressionType(){}


/*
  Pre: Calling object initialized.
  Post: Function returns the calling object's data member "expression".
*/
queue<TokenType> ExpressionType::GetExpression() const
{
  return expression;
}


/*
  Pre: Argument is initilized and contains only digits 0-9, '(', ')', 
       and the four arithmetic operators. 
       No white spaces or anything beyond what's mentioned above. Calling object's data member "expression" is empty.
  Post: Calling "ExpressionType" object has "expression" in infix format.
*/
void ExpressionType::StringToInfix(string str)
{
  int i=0;
  while(i<str.length())
  {
    if(isdigit(str[i]))
    {
      string digits;
      
      do{
      digits.push_back(str[i]);
      i++;
      }while(isdigit(str[i]));
      
      try
      {
        long number = stol(digits);  
      }
      catch (exception& e)
      {
        cout << "Error: " << e.what() << " throws an exception, which is probably an instance of std::out_of_range, so input a number with smaller absolute value instead. \n";
        /*
         stol() can throw two exceptions, std::out_of_range and std::invalid_argument.
         Both are derived from the std::exception
        */
        exit (6);
      }
      
      TokenType token(NUMBER, stol(digits));
      expression.push(token);
    }
    else if(str[i] == '(')
    {
      TokenType token(O_PARENTHESIS, '(');
      expression.push(token);
      i++;
    }
    else if(str[i] == ')')
    {
      TokenType token(C_PARENTHESIS, ')');
      expression.push(token);
      i++;
    }
    else if (str[i] == '-' && isdigit(str[i+1]) && (i==0 || !isdigit(str[i-1]))) //interprets '-' as unary operator
    {
      string negative;
      
      do{
      negative.push_back(str[i]);
      i++;
      }while(isdigit(str[i]));
      
      try
      {
        long number = stol(negative);  
      }
      catch (exception& e)
      {
        cout << "Error: " << e.what() << " throws an exception, which is probably a instance of std::out_of_range, so input a number with smaller absolute value instead. \n";
      }
      
      TokenType token(NUMBER, stol(negative));
      expression.push(token);
    }
    else if (str[i] == '+' && isdigit(str[i+1]) && (i==0 || !isdigit(str[i-1]))) //interprets '+' as unary operator
    {
      string positive;
      
      do{
      positive.push_back(str[i]);
      i++;
      }while(isdigit(str[i]));
      
      try
      {
        long number = stol(positive);  
      }
      catch (exception& e)
      {
        cout << "Error: " << e.what() << " throws an exception, which is probably a instance of std::out_of_range, so input a number with smaller absolute value instead. \n";
      }
      
      TokenType token(NUMBER, stol(positive));
      expression.push(token);
    }
    else
    {
      TokenType token(OPERATOR, str[i]);
      expression.push(token);
      i++;
    }
  }
}


/*
Pre: Argument has data member "expression" in infix format and contains only numbers, parentheses
     and the four arithmatic operators. Calling object's data member "expression" is empty.
Post: Calling "ExpressionType" object contains "expression" in postfix format, which means it only
      has numbers and operators, and is not empty.
*/
void ExpressionType::InfixToPostfix(const ExpressionType& infix)
{
  cout << "InfixToPostfix() called \n";
  queue<TokenType> tokens = infix.GetExpression();
  stack<TokenType> tokenStack;
  
  while(!tokens.empty())
  {
    TokenType nextToken = tokens.front();
    switch (nextToken.GetType())
    {
      case NUMBER:
      {
        expression.push(nextToken);
        tokens.pop();
        cout << "case NUMBER \n";
      }
      break;
      case O_PARENTHESIS:
      {
        cout << "case O_PARENTHESIS \n";
        tokenStack.push(nextToken);
        tokens.pop();
      }
      break;
      case OPERATOR:
      {
        cout << "case OPERATOR \n";
        bool moreToLoop = true;
        char front = nextToken.GetCharacter();
        char top;
        while(moreToLoop)
        {
          if(!tokenStack.empty())
            top = tokenStack.top().GetCharacter();
              
          if(tokenStack.empty())
          {
            tokenStack.push(nextToken);
            tokens.pop();
            moreToLoop = false;
          }
          else if (top == '(')
          {  
            tokenStack.push(nextToken);
            tokens.pop();
            moreToLoop = false;
          }
          else if((front == '*' || front == '/') && (top == '-' || top == '+'))
          {
            tokenStack.push(nextToken);
            tokens.pop();
            moreToLoop = false;
          }
          else
          {
            expression.push(tokenStack.top());
            tokenStack.pop();
          }
        }  
      } 
      break;
      case C_PARENTHESIS:
      {
        cout << "case C_PARENTHESIS \n";
        try 
        {
          CheckForOP(tokenStack);
        } 
        catch(MissingOpeningP& mop) 
        {
          cout << "Error: " << mop.GetErrorMessage();
          exit(1);         
        }
        tokens.pop();
      }
      break;
    }
  }
  
  try
  {
    this->OutputRemaining(tokenStack);
  }
  catch(DanglingOpeningP& dop)
  {
    cout << "Error: " << dop.GetErrorMessage();
    exit(2);
  }
  
  try
  {
    this->CheckExpression();
  }
  catch(VacuousExpression& ve)
  {
    cout << "Error: " << ve.GetErrorMessage();
    exit (3);
  }
}


/*
  Pre: Calling "ExpressionType" object contains "expression" in postix format, and is not empty.
  Post: Function returns the result of that expression, and the result is of double type.
*/
double ExpressionType::EvaluatePostfix() const
{
  cout << "EvaluatePostfix() const called \n";
  queue <TokenType> tokens = expression;
  stack <double> doubleStack;
  
  while (!tokens.empty())
  {
    TokenType front = tokens.front();
    if(front.GetType() == NUMBER)
    {
      cout << "NUMBER \n";
      double doubleNumber = static_cast<double> (front.GetNumber());
      doubleStack.push(doubleNumber);
      tokens.pop();
    }
    else
    {
      cout << "OPERATOR \n";
      try
      {
        this->BinaryOperation(doubleStack, front);
      }
      catch(DivisionByZero& dbz)
      {
        cout << "Error: " << dbz.GetErrorMessage();
        exit(4);   
      }
      catch(DanglingOperator& DO)
      {
        cout << "Error: " << DO.GetErrorMessage();
        exit(5);   
      }
      tokens.pop();
    }
  }
  
  try
  {
    this->CheckStack(doubleStack);
  }
  catch(MissingOperator& mo)
  {
    cout << "Error: " << mo.GetErrorMessage();
    exit(6);
  }
  
  return doubleStack.top();
}


/*
  Pre: Calling object is inialized, and the arugment is a "stack<TokenType>" object.
  Post: Function outputs everything on "tokenStack" to the calling object's data member "expression"
        until it finds an opening parenthesis, or that the stack is empty.
        Then it throws "MissingOpingP", if no opening parenthesis is found.
*/
void ExpressionType::CheckForOP(stack <TokenType>& tokenStack)
{
  bool foundOP = false; 
  
  while(!tokenStack.empty())
  {
    TokenType top = tokenStack.top();
    if (top.GetType() == O_PARENTHESIS)
    {
      foundOP = true;
      tokenStack.pop();
      break;
    }
    else
    {
      expression.push(top);
      tokenStack.pop();
    }
  }
  
  if(foundOP == false)
    throw MissingOpeningP();
}


/*
  Pre: Calling object is inialized, and the arugment is a "stack<TokenType>" object.
  Post: Function outputs everything on "tokenStack" to the calling object's data member "expression",
        until it finds an opening parenthesis, or that the stack is empty.
        Then it throws "DanglingOpeningP", if an opening parenthesis is found.
*/
void ExpressionType::OutputRemaining(stack <TokenType>& tokenStack)
{
  bool foundOP = false;
  
  while (!tokenStack.empty())
  {
    TokenType top = tokenStack.top();
    if (top.GetType() == O_PARENTHESIS)
    {
      foundOP = true;
      tokenStack.pop();
      break;
    }
    else
    {
      expression.push(top);
      tokenStack.pop();
    }
  }
  
  if(foundOP == true)
    throw DanglingOpeningP();
}


/*
  Pre: "doubleStack" is initialized.
  Post: Function throws MissingOperator(), if "doubleStack" has more than 1 element.
*/
void ExpressionType::CheckStack(stack <double> doubleStack) const
{
  if(doubleStack.size()>1)
    throw MissingOperator();
}


/*
  Pre: Calling object initialized.
  Post: If data member "expression" is empty, the function throws an instance of class "VacuousExpression".
*/
void ExpressionType::CheckExpression() const
{
  if(expression.empty())
    throw VacuousExpression();
}


/*
  Pre: "doubleStack" and "token" are initialized. "token" should only be an operator.
  Post: If "doubleStack" does not have at least two elements, the function throws "DanglingOperator".
        If the top of "doubleStack" has value 0 and the "token" has the division operator, the function
        throws "DivisionByZero".
        Otherwise, the function pops the top two elements of "doubleStack" and pushes the result of indicated
        binary operaton into "doubleStack".
*/
void ExpressionType::BinaryOperation(stack <double>& doubleStack, TokenType token) const
{
  double operand2;
  double operand1;
  char binaryOperator = token.GetCharacter();
  
  if (doubleStack.empty())
    throw DanglingOperator();
  else
  {
    operand2 = doubleStack.top();
    doubleStack.pop();
    if (doubleStack.empty())
      throw DanglingOperator();
    else
      {
        operand1 = doubleStack.top();
        doubleStack.pop();
        cout << "operand1: "<< operand1;
        cout << " operand2: " << operand2 << endl;
        switch(binaryOperator)
        {
          case '*':
          {
            cout << "*\n";
            doubleStack.push(operand1 * operand2);
          }
          break;
          case '/':
          {
            if(operand2 == 0)
              throw DivisionByZero();
            else
              cout << "/\n";
              doubleStack.push(operand1 / operand2);
          }
          break;
          case '+':
          {
            cout << "+\n";
            doubleStack.push(operand1 + operand2);
          }
          break;
          case '-':
          {
            cout << "-\n";
            doubleStack.push(operand1 - operand2);
          }
          break;
        } 
      } 
  }
}


/*
  Pre: Calling object is initialized.
  Post: Prints out each of the "TokenType" element in the data member "expression", 
  with one whitespace as separator.
*/
void ExpressionType::PrintExpression() const
{
  queue<TokenType> tokens = expression;
  while (!tokens.empty())
  {
    tokens.front().PrintToken();
    cout << " ";
    tokens.pop();
  }
}