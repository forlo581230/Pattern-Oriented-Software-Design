#ifndef VARIABLE_H
#define VARIABLE_H

#include <vector>
#include "term.h"

class Variable : public Term{
public:
  Variable(string s):_symbol(s), _value(s){
    _tvalue = 0;
    assignable=true;
  }
  string symbol() const{return _symbol;}
  string value() const{
    if(_tvalue==0)
      return _value;
    else
      return _tvalue->value();
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
        Variable *var = dynamic_cast<Variable*>(&term);
        v.push_back(&term);
        var->v.push_back(this);
        
        if(_symbol!=_value)
          term.match(*this);
        else
          _value=term.symbol();
          //_value=term.value();
         /*
        if(term.value()!=term.symbol()){
          assignValue(term.value(), new std::vector<string>);
        }
        */
      }
      else if(term.type()=="Struct"){
        _tvalue = &term;

      }
      else if(term.type()=="List"){
        _tvalue = &term;
        assignable=false;
      }
      else if(this!=&term){//表示傳進來的不是struct variable
        assignValue(term.symbol(), new std::vector<string>);
      }
      
      return true;
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
