#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <limits.h>
#include "types.h"
#include "list.h"
#include "stack_fp.h"
#include "extrafunctions_int.h"
#define MAX_ID 1000


/**
* @brief This functión insert n random integers between 0 and MAX_ID into
* an ordered list.
*
* This functions modifies the list input parameter.
*
* @param n, Length of the list
* @param ppl, Address of object list
* @return This function returns OK or ERROR.
**/
Status listOfRandomOrdered (int n, List *pl);



/* Type definition. Pointer function to compare two elements */
typedef int (*f_cmp_type)(const void *, const void*);


/**
* @brief This function concatenate two increased ordered lists
*
* This functions does not modified the ordered input lists l1 and l2.
*
* @parameter l1, Pointer to one list
* @parameter l2, Pointer to the second list
* @parameter lout, Pointer to the output concatenated list
* @parameter fun, Function used to compare the list elements
*
* @return This function returns OK or ERROR.
**/
Status listMergeOrdered (List *l1, List *l2, List *lout, f_cmp_type fun);

void cleanup(List *l1, List *l2, List *lout);

void cleanfun(Stack *s1, Stack *s2);

int main(int argc, char* argv[])
{

  List * l1;
  List * l2;
  List * lout;
  int num_ele;

  if(argc != 2 ){
    fprintf(stderr, "ERROR DE FORMATO\n");
    return ERROR;
  }

  l1=list_new(extraint_free, extraint_copy, extraint_print, extraint_cmp);
  if(!l1) return -1;

  l2=list_new(extraint_free, extraint_copy, extraint_print, extraint_cmp);
  if(!l2){
    list_free(l1);
    return -1;
  }

  lout=list_new(extraint_free, extraint_copy, extraint_print, extraint_cmp);
  if(!lout){
    list_free(l1);
    list_free(l2);
    return -1;
  }

  num_ele = atoi(argv[1]);
  if(listOfRandomOrdered(num_ele, l1) == ERROR){
    cleanup(l1, l2, lout);
    return -1;
  }

  /**
  * Impresion de las listas antes de ejecutar el codigo
  */
  fprintf (stdout, "input l1: [");
  list_print(stdout, l1);
  fprintf(stdout, "] size: %d\n\n", list_size(l1));

  if(listOfRandomOrdered(num_ele, l2) == ERROR){
      cleanup(l1, l2, lout);
    return -1;
  }

  /**
  * Impresion de las listas antes de ejecutar el codigo
  */
  fprintf (stdout, "input l2: [");
  list_print(stdout, l2);
  fprintf(stdout, "] size: %d\n\n", list_size(l2));

  /**
  * Impresion de las listas antes de ejecutar el codigo
  */
  fprintf (stdout, "input lout: [");
  list_print(stdout, lout);
  fprintf(stdout, "] size: %d\n\n", list_size(lout));


  if(listMergeOrdered(l1, l2, lout, int_cmp)==ERROR){
    fprintf(stderr, "ERROR EN LA FUNCION\n");
      cleanup(l1, l2, lout);
    return -1;
  }

  /**
  * Impresion de las listas despues de ejecutar la funcion
  */
  fprintf (stdout, "output l1: [");
  list_print(stdout, l1);
  fprintf(stdout, "] size: %d\n\n", list_size(l1));

  fprintf (stdout, "output l2: [");
  list_print(stdout, l2);
  fprintf(stdout, "] size: %d\n\n", list_size(l2));

  fprintf (stdout, "output lout: [");
  list_print(stdout, lout);
  fprintf(stdout, "] size: %d\n\n", list_size(lout));

  cleanup(l1, l2, lout);

return 0;
}


Status listMergeOrdered (List *l1, List *l2, List *lout, f_cmp_type fun)
{

  Stack *s1, *s2, *saux;
  List *laux;
  void * ele;


  if(!l1 || !l2 || !lout || !fun ) return ERROR;

  s1 = stack_init (int_free, int_copy, int_print);
  if(!s1){
    return ERROR;
  }

  s2 = stack_init (int_free, int_copy, int_print);
  if(!s2){
    stack_free(s1);
    return ERROR;
   }

  while (list_isEmpty (l1) == FALSE) {
      ele = list_popFront (l1);
      if(!ele ){
        cleanfun(s1, s2);
        return ERROR;
      }
      stack_push (s1, ele);
      free(ele);
  }

  while (list_isEmpty (l2) == FALSE ){
    ele = list_popFront (l2);
    if(!ele ){
      cleanfun(s1, s2);
      return ERROR;
    }
    stack_push (s2, ele);
    free(ele);
  }


  while ((stack_isEmpty (s1) == FALSE) && (stack_isEmpty (s2) == FALSE )){
    if (fun(stack_top(s1), stack_top(s2)) > 0) {
        ele = stack_pop (s1);
        if(!ele ){
          cleanfun(s1, s2);
          return ERROR;
        }
        list_pushFront (l1, ele);
    }
    else {
      ele = stack_pop (s2);
      if(!ele ){
        cleanfun(s1, s2);
        return ERROR;
      }
      list_pushFront (l2, ele);
    }
    list_pushFront (lout, ele);
    free(ele);
  }

  if (stack_isEmpty (s1) == TRUE) {
    saux = s2;
    laux = l2;
  }
  else {
    saux = s1;
    laux = l1;
  }

  while (stack_isEmpty (saux) == FALSE){
  ele = stack_pop (saux);
  if(!ele ){
    cleanfun(s1, s2);
    return ERROR;
  }
  list_pushFront (laux, ele);
  list_pushFront (lout, ele);
  free(ele);
  }


  cleanfun(s1, s2);

  return OK;
}


Status listOfRandomOrdered (int n, List *pl)
 {
   int i, x;
   Status st = OK;
    if (!pl) return ERROR;
    for (i=0; i < n && st == OK; i++) {
      x = rand () % MAX_ID ;
      st = list_pushOrder (pl, &x, 1);
    }
    if (st == ERROR) {
      fprintf (stderr, "%s\n", strerror (errno));
      return ERROR;
    }
    return OK;
}


void cleanup(List *l1, List *l2, List *lout)
{

  if(!l1 || !l2 || !lout) return;

  list_free(l1);
  list_free(l2);
  list_free(lout);

  return ;
}

void cleanfun(Stack *s1, Stack *s2)
{
  if(!s1 || !s2) return;

  stack_free(s1);
  stack_free(s2);

  return;
}
