#include "list.h"
#include "iterator.h"

Iterator<Term*>* List::createIterator(){
    return new ListIterator<Term*>(this);
}

// Iterator* List::createDFSIterator()
// {
//   return new DFSIterator(this);
// }

// Iterator* List::createBFSIterator()
// {
//   return new BFSIterator(this);
// }
