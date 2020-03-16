#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "element.h"

struct _Element {
    char *a;
};

Element * element_init(){
    Element *e=NULL;

    ele=(Element *)malloc(sizeof(Element));
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

Element * element_setInfo(Element s, void c){
  if(!s || !c) return NULL;

  if(s->a !=NULL) free(s->a);

  s->a = (char *)malloc(sizeof(char));
  char *temp = (char *)c;
  (*s->a)=(*temp);

  if(!s->a) return NULL;

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

    p=fprintf(f, "[%s]", e->a);

    if(!p) return -1;

    return p;
}
