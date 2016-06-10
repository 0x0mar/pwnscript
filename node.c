#include "node.h"

static node_t *new(enum type t) {
    node_t *r = malloc(sizeof(node_t));
    r->t = t;
    r->next = NULL;
    return r;
}

node_t *node_call(node_t *callers, node_t *callees) {
    node_t *r = new(FNCALL);
    r->callers = callers;
    r->callees = callees;
    return r;
}

node_t *node_fn(node_t *args, node_t *block) {
    node_t *r = new(FN);
    r->nodes = block;
    return r;
}

node_t *node_table(node_t *nodes) {
    node_t *r = new(FN);
    r->nodes = nodes;
    return r;
}

node_t *node_atom(enum type t, char *val) {
    node_t *r = new(t);
    r->s = val;
    return r;
}

void node_add(node_t *nodes, node_t *n) {
    GOTO_END(nodes);
    nodes->next = n;
}
