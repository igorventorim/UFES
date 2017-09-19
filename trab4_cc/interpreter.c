#include <stdio.h>
#include <stdlib.h>
#include "interpreter.h"
#include "tables.h"
#include "string.h"

extern SymTable *ft;
extern SymTable *vt;
extern LitTable *lt;

// Data stack -----------------------------------------------------------------

#define STACK_SIZE 100

int stack[STACK_SIZE];
int sp; // stack pointer

void push(int x) {
    stack[++sp] = x;
}

int pop() {
    return stack[sp--];
}

void init_stack() {
    for (int i = 0; i < STACK_SIZE; i++) {
        stack[i] = 0;
    }
    sp = -1;
}

void print_stack() {
    printf("*** STACK: ");
    for (int i = 0; i <= sp; i++) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

// ----------------------------------------------------------------------------

// Variables memory -----------------------------------------------------------

#define MEM_SIZE 100

int* mem[MEM_SIZE];

void alloc_svar(int addr) {
    mem[addr] = (int*) malloc(sizeof(int));
}

void alloc_cvar(int addr,int size) {
    mem[addr] = (int*) malloc(size*sizeof(int));
}

void store_svar(int addr, int val) {
    *(mem[addr]) = val;
}

void store_cvar(int addr,int index,int val) {
    mem[addr][index] = val;
}

int load_svar(int addr) {
    return *(mem[addr]);
}

int load_cvar(int addr,int index) {
    return mem[addr][index];
}

void init_mem() {

    int addr;

    for (addr = 0; addr < MEM_SIZE; addr++) {
        mem[addr] = NULL;
    }
}

void free_mem() {

    int addr;

    for (addr = 0; addr < MEM_SIZE; addr++) {
       
        if(mem[addr] != NULL) {
            free(mem[addr]);
        }

    }

}

// ----------------------------------------------------------------------------

// #define TRACE
#ifdef TRACE
#define trace(msg) printf("TRACE: %s\n", msg);
#else
#define trace(msg) 
#endif

void rec_run_ast(AST *ast);
char *replace_str(char *str, char *orig, char *rep);


void run_func_list(AST *ast)
{
    trace("func_list")
    int tam = get_child_count(ast);

    for(int i=0;i < tam-1;i++) 
    {
        AST* func_pointer = get_child(ast, i);
        int idx = get_data(get_child(ast,i));
        insert_func_pointer(ft,idx,func_pointer);
    }

    rec_run_ast(get_child(ast, tam-1));
}

void run_func_decl(AST *ast)
{
    trace("func_decl")
    rec_run_ast(get_child(ast,0));
    rec_run_ast(get_child(ast,1));
}

void run_func_header(AST *ast)
{
    trace("func_header");
    rec_run_ast(get_child(ast, 2));
}

void run_func_body(AST *ast)
{
    trace("func_body");
    rec_run_ast(get_child(ast,0));
    rec_run_ast(get_child(ast,1)); 
}

void run_var_list(AST *ast)
{
    trace("var_list")
    AST* var;
    int tam, idx;

    for(int i=0;i < get_child_count(ast);i++) {
        var = get_child(ast,i);
        switch(get_kind(var)) 
        {
            case SVAR_NODE:
                alloc_svar(get_data(var));
                break;
            case CVAR_NODE:
                tam = get_data(get_child(var,0));
                idx = get_data(var);
                alloc_cvar(idx,tam);
                break;
            default:
                exit(1);
        }
    }
}

void run_svar(AST *ast) {
    trace("svar")
    int idx = get_data(ast);
    push(load_svar(idx));
}

void run_cvar(AST *ast) {
    trace("cvar")
    rec_run_ast(get_child(ast,0));
    int idx = get_data(ast);
    push(load_cvar(idx,pop()));
}

void run_param_list(AST *ast)
{
    trace("param_list");
    int idx,tam,value;
    for (int i = 0; i < get_child_count(ast); i++) {
        AST* child = get_child(ast, i);
        idx = get_data(child);
         switch(get_kind(child)) 
         {
            case SVAR_NODE:
                value = pop();
                alloc_svar(idx);
                store_svar(idx, value);
                break;
            case CVAR_NODE:
                if(get_child_count(child)) 
                {
                    tam = get_data(get_child(child,0));
                    alloc_cvar(idx,tam);
                     for(int j = 0; j < tam; j++)
                     {
                        store_cvar(idx,j,pop());
                     }
                 }
                break;
            default:
                exit(1);
        } 
        
    }
}



void run_block(AST *ast)
{
    trace("block");
    int tam = get_child_count(ast);
    for(int i=0;i < tam;i++) {
        rec_run_ast(get_child(ast,i));
    }

}

void run_fcall(AST *ast)
{
    trace("func_call");
    rec_run_ast(get_child(ast, 0)); 
    int idx = get_data(ast);
    AST* func_pointer = get_func_pointer(ft, idx);
    rec_run_ast(func_pointer);
}

void run_arg_list(AST *ast)
{
    trace("arg_list");
    int tam = get_child_count(ast);
    for (int i = tam-1; i >= 0; i--)
    {
        rec_run_ast(get_child(ast, i));
    }
}

void run_if(AST *ast)
{
    trace("if");
    rec_run_ast(get_child(ast, 0));
    int test = pop();
    if (test == 1) {
        rec_run_ast(get_child(ast, 1));
    } else if (test == 0 && get_child_count(ast) == 3) {
        rec_run_ast(get_child(ast, 2));
    }
}

void run_while(AST *ast)
{
    trace("while");
    int again = 1;
    while (again) {
        rec_run_ast(get_child(ast, 1)); // Run test.
        rec_run_ast(get_child(ast, 0)); // Run body.
        again = pop();
    }
}

void run_assign(AST *ast) {
    trace("assign");
    int idx,vec_index,value;

    rec_run_ast(get_child(ast, 1));
    AST *assigned_var = get_child(ast, 0);

    switch(get_kind(assigned_var)) {
        case SVAR_NODE:
            idx = get_data(assigned_var);
            value = pop();
            store_svar(idx, value);
            break;
        case CVAR_NODE:
            rec_run_ast(get_child(assigned_var,0));
            idx = get_data(assigned_var);
            vec_index = pop();
            value = pop();
            store_cvar(idx,vec_index,value);
            break;
        default:
            exit(1);
    }
}

void run_write(AST *ast) {
    trace("write");
    int idx = get_data(get_child(ast, 0));
    char* string = get_literal(lt,idx);
    char* ptr = strtok(string,"\"");
    printf("%s",replace_str(ptr,"\\n","\n"));

}

void run_num(AST *ast) {
    trace("num");
    push(get_data(ast));
}

void run_input(AST *ast)
{
    trace("input");
    int x;
    printf("input: ");
    scanf("%d", &x);
    push(x);
}

void run_output(AST *ast)
{
    trace("output");
    rec_run_ast(get_child(ast, 0));
    int x = pop();
    printf("%d", x);   
}

void run_return(AST *ast) {
    trace("return");
    if(get_child_count(ast) <= 0)
    {
        return;
    }else{
        rec_run_ast(get_child(ast, 0));
    } 

}

#define bin_op() \
    rec_run_ast(get_child(ast, 0)); \
    rec_run_ast(get_child(ast, 1)); \
    int r = pop(); \
    int l = pop()

void run_plus(AST *ast) {
    trace("plus");
    bin_op();
    push(l + r);
}

void run_minus(AST *ast) {
    trace("minus");
    bin_op();
    push(l - r);
}

void run_times(AST *ast) {
    trace("times");
    bin_op();
    push(l * r);
}

void run_over(AST *ast) {
    trace("over");
    bin_op();
    push((int) l / r);
}

void run_lt(AST *ast) {
    trace("lt");
    bin_op();
    push(l < r);
}

void run_eq(AST *ast) {
    trace("eq");
    bin_op();
    push(l == r);
}

void run_le(AST *ast) {
    trace("le");
    bin_op();
    push(l <= r);
}

void run_gt(AST *ast) {
    trace("gt");
    bin_op();
    push(l > r);
}

void run_ge(AST *ast) {
    trace("ge");
    bin_op();
    push(l >= r);
}

void run_neq(AST *ast) {
    trace("neq");
    bin_op();
    push(l != r);
}

void rec_run_ast(AST *ast) {
    switch(get_kind(ast)) {
        case FUNC_LIST_NODE:    //
            run_func_list(ast); 
            break;
        case FUNC_DECL_NODE:    //
            run_func_decl(ast); 
            break;
        case FUNC_HEADER_NODE:  // 
            run_func_header(ast);
            break;
        case FUNC_BODY_NODE: 
            run_func_body(ast); //
            break;
        case VAR_LIST_NODE: 
            run_var_list(ast);  //
            break;
        case PARAM_LIST_NODE: 
            run_param_list(ast);
            break;
        case BLOCK_NODE:        //
            run_block(ast);
            break;
        case USER_FCALL_NODE:   //
            run_fcall(ast);
            break;
        case IF_NODE:           //
            run_if(ast);
            break;
        case WHILE_NODE:        //
            run_while(ast); 
            break;
        case ASSIGN_NODE:       // 
            run_assign(ast);
            break;
        case ARG_LIST_NODE:     //
            run_arg_list(ast);
            break;
        case WRITE_NODE:        //
            run_write(ast);
            break;
        case PLUS_NODE:         //
            run_plus(ast);
            break;
        case MINUS_NODE:        //
            run_minus(ast);
            break;
        case TIMES_NODE:        //
            run_times(ast);
            break;
        case OVER_NODE:         //
            run_over(ast);
            break;
        case LT_NODE:           //
            run_lt(ast); 
            break;
        case EQ_NODE:           //
            run_eq(ast);
            break;
        case LE_NODE:           //
            run_le(ast); 
            break;
        case GT_NODE:           //
            run_gt(ast);        
            break;
        case GE_NODE:           //
            run_ge(ast);
            break;
        case NEQ_NODE:          //
            run_neq(ast);
            break;
        case NUM_NODE:          //
            run_num(ast);
            break;
        case OUTPUT_NODE:       //
            run_output(ast);
            break;
        case INPUT_NODE:        //
            run_input(ast);
            break;
        case RETURN_NODE:      //
            run_return(ast);
            break;
        case CVAR_NODE:        //
            run_cvar(ast);
            break;
        case SVAR_NODE:        //
            run_svar(ast);
            break;
        default:
            fprintf(stderr, "Invalid kind: %s!\n", kind2str(get_kind(ast)));
            exit(1);
    }
}

/* Função para realizar replace nas strings */
char *replace_str(char *str, char *orig, char *rep)
{
  static char buffer[4096];
  char *p;

  if(!(p = strstr(str, orig))) 
    return str;

  strncpy(buffer, str, p-str);
  buffer[p-str] = '\0';

  sprintf(buffer+(p-str), "%s%s", rep, p+strlen(orig));

  return buffer;
}

void run_ast(AST *ast) {
    init_stack();
    init_mem();
    rec_run_ast(ast);
}
