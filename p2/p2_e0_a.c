#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_fp.h"
#include "stack_types.h"
#define DIM_SIZE 3

int main(){
    char *c;
    char array[DIM_SIZE]={'a', 'b', 'c'};
    Stack *stc=NULL;
    int i;

    /*Inicializamos nuestra pila y hacemos control de errores*/
    stc=stack_init(char_free, char_copy, char_print);
    if(!s) return -1;

    /*Extremos de la pila los elementos*/
    for(i=0; i<DIM_SIZE; i++){
        stack_push (stc, &array[i]);
    }

    stack_print(stdout, stc);
    
    /*Imprimimos por pantalla el tamanio de la pila*/
    fprintf(stdout, "Stack size: %ld\n", stack_size(stc));

    /*Mientras que la pila no este llena, mostramos por pantalla los elementos extraidos*/
    while(stack_isEmpty(stc)==FALSE){
      c = (char*)stack_pop(stc);
      fprintf(stdout, "El elemento extraido: %c\n", *c);
      free(c);
    }
    
    /*Imprimimos por pantalla el tamanio de la pila*/
    fprintf(stdout, "Stack size: %ld\n", stack_size(stc));
    
    /*Liberamos la pila*/
    stack_free(stc);

    return 0;
}
