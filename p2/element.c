#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "element.h"

struct _Element {
    char *x;
};

Element * element_init(){
    Element *e=NULL;

    ele=(Element *)malloc(sizeof(Element));
    if(!e) return NULL;

    e->x = NULL;

    return e;
}
void element_free(Element *e){
    if(!e) return;

    free(e->x);
    free(e);

    return;
}

Element * element_setInfo(Element s, void c){
  if(!s || !c) return NULL;

  if(s->x !=NULL) free(s->x);

  s->x = (char *)malloc(sizeof(char));
  char *temp = (char *)c;
  (*s->x)=(*temp);

  if(!s->x) return NULL;

  return s;

}

void * element_getInfo(Element *e){
    if(!e) return NULL;

    return e;
}

Element * element_copy(const Element *e){
    Element *s;

    s=element_init();
    if(!s) return NULL;

    element_setInfo(s, e->x);

    return s;
}

Bool element_equals(const Element *e1, const Element *e2){
    if(!e1 || !e2) return FALSE;

    if(e1->x == e2->x) return TRUE;

    return FALSE;
}

int element_print(FILE *f, const Element *e){
    int p=0;

    if(!f || !e) return -1;

    p=fprintf(f, "[%s]", e->x);

    if(!p) return -1;

    return p;
}
