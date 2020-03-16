/*
* File: element.h
* Author: Profesores de PROG2
*/

#ifndef ELEMENT_H
#define ELEMENT_H
#include "types.h"
typedef struct _Element Element;

/**
* @brief Esta funcion inicializa un elemento
*
* @return devuelve el elemento inicializado con la correspondiente reserva de memoria 
*/
Element * element_init();

/**
* @brief Esta funcion libera nuestra elemento
*/
void element_free(Element *e);

/**
* @brief Esta funcion establece la informacion de nuestro elemento
*
* @param e Un puntero a elemento 
* @param c Un puntero generico
* @return el elemento con la informacion cambiada
*/
Element * element_setInfo(Element *e, void *c);

/**
* @brief Esta funcion establece la informacion de nuestro elemento
*
* @param e Un puntero a elemento 
*/
void * element_getInfo(Element *e);

/**
* @brief Esta funcion copia un elemento a otro
*
* @param e Un puntero a elemento 
* @return el elemento copiado
*/
Element * element_copy(const Element *e);

/**
* @brief Esta funcion establece si dos elementos son iguales o no
*
* @param e Un puntero a elemento 
* @param e Un puntero a elemento
* @return TRUE o FALSE dependiendo de si los elementos son o no iguales
*/
Bool element_equals(const Element *e, const Element *e);

/**
* @brief Esta funcion imprime el elemento
* 
* @param f Un fichero de texto
* @param s Un puntero a elemento
* @return el valor del elemento
*/
int element_print(FILE *f, const Element *e);
#endif /* ELESTACK_H */
