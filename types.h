// CMSC 430 Compiler Theory and Design
// Project 4 Skeleton
// Keith Lee
// Summer 2024

// This file contains type definitions and the function
// prototypes for the type checking functions

typedef char* CharPtr;

enum Types {MISMATCH, INT_TYPE, CHAR_TYPE, REAL_TYPE, NONE};

void checkAssignment(Types lValue, Types rValue, string message);
void checkListVar(Types lValue, Types rValue);
Types checkWhen(Types true_, Types false_);
Types checkSwitch(Types case_, Types when, Types other);
Types checkCases(Types left, Types right);
Types checkListElems(Types left, Types right);
Types checkArithmetic(Types left, Types right);

