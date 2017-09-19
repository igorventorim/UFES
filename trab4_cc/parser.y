
/* Options to bison */
// File name of generated parser.
%output "parser.c"
// Produces a 'parser.h'
%defines "parser.h"
// Give proper error messages when a syntax error is found.
%define parse.error verbose
// Enable LAC (lookahead correction) to improve syntax error handling.
%define parse.lac full

// Enable the trace option so that debugging is possible.
%define parse.trace

%{
#include <stdio.h>
#include <stdlib.h>
#include "tables.h"
#include "ast.h"
#include "interpreter.h"

void check_var();
void new_var();
void check_function();
void new_function();
void check_arity(int value);

int yylex(void);
void yyerror(char const *s);


extern int yylineno;
extern char *yytext;
char *yytext2 = "";
char *yytext3;
int scope = 0;
int aridade = 0;

AST *ast;

LitTable *lt;
SymTable *vt;
SymTable *ft;
%}
%define api.value.type {struct node*}

%token NUM ID IF ELSE WHILE WRITE RETURN ASSIGN SEMI INPUT OUTPUT COMMA
%token LPAREN RPAREN LBRACK RBRACK LBRACE RBRACE
%token STRING INT VOID
%left LT LE GT GE EQ NEQ
%left PLUS MINUS
%left TIMES OVER

%%

program: func_decl_list { ast = $1; };

func_decl_list: 
	func_decl_list func_decl { add_child($1,$2); $$ = $1;}
|	func_decl { $$ = new_subtree(FUNC_LIST_NODE,1, $1);}
;

func_decl: func_header func_body {scope++; $$ = new_subtree(FUNC_DECL_NODE,2,$1,$2);};

func_header: ret_type ID {new_function();$2 = new_node(ID_NODE,add_function(ft,yytext2,yylineno,aridade));} LPAREN params RPAREN { set_arity(ft,get_data($2),aridade); aridade = 0;$$ = new_subtree(FUNC_HEADER_NODE,3,$1,$2,$5);  };

func_body: LBRACE opt_var_decl opt_stmt_list RBRACE  { $$ = new_subtree(FUNC_BODY_NODE,2,$2,$3); } ;

opt_var_decl: 
	%empty { $$ = new_node(VAR_LIST_NODE, 0);}
| 	var_decl_list { $$ = $1;}
;

opt_stmt_list:
	%empty { $$ = new_node(BLOCK_NODE, 0); }
|	stmt_list { if(get_kind($$) != BLOCK_NODE){ $$ = new_subtree(BLOCK_NODE,1,$1);}else{ $$ = $1;} }
;

ret_type:
	INT { $$ = new_node(INT_NODE, 0);}
|	VOID { $$ = new_node(VOID_NODE, 0);}
;

params:
	VOID { $$ = new_node(PARAM_LIST_NODE, 0);}
|	param_list { $$ = $1; aridade = get_child_count($1); }
;

param_list: 
	param_list COMMA param { add_child($1, $3); $$ = $1;}
|	param { $$ = new_subtree(PARAM_LIST_NODE,1,$1); }
;

param: 
	INT ID { new_var(); $$ =  new_node(SVAR_NODE, add_var(vt, yytext2, yylineno,scope)); }
|	INT ID { new_var(); $2 = new_node(CVAR_NODE, add_var(vt, yytext2, yylineno,scope)); } LBRACK RBRACK {$$ = $2;}
;
 
var_decl_list: 
	var_decl_list var_decl { add_child($1,$2); $$ = $1;}
|	var_decl { $$ = new_subtree(VAR_LIST_NODE,1,$1); }
;

var_decl: 
	INT ID{new_var(); $2 = new_node(SVAR_NODE, add_var(vt, yytext2, yylineno,scope));} SEMI { $$ = $2;}
|	INT ID{new_var(); $2 = new_node(CVAR_NODE, add_var(vt, yytext2, yylineno,scope));} LBRACK NUM RBRACK SEMI {add_child($2,$5);$$ = $2;  }
;

stmt_list:
	stmt_list stmt { if(get_kind($$) != BLOCK_NODE){ $$ = new_subtree(BLOCK_NODE,2,$1,$2);}else{ add_child($1,$2),$$ = $1;} }
|	stmt { $$ = $1; }
;

stmt: 
	assign_stmt { $$ = $1; }
|	if_stmt { $$ = $1; }
|	while_stmt { $$ = $1; }
|	return_stmt { $$ = $1; }
|	func_call SEMI { $$ = $1; }
;

assign_stmt: lval ASSIGN arith_expr SEMI { $$ = new_subtree(ASSIGN_NODE,2,$1,$3); };

lval : 
	ID {check_var(); $1 = new_node(SVAR_NODE, lookup_var(vt, yytext2,scope)); $$ = $1;}
|	ID LBRACK {check_var(); $1 = new_node(CVAR_NODE, lookup_var(vt, yytext2,scope)); } NUM RBRACK { add_child($1,$4), $$ = $1; }
|	ID LBRACK {check_var(); $1 = new_node(CVAR_NODE, lookup_var(vt, yytext3,scope));} ID { check_var(); $4 = new_node(SVAR_NODE, lookup_var(vt, yytext2,scope));} RBRACK { add_child($1,$4), $$ = $1; }

;

if_stmt: 
	IF LPAREN bool_expr RPAREN block	{ $$ = new_subtree(IF_NODE,2,$3,$5); }
