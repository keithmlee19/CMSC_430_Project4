/* CMSC 430 Compiler Theory and Design
   Project 4 Skeleton
   Keith Lee
   Summer 2024 */

/* This file contains flex input file */

%{
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

#include "types.h"
#include "listing.h"
#include "tokens.h"

%}

%option noyywrap

ws		[ \t\r]+
comment		("//"|"--").*\n
line		[\n]
id		[A-Za-z](_?_?[A-Za-z0-9]+)*
digit		[0-9]
dec		{digit}+
hex		#[A-Fa-f0-9]+
real		[0-9]*\.[0-9]+([eE][+-]?[0-9]+)*
char		'(\\b|\\t|\\n|\\f|\\r|.)'
punc		[\(\),:;]
%%

{ws}		{ ECHO; }
{comment}	{ ECHO; nextLine(); }
{line}		{ ECHO; nextLine(); }
"+"		{ ECHO; return(ADDOP); }
"*"		{ ECHO; return(MULOP); }
"&"		{ ECHO; return(ANDOP); }
"<"		{ ECHO; return(RELOP); }
"=>"		{ ECHO; return(ARROW); }
begin		{ ECHO; return(BEGIN_); }
case		{ ECHO; return(CASE); }
character	{ ECHO; return(CHARACTER); }
end		{ ECHO; return(END); }
endswitch	{ ECHO; return(ENDSWITCH); }
function	{ ECHO; return(FUNCTION); }
integer		{ ECHO; return(INTEGER); }
is		{ ECHO; return(IS); }
list		{ ECHO; return(LIST); }
of		{ ECHO; return(OF); }
others		{ ECHO; return(OTHERS); }
real		{ ECHO; return(REAL); }
returns		{ ECHO; return(RETURNS); }
switch		{ ECHO; return(SWITCH); }
when		{ ECHO; return(WHEN); }

{id}		{ ECHO; yylval.iden = (CharPtr)malloc(yyleng + 1); 
			strcpy(yylval.iden, yytext); return(IDENTIFIER);}
{dec}		{ ECHO; yylval.type = INT_TYPE; return(INT_LITERAL); }
{real}		{ ECHO; yylval.type = REAL_TYPE; return(REAL_LITERAL); }
{char}		{ ECHO; yylval.type = CHAR_TYPE; return(CHAR_LITERAL); }
{punc}		{ ECHO; return(yytext[0]); }
.		{ ECHO; appendError(LEXICAL, yytext); }
%%
