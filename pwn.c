#include <stdio.h>
#include "node.h"

extern node_t *prog;
extern int yyparse();

void dump_node(node_t *node, int level) {
    if(!node) return;
    do {
#define SPACELEVEL for(i = 0; i < level * 3; i++) putchar(' ');
        int i = 0;
        switch(node->t) {
            case FNCALL:
                SPACELEVEL;
                puts("FNCALL {");
                SPACELEVEL;
                puts("   CALLERS {");
                dump_node(node->callers, level + 2);
                SPACELEVEL;
                puts("   }");
                SPACELEVEL;
                puts("   CALLEES {");
                dump_node(node->callees, level + 2);
                SPACELEVEL;
                puts("   }");
                SPACELEVEL;
                puts("}");
                break;
            case FN:
                SPACELEVEL;
                puts("FN {");
                SPACELEVEL;
                puts("   ARGS {");
                dump_node(node->args, level + 2);
                SPACELEVEL;
                puts("   }");
                SPACELEVEL;
                puts("   BLOCK {");
                dump_node(node->block, level + 2);
                SPACELEVEL;
                puts("   }");
                SPACELEVEL;
                puts("}");
                break;
            case NUM:
                SPACELEVEL;
                printf("NUM { %s }\n", node->s);
                break;
            case ID:
                SPACELEVEL;
                printf("ID { %s }\n", node->s);
                break;
        }
    } while (node = node->next);
}

int main() {
    if(yyparse() == 0)
        dump_node(prog, 0);
    return 0;
}
