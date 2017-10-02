#ifndef ATOM_H
#define ATOM_H

#include "Term.h"
class Atom: public Term{
public:
    Atom(string num){
        _symbol=num;
        _value=num;
    }
    bool match(Term *term){
        if(term->type()=="Var" && term->value().empty()){
            term->setValue(this);
        }
        else if(!term->value().empty()){
            return term->value()==value();
        }
        else{
            return term->symbol()==symbol();
        }
    }
    string symbol() const{
        return _symbol;
    }
    string value() const{
        return _value;
    }
    bool setValue(Term *t){
        return false;
    }
    string type() const{
        return "Atom";
    }
private:
    string _symbol;
    string _value;
};
#endif