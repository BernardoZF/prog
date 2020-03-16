#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "element.h"

#define MAXSTACK 1024

struct _Stack {
    int top;
    Element * item[MAXSTACK];
};

Stack * stack_init (){
    Stack *s = NULL;
    int i;
    s=(Stack *)malloc(sizeof(Stack));
    if(!s) return NULL;

    s->top = 0;

    for(i=0; i<MAXSTACK; i++){
        s->item[i] = NULL;
    }

    return s;
}

void stack_free(Stack *s){
    int i;

    if(!s) return;

    for(i=0; i<MAXSTACK; i++){
        element_free(s->item[i]);
    }

    free(s);

    return;

}
Status stack_push(Stack *s, const Element *ele){
    if(!s || !ele) return ERROR;

    if(stack_isFull(s) == TRUE) return ERROR;

    s->item[s->top] = element_copy(ele);

    if(s->item[s->top] == NULL) return ERROR;

    s->top++;

    return OK;
}

Element * stack_pop(Stack *s){
    Element *ele=NULL;

    if(!s) return NULL;

    if(stack_isEmpty(s)==TRUE) return NULL;

    s->top--;
    ele=s->item[s->top];
    s->item[s->top]=NULL;

    return ele;
}
Element * stack_top(const Stack *);
Bool stack_isEmpty(const Stack *s){
    if(!s) return FALSE;

    if(s->top==0) return TRUE;

    return FALSE;
}
Bool stack_isFull(const Stack *s){
    if(!s) return FALSE;

    if(s->top==MAXSTACK) return TRUE;

    return FALSE;
}
int stack_print(FILE* pf, const Stack* s){
    int i;
    int k=0;

    if(!pf || !s) return 0;

    for(i=0; i<s->top; i++){
        k += element_print(pf, s->item[i]);
    }

    return k;
}
