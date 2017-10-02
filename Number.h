#ifndef NUMBER_H
#define NUMBER_H

#include "Term.h"
class Number: public Term{
public:
    Number(int num){
        std::ostringstream ss;
        ss<<num;
        _symbol=ss.str();
        _value=ss.str();
    }
    bool match(Term &term){
        if(term.type()=="Var" && term.value().empty()){
            term.setValue(this);
        }
        else if(!term.value().empty()){
            return term.value()==value();
        }
        else{
            return term.symbol()==_symbol;
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
        return "Number";
    }
private:
    string _symbol;
    string _value;

};
#endif