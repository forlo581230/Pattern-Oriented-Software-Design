#ifndef LIST_H
#define LIST_H

#include "term.h"
#include <vector>
#include <iostream>
using std::vector;

class List : public Term {
public:
  string symbol() const{
    if(_elements.empty())
      return "[]";
    else{
      string ret ="[";
      for(int i = 0; i < _elements.size() - 1 ; i++){
        ret += _elements[i]-> value() + ", ";
      }
      ret += _elements[_elements.size()-1]-> value() + "]";
      return  ret;
    }
  }

  bool match(Term & term){
    List * ps = dynamic_cast<List *>(&term);

    if(term.type()==type()){//list=list
      if(ps->_elements.size()!= _elements.size())
        return false;


      for(int i = 0; i < _elements.size() - 1 ; i++){
        if(!_elements[i]->match(*(ps->_elements[i])))
          return false;
      }

      return true;
    }
    else if(term.type()=="Variable"){
      return term.match(*this);
    }
    else{
      return false;
    }
  }
  bool isExist(Term &t){
    for(int i = 0; i < _elements.size() - 1 ; i++){
      if(_elements[i]-> symbol()==t.symbol())
        return true;
    }
    return false;

  }
  string type()const{
    return "List";
  }

public:
  List (): _elements(0){}
  List (vector<Term *> const & elements):_elements(elements){}
  Term * head() const{
    if(_elements.empty())throw "AA";
      return *_elements.begin();

  }
  List * tail() const{
      if(_elements.empty())throw "AA";
      vector<Term *> args;
      for(int i = 1; i < _elements.size() ; i++){
        args.push_back(_elements[i]);
      }
      List *t=new List(args);
      return t;

  }

private:
  vector<Term *> _elements;

};

#endif
