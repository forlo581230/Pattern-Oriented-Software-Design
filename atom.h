#ifndef ATOM_H
#define ATOM_H

#include "term.h"

class Atom : public Term{
public:
  Atom (string s):_symbol(s){}

  string symbol() const{
    return _symbol;
  }
  string value() const{return symbol();}

  bool match(Term &term){
    if(term.type()=="Variable"){

      if(term.value()==term.symbol()){
        term.match(*this);
      }
      else if(term.value()!=term.symbol()){
          return term.value()==value();
      }
    }
    else if(term.type()=="List"){
      return false;
    }
    else{
      return term.symbol()==_symbol;
    }
  }

  string type() const{return "Atom";}
private:
  string _symbol;
};


#endif
