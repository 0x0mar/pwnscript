#include <stdio.h>
#include "node.h"

extern node_t *prog;
extern int yyparse();

int main() {
    if(yyparse() == 0)
        printf("%i\n", prog->t);
    return 0;
}
