#ifndef TERM_H
#define TERM_H

#include <string>
using std::string;

template<class Item>
class Iterator;
class Term{
    
    public:
      virtual string symbol() const = 0;
    
      virtual string value() const {
        return symbol();
      };
    
      virtual bool match(Term & term) {
        return symbol() == term.symbol();
      }

      virtual string type() const = 0;

      virtual int arity() const {
        return 1;
      }
      
      virtual Iterator<Term*>* createIterator();
      virtual Iterator<Term*>* createDFSIterator();
      virtual Iterator<Term*>* createBFSIterator();
      
};

#endif