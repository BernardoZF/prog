#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "element.h"
#include "types.h"

#define MAXSTACK 1024

struct _Stack 
{
    int top;
    Element * item[MAXSTACK];
};

Stack * stack_init ()
{
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

void stack_free(Stack *s)
{
    int i;

    if(!s) return;

    for(i=0; i<MAXSTACK; i++){
        element_free(s->item[i]);
    }

    free(s);

    return;

}

Status stack_push(Stack *s, const Element *e)
{
    if(!s || !e) return ERROR;

    if(stack_isFull(s) == TRUE) return ERROR;

    s->item[s->top] = element_copy(e);

    if(s->item[s->top] == NULL) return ERROR;

    s->top++;

    return OK;
}

Element * stack_pop(Stack *s)
{
    Element *e=NULL;

    if(!s) return NULL;

    if(stack_isEmpty(s)==TRUE) return NULL;

    s->top--;
    e=s->item[s->top];
    s->item[s->top]=NULL;

    return e;
}

Element * stack_top(const Stack *s)
{
    int aux;

    if(!s) return NULL;
    aux = s->top -1;

    return s->item[aux];
}

Bool stack_isEmpty(const Stack *s)
{
    if(!s) return FALSE;

    if(s->top==0) return TRUE;

    return FALSE;
}

Bool stack_isFull(const Stack *s)
{
    if(!s) return FALSE;

    if(s->top==MAXSTACK) return TRUE;

    return FALSE;
}

int stack_print(FILE* f, const Stack* s)
{
    int i;
    int p=0;

    if(!f || !s) return 0;

    for(i=0; i<s->top; i++){
        p += element_print(f, s->item[i]);
    }   

    return p;
}

int stack_size(const Stack * s)
{
    if(!s)return -1;

    return s->top;
}