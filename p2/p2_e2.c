#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_fp.h"
#include "stack_types.h"

/**
* @brief: Get the postfix expression of an infix expression.
* The infix and postfix strings may not overlap and
* the destination postfix string must be
* large enough to receive the infix expression
* (to be checked before calling this function).
*
* @param in Pointer to the infix expression
* @param suf Pointer to the suffix expression
*
* @return The function returns OK on success or ERROR
* when any of its parametrs is NULL
**/
Status infix2postfix (char *suf, const char *in);

#define OPERATORS {'+', '-', '*', '/', '%', '^'}

Bool isOperator (char c);

Bool isOperator (char c){
  char array[] = OPERATORS;
  int i;

  for(i=0;i<6;i++){
    if(c == array[i]){
      return TRUE;
    }
  }

  return FALSE;
}

int prec (char *c){
  char array[] = OPERATORS;

  if(array[0] == *c || array[1] == *c) return 0;

  if(array[2] == *c || array[3] == *c || array[4] == *c) return 1;

  if(array[5] == *c) return 2;

  return -1;
}
/**
* @brief: Get the postfix expression of an infix expression.

* The infix and postfix strings may not overlap and
* the destination postfix string must be
* large enough to receive the infix expression
* (to be checked before calling this function).
*
* @param in Pointer to the infix expression
* @param suf Pointer to the suffix expression
* @return The function returns OK on success or ERROR
* when any of its parametrs is NULL
**/
Status infix2postfix (char *suf, const char *in){
  Stack *s = NULL;
  char *ele = NULL;
  char cpy[1000];
  int i = 0, j = 0;

  if(!in) return ERROR;

  if(!suf) return ERROR;

  s=stack_init(char_free, char_copy, char_print);
  if(!s) return ERROR;

  strcpy(cpy, in);

  while(cpy[i] != '\0'){
    if(isOperator(cpy[i]) == TRUE){
      while((stack_isEmpty(s) == FALSE) && (prec((char*)stack_top(s)) >= prec(cpy+i))){
        ele = (char *)stack_pop(s);
        suf[j] = *ele;
        free(ele);
        j++;
      }
      stack_push(s, &cpy[i]);
    }

    else if(cpy[i] == '('){
      stack_push(s, &cpy[i]);
    }

    else if(cpy[i] == ')'){
      while((stack_isEmpty(s) == FALSE) && (*(char*)stack_top(s)!='(')){
        ele = (char *)stack_pop(s);
        suf[j] = *ele;
        free(ele);
        j++;
      }
      ele=(char*)stack_pop(s);
      free(ele);
    }

    else{
      suf[j] = cpy[i];
      j++;
    }
    i++;
  }
  while(stack_isEmpty(s) == FALSE){
    ele = (char *)stack_pop(s);
    suf[j] = *ele;
    free(ele);
    j++;
  }
  stack_free(s);
  return TRUE;
}

int main(int argc, char* argv[]){
  char suf[1000]="suffix";
  char in[1000]="infix";

  if(argc!=2){
    fprintf(stdout, "ERROR EN ARGUMENTOS");
    return -1;
  }
  strcpy(in, argv[1]);
  fprintf(stdout, "Input: %s\n", argv[1]);

  infix2postfix(suf, argv[1]);
  fprintf(stdout, "Output: %s\n", suf);

  return 0;
}
