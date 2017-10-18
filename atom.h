#ifndef ATOM_H
#define ATOM_H

#include <string>

using std::string;


class Term{

public:
  virtual string symbol() const = 0;

  virtual string value() const {
    return symbol();
  };

  virtual bool match(Term & term) {
    return symbol() == term.symbol();
  }
  virtual bool setValue(Term *t) {
    return false;
  }
  virtual string type() const = 0;
  

};


class Atom : public Term{
public:
  Atom (string s):_symbol(s){}

  string symbol() const{
    return _symbol;
  }
  string value() const{return symbol();}

  bool match(Term &term){
    if(term.type()=="Variable" && term.value()==term.symbol()){
      term.match(*this);
    }
    else if(term.value()!=term.symbol()){
        return term.value()==value();
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
