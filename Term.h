#ifndef TERM_H
#define TERM_H

#include <iostream>
#include<string>
using std::string;

class Term{
public:
    virtual string symbol() const=0;
    virtual string value() const=0;
    virtual bool setValue(Term *t) =0;
    virtual string type() const=0;
};

#endif