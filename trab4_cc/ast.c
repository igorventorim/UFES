
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

#define CHILDREN_LIMIT 20

struct node {
    NodeKind kind;
    int data;
    int count;
    AST* child[CHILDREN_LIMIT];
};

AST* new_node(NodeKind kind, int data) {
    AST* node = malloc(sizeof * node);
    node->kind = kind;
    node->data = data;
    node->count = 0;
    for (int i = 0; i < CHILDREN_LIMIT; i++) {
        node->child[i] = NULL;
    }
    return node;
}

void add_child(AST *parent, AST *child) {
    if (parent->count == CHILDREN_LIMIT) {
        fprintf(stderr, "Cannot add another child!\n");
        exit(1);
    }
    parent->child[parent->count] = child;
    parent->count++;
}

AST* get_child(AST *parent, int idx) {
    return parent->child[idx];
}

AST* new_subtree(NodeKind kind, int child_count, ...) {
    if (child_count > CHILDREN_LIMIT) {
        fprintf(stderr, "Too many children as arguments!\n");
        exit(1);
    }

    AST* node = new_node(kind, 0);
    va_list ap;
    va_start(ap, child_count);
    for (int i = 0; i < child_count; i++) {
        add_child(node, va_arg(ap, AST*));
    }
    va_end(ap);
    return node;
}

NodeKind get_kind(AST *node) {
    return node->kind;
}

int get_data(AST *node) {
    return node->data;
}

int get_child_count(AST *node) {
    return node->count;
}

char* kind2str(NodeKind kind) {
    switch(kind) {
        case FUNC_LIST_NODE: return "func_list";
        case FUNC_DECL_NODE: return "func_decl";
        case FUNC_HEADER_NODE: return "func_header";
        case FUNC_BODY_NODE: return "func_body";
        case VAR_LIST_NODE: return "var_list";
        case PARAM_LIST_NODE: return "param_list";
        case BLOCK_NODE: return "block";
        case USER_FCALL_NODE: return "fcall";
        case IF_NODE: return "if";
        case WHILE_NODE: return "while";
        case ASSIGN_NODE: return "=";
        case ARG_LIST_NODE: return "arg_list";
        case WRITE_NODE: return "write" ;
        case PLUS_NODE: return "+";
        case MINUS_NODE: return "-";
        case TIMES_NODE: return "*";
        case OVER_NODE: return "/";
        case LT_NODE: return "<";
        case EQ_NODE: return "==";
        case LE_NODE: return "<=";
        case GT_NODE: return ">";
        case GE_NODE: return ">=";
        case NEQ_NODE: return "!=";
        case NUM_NODE: return "num";
        case ID_NODE: return "id";
        case STRING_NODE: return "string";
        case OUTPUT_NODE: return "output";
        case INT_NODE: return "int";
        case VOID_NODE: return "void";
        case INPUT_NODE: return "input";
        case RETURN_NODE: return "return";
        case CVAR_NODE: return "cvar";
        case SVAR_NODE: return "svar";
        default: return "ERROR!!";
    }
}

void print_node(AST *node, int level) {
    printf("%d: Node -- Addr: %p -- Kind: %s -- Data: %d -- Count: %d\n",
           level, node, kind2str(node->kind), node->data, node->count);
    for (int i = 0; i < node->count; i++) {
        print_node(node->child[i], level+1);
    }
}

void print_tree(AST *tree) {
    print_node(tree, 0);
}

void free_tree(AST *tree) {
    if (tree == NULL) return;
    for (int i = 0; i < tree->count; i++) {
        free_tree(tree->child[i]);
    }
    free(tree);
}


int nr;

int has_data(NodeKind kind) {
    if (kind == ID_NODE || kind == NUM_NODE || kind == STRING_NODE || kind == SVAR_NODE || kind == CVAR_NODE || kind == USER_FCALL_NODE) {
        return 1;
    } else {
        return 0;
    }
}

int print_node_dot(AST *node) {
    int my_nr = nr++;
    if (has_data(node->kind)) {
        printf("node%d[label=\"%s,%d\"];\n", my_nr, kind2str(node->kind), node->data);
    } else {
        printf("node%d[label=\"%s\"];\n", my_nr, kind2str(node->kind));
    }
    for (int i = 0; i < node->count; i++) {
        int child_nr = print_node_dot(node->child[i]);
        printf("node%d -> node%d;\n", my_nr, child_nr);
    }
    return my_nr;
}

void print_dot(AST *tree) {
    nr = 0;
    printf("digraph {\ngraph [ordering=\"out\"];\n");
    print_node_dot(tree);
    printf("}\n");
}
