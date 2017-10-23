#ifndef NUMBER_H
#define NUMBER_H

#include "term.h"
#include <sstream>

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
    string type() const{return "Number";}

private:
    string _symbol;
    string _value;
};

#endif