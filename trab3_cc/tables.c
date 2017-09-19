
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tables.h"

// Literals Table
// ----------------------------------------------------------------------------

#define LITERAL_MAX_SIZE 128
#define LITERALS_TABLE_MAX_SIZE 100

struct lit_table {
    char t[LITERALS_TABLE_MAX_SIZE][LITERAL_MAX_SIZE];
    int size;
};

LitTable* create_lit_table() {
    LitTable *lt = malloc(sizeof * lt);
    lt->size = 0;
    return lt;
}

int add_literal(LitTable* lt, char* s) {
    for (int i = 0; i < lt->size; i++) {
        if (strcmp(lt->t[i], s) == 0) {
            return i;
        }
    }
    strcpy(lt->t[lt->size], s);
    int idx_added = lt->size;
    lt->size++;
    return idx_added;
}

char* get_literal(LitTable* lt, int i) {
    return lt->t[i];
}

void print_lit_table(LitTable* lt) {
    printf("Literals table:\n");
    for (int i = 0; i < lt->size; i++) {
        printf("Entry %d -- %s\n", i, get_literal(lt, i));
    }
}

void free_lit_table(LitTable* lt) {
    free(lt);
}

// Var Table and Function Table
// ----------------------------------------------------------------------------

#define SYMBOL_MAX_SIZE 128
#define SYMBOL_TABLE_MAX_SIZE 100

typedef struct {
  char name[SYMBOL_MAX_SIZE];
  int line;
  int scope;
  int arity;
} Entry;

struct sym_table {
    Entry t[SYMBOL_TABLE_MAX_SIZE];
    int size;
};

SymTable* create_sym_table() {
    SymTable *st = malloc(sizeof * st);
    st->size = 0;
    return st;
}

int lookup_var(SymTable* st, char* s, int scope) {
    for (int i = 0; i < st->size; i++) {
        if (strcmp(st->t[i].name, s) == 0 && st->t[i].scope == scope)  {
            return i;
        }
    }
    return -1;
}

int lookup_function(SymTable* st, char* s) {
    for (int i = 0; i < st->size; i++) {
        if (strcmp(st->t[i].name, s) == 0)  {
            return i;
        }
    }
    return -1;
}

int add_var(SymTable* st, char* s, int line,int scope) {
    strcpy(st->t[st->size].name, s);
    st->t[st->size].line = line;
    st->t[st->size].scope = scope;
    int idx_added = st->size;
    st->size++;
    return idx_added;
}

int add_function(SymTable* st, char* s, int line,int arity) {
    strcpy(st->t[st->size].name, s);
    st->t[st->size].line = line;
    st->t[st->size].arity = arity;
    int idx_added = st->size;
    st->size++;
    return idx_added;
}

char* get_name(SymTable* st, int i) {
    return st->t[i].name;
}

int get_line(SymTable* st, int i) {
    return st->t[i].line;
}

int get_scope(SymTable* st, int i)
{   
    return st->t[i].scope;
}

int get_arity(SymTable* st, int i)
{   
    return st->t[i].arity;
}

void set_arity(SymTable* st, int i, int value)
{
    st->t[i].arity = value;
}

void print_sym_table(SymTable* st) {
    printf("Variables table:\n");
    for (int i = 0; i < st->size; i++) {
         printf("Entry %d -- name: %s, line: %d, scope: %d\n", i, get_name(st, i), get_line(st, i), get_scope(st,i));
    }
}

void free_sym_table(SymTable* st) {
    free(st);
}


void print_function_table(SymTable* st) {
    printf("Function table:\n");
    for (int i = 0; i < st->size; i++) {
         printf("Entry %d -- name: %s, line: %d, arity: %d\n", i, get_name(st, i), get_line(st, i),get_arity(st,i));
    }
}