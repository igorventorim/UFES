#ifndef AST_H
#define AST_H

typedef enum {
    FUNC_LIST_NODE,
    FUNC_DECL_NODE,
    FUNC_HEADER_NODE,
    FUNC_BODY_NODE,
    VAR_LIST_NODE,
    PARAM_LIST_NODE,
    BLOCK_NODE,
    OUTPUT_NODE,
    USER_FCALL_NODE,
    STMT_LIST_NODE,
    IF_NODE,
    WHILE_NODE,
    ASSIGN_NODE,
    ARG_LIST_NODE,
    READ_NODE,
    WRITE_NODE,
    PLUS_NODE,
    MINUS_NODE,
    TIMES_NODE,
    OVER_NODE,
    LT_NODE,
    EQ_NODE,
    LE_NODE,
    GT_NODE,
    GE_NODE,
    NEQ_NODE,
    NUM_NODE,
    ID_NODE,
    STRING_NODE,
    INT_NODE,
    VOID_NODE,
    INPUT_NODE,
    RETURN_NODE,
    CVAR_NODE,
    SVAR_NODE
} NodeKind;

struct node;

typedef struct node AST;

AST* new_node(NodeKind kind, int data);

void add_child(AST *parent, AST *child);
AST* get_child(AST *parent, int idx);

AST* new_subtree(NodeKind kind, int child_count, ...);

NodeKind get_kind(AST *node);
char* kind2str(NodeKind kind);
int get_data(AST *node);
int get_child_count(AST *node);

void print_tree(AST *ast);
void print_dot(AST *ast);

void free_tree(AST *ast);

#endif
