#include "struct.h"
#include "iterator.h"
Iterator<Term*>* Struct::createIterator()
{
  return new StructIterator<Term*>(this);
}

// Iterator* Struct::createDFSIterator()
// {
//   return new DFSIterator(this);
// }

// Iterator* Struct::createBFSIterator()
// {
//   return new BFSIterator(this);
// }

