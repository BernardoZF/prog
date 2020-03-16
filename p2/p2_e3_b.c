#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "element.h"
#include "stack.h"
#define DIM_SIZE 3

int main(){
    Element *e=NULL;
    char array[DIM_SIZE]={'a', 'b', 'c'};
    Stack *stc=NULL;
    int i;

    /*Inicializamos nuestra pila y hacemos control de errores*/
    stc=stack_init();
    if(!stc) return -1;

    /*Inicializamos nuestro elemento y hacemos control de errores*/
    e=element_init();
    if(!e) return -1;

    /*Extremos de la pila los elementos*/
    for(i=0; i<DIM_SIZE; i++){
        element_setInfo(e, &array[i]);
        stack_push (stc, e);
    }
    element_free(e);

    stack_print(stdout, stc);
    
    /*Imprimimos por pantalla el tamanio de la pila*/
    fprintf(stdout, "Stack size: %d\n", stack_size(stc));

    /*Mientras que la pila no este llena, mostramos por pantalla los elementos extraidos*/
    while(stack_isEmpty(stc)==FALSE){
      e = stack_pop(stc);
      fprintf(stdout, "El elemento extraido: %c\n", *(char *)element_getInfo(e));
      element_free(e);
    }
    
    /*Imprimimos por pantalla el tamanio de la pila*/
    fprintf(stdout, "Stack size: %d\n", stack_size(stc));
    
    /*Liberamos la pila*/
    stack_free(stc);

    return 0;
}