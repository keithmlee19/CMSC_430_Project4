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
		if (lValue == INT_TYPE && rValue == REAL_TYPE)
			appendError(GENERAL_SEMANTIC, "Illegal Narrowing " + message);
		else
			appendError(GENERAL_SEMANTIC, "Type Mismatch on Variable Initialization ");
}

void checkListVar(Types listVar, Types listType) {
	if (listVar != MISMATCH && listType != MISMATCH && listVar != listType)
		appendError(GENERAL_SEMANTIC, "List Type Does Not Match Element Type");
}

void checkRelopTypes(Types lValue, Types rValue) {
	if (lValue != MISMATCH && rValue != MISMATCH)
		if (lValue == (INT_TYPE || REAL_TYPE) && rValue == CHAR_TYPE || lValue == CHAR_TYPE && rValue == (INT_TYPE || REAL_TYPE))
			appendError(GENERAL_SEMANTIC, "Character Literals Cannot be Compared to Numeric Expressions ");
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

Types checkArithmetic(Types left, Types right) {
	if (left == INT_TYPE && right == INT_TYPE)
		return INT_TYPE;
	else if (left == INT_TYPE && right == REAL_TYPE)
		return REAL_TYPE;
	else if (left == REAL_TYPE && right == INT_TYPE)
		return REAL_TYPE;
	else if (left == MISMATCH || right == MISMATCH)
		return MISMATCH;
	appendError(GENERAL_SEMANTIC, "Arithmetic Operator Requires Numeric Types ");
	return MISMATCH;
}

Types checkIf(Types left, Types middle, Types right) {
	if (left == MISMATCH || middle == MISMATCH || right == MISMATCH)
		return MISMATCH;
	if (middle == NONE)
		if (left == right)
			return left;
	else if (left == middle && left == right && middle == right)
		return left;
	appendError(GENERAL_SEMANTIC, "If-Elsif-Else Type Mismatch ");
	return MISMATCH;
}

Types checkListElems(Types left, Types right) {
	if (left == MISMATCH || right == MISMATCH)
		return MISMATCH;
	else if (left == right)
		return left;
	appendError(GENERAL_SEMANTIC, "List Element Types Do Not Match ");
	return MISMATCH;
}

Types checkSubInteger(Types sub) {
	if (sub == INT_TYPE)
		return INT_TYPE;
	appendError(GENERAL_SEMANTIC, "List Subscript Must Be Integer ");
	return MISMATCH;
}

Types checkMod(Types left, Types right) {
	if (left == INT_TYPE && right == INT_TYPE)
		return INT_TYPE;
	appendError(GENERAL_SEMANTIC, "Remainder Operator Requires Integer Operands ");
	return MISMATCH;
}

Types checkFold(Types listType) {
	if (listType == INT_TYPE || listType == REAL_TYPE)
		return listType;
	appendError(GENERAL_SEMANTIC, "Fold Requires A Numeric List ");
	return MISMATCH;
}