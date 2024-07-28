// CMSC 430 Compiler Theory and Design
// Project 4 Skeleton
// Keith Lee
// Summer 2024

// This file contains the bodies of the type checking functions

#include <string>
#include <vector>

using namespace std;

#include "types.h"
#include "listing.h"

const string ToString(Types t)
{
    switch (t)
    {
        case MISMATCH:   return "MISMATCH ";
        case INT_TYPE:   return "INT_TYPE ";
        case CHAR_TYPE: return "CHAR_TYPE ";
		case REAL_TYPE: return "REAL_TYPE ";
		case NONE: return "NONE ";
        default:      return "OTHER ";
    }
}

void checkAssignment(Types lValue, Types rValue, string message) {
	if (lValue != MISMATCH && rValue != MISMATCH && lValue != rValue)
		appendError(GENERAL_SEMANTIC, "Type Mismatch on " + message);
}

void checkListVar(Types lValue, Types rValue) {
	if (lValue != MISMATCH && rValue != MISMATCH && lValue != rValue)
		appendError(GENERAL_SEMANTIC, "List Type Does Not Match Element Type");
}

Types checkWhen(Types true_, Types false_) {
	if (true_ == MISMATCH || false_ == MISMATCH)
		return MISMATCH;
	if (true_ != false_)
		appendError(GENERAL_SEMANTIC, "When Types Mismatch ");
	return true_;
}

Types checkSwitch(Types case_, Types when, Types other) {
	if (case_ != INT_TYPE)
		appendError(GENERAL_SEMANTIC, "Switch Expression Not Integer");
	return checkCases(when, other);
}

Types checkCases(Types left, Types right) {
	if (left == MISMATCH || right == MISMATCH)
		return MISMATCH;
	if (left == NONE || left == right)
		return right;
	appendError(GENERAL_SEMANTIC, "Case Types Mismatch");
	return MISMATCH;
}

Types checkListElems(Types left, Types right) {
	if (left == right)
		return left;
	else if (left == MISMATCH || right == MISMATCH)
		return MISMATCH;
	appendError(GENERAL_SEMANTIC, "List Element Types Do Not Match");
	return MISMATCH;
}

Types checkArithmetic(Types left, Types right) {
	if (left == INT_TYPE && right == INT_TYPE)
		return INT_TYPE;
	else if (left == INT_TYPE && right == REAL_TYPE)
		return REAL_TYPE;
	else if (left == REAL_TYPE && right == INT_TYPE)
		return REAL_TYPE;
	else if (left == MISMATCH || right == MISMATCH)
		return MISMATCH;
	appendError(GENERAL_SEMANTIC, "Integer Type Required");
	return MISMATCH;
}

Types checkSubInteger(Types sub) {
	if (sub == INT_TYPE)
		return INT_TYPE;
	appendError(GENERAL_SEMANTIC, "List Subscript Must Be Integer");
	return MISMATCH;
}