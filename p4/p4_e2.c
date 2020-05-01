/**
* @file p4_e2.c
* @author Bernardo zambrano && Alvaro Platon
* @date 1 May 2020
* @version 2.0
* @brief ej2
**
@details
**
@see
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue_fp.h"
#include "graph_list.h"
#include "node.h"
#include "types.h"

#define MAXSTRING 65536
#define MAXNAME 64

/****
* @brief Implements the BFS algorithm from an initial node
* @param pg, Graph
* @param ini_id, Origin node Id
* @param end_id, Destination node Id
* @param path, String with the traversed node's name.
* This parameter is modified by the function.
* @return, OK or ERROR if any pointer is NULL
****/
Status graph_breadthFirst (Graph *pg, long ini_id, long end_id,
char *nodestraversed);

/**
* Libera la memoria reservada en el main
* @param pf puntero al fichero a librerar
* @param g grafo a liberar
*/
void clean_main (FILE *pf, Graph *g);


/**
* Libera la cola reservada en graph_breadthFirst
* @param q cola a liberar
*/
void clean_fun_q (Queue *q);

/**
* Libera el nodo reservada en graph_breadthFirst
* @param n nodo a liberar
*/
void clean_fun_n (Node *n);

/**
* Libera la cola y un nodo reservado en graph_breadthFirst
* @param q cola a liberar
* @param n Nodo a liberar
*/
void clean_fun_q_node (Queue *q, Node *n);


/**
* Libera la cola y los nodos reservados en graph_breadthFirst
* @param q cola a liberar
* @param n Nodo a liberar
* @param aux Nodo a liberar
*/
void clean_fun_q_nodes (Queue *q, Node *n, Node *aux);


int main(int argc, char* argv[])
{

  Graph *g;
  long ini_id;
  long end_id;
  char nt[MAXSTRING]="";
  FILE *pf;
  int flag;

  if(argc != 4){
      fprintf(stderr, "ERROR EN EL FORMATO DE EJECUCION\n");
      return -1;
  }

  pf=fopen(argv[1], "r");
  if(!pf) {
      fprintf(stderr, "Error abriendo el archivo\n ");
      return -1;
  }

  g=graph_init();
  if(!g){
      fprintf(stderr, "Error al iniciaizar el grafo\n");
      fclose(pf);
      return -1;
  }

  flag=graph_readFromFile(pf, g);
  if(flag==ERROR){
      fprintf(stderr, "Error al crear el grafo\n");
      clean_main (pf, g);
      return -1;
  }

  ini_id=atol(argv[2]);
  end_id=atol(argv[3]);

  if(graph_breadthFirst(g, ini_id, end_id, nt)==ERROR){
    fprintf(stderr, "ERROR en la funcion\n");
    clean_main (pf, g);
    return -1;
  }

  fprintf(stdout, "%s\n", nt);


  clean_main (pf, g);

  return 0;
}


Status graph_breadthFirst (Graph *pg, long ini_id, long end_id,
char *nodestraversed)
{
  Queue * q = NULL;
  Node * n = NULL;
  Node * naux = NULL;
  int flag = ERROR;
  int i;
  int numcon = 0;
  char s[MAXNAME]="";
  char tab[MAXNAME] = "\t";
  long *ids=NULL;
  long *nodesId = NULL;

  if(!pg || ini_id==-1 || end_id==-1 || !nodestraversed){
      return ERROR;
  }

  q=queue_init(node_free, node_copy, node_print);
  if(!q){
    return ERROR;
  }

  nodesId=graph_getNodesId(pg);
  if(nodesId == NULL){
    clean_fun_q(q);
    return ERROR;
  }

  for(i=0;i<graph_getNumberOfNodes(pg); i++){
      n=graph_getNode(pg,nodesId[i]);
      if(n==NULL){
        clean_fun_q(q);
        return ERROR;
      }
      node_setLabel(n, WHITE);
      if(node_getId(n)==ini_id){
        node_setLabel(n, BLACK);
        flag=queue_insert(q, (void *)n);
        if(flag==ERROR){
            clean_fun_q_node(q, n);
            return ERROR;
        }
      }
      graph_setNode(pg, n);
      clean_fun_n(n);
    }
    free(nodesId);

    while(queue_isEmpty(q) == FALSE && flag == OK){
      n=(Node *)queue_extract(q);
      if(n == NULL){
        clean_fun_q(q);
        return ERROR;
      }

      strcpy(s, node_getName(n));
      strcat(nodestraversed, s);
      strcat(nodestraversed, tab);

      if(node_getId(n) == end_id){
        clean_fun_n(n);
        flag = END;
      }
      else {
        ids=graph_getConnectionsFrom(pg, node_getId(n));
        if(!ids){
          clean_fun_q(q);
          return ERROR;
        }
        numcon = graph_getNumberOfConnectionsFrom(pg, node_getId(n));
        for(i=0;i<numcon;i++){
          naux=graph_getNode(pg, ids[i]);
          if(!naux){
            clean_fun_q_node(q, n);
            return ERROR;
          }
          if(node_getLabel(naux) == WHITE){
            node_setPredecessorId(naux, node_getId(n));
            node_setLabel(naux,  BLACK);
            if(queue_insert(q, naux) == ERROR){
              clean_fun_q_nodes(q, n, naux);
              return ERROR;
            }
            graph_setNode(pg , naux);
          }
        clean_fun_n(naux);
        }
        clean_fun_n(n);
        free(ids);
      }
    }
    clean_fun_q(q);
    return OK;
}


void clean_main (FILE *pf, Graph *g)
{
  if(!pf || !g) return;

  fclose(pf);
  graph_free(g);

  return;
}


void clean_fun_q (Queue *q)
{
  if(!q) return;

  queue_free(q);

  return ;
}

void clean_fun_q_node (Queue *q, Node *n)
{
  if(!q || !n )return;

  queue_free(q);
  node_free(n);

  return;
}

void clean_fun_n (Node *n)
{
  if(!n) return;

  node_free(n);

  return;
}


void clean_fun_q_nodes (Queue *q, Node *n, Node *aux)
{
  if(!q || !n || !aux)return;

  queue_free(q);
  node_free(n);
  node_free(aux);

  return;
}
