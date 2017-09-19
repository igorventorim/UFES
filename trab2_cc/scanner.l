/* Options to flex */
%option outfile="scanner.c"
/* Tell flex to don't declare this functions to avoid compilation warnings.
 * They are not necessary for the kind of scanner we need.
**/
%option noyywrap
%option nounput
%option noinput
/* Tell flex to automatically increment the yylineno variable every time a
 * '\n' is read.
**/
%option yylineno

%{
#include "parser.h"
#include <stdlib.h>	

void process_error();
%}

number      [0-9]+
identifier  [a-zA-Z][a-z0-9A-Z]*
string 		"\""(\\.|[^"])*"\""
ignore      [ \t\n]+
comment 	"//".*

/* ESTADO ESPECIAL QUE ESTARÁ ENQUANTO ESTIVER LENDO DENTRO DE COMENTÁRIOS*/
%x          MLC

%%

"/*"            { BEGIN(MLC); } /* Enter special state. */
<MLC>"*/"       { BEGIN(INITIAL); } /* Go back to normal state. */
<MLC>.|\n       { } /* Ignore everything that is inside a comment. */
{comment}		{ } /* Get line comments */

"else"          { return ELSE; }
"if"            { return IF; }
"input"         { return INPUT; }
"int"          	{ return INT; }
"output"        { return OUTPUT; }
"return"        { return RETURN; }
"void"          { return VOID; }
"while"         { return WHILE; }
"write"         { return WRITE; }

"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return TIMES; }
"/"             { return OVER; }
"<"             { return LT; }
"<="            { return LE; }
">"             { return GT; }
">="            { return GE; }
"=="            { return EQ; }
"!="            { return NEQ; }
"="             { return ASSIGN; }

";"             { return SEMI; }
","             { return COMMA; }
"("             { return LPAREN; }
")"             { return RPAREN; }
"["             { return LBRACK; }
"]"             { return RBRACK; }
"{"             { return LBRACE; }
"}"             { return RBRACE; }

{number}        { return NUM; }
{identifier}    { return ID; }
{string}		{ return STRING;}
{ignore}		{}

.               { process_error(); } /* Be sure to keep this as the last rule. */

%%

void process_error() {
    printf("SCANNING ERROR (%d): Unknown symbol %s\n", yylineno, yytext);
    exit(1);
}

