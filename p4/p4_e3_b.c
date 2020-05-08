/**
* @file p4_e3_b.c
* @author Bernardo zambrano && Alvaro Platon
* @date 8 May 2020
* @version 1.0
* @brief ej4
**
@details
**
@see
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <limits.h>
#include "tree.h"
#include "types.h"
#include "list.h"
#include "stack_fp.h"
#include "extrafunctions_int.h"
#define NUM_LISTAS 2
#define MAX_ID 1000

/**
* Funcion que genera una lista de numeros pseudo-aleatorios
* @param n Numero de elementos de la lista
* @param pl puntero a las listas
* @return OK si todo ha ido bien
*/
Status listRandomAndOrdered (int n, List *pl[]);

/**
* Funcion que libera la memoria de las listas
* @param pl listas a liberar
**/
void clean_listas(List *pl[]);

/**
* Funcion que libera la memoria de las listas y los arboles
* @param pl listas a liberar
* @param t1 arbol a liberar
* @param t2 arbol a liberar
**/
void clean_up(List *pl[], BSTree *t1, BSTree *t2);


/**
* Funcion creada para una impresion de los arboles mas sencilla
* @param pf lugar donde se quiere imprimir el arbol
* @param t arbol a imprimir
*/
void tree_prints(FILE *pf, BSTree *t);

/**
* Esta funcion esta implementada ya que no sabemos si lo que se pedia es que
* ejecucion cambien los valores random o que se mantengan con la pseudo-aleatoriedad
* @param n Numero de elementos de la lista
* @param pl puntero a las listas
* @return OK si todo ha ido bien
*/
Status listRandomAndOrdered_every_run_changes (int n, List *pl[]);

/**
* Si se quiere comprobar con valores distintos en cada ejecucion
* la linea a cambiar es la linea 94 (completa) por lo siguiente:
* if(listRandomAndOrdered_every_run_changes(tam, pl) == ERROR) {
*/
int main(int argc, char* argv[])
{
  List *pl[NUM_LISTAS];
  BSTree *tord;
  BSTree *tnord;
  void *elem;
  int tam;
  int i;
  Status flag = OK;

  if(argc != 2) return -1;

  for(i = 0; i< NUM_LISTAS ;i++){
    pl[i] = list_new(extraint_free, extraint_copy, extraint_print, extraint_cmp);
    if(!pl[i]){
      if(pl[i-1]){
        list_free(pl[i-1]);
      }
      return -1;
    }
  }

  tam = atoi(argv[1]);

  if(listRandomAndOrdered(tam, pl) == ERROR) {
    clean_listas(pl);
  }

  tord = tree_init(extraint_free, extraint_copy, extraint_print, extraint_cmp);
  if(!tord){
    clean_listas(pl);
  }
  tnord = tree_init(extraint_free, extraint_copy, extraint_print, extraint_cmp);
  if(!tnord){
    clean_listas(pl);
    tree_destroy(tord);
  }

  fprintf(stdout, "--- Printing List: Ordered ...\n" );
  list_print(stdout, pl[0]);
  fprintf(stdout, "\n\n");

  while(list_isEmpty(pl[0]) != TRUE && flag == OK){
    elem = list_popFront(pl[0]);
    flag = tree_insert(tord, elem);
    extraint_free(elem);
  }
  if(flag != OK){
    clean_up(pl, tord, tnord);
    return -1;
  }

  tree_prints(stdout, tord);

  fprintf(stdout, "--- Printing List: NOT Ordered ...\n" );
  list_print(stdout, pl[1]);
  fprintf(stdout, "\n\n");

  while(list_isEmpty(pl[1]) != TRUE && flag == OK){
    elem = list_popFront(pl[1]);
    flag = tree_insert(tnord, elem);
    extraint_free(elem);
  }
  if(flag != OK){
      clean_up(pl, tord, tnord);
      return -1;
    }


  tree_prints(stdout, tnord);

  clean_up(pl, tord, tnord);

  return 0;
}


Status listRandomAndOrdered_every_run_changes (int n, List *pl[])
{
  List *orden = NULL;
  List *nOrden = NULL;

  int i, x;
  Status st = OK;
   if (!pl) return ERROR;
   srand(time(NULL));
   orden = pl[0];
   nOrden = pl[1];
   for (i=0; i < n && st == OK; i++) {
     x = rand () % MAX_ID ;
     st = list_pushOrder (orden, &x, 1);
     st = list_pushFront (nOrden, &x);
   }
   if (st == ERROR) {
     fprintf (stderr, "%s\n", strerror (errno));
     return ERROR;
   }
   return OK;
}

Status listRandomAndOrdered (int n, List *pl[])
{
  List *orden = NULL;
  List *nOrden = NULL;

  int i, x;
  Status st = OK;
   if (!pl) return ERROR;
   orden = pl[0];
   nOrden = pl[1];
   for (i=0; i < n && st == OK; i++) {
     x = rand () % MAX_ID ;
     st = list_pushOrder (orden, &x, 1);
     st = list_pushFront (nOrden, &x);
   }
   if (st == ERROR) {
     fprintf (stderr, "%s\n", strerror (errno));
     return ERROR;
   }
   return OK;
}

void clean_listas(List *pl[])
{
  int i;
  if(!pl) return;
  for(i= 0; i< NUM_LISTAS ; i++){
    list_free(pl[i]);
  }
}


void clean_up(List *pl[], BSTree *t1, BSTree *t2)
{
  int i;
  if(!pl) return;
  for(i= 0; i< NUM_LISTAS ; i++){
    list_free(pl[i]);
  }
  tree_destroy(t1);
  tree_destroy(t2);

}

void tree_prints(FILE *pf, BSTree *t)
{
    if(!t) return;

    fprintf(pf, "Tree depth: %d\n\n", tree_depth(t));

    fprintf(pf, "Tree postOrder Traversal ...\n" );
    tree_postOrder(pf, t);
    fprintf(pf, "\n\n");


    fprintf(stdout, "Tree preOrder Traversal ...\n" );
    tree_preOrder(pf, t);
    fprintf(pf, "\n\n");


    fprintf(pf, "Tree inOrder Traversal ...\n" );
    tree_inOrder(pf, t);
    fprintf(pf, "\n\n");
}
