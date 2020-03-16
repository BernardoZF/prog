#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_fp.h"
#include "stack_types.h"

#define MAX_WORD 1024

char *reverseWords (char *strout, const char *strin);

int main(){
  char in[MAX_WORD]="in", out[MAX_WORD]="out";

  printf("Input: ");
  scanf("\n%[^\n]s", in);

  printf("Output: %s\n", reverseWords(out, in));


    return 0;
}

/***@brief: Reverse the words of an input string to an output string.
* The words in the input string are separated by a space character.
* The strings may not overlap, and the destination string strout
* must be large enough to receive the inverted expression.
*
*@paramstrout, Pointer to the output buffer
*@paramstrin, Pointer to the input expression
*@returnThe function returns OK or ERROR
**/
char * reverseWords (char *strout, const char *strin){
  Stack *s = NULL;
  char *car;
  int i, j=0;
  
  /*Inicializamos la pila y su correspondiente control de errores*/
  s = stack_init(char_free, char_copy, char_print);
  if(!s) return ERROR;
  

  i = 0;

  /*Mediante este bucle damos la vuelta a cada palabra individualmente, cambiando
  unicamente el orden de las letras y no el de las palabras en las frases*/
  for(i=0; strin[i] != '\0'; i++){
    if(strin[i] == ' '){
      while(stack_isEmpty(s) == FALSE){
        car = (char*)stack_pop(s);
        strncpy(&strout[j], car, 1);
        free(car);
        j++; 
      }
      strout[j] = ' ';
      j++;
      i++;
    }
    stack_push(s, &strin[i]);//Insertamos letra a letra de nuestra cadena
  }
  
  /*Mientras que la pila este llena, metemos las letras en nuestra cadena de salida*/
  while(stack_isEmpty(s) == FALSE){
    car = (char*)stack_pop(s);
    strncpy(&strout[j], car, 1);
    free(car);
    j++; 
  }
  
  /*Liberamos la pila*/
  stack_free(s);

  return strout;
}
