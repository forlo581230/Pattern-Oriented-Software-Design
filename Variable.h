#ifndef VARIABLE_H
#define VARIABLE_H

#include "Term.h"
class Variable: public Term{
public:
    Variable(string num){
        _symbol=num;
    }
    bool match(Term &term){
        if(term.type()!="Var" && value().empty()){
            setValue(&term);
        }
        else if(!term.value().empty()){
            return term.value()==value();
        }
        else{
            return term.symbol()==symbol();
        }
    }
    string symbol() const{
        return _symbol;
    }
    string value() const{
        return _value;
    }
    bool setValue(Term *t) {
        _value = (t)->value();
        return true;
    }
    string type() const{
        return "Var";
    }
private:
    string _symbol;
    string _value;
};
#endif