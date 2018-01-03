#ifndef EXP_H
#define EXP_H

#include "atom.h"
#include <iostream>
#include <vector>
using std::vector;

class Exp {
public:
  virtual bool evaluate() = 0;
  virtual string getEvaluateString() {return "";}
};


class MatchExp : public Exp {
public:
  MatchExp(Term* left, Term* right): _left(left), _right(right){

  }

  bool evaluate(){
    return _left->match(*_right);
  }
  string getEvaluateString(){
    
    
    if(evaluate()){
      if(_left->symbol()==_right->symbol())
        return "true";;
      if(_left->value()==_right->value())
        return _left->symbol() + " = " + _right->value() ;
      return "true";
    }
    else
      return "false";
  }
  
private:
  Term* _left;
  Term* _right;
};

class ConjExp : public Exp {//,
public:
  ConjExp(Exp *left, Exp *right) : _left(left), _right(right) {
    _data.clear();
    first=true;
  }

  bool evaluate() {
    return (_left->evaluate() && _right->evaluate());
  }

  string getEvaluateString(){
    if(!evaluate())return "false";

    if((_left->getEvaluateString().find(_right->getEvaluateString(),0)!=std::string::npos)){
      return _left->getEvaluateString();
    }
      
    else if(_left->getEvaluateString()=="true"){
      return _right->getEvaluateString();
    }
      
    else if (_right->getEvaluateString()=="true"){
      return _left->getEvaluateString();
    }

    return (_left->getEvaluateString() + ", "+  _right->getEvaluateString());
  }


private:
  Exp * _left;
  Exp * _right;
  bool first;
  vector<string>_data;
};

class DisjExp : public Exp {//;
public:
  DisjExp(Exp *left, Exp *right) : _left(left), _right(right) {

  }

  bool evaluate() {
    return (_left->evaluate() || _right->evaluate());
  }

  string getEvaluateString(){

    // if(_left->getEvaluateString()=="true"){
    //   return _right->getEvaluateString();
    // }
      
    // else if (_right->getEvaluateString()=="true"){
    //   return _left->getEvaluateString();
    // }
    if(!_right->evaluate())return _left->getEvaluateString();

    return (_left->getEvaluateString() + "; "+  _right->getEvaluateString());
  }

private:
  Exp * _left;
  Exp * _right;
};
#endif
