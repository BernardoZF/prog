#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "element.h"

struct _Element {
    char *a;
};

Element * element_init(){
    Element *e=NULL;

    e=(Element *)malloc(sizeof(Element));
    if(!e) return NULL;

    e->a = NULL;

    return e;
}
void element_free(Element *e){
    if(!e) return;

    free(e->a);
    free(e);

    return;
}

Element * element_setInfo(Element *e, void *c){
  if(!e || !c) return NULL;

  if(e->a !=NULL) free(e->a);

  e->a = (char *)malloc(sizeof(char));
  char *temp = (char *)c;
  (*e->a)=(*temp);

  if(!e->a) return NULL;

  return e;

}

void * element_getInfo(Element *e){
    if(!e) return NULL;

    return e->a;
}

Element * element_copy(const Element *e){
    Element *s;

    s=element_init();
    if(!s) return NULL;

    element_setInfo(s, e->a);

    return s;
}

Bool element_equals(const Element *e1, const Element *e2){
    if(!e1 || !e2) return FALSE;

    if(e1->a == e2->a) return TRUE;

    return FALSE;
}

int element_print(FILE *f, const Element *e){
    int p=0;

    if(!f || !e) return -1;

    p=fprintf(f, "%c \n", *(char *)element_getInfo(e));

    if(!p) return -1;

    return p;
}
