#ifndef TOKENTYPE_H
#define TOKENTYPE_H

#include <iostream>

using std::string;
using std::cout;

enum TypeOfToken {OPERATOR, O_PARENTHESIS, C_PARENTHESIS, NUMBER, DEFAULT};

/* A "TokenType" object has three data members:
   a "char" type one called "character",
   a "long" type one called "number",
   and a enumeration type one called "type".
   
   Since number uses long type, it can store at least plus or minus 2,147,483,647
   On storm, a long number has upper bound 9,223,372,036,854,775,807 and lower bound -9,223,372,036,854,775,808
   Any number whith no more than 18 digits is safe.
*/
class TokenType
{
  public:
  
    TokenType()
    {
      type = DEFAULT;
    }
    
    
    TokenType(TypeOfToken type, char character)
    {
      this->type = type;
      this->character = character;
    }
    
    TokenType(TypeOfToken type, long number)
    {
      this->type = type;
      this->number = number;
    }
    

    TypeOfToken GetType()
    {
      return type;
    }
    
    
    char GetCharacter()
    {
      return character;
    }
    
        
    long GetNumber()
    {
      return number;
    }
    
    void PrintToken()
    {
      switch(type)
      {
        case OPERATOR: cout << character;
                       break;
        case NUMBER:   cout << number;
                       break; 
        
        case O_PARENTHESIS: cout << character;
                            break;
        case C_PARENTHESIS: cout << character; 
                            break;
        default: cout << "default";
      }
    }
    
  private:
    TypeOfToken type;
    char character;
    long number;
};
#endif