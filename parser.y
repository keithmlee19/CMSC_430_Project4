/* CMSC 430 Compiler Theory and Design
   Project 4 Skeleton
   Keith Lee
   Summer 2024
   
   Project 4 Parser with semantic actions for static semantic errors */

%{
#include <string>
#include <vector>
#include <map>

using namespace std;

#include "types.h"
#include "listing.h"
#include "symbols.h"

int yylex();
Types find(Symbols<Types>& table, CharPtr identifier, string tableName);
void yyerror(const char* message);

Symbols<Types> scalars;
Symbols<Types> lists;

%}

%define parse.error verbose

%union {
	CharPtr iden;
	Types type;
}

%token <iden> IDENTIFIER

%token <type> INT_LITERAL CHAR_LITERAL REAL_LITERAL

%token ADDOP MULOP MODOP EXPOP ANDOP OROP RELOP NEGOP NOTOP ARROW

%token BEGIN_ CASE CHARACTER ELSE ELSIF END ENDFOLD ENDIF ENDSWITCH FOLD FUNCTION IF INTEGER IS LEFT LIST OF OTHERS
	REAL RETURNS RIGHT SWITCH THEN WHEN

%type <type> list list_choice expressions body type statement_ statement cases case_ case expression
	term primary exp_term neg_term elsif_clauses elsif_clause function_header

%%

function:	
	function_header optional_variable_ body {checkAssignment($1,$3,"Function Return");} ;
		
function_header:	
	FUNCTION IDENTIFIER RETURNS type ';' {$$ = $4;} ;

type:
	INTEGER {$$ = INT_TYPE;} |
	CHARACTER {$$ = CHAR_TYPE; } |
	REAL {$$ = REAL_TYPE; };

optional_variable_:
	optional_variable |
	error ';' ;
	
optional_variable:
	optional_variable variable |
	%empty ;
    
variable:	
	IDENTIFIER ':' type IS statement ';' {checkAssignment($3, $5, "Variable Initialization"); scalars.findDup($1, "Scalar "); scalars.insert($1, $3);} |
	IDENTIFIER ':' LIST OF type IS list ';' {checkListVar($5, $7); lists.findDup($1, "List "); lists.insert($1, $5);} ;

list:
	'(' expressions ')' {$$ = $2;} ;
	
list_choice:
	list |
	IDENTIFIER {$$ = find(scalars, $1, "Scalar");} ;

expressions:
	expressions ',' expression {$$ = checkListElems($1, $3);} | 
	expression ;

body:
	BEGIN_ statement_ END ';' {$$ = $2;} ;
    
statement_:
	statement ';' |
	error ';' {$$ = MISMATCH;} ;
	
statement:
	expression |
	WHEN or_condition ',' expression ':' expression 
		{$$ = checkWhen($4, $6);} |
	SWITCH expression IS cases OTHERS ARROW statement ';' ENDSWITCH 
		{$$ = checkSwitch($2, $4, $7);} |
	IF or_condition THEN statement_ elsif_clauses ELSE statement_ ENDIF
		{$$ = checkIf($4, $5, $7);} |
	FOLD direction operator list_choice ENDFOLD {$$ = checkFold($4);} ;

elsif_clauses:
	elsif_clauses elsif_clause |
	%empty {$$ = NONE;} ;

elsif_clause:
	ELSIF or_condition THEN statement_ {$$ = $4;} ;

cases:
	cases case_ {$$ = checkCases($1, $2);} |
	%empty {$$ = NONE;} ;

case_:
	case |
	error ';' {$$ = MISMATCH;} ;
	
case:
	CASE INT_LITERAL ARROW statement ';' {$$ = $4;} ;

direction:
	LEFT |
	RIGHT ;

operator:
	ADDOP |
	MULOP |
	EXPOP ;
	
or_condition:
	or_condition OROP condition |
	condition ;

condition:
	condition ANDOP not_condition |
	not_condition ;
	
not_condition:
	NOTOP relation |
	relation ;

relation:
	'(' or_condition')' |
	expression RELOP expression {checkRelopTypes($1, $3);} ;
	
expression:
	expression ADDOP term {$$ = checkArithmetic($1, $3);} |
	term ;
      
term:
	term MULOP exp_term {$$ = checkArithmetic($1, $3);} |
	term MODOP exp_term {$$ = checkMod($1, $3);} |
	exp_term ;
	
// the only right associative binary operator
exp_term:
	neg_term EXPOP exp_term {$$ = checkArithmetic($1, $3);} |
	neg_term ;

neg_term:
	NEGOP primary {$$ = checkArithmetic($2,$2);} |
	primary ;

primary:
	'(' expression ')' {$$ = $2;} |
	INT_LITERAL | 
	CHAR_LITERAL |
	REAL_LITERAL |
	IDENTIFIER '(' expression ')' {checkSubInteger($3); $$ = find(lists, $1, "List");} |
	IDENTIFIER  {$$ = find(scalars, $1, "Scalar");} ;

%%

Types find(Symbols<Types>& table, CharPtr identifier, string tableName) {
	Types type;
	if (!table.find(identifier, type)) {
		appendError(UNDECLARED, tableName + " " + identifier);
		return MISMATCH;
	}
	return type;
}

void yyerror(const char* message) {
	appendError(SYNTAX, message);
}

int main(int argc, char *argv[]) {
	firstLine();
	yyparse();
	lastLine();
	return 0;
} 
