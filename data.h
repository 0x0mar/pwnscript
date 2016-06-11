#ifndef DATA_H
#define DATA_H
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// TODO: implement big integer/big float
typedef struct {
    int *data;
    int size;
} bigi;

bigi *bigi_new();
bigi *bigi_fromstr(char *s);
bigi *bigi_tostr(bigi *a);
bigi *bigi_add(bigi *a, bigi *b);
bigi *bigi_multiply(bigi *a, bigi *b);
bigi *bigi_divide(bigi *a, bigi *b);

/////

typedef struct {
    enum {BIGI, BIGF, LONG, DOUB} type;
    void *data;
} num_t;

typedef struct {
    char *data;
    size_t len;
    size_t size;
} str_t;

// NUMBERS
num_t *numd_new(double v);
num_t *numl_new(long v);
void num_free(num_t *n);

// STRING
str_t *str_new(char *s);
void str_free(str_t *s);

#endif // DATA_H
