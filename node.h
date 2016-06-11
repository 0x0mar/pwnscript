#ifndef NODE_H
#define NODE_H
#include <stdlib.h>

#define GOTO_END(nodes) while(nodes->next != NULL) nodes = nodes->next;

enum type {
    FNCALL,                 // function call
    FN,                     // function (anonymous)
    TABLE,                  // array/(dictionary) (taken from lua)
    NUM,                    // number
    STRING,                 // string
    ID,                     // identifier
};

typedef struct node_t {
    enum type t;

    union {
        char *s;                       // string value of token
        struct node_t *nodes;          // linked list of nodes
        struct {
            struct node_t *callers;    // linked list of nodes on left side
            struct node_t *callees;    // linked list of nodes on right side
        };
        struct {
            struct node_t *args;       // linked list of argument nodesj
            struct node_t *block;      // linked list of block
        };
    };

    struct node_t *next; // linked list
} node_t;

node_t *node_call(node_t *caller, node_t *callees);
node_t *node_fn(node_t *args, node_t *block);
node_t *node_table(node_t *nodes);
node_t *node_atom(enum type t, char *val); // create a number or ident
void node_add(node_t *nodes, node_t *n);
void node_free(node_t *n);

#endif // NODE_H
