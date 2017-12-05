#include "struct.h"
#include "iterator.h"
#include "list.h"
#include <iostream>

// StructIterator::StructIterator(Struct *s): _index(0), _s(s) {}

// void StructIterator::first() {
//   _index = 0;
// }

// Term* StructIterator::currentItem() const {
//   return _s->args(_index);
// }

// bool StructIterator::isDone() const {
//   return _index >= _s->arity();
// }

// void StructIterator::next() {
//   _index++;
// }

// ListIterator::ListIterator(List *list): _index(0), _list(list) {}

// void ListIterator::first() {
//   _index = 0;
// }

// Term* ListIterator::currentItem() const {
//   return _list->args(_index);
// }

// bool ListIterator::isDone() const {
//   return _index >= _list->arity();
// }

// void ListIterator::next() {
//   _index++;
// }


//DFS
// DFSIterator::DFSIterator(Term *t):_index(0){
//   _it.push_back(t->createIterator());
// }

// void DFSIterator::first(){
//   _it[_it.size()-1]->first();
// }

// Term* DFSIterator::currentItem() const{
//   return _it[_it.size()-1]->currentItem();
// }

// bool DFSIterator::isDone() const{
//   return _it.empty();
// }

// void DFSIterator::next(){
//   if(!isDone()){
//     // std::cout<<_it[_it.size()-1]->currentItem()->symbol()<<std::endl;
//     _it.push_back(_it[_it.size()-1]->currentItem()->createIterator());
//     _it[_it.size()-1]->first();
//     //node is empty.
//     while(_it[_it.size()-1]->isDone()){
//       _it.pop_back();
//       if(!isDone())
//         _it[_it.size()-1]->next();
//       else
//         break;
//     }
//   }
// }

//BFS
// BFSIterator::BFSIterator(Term *t):_index(0){
//   _q.push(t->createIterator());

//   while(!_q.empty()){
    
//     Iterator* it=_q.front();
//     _q.pop();

//     for(it->first();it->isDone()!=true;it->next()){
//       _q.push(it->currentItem()->createIterator());
//       _terms.push_back(it->currentItem());
//     }
//   }
//   // for(int i=0;i<_terms.size();i++){
//   //   std::cout<<_terms[i]->symbol()<<std::endl;
//   // }
// }
// void BFSIterator::first(){
//   _index=0;
// }
// Term* BFSIterator::currentItem() const{
//   return _terms[_index];
// }
// bool BFSIterator::isDone() const{
//   return _index>=_terms.size();
// }
// void BFSIterator::next(){
//   _index++;
// }
