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
6
* @return The function returns OK on success or ERROR
* when any of its parametrs is NULL
**/
Status infix2postfix (char *suf, const char *in);

#define OPERATORS {'+', '-', '*', '/', '%', '^'}

Bool isOperator (char c);

int main(){


    return 0;
}

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

int prec (char c){
  char array[] = OPERATORS;

  if(array[0] == c || array[1] == c) return 0;

  if(array[2] == c || array[3] == c || array[4] == c) return 1;

  if(array[5] == c) return 2;

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
  Status ret = TRUE;
  Stack *s = NULL;
  char *ele = NULL;
  int i = 0, j = 0;

  s=stack_init(char_free, char_copy, char_print);
  if(!s) return ERROR;

  while(in[i] != '\0'){
    if(isOperator(in[i]) == TRUE){
      while((stack_isEmpty(s) == FALSE) && (prec(stack_top(s)) >= prec(in[i]))){
        ele = (char *)stack_pop(s);
        suf[j] = ele;
        j++;
      }
      stack_push(s, in[i]);
    }

    else if(in[i] == '('){
      stack_push(s, in[i]);
    }

    else if(in[i] == ')'){
      while((stack_isEmpty(s) == FALSE) && (stack_top(s) != '(')){
        ele = (char *)stack_pop(s);
        suf[j] = ele;
        j++;
      }
      stack_pop(s);
    }

    else{
      suf[j] = in[i];
      j++;
    }
    i++;
  }

  while(stack_isEmpty(s) == FALSE){
    ele = (char *)stack_pop(s);
    suf[j] = ele;
    j++;
  }

  stack_free(s);

  return TRUE;
}

int main(int argc, char* argv[]){
  int i;
  char *suf;
  char *in;

  strcpy(in, argv[1]);

  infix2postfix(in, suf);

  return 0;
}