|	IF LPAREN bool_expr RPAREN block ELSE block { $$ = new_subtree(IF_NODE,3,$3,$5,$7);}
;

block: LBRACE opt_stmt_list RBRACE { $$ = $2; } ;

while_stmt: WHILE LPAREN bool_expr RPAREN block { $$ = new_subtree(WHILE_NODE,2,$3,$5); };

return_stmt: 
	RETURN SEMI {$$ = new_node(RETURN_NODE, 0);}
|	RETURN arith_expr SEMI { $$ = new_node(RETURN_NODE, 0);add_child($$,$2);}
;

func_call: 
	output_call { $$ = $1;}
|	write_call	{ $$ = $1;}
|	user_func_call { $$ = $1;}
;

input_call: INPUT LPAREN RPAREN { $$  = new_node(INPUT_NODE, 0);};

output_call: OUTPUT LPAREN arith_expr RPAREN{ $$ = new_subtree(OUTPUT_NODE, 1, $3);};

write_call: WRITE LPAREN STRING RPAREN{ $$ = new_subtree(WRITE_NODE, 1, $3); };

user_func_call: ID{ check_function(); aridade = get_arity(ft,lookup_function(ft,yytext2));$1 = new_node(ID_NODE,lookup_function(ft,yytext2));} LPAREN opt_arg_list RPAREN{check_arity(get_child_count($4)); $$ = new_subtree(USER_FCALL_NODE,1,$4); } ;

opt_arg_list: 
	%empty { $$ = new_node(ARG_LIST_NODE,0);}
|	arg_list { $$ = $1; }
;

arg_list:
	arg_list COMMA arith_expr {  add_child($1,$3); $$ = $1;  }
|	arith_expr	{ $$ = new_subtree(ARG_LIST_NODE,1,$1); }
;

bool_expr:
	arith_expr EQ arith_expr {$$ = new_subtree(EQ_NODE,2,$1,$3); }
|	arith_expr NEQ arith_expr {$$ = new_subtree(NEQ_NODE,2,$1,$3); }
|	arith_expr GE arith_expr {$$ = new_subtree(GE_NODE,2,$1,$3); }
| 	arith_expr GT arith_expr {$$ = new_subtree(GT_NODE,2,$1,$3); }
|	arith_expr LE arith_expr {$$ = new_subtree(LE_NODE,2,$1,$3); }
|	arith_expr LT arith_expr {$$ = new_subtree(LT_NODE,2,$1,$3); }
;

arith_expr:
	NUM	{ $$ = $1; }
|	user_func_call { $$ = $1; }
|	input_call { $$ = $1; }
|	lval { $$ = $1; }
|	LPAREN arith_expr RPAREN	{$$ = $2; }
|	arith_expr PLUS arith_expr	{$$ = new_subtree(PLUS_NODE,2,$1,$3); }
|	arith_expr MINUS arith_expr	{$$ = new_subtree(MINUS_NODE,2,$1,$3); }
|	arith_expr TIMES arith_expr {$$ = new_subtree(TIMES_NODE,2,$1,$3); }
|	arith_expr OVER arith_expr	{$$ = new_subtree(OVER_NODE,2,$1,$3); }



%%

void check_var() {
    int idx = lookup_var(vt, yytext2,scope);
    if (idx == -1) {
        printf("SEMANTIC ERROR (%d): variable '%s' was not declared.\n",
                yylineno, yytext2);
        exit(1);
    }
}

void new_var() {
    int idx = lookup_var(vt, yytext2,scope);
    if (idx != -1) {
        printf("SEMANTIC ERROR (%d): variable '%s' already declared at line %d.\n",
                yylineno, yytext2, get_line(vt, idx));
        exit(1);
    }

    // add_var(vt, yytext, yylineno,scope);
}


void check_function() {
    int idx = lookup_function(ft, yytext2);
    if (idx == -1) {
        printf("SEMANTIC ERROR (%d): function '%s' was not declared.\n",
                yylineno, yytext2);
        exit(1);
    }

}

void check_arity(int value)
{
    if( aridade != value)
    {
        printf("SEMANTIC ERROR (%d): function '%s' was called with %d arguments but declared with %d parameters.\n", yylineno, yytext2,value,aridade);
        exit(1);
    }
    aridade = 0;
}

void new_function() {
    int idx = lookup_function(ft, yytext2);
    if (idx != -1) {
        printf("SEMANTIC ERROR (%d): function '%s' already declared at line %d.\n",
                yylineno, yytext2, get_line(vt, idx));
        exit(1);
    }
    // add_function(vt, yytext, yylineno,scope);
}



// Error handling.
void yyerror (char const *s) {
	extern int yylineno;
	printf("PARSE ERROR (%d): %s\n", yylineno, s);
	exit(1);
}

int main() {
	
	yydebug = 0;

	lt = create_lit_table();
	vt = create_sym_table();
	ft = create_sym_table();	
	
    if (yyparse() == 0) {
        stdin = fopen(ctermid(NULL), "r");
        run_ast(ast);
    }

	//printf("\n\n");
    //print_lit_table(lt); printf("\n\n");
    // print_sym_table(vt); printf("\n\n");
    // print_function_table(ft);
    // print_dot(ast);
    // print_tree(ast);

	// printf("PARSE SUCCESSFUL!\n\n");
	free_lit_table(lt);
    free_sym_table(vt);
    free_sym_table(ft);
    free_tree(ast);
    free(yytext2);

    return 0;
}
