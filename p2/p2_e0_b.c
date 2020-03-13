#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_fp.h"
#include "stack_types.h"
#include "node.h"

int main(){

    Node *n =NULL;
    Stack *snode =NULL;
    Stack *sstring=NULL;

    n=node_init();
    if(!n) return -1;

    node_setName(n, "first");
    node_setId(n, 111);
    node_setLabel(n, WHITE);

    snode=stack_init(node_free, node_copy, node_print);
    if(!snode) return -1;

    sstring=stack_init(string_free, string_copy, string_print);
    if(!sstring) return -1;

    stack_push(snode, (const void*)n);
    stack_push(sstring, (const void*)node_getName(n));

    node_setName(n, "second");
    node_setId(n, 222);

    stack_push(snode, (const void*)n);
    stack_push(sstring, (const void*)node_getName(n));
    fprintf(stdout, "Print Stack nodes: \n");
    stack_print(stdout, snode);
    fprintf(stdout, "Print Stack string: \n");
    stack_print(stdout, sstring);

    fprintf(stdout, "Poping nodes.... \n");
    while(stack_isEmpty(snode)==FALSE){

        node_print(stdout, (Node*)stack_pop(snode));
    }

    fprintf(stdout, "\nPoping nodes-names.... \n");
    while(stack_isEmpty(sstring)==FALSE){

        fprintf(stdout, " ", *(char *)stack_pop(sstring));
    }

    node_free(n);
    stack_free(snode);
    stack_free(sstring);

    return 0;
}
