#ifndef ITERATOR_H
#define ITERATOR_H

#include <vector>
#include <queue>

// class Term;
// class Struct;
// class List;
#include "struct.h"
#include "list.h"
// #include "iterator.h"

template<class Item>
class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual Item currentItem() const = 0;
  virtual bool isDone() const{
    return true;
  }
};

template<class Item>
class NullIterator :public Iterator<Item>{
public:
  NullIterator(Item n){}
  void first(){}
  void next(){}
  Item currentItem() const{
      return nullptr;
  }
  bool isDone() const{
      return true;
  }
};

template<class Item>
class StructIterator :public Iterator<Item> {
public:
  friend class Struct;
  
  void first() {
    _index = 0;
  }
  
  Item currentItem() const {
    return _s->args(_index);
  }
  
  bool isDone() const {
    return _index >= _s->arity();
  }
  
  void next() {
    _index++;
  }
  
private:
  StructIterator(Struct *s): _index(0), _s(s) {}
  int _index;
  Struct* _s;
};

template<class Item>
class ListIterator :public Iterator<Item> {
public:
  friend class List;

  void first() {
    _index = 0;
  }
  
  Item currentItem() const {
    return _list->args(_index);
  }
  
  bool isDone() const {
    return _index >= _list->arity();
  }
  
  void next() {
    _index++;
  }
private:
  ListIterator(List *list): _index(0), _list(list) {}
  int _index;
  List* _list;
};

  

template<class Item>
class DFSIterator :public Iterator<Item> {
public:
  DFSIterator(Item t):_index(0){
    DFS(t->createIterator());
  }
  void DFS(Iterator<Item> *it){
    for(it->first();it->isDone()!=true;it->next()){
      _terms.push_back(it->currentItem());
      DFS(_terms.back()->createIterator());
    }
  }
  
  void first(){
    //_it[_it.size()-1]->first();
    _index=0;
  }
  
  Item currentItem() const{
    //return _it[_it.size()-1]->currentItem();
    return _terms[_index];
  }
  
  bool isDone() const{
    //return _it.empty();
    return _index>=_terms.size();
  }
  
  void next(){
    // if(!isDone()){
    //   // std::cout<<_it[_it.size()-1]->currentItem()->symbol()<<std::endl;
    //   _it.push_back(_it[_it.size()-1]->currentItem()->createIterator());
    //   _it[_it.size()-1]->first();
    //   //node is empty.
    //   while(_it[_it.size()-1]->isDone()){
    //     _it.pop_back();
    //     if(!isDone())
    //       _it[_it.size()-1]->next();
    //     else
    //       break;
    //   }
    // }
    _index++;
  }
private:
  std::vector<Iterator<Item>*>_it;
  std::vector<Item> _terms;
  int _index;
};

template<class Item>
class BFSIterator :public Iterator<Item> {
public:
  BFSIterator(Item t):_index(0){
    _q.push(t->createIterator());
  
    while(!_q.empty()){
      
      Iterator<Item>* it=_q.front();
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
  Item currentItem() const{
    return _terms[_index];
  }
  bool isDone() const{
    return _index>=_terms.size();
  }
  void next(){
    _index++;
  }
private:
  std::queue<Iterator<Item>*> _q;
  std::vector<Item> _terms;
  int _index;
};

#endif