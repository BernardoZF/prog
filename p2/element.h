/*
* File: element.h
* Author: Profesores de PROG2
*/

#ifndef ELEMENT_H
#define ELEMENT_H
#include "types.h"
typedef struct _Element Element;


Element * element_init();
void element_free(Element *e);
Element * element_setInfo(Element *e, void*c);
void * element_getInfo(Element *e);
Element * element_copy(const Element *e);
Bool element_equals(const Element *e, const Element *e);
int element_print(FILE *, const Element *e);
#endif /* ELESTACK_H */
