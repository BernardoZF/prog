#ifndef EXTRAFUNCTIONS_INT_H
#define EXTRAFUNCTIONS_INT_H


#include <stdlib.h>
#include <stdio.h>

/**
* Estas funciones las hemos creado debido a que las otras que estan en libstack.a
* no imprimen con espacios entre los enteros lo que hace imposible la comprension
* de la impresion de las listas.
*/

int extraint_print(FILE *pf, const void  *a);

void * extraint_copy (const void* a);

void extraint_free(void * a);

int extraint_cmp(const void * a, const void * b);


#endif /* EXTRAFUNCTIONS_INT_H */
