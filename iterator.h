#ifndef ITERATOR_H
#define ITERATOR_H

#include <vector>
#include <queue>

// class Term;
// class Struct;
// class List;
#include "struct.h"
// #include "iterator.h"
#include "list.h"

class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual Term* currentItem() const = 0;
  virtual bool isDone() const{
    return true;
  }
};

class NullIterator :public Iterator{
public:
  NullIterator(Term *n){}
  void first(){}
  void next(){}
  Term* currentItem() const{
      return nullptr;
  }
  bool isDone() const{
      return true;
  }
};

class StructIterator :public Iterator {
public:
  StructIterator(Struct *s): _index(0), _s(s) {}
  
  void first() {
    _index = 0;
  }
  
  Term* currentItem() const {
    return _s->args(_index);
  }
  
  bool isDone() const {
    return _index >= _s->arity();
  }
  
  void next() {
    _index++;
  }
  
private:
  int _index;
  Struct* _s;
};

class ListIterator :public Iterator {
public:
  ListIterator(List *list): _index(0), _list(list) {}
  
  void first() {
    _index = 0;
  }
  
  Term* currentItem() const {
    return _list->args(_index);
  }
  
  bool isDone() const {
    return _index >= _list->arity();
  }
  
  void next() {
    _index++;
  }
private:
  int _index;
  List* _list;
};

  
/**
 * Implement the interface through your design, 
 * and do not modify the function signature of each.
*/

class DFSIterator :public Iterator {
public:
  DFSIterator(Term *t):_index(0){
    _it.push_back(t->createIterator());
  }
  
  void first(){
    _it[_it.size()-1]->first();
  }
  
  Term* currentItem() const{
    return _it[_it.size()-1]->currentItem();
  }
  
  bool isDone() const{
    return _it.empty();
  }
  
  void next(){
    if(!isDone()){
      // std::cout<<_it[_it.size()-1]->currentItem()->symbol()<<std::endl;
      _it.push_back(_it[_it.size()-1]->currentItem()->createIterator());
      _it[_it.size()-1]->first();
      //node is empty.
      while(_it[_it.size()-1]->isDone()){
        _it.pop_back();
        if(!isDone())
          _it[_it.size()-1]->next();
        else
          break;
      }
    }
  }
private:
  std::vector<Iterator*>_it;
  int _index;
};

class BFSIterator :public Iterator {
public:
  BFSIterator(Term *t):_index(0){
    _q.push(t->createIterator());
  
    while(!_q.empty()){
      
      Iterator* it=_q.front();
      _q.pop();
  
      for(it->first();it->isDone()!=true;it->next()){
        _q.push(it->currentItem()->createIterator());
        _terms.push_back(it->currentItem());
      }
    }
    // for(int i=0;i<_terms.size();i++){
    //   std::cout<<_terms[i]->symbol()<<std::endl;
    // }
  }
  void first(){
    _index=0;
  }
  Term* currentItem() const{
    return _terms[_index];
  }
  bool isDone() const{
    return _index>=_terms.size();
  }
  void next(){
    _index++;
  }
private:
  std::queue<Iterator*> _q;
  std::vector<Term*> _terms;
  int _index;
};

#endif