#ifndef UTTERM_H
#define UTTERM_H

#include "Term.h"
#include "Number.h"
#include "Atom.h"
#include "Variable.h"

//test Number.value()
TEST (Number,ctor) {
    Number _25(25);
    EXPECT_EQ("25",_25.value());
}
//test Number.symbol()
TEST (Number, symbol) {
    Number _25(25);
    EXPECT_EQ("25",_25.symbol());
}
//?- 25=25.
//true.
TEST (Number, matchSuccess) {
    Number _25(25);
    Number _25_2(25);
    EXPECT_TRUE(_25.match(&_25_2));
}
//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
    Number _25(25);
    Number _0(0);
    EXPECT_FALSE(_25.match(&_0));
}
//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
    Number _25(25);
    Atom tom("tom");
    EXPECT_FALSE(_25.match(&tom));
}
//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
    Number _25(25);
    Var X("X");
    EXPECT_TRUE(_25.match(&X));
}

//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {
    Atom tom("tom");
    Number _25(25);
    EXPECT_FALSE(tom.match(&_25));
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
    Atom tom("tom");
    Var X("X");
    EXPECT_TRUE(tom.match(&X));
}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
    Atom tom("tom");
    Var X("X");
    EXPECT_TRUE(X.match(&tom));
    EXPECT_TRUE(tom.match(&X));
}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
    Var X("X");
    Atom tom("tom");
    Atom jerry("jerry");
    EXPECT_FALSE(X.match(&jerry) && tom.match(&X));
}

// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber) {
    Var X("X");
    Number _5(5);
    EXPECT_TRUE(X.match(&_5));
}

// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers) {
    Var X("X");
    Number _25(25);
    Number _100(100);
    EXPECT_FALSE(X.match(&_25) && X.match(&_100));
}

// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber) {
    Var X("X");
    Atom tom("tom");
    Number _25(25);
    EXPECT_FALSE(X.match(&tom) && X.match(&_25));
}
//?- tom=X, 25=X.
//false.
TEST (Var, matchSuccessToAtomThenFailureToNumber2) {
    Atom tom("tom");
    Var X("X");
    Number _25(25);
    EXPECT_FALSE(tom.match(&X) && _25.match(&X));
}
//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom){
    Var X("X");
    Atom tom("tom");
    EXPECT_FALSE(X.match(&tom) && X.match(&tom));
}
#endif
