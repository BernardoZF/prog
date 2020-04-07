#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue_fp.h"
#include "graph.h"
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
char *nodestraversed)
{
  Queue * q = NULL;
  Node * n = NULL;
  int flag = ERROR;
  int i;
  int numcon = 0;
  char s[MAXNAME]="";
  char tab[MAXNAME] = "\t";
  long *ids=NULL;
  long *nodesId = NULL;

  if(!pg || ini_id==-1 || end_id==-1){
      return ERROR;
  }

  q=queue_init(node_free, node_copy, node_print);
  if(!q){
    return ERROR;
  }
 /*Obtenemos los ids de los nodos del gtafo*/
  nodesId=graph_getNodesId(pg);
  if(nodesId == NULL){
    queue_free(q);
    return ERROR;
  }
  /*Bucle para recorrer todos los nodos del grafo etiquetando todos en blanco menos el del inicio*/
  for(i=0;i<graph_getNumberOfNodes(pg); i++){
      n=graph_getNode(pg,nodesId[i]);
      if(n==NULL){
        queue_free(q);
        return ERROR;
      }
      node_setLabel(n, WHITE);
      /*Comprobamos si el id del nodo es igual al nodo inicial*/
      if(node_getId(n)==ini_id){
        /*Si esto es asi, cambiamos la etiqueta a negro y lo insertamos en la cola*/
        node_setLabel(n, BLACK);
        flag=queue_insert(q, (void *)n);
        if(flag==ERROR){
            queue_free(q);
            node_free(n);
            return ERROR;
        }
      }
      graph_setNode(pg, n);
      node_free(n);
    }
    free(nodesId);
    /*Mientras la cola no este vacia y el nodo extraido no sea el del final*/
    while(queue_isEmpty(q) == FALSE && flag != END){
      /*Extraemos nodo*/
      n=(Node *)queue_extract(q);
      if(n == NULL){
        queue_free(q);
        return ERROR;
      }
      /*Obtenemos su nombre*/
      strcpy(s, node_getName(n));
      /*Lo insertamos en la cadena ujunto a una tabulacion*/
      strcat(nodestraversed, s);
      strcat(nodestraversed, tab);

      /*Comprobamos si el nodo que acabamos de extraer es el final*/
      if(node_getId(n) == end_id){
        flag = END; /*Si lo es establecemos falg a END y acabarian los procesos relevamntes del bucle*/
      }
      else {
        ids=graph_getConnectionsFrom(pg, node_getId(n));/*Si no obtenemos los adyacentes del nodo*/
        numcon = graph_getNumberOfConnectionsFrom(pg, node_getId(n));/*Obtenemos el numero de conexiones*/
        for(i=0;i<numcon;i++){
          node_free(n);
          n=graph_getNode(pg, ids[i]);/*Vamos obteniendo los nodos*/
          if(!n){
            queue_free(q);
            return ERROR;
          }
          if(node_getLabel(n) == WHITE){
            /*Si no se han visitado lo establecemos como visitados*/
            node_setLabel(n,  BLACK);
            /*Lo insertamos en la  cola*/
            if(queue_insert(q, n) == ERROR){
              queue_free(q);
              return ERROR;
            }
            /*Actualizamos el grafo estableciendo el nodo como visitado*/
            graph_setNode(pg , n);
          }
        }
        free(ids);
      }
      node_free(n);
    }
    queue_free(q);
    return OK;
}

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
      fclose(pf);
      graph_free(g);
      return -1;
  }

  ini_id=atol(argv[2]);
  end_id=atol(argv[3]);

  if(graph_breadthFirst(g, ini_id, end_id, nt)==ERROR){
    fprintf(stderr, "ERROR en la funcion\n");
    fclose(pf);
    graph_free(g);
    return -1;
  }

  fprintf(stdout, "%s\n", nt);

  graph_free(g);
  fclose(pf);

  return 0;
}
