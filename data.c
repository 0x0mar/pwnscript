#include "data.h"

num_t *numd_new(double v) {
    num_t *r = malloc(sizeof(num_t));
    r->type = DOUB;
    memcpy(r->data, &v, sizeof(double));
    return r;
}

num_t *numl_new(long v) {
    num_t *r = malloc(sizeof(num_t));
    r->type = LONG;
    memcpy(r->data, &v, sizeof(long));
    return r;
}

void num_free(num_t *n) {
    free(n->data);
    free(n);
}

str_t *str_new(char *s) {
    size_t size = 32; // default size
    str_t *r = malloc(sizeof(str_t));
    r->len = strlen(s);
    if(r->len > size)
	r->size = r->len * 2;
    else
	r->size = size;
    r->data = malloc(size);

    strncpy(r->data, s, r->size);
}

void str_free(str_t *s) {
    free(s->data);
    free(s);
}
