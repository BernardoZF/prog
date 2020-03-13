#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_fp.h"
#include "stack_types.h"

int main(){
    char array[3]={'a', 'b', 'c'};
    Stack *s=NULL;
    int i;

    s=stack_init(char_free, char_copy, char_print);
    if(!s) return -1;

    for(i=0; i<3; i++){
        stack_push (s, &array[i]);
    }

    stack_print(stdout, s);

    fprintf(stdout, "Stack size: %ld\n", stack_size(s));

    while(stack_isEmpty(s)==FALSE){

        fprintf(stdout, "El elemento extraido: %c\n", *(char *)stack_pop(s));
    }

    fprintf(stdout, "Stack size: %ld\n", stack_size(s));

    stack_free(s);

    return 0;
}
