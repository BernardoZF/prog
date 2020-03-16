/*
* File: stack.h
* Author: Profesores de PROG2
*/

#ifndef STACK_H
#define STACK_H
#include "element.h"

typedef struct _Stack Stack;

/**
* @brief Esta funcion inicializa nuestra pila
*
* @return devuelve nuestra pila inicializada con la correspondiente reserva de memoria 
*/
Stack * stack_init ();

/**
* @brief Esta funcion libera nuestra pila
*/
void stack_free(Stack *s);

/**
* @brief Esta funcion extrae elementos de nuestra pila
*
* @param s Un puntero a pila
* @param e Un puntero a elemento
* @return OK o ERROR segun si el elemento ha sido extraido correctamente o no
*/
Status stack_push(Stack *s, const Element *s);

/**
* @brief Esta funcion introduce un elemento en una pila
*
* @param s Un puntero a pila
* @return El elemento introducido
*/
Element * stack_pop(Stack *s);

/**
* @brief Esta funcion devuelve el elemento que se encuentra en la posicion mas alta de la pila
*
* @param s Un puntero a pila
* @return La siguiente posicion a introducir en la pila
*/
Element * stack_top(const Stack *s);

/**
* @brief Esta funcion nos informa si la pila esta vacia o no
*
* @param s Un puntero a pila
* @return TRUE o FALSE segun si la pila esta o no vacia
*/
Bool stack_isEmpty(const Stack *s);

/**
* @brief Esta funcion nos informa si la pila esta llena o no
*
* @param s Un puntero a pila
* @return TRUE o FALSE segun si la pila esta o no llena
*/
Bool stack_isFull(const Stack *s);

/**
* @brief Esta funcion imprime la pila
* 
* @param f Un fichero de texto
* @param s Un puntero a pila
* @return el valor de la pila
*/
int stack_print(FILE*, const Stack *s);

#endif /* STACK_H */
