#include "struct.h"
#include "iterator.h"

Iterator* Struct::createIterator()
{
  return new StructIterator(this);
}

// Iterator* Struct::createDFSIterator()
// {
//   return new DFSIterator(this);
// }

// Iterator* Struct::createBFSIterator()
// {
//   return new BFSIterator(this);
// }

