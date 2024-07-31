// CMSC 430 Compiler Theory and Design
// Project 4 Skeleton
// Keith Lee
// Summer 2024

// This file contains type definitions and the function
// prototypes for the type checking functions

typedef char* CharPtr;

enum Types {MISMATCH, INT_TYPE, CHAR_TYPE, REAL_TYPE, NONE};

// just a helper function to help me troubleshoot the other functions
const string ToString(Types t);

void checkAssignment(Types lValue, Types rValue, string message);
void checkListVar(Types listVar, Types listType);
void checkRelopTypes(Types lValue, Types rValue);
Types checkWhen(Types true_, Types false_);
Types checkSwitch(Types case_, Types when, Types other);
Types checkCases(Types left, Types right);
Types checkArithmetic(Types left, Types right);
Types checkIf(Types left, Types middle, Types right);
Types checkListElems(Types left, Types right);
Types checkSubInteger(Types sub);
Types checkMod(Types left, Types right);
Types checkFold(Types listType);

