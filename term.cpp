#include "term.h"
#include "iterator.h"

Iterator<Term*>* Term::createIterator(){
    return new NullIterator<Term*>(this);
}

Iterator<Term*>* Term::createDFSIterator(){
    return new DFSIterator<Term*>(this);
}

Iterator<Term*>* Term::createBFSIterator(){
    return new BFSIterator<Term*>(this);
}
