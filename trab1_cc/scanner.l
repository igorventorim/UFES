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
#include "token.h"

void process_token(TokenType);
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

"else"          { process_token(ELSE); }
"if"            { process_token(IF); }
"input"         { process_token(INPUT); }
"int"          	{ process_token(INT); }
"output"        { process_token(OUTPUT); }
"return"        { process_token(RETURN); }
"void"          { process_token(VOID); }
"while"         { process_token(WHILE); }
"write"         { process_token(WRITE); }

"+"             { process_token(PLUS); }
"-"             { process_token(MINUS); }
"*"             { process_token(TIMES); }
"/"             { process_token(OVER); }
"<"             { process_token(LT); }
"<="            { process_token(LE); }
">"             { process_token(GT); }
">="            { process_token(GE); }
"=="            { process_token(EQ); }
"!="            { process_token(NEQ); }
"="             { process_token(ASSIGN); }

";"             { process_token(SEMI); }
","             { process_token(COMMA); }
"("             { process_token(LPAREN); }
")"             { process_token(RPAREN); }
"["             { process_token(LBRACK); }
"]"             { process_token(RBRACK); }
"{"             { process_token(LBRACE); }
"}"             { process_token(RBRACE); }

{number}        { process_token(NUM); }
{identifier}    { process_token(ID); }
{string}		{ process_token(STRING);}
{ignore}		{}

.               { process_error(); } /* Be sure to keep this as the last rule. */

%%

void process_token(TokenType tk) {
    printf("%d: %s -> %s\n", yylineno, yytext, TOKEN_TYPE_STRING[tk]);
}

void process_error() {
    printf("%d: %s -> %s\n", yylineno, yytext, "UNKNOWN");
}

int main(void) {
    yylex();
    return 0;
}
