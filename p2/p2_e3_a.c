#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "element.h"
#include "stack.h"
#include "types.h"

#define MAX_WORD 1024

char *reverseWords (char *strout, const char *strin);

int main(int argc, char* argv[])
{
  char in[MAX_WORD]="in", out[MAX_WORD]="out";

  if(argc!=2){
      fprintf(stdout, "ERROR EN LOS ARGUMENTOS");
        return -1;
  }

  strcpy(in, argv[1]);

  printf("Input: %s\n", in);
  reverseWords(out, in);

  printf("Output: %s\n", out);


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
char * reverseWords (char *strout, const char *strin)
{
  Stack *s = NULL;
  Element *input, *output;
  char aux[MAX_WORD]="aux";
  int i, j=0;
  
  strcpy(aux, strin);
  /*Inicializamos la pila y su correspondiente control de errores*/
  s = stack_init();
  if(!s) return ERROR;
  
  /*Inicializamos el elemento y su correspondiente control de errores*/
  input = element_init();
  if(!input) return ERROR;

  i = 0;

  /*Mediante este bucle damos la vuelta a cada palabra individualmente, cambiando
  unicamente el orden de las letras y no el de las palabras en las frases*/
  for(i=0; strin[i] != '\0'; i++){
    if(strin[i] == ' '){
      while(stack_isEmpty(s) == FALSE){
        output = stack_pop(s);
        strout[j]= *(char*)element_getInfo(output);
        element_free(output);
        j++; 
      }
      strout[j] = ' ';
      j++;
      i++;
    }
    element_setInfo(input, &aux[i]);
    stack_push(s, input);//Insertamos letra a letra de nuestra cadena
  }
  
  element_free(input);
  /*Mientras que la pila no este vacia, metemos las letras en nuestra cadena de salida*/
  while(stack_isEmpty(s) == FALSE){
    output = stack_pop(s);
    strncpy(&strout[j], (char*)element_getInfo(output), 1);
    element_free(output);
    j++;  
  }
  
  /*Liberamos la pila*/
  stack_free(s);

  return strout;
}