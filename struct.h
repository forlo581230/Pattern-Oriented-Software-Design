#ifndef STRUCT_H
#define STRUCT_H

#include "term.h"
#include "atom.h"
#include <vector>
#include <iostream>

class Struct:public Term{
public:
  Struct(Atom const & name, std::vector<Term *> args):_name(name), _args(args) {
  }

  Term * args(int index) {
    return _args[index];
  }

  Atom const & name() {
    return _name;
  }
  string symbol() const{
    string ret =_name.symbol() + "(";

    if(_args.size()==0){
      ret+=")";
      return ret;
    }
    for(int i = 0; i < _args.size() - 1 ; i++){
      ret += _args[i]-> symbol() + ", ";
    }

    ret += _args[_args.size()-1]-> symbol() + ")";
    
      

    return  ret;
  }
  string value() const{
    string ret =_name.value() + "(";
    for(int i = 0; i < _args.size() - 1 ; i++){
      ret += _args[i]-> value() + ", ";
    }
    ret += _args[_args.size()-1]-> value() + ")";
    return  ret;
  }

  bool match(Term &term){
    Struct * ps = dynamic_cast<Struct *>(&term);
    if (ps){
      if (!_name.match(ps->_name))
        return false;
      if(_args.size()!= ps->_args.size())
        return false;
      for(int i=0;i<_args.size();i++){
        if(_args[i]->symbol() != ps->_args[i]->symbol())
            return false;
      }
      return true;
    }
    return false;
  }
  string type() const{return "Struct";}
  int arity() const{
    return _args.size();
  }
  
private:
  Atom _name;
  std::vector<Term *> _args;
};

#endif