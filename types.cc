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

void checkAssignment(Types lValue, Types rValue, string message) {
	if (lValue != MISMATCH && rValue != MISMATCH && lValue != rValue)
		if (!((lValue == INT_TYPE && rValue == REAL_TYPE) || (lValue == REAL_TYPE && rValue == INT_TYPE)))
			appendError(GENERAL_SEMANTIC, "Type Mismatch on " + message);
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

Types checkLists(Types left, Types right) {
	if (left == MISMATCH || right == MISMATCH)
		return MISMATCH;
	appendError(GENERAL_SEMANTIC, "List Element Types Do Not Match");
	return MISMATCH;
}

Types checkArithmetic(Types left, Types right) {
	if (left == MISMATCH || right == MISMATCH)
		return MISMATCH;
	if (left == INT_TYPE && right == INT_TYPE)
		return INT_TYPE;
	if (left == INT_TYPE && right == REAL_TYPE)
		return INT_TYPE;
	if (left == REAL_TYPE && right == INT_TYPE)
		return INT_TYPE;
	appendError(GENERAL_SEMANTIC, "Integer Type Required");
	return MISMATCH;
}