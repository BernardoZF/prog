#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "element.h"

struct _Element {
    char *a;
};

Element * element_init(){
    Element *ele=NULL;

    ele=(Element *)malloc(sizeof(Element));
    if(!ele) return NULL;

    ele->a = NULL;

    return ele;
}
void element_free(Element *ele){
    if(!ele) return;

    free(ele->a);
    free(ele);

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

void * element_getInfo(Element *ele){
    if(!ele) return NULL;

    return ele;
}

Element * element_copy(const Element *ele){
    Element *s;

    s=element_init();
    if(!s) return NULL;

    element_setInfo(s, ele->a);

    return s;
}

Bool element_equals(const Element *e1, const Element *e2){
    if(!e1 || !e2) return FALSE;

    if(e1->a == e2->a) return TRUE;

    return FALSE;
}

int element_print(FILE *f, const Element *ele){
    int k=0;

    if(!f || !ele) return -1;

    k=fprintf(f, "[%s]", ele->a);

    if(!k) return -1;

    return k;
}
