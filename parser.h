#ifndef PARSER_H
#define PARSER_H
#include <string>
#include<iostream>
using std::string;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "number.h"
#include "node.h"

#include "utParser.h"

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(){}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        return structure();
      }
      else
        return atom;
    }
    else if(token == '['){
      return list();
    }

    return nullptr;
  }



  Term * structure() {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms();
    if(_currentToken == ')')
    {
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      return new Struct(structName, args);
    } else {
      throw string("unexpected token");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      return new List(args);
    } else {
      throw string("unexpected token");
    }
  }

  vector<Term *> & getTerms() {
    return _terms; //所有建立好的Terms
  }

  Node* matchings(){

    createTerms2();
    Node *l = new Node(TERM, _terms[_terms.size()-1], nullptr,nullptr);
    int token = _currentToken;
    //std::cout<<(char)token<<std::endl;
    createTerms2();
    Node *r = new Node(TERM, _terms[_terms.size()-1], nullptr,nullptr);

    Node *node;
    if(token=='='){
      node = new Node(EQUALITY, nullptr, l, r);
    }
    
    token=_currentToken;
    if(token==','){
      _op=token;
      node=new Node(COMMA,nullptr,node,matchings());
    }
    else if(token==';'){
      _op=token;
      node=new Node(SEMICOLON,nullptr,node,matchings());
    }
    else if(token=='.'){
    }
    express=node;
    return node;
    //Node *node = new Node(token, nullptr, l, r);

    
  }
  Node* expressionTree(){
    return express;
  }
private:
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      //new
      if(_op==','){
        for(int i=_terms.size()-3;i<_terms.size();i++)
          if(term->symbol()==_terms[i]->symbol()){
            term=_terms[i];
            break;
          }
      }
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',') {
        _terms.push_back(createTerm());
      }
    }
  }

  void createTerms2() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      //std::cout<<(char)_scanner.currentChar()<<std::endl;
      if(_op==',')
        for(int i=0;i<_terms.size();i++)
          if(_terms[i]->symbol()==term->symbol()){
            _terms.push_back(_terms[i]);
            _currentToken = _scanner.nextToken();
            return;
          }
          else if(_terms[i]->type()=="Struct"){
            Struct *s=dynamic_cast<Struct*>(_terms[i]);
            for(int j=0;j<s->arity();j++){
              if(s->args(j)->symbol()==term->symbol()){
                _terms.push_back(s->args(j));
                _currentToken = _scanner.nextToken();
                return;
              }
            }
          }
        
      _terms.push_back(term);
      if(_scanner.currentChar()=='.'){
        _currentToken=_scanner.currentChar();
      }
      else
        _currentToken = _scanner.nextToken();
    }
  }

  vector<Term *> _terms;
  Scanner _scanner;
  int _currentToken;
  int _op;
  Node *express;
};
#endif
