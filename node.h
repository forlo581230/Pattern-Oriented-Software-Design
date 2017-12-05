#ifndef NODE_H
#define NODE_H
#include<iostream>
#include"term.h"

enum Operators {SEMICOLON, COMMA, EQUALITY, TERM};

class Node {
public:
  Node(Operators op):payload(op), term(0), left(0), right(0) {}
  Node(Operators op, Term *t, Node *l, Node *r):payload(op), term(t), left(l), right(r) {}

  bool evaluate(){
    //先走左 再走右
    //std::cout<<payload<<std::endl;
    bool a,b;
    switch(payload){
      case SEMICOLON://; or
        a=left->evaluate();
        b=right->evaluate();
        return (a||b);
        break;
      case COMMA://, and
        return left->evaluate()&&right->evaluate();
        break;
      case EQUALITY:
      //std::cout<<left->term->symbol()<<std::endl;
      //std::cout<<right->term->symbol()<<std::endl;
      //std::cout<<left->term->match(*right->term)<<"GG"<<std::endl;
        return left->term->match(*right->term);
        break;
      default:
      std::cout<<"D"<<std::endl;
        break;        
    }
  }
  Operators payload;
  Term *term;
  Node *left;
  Node *right;


};

#endif
