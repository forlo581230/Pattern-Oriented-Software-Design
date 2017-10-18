#ifndef NUMBER_H
#define NUMBER_H

#include "atom.h"
#include <string>
#include <sstream>
using std::string;

class Number : public Term{

public:
    Number(float  v){
        std::stringstream ss;
        ss<<v;
        _value = ss.str();
        _symbol = ss.str();
    }
    string symbol() const{return _symbol;}
    string value() const{return _value;}
    bool match(Term &term){
        if(term.type()=="Variable" && term.value().empty()){
            term.setValue(this);
        }
        else if(!term.value().empty()){
            return term.value()==value();
        }
        else{
            return term.symbol()==_symbol;
        }
    }
    string type() const{return "Number";}

private:
    string _symbol;
    string _value;
};

#endif