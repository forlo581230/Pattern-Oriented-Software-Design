#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;

#include "atom.h"
#include "number.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner){}

  Term* createTerm(){
    int token = _scanner.nextToken();
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM||token ==ATOMSC){
      
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);

      _currentToken.push_back(_scanner.nextToken());
    
      if(_currentToken.back() == '(') {
        vector<Term*> terms = getArgs();
        if(_currentToken.back() == ')'){
          _currentToken.pop_back();
          if(_currentToken.back()=='('){
            _currentToken.pop_back();
            return new Struct(*atom, terms);
          }
          else
            throw string("unexpected token");
        }
      }
      else{
        return atom;
      }
    }
    else if(token==','){//繼續抓
      return createTerm();
    }
    else if(token==')'){
      _currentToken.push_back(token);
    }
    else if(token=='['){
        _currentToken.push_back(token);
        vector<Term*> terms = getArgs();
        
        if(_currentToken.back() == ']'){
           _currentToken.pop_back();
           
          if(_currentToken.back()=='['){
            _currentToken.pop_back();
            return new List(terms);
          }
          else
            throw string("unexpected token");
        }
    }
    else if(token==']'){
      _currentToken.push_back(token);
    }
  return NULL;
}

vector<Term*> getArgs()
{
  Term* term = createTerm();
  vector<Term*> args;
  if(term)
    args.push_back(term);

  if(!_currentToken.empty()){//被空list 吃掉
    if(_currentToken.back()==']'){
      return args;
    }
    else if(_currentToken.back()==')'){
      return args;
    }
  }

  int token;
  while((token=_scanner.nextToken()) == ',') {
    args.push_back(createTerm());

    if(!_currentToken.empty()){
      if(_currentToken.back()==','){
        args.push_back(createTerm());
      }
    }
  }
  //收尾
  if(token ==')'){
    _currentToken.push_back(')');
  }
  else if(token ==']'){
    _currentToken.push_back(']');
  }


  return args;
}



private:
  vector<int> _currentToken;
  Scanner _scanner;
};
#endif
