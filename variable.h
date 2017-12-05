#ifndef VARIABLE_H
#define VARIABLE_H

#include <vector>
#include "term.h"
#include "list.h"
class Variable : public Term{
public:
  Variable(string s):_symbol(s), _value(s),_tvalue(nullptr){
    _tvalue= 0;
    assignable=true;
  }
  string symbol() const{return _symbol;}
  string value() const{
    if(_tvalue==nullptr)
      return _value;
    else{
      return _tvalue->value();
    }
  }

  void assignValue(string val, std::vector<string>*symbols){
    _value = val;
    assignable=false;
    for(int i = 0; i<v.size(); i++){
      if(!find(v[i]->symbol(),symbols)){
        symbols->push_back(v[i]->symbol());
        dynamic_cast<Variable*>(v[i])->assignValue(val, symbols);
      }
    }
  }

  bool find(string data, std::vector<string>*symbols){
    
    for(std::vector<string>::iterator it = symbols->begin(); it!=symbols->end(); ++it){
      if(*it==data)
        return true;
    }
    return false;
  }

  bool match(Term &term ){
    if(assignable){
      if(term.type()=="Variable" && this!=&term){

        if(_tvalue!=nullptr)
          term.match(*this);
        else{
          _tvalue=&term;
          assignable=false;
        }

      }
      else if( this==&term)
        return true;
      else{
        _tvalue = &term;
        assignable=false;
      }
      return true;
    }
    else if(!assignable && _tvalue!=nullptr){
      return (_tvalue->match(term));
    }
    else if(!assignable){
      return term.value()==value();
    }
    else{
      return term.symbol()==symbol();
    }
  }
  string type() const{return "Variable";}

private:
  string _symbol;
  string _value;
  std::vector<Term*> v;
  Term *_tvalue;
  bool assignable;
};

#endif
