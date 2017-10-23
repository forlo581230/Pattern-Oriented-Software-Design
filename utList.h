#ifndef UTLIST_H
#define UTLIST_H

#include <string>
using std::string;

#include "list.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include "variable.h"

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {
  vector<Term *> args;
  List list(args);
  EXPECT_EQ("[]", list.symbol());
}

// Given there are two perfect numbers: 8128
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[8128]"
TEST(List, Numbers) {
  Number _8128(8128);
  vector<Term *> args = {&_8128};
  List list(args);
  EXPECT_EQ("[8128]", list.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
  Atom t("terence_tao"), a("alan_mathison_turing");
  vector<Term *> args = {&t, &a};
  List list(args);
  EXPECT_EQ("[terence_tao, alan_mathison_turing]", list.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
  Variable X("X"), Y("Y");
  vector<Term *> args = {&X, &Y};
  List list(args);
  EXPECT_EQ("[X, Y]", list.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
  Number _496(496);
  Variable X("X");
  Atom t("terence_tao");
  vector<Term *> args = {&_496, &X, &t};
  List list(args);
  Atom tom("tom");
  EXPECT_FALSE(tom.match(list));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
  Number _496(496);
  Variable X("X");
  Atom t("terence_tao");
  vector<Term *> args = {&_496, &X, &t};
  List list(args);
  Number _8128(8128);
  EXPECT_FALSE(_8128.match(list));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
  Number _496(496);
  Variable X("X");
  Atom t("terence_tao");
  vector<Term *> args = {&_496, &X, &t};
  List list(args);
  std::vector<Term *> v = {&X};
  Struct s(Atom("s"), v);
  EXPECT_FALSE(s.match(list));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
  Number _496(496);
  Variable X("X");
  Atom t("terence_tao");
  vector<Term *> args = {&_496, &X, &t};
  List list(args);
  Variable Y("Y");
  Y.match(list);
  EXPECT_EQ("[496, X, terence_tao]", Y.value());
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
  Number _496(496);
  Variable X("X");
  Atom t("terence_tao");
  vector<Term *> args = {&_496, &X, &t};
  List list(args);
  EXPECT_TRUE(X.match(list));//?????
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
  Number _496(496);
  Variable X("X");
  Atom t("terence_tao");
  vector<Term *> args = {&_496, &X, &t};
  List list(args);
  EXPECT_TRUE(list.match(list));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
  Number _496(496);
  Variable X("X");
  Atom t("terence_tao");
  vector<Term *> args = {&_496, &X, &t};
  List list(args);
  Variable Y("Y");
  vector<Term *> argsY = {&_496, &Y, &t};
  List listY(argsY);
  EXPECT_TRUE(list.match(listY));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
  Number _496(496);
  Variable X("X");
  Atom t("terence_tao");
  vector<Term *> args = {&_496, &X, &t};
  List list(args);
  Number _8128(8128);
  vector<Term *> argsY = {&_496, &_8128, &t};
  List listY(argsY);
  EXPECT_TRUE(list.match(listY));
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
  Number _496(496);
  Variable X("X");
  Atom t("terence_tao");
  vector<Term *> args = {&_496, &X, &t};
  List list(args);
  Variable Y("Y");
  Y.match(list);
  Atom amt("alan_mathison_turing");
  X.match(amt);
  EXPECT_EQ("[496, alan_mathison_turing, terence_tao]",Y.value());
  EXPECT_EQ("alan_mathison_turing",X.value());
}

// Example: 
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("first"), l.head()->symbol());
  EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("second"), l.tail()->head()->value());
  EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {
  Atom f("[first]"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("[first]"), l.head()->symbol());
  EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("third"), l.tail()->tail()->head()->value());
  EXPECT_EQ(string("[]"), l.tail()->tail()->tail()->value());
}
  
// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {
  //List emptyList;
  //emptyList.head();
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {
  List emptyList;
  emptyList.tail();
}




#endif
