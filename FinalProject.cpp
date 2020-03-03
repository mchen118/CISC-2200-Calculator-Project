#include <iostream>
#include <string>
#include "ExpressionType.h"

using namespace std;

/*
  Pre: "raw" is initialized.
  Post: Function returns string that only contains '+', '-', '*','/','(', ')', and digits.
        The returned string has no white spaces or any other characters that are not shown above.
*/
string Filter(string raw)
{
	string result;
	char temp;
	for (int i = 0; i < raw.length(); i++)
	{
		temp = raw[i];
		if (isdigit(temp))
			result.push_back(temp);
		else if (temp == '+' || temp == '-' || temp == '*' || temp == '/')
			result.push_back(temp);
		else if (temp == '(')
			result.push_back('(');
		else if (temp == ')')
			result.push_back(')');
  } 
	return result;
}

int main()
{
	double result;
  string raw;
  string filtered;
  ExpressionType infix;
  ExpressionType postfix;
  
	cout << "Enter an expression consists of integers, arithmatic operator '+', '-', '/', and '*', and parentheses: ";
	getline(cin, raw);
 
	filtered = Filter(raw);

  infix.StringToInfix(filtered);
  cout << "Infix Expression: ";
  infix.PrintExpression();
  cout << endl;
  
  postfix.InfixToPostfix(infix);
  cout << "Postfix Expression: ";
  postfix.PrintExpression();
  cout << endl;

  result = postfix.EvaluatePostfix();
  cout << "result: " << result << endl;
  

  return 0;
}
