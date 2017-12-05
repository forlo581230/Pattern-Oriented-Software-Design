#include "term.h"
#include "iterator.h"

Iterator* Term::createIterator(){
    return new NullIterator(this);
}

Iterator* Term::createDFSIterator(){
    return new DFSIterator(this);
}

Iterator* Term::createBFSIterator(){
    return new BFSIterator(this);
}

