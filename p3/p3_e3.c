#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue_fp.h"
#include "graph.h"
#include "node.h"
#include "types.h"
#include "stack_fp.h"
#include "stack_types.h"

#define MAXSTRING 65536
#define MAXNAME 64

int printNode (FILE *fp, const Graph *g, long actualid)
{
  Node * n;
  int ret=0;

  if(!fp || !g || actualid == -1) return -1;

  n = graph_getNode(g, actualid);

  ret+=node_print(fp, n);

  node_free(n);

  return ret;
}


int pathFromTo_rec (FILE *dev, Graph *g, long originid, long actualid)
{

  int ret = 0;
  Node * n;
  long predid;

  if(!dev || !g || originid == -1  || actualid == -1) return -1;

  /*Caso base*/
  if (originid == actualid){
    ret += printNode (dev, g, actualid);
    return ret;
  }

  /* get actual node */
  n = graph_getNode (g, actualid);
  if (!n)  return -1;

  /* get predecessor id */
  predid = node_getPredecessorId (n);

  /* recursive call */
  ret += pathFromTo_rec (dev, g, originid, predid);
  if (ret == -1)
    return -1;


  /* print actual node */
  ret += node_print (dev, n);
  node_free (n);


  return ret;
}

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
  Node * naux = NULL;
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

  nodesId=graph_getNodesId(pg);
  if(nodesId == NULL){
    queue_free(q);
    return ERROR;
  }

  for(i=0;i<graph_getNumberOfNodes(pg); i++){
      n=graph_getNode(pg,nodesId[i]);
      if(n==NULL){
        queue_free(q);
        return ERROR;
      }
      node_setLabel(n, WHITE);
      if(node_getId(n)==ini_id){
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

    while(queue_isEmpty(q) == FALSE && flag != END){
      n=(Node *)queue_extract(q);
      if(n == NULL){
        queue_free(q);
        return ERROR;
      }

      strcpy(s, node_getName(n));
      strcat(nodestraversed, s);
      strcat(nodestraversed, tab);

      if(node_getId(n) == end_id){
        node_free(n);
        flag = END;
      }
      else {
        ids=graph_getConnectionsFrom(pg, node_getId(n));
        numcon = graph_getNumberOfConnectionsFrom(pg, node_getId(n));
        for(i=0;i<numcon;i++){
          naux=graph_getNode(pg, ids[i]);
          if(!naux){
            node_free(n);
            queue_free(q);
            return ERROR;
          }
          if(node_getLabel(naux) == WHITE){
            node_setPredecessorId(naux, node_getId(n));
            node_setLabel(naux,  BLACK);
            if(queue_insert(q, naux) == ERROR){
              queue_free(q);
              node_free(naux);
              node_free(n);
              return ERROR;
            }
            graph_setNode(pg , naux);
          }
          node_free(naux);
        }
        node_free(n);
        free(ids);
      }
    }
    queue_free(q);
    return OK;
}


/****
* @brief Prints a path from the destination node to the origin
* using the predecessors
* @param dev, Stream pointer
* @param g, Pointer to the graph
* @param originid, node origin id
* @param toid, node destination id
* @return. Return the number of characters printed.
* If there have been errors in the Output flow
* prints an error message in stderror and returns the value -1.
**/
int pathToFrom (FILE *dev, Graph *g, long orignid, long toid)
{
  int ret = 0;
  Node * n = NULL;

  if(!dev || !g || orignid == -1  || toid == -1) return -1;


  while ( toid != orignid){
    n = graph_getNode(g, toid);
    if(!n){
      ret = -1;
      return ret;
    }
    ret+= printNode(dev, g, toid);

    toid= node_getPredecessorId(n);
    node_free(n);
  }

  n = graph_getNode(g, orignid);
  ret += node_print(dev, n);
  node_free(n);

return ret;
}


/**
@brief Prints a path from the destination node to the origin
* using the predecessors
* @param dev, Stream pointer
* @param g, Pointer to the graph
* @param originid, node origin id
* @param toid, node destination id
* @return. Return the number of characters printed.
* If there have been errors in the Output flow
* prints an error message in stderror and returns the value -1.
**/
int pathFromTo (FILE *dev, Graph *g, long orignid, long toid)
{
  int ret = 0;

  if(!dev || !g || orignid == -1  || toid == -1) return -1;

  ret+=pathFromTo_rec(dev, g, orignid, toid);

  return ret;
}


/**
* @brief This function implements the DFS algorithm starting
* from the node with id ini_id
* @param pg, Graph
* @param ini_id, Origin node Id
* @param end_id, Destination node Id
* @param path, String with the traversed node's name.
* This parameter is modified by the function.
**/
Status graph_deepFirst (Graph *pg, long ini_id, long end_id,
char *nodestraversed)
{
  Stack * q = NULL;
  Node * n = NULL;
  Node * naux = NULL;
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

  q = stack_init(node_free, node_copy, node_print);
  if(!q){
    return ERROR;
  }

  nodesId=graph_getNodesId(pg);
  if(nodesId == NULL){
    stack_free(q);
    return ERROR;
  }

  for(i=0;i<graph_getNumberOfNodes(pg); i++){
      n=graph_getNode(pg,nodesId[i]);
      if(n==NULL){
        stack_free(q);
        return ERROR;
      }
      node_setLabel(n, WHITE);
      if(node_getId(n)==ini_id){
        node_setLabel(n, BLACK);
        flag=stack_push(q, (void *)n);
        if(flag==ERROR){
            stack_free(q);
            node_free(n);
            return ERROR;
        }
      }
      graph_setNode(pg, n);
      node_free(n);
    }
    free(nodesId);

    while(stack_isEmpty(q) == FALSE && flag != END){
      n=(Node *)stack_pop(q);
      if(n == NULL){
        stack_free(q);
        return ERROR;
      }

      strcpy(s, node_getName(n));
      strcat(nodestraversed, s);
      strcat(nodestraversed, tab);

      if(node_getId(n) == end_id){
        node_free(n);
        flag = END;
      }
      else {
        ids=graph_getConnectionsFrom(pg, node_getId(n));
        numcon = graph_getNumberOfConnectionsFrom(pg, node_getId(n));
        for(i=0;i<numcon;i++){
          naux=graph_getNode(pg, ids[i]);
          if(!naux){
            node_free(n);
            stack_free(q);
            return ERROR;
          }
          if(node_getLabel(naux) == WHITE){
            node_setPredecessorId(naux, node_getId(n));
            node_setLabel(naux,  BLACK);
            if(stack_push(q, (void *)naux) == ERROR){
              stack_free(q);
              node_free(naux);
              node_free(n);
              return ERROR;
            }
            graph_setNode(pg , naux);
          }
          node_free(naux);
        }
        node_free(n);
        free(ids);
      }
    }
    stack_free(q);
    return OK;


}

/**
* Si se quiere comprobar la busqueda en profundidad en vez de en anchura
* habra que cambiar la linea 386 (completa) por lo siguiente
* if(graph_deepFirst(g, ini_id, end_id, nt)==ERROR){
*/
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

  fprintf(stdout, "From Origin to End: \n\n");

  if(pathFromTo (stdout, g, ini_id, end_id) == -1){
    fprintf(stderr, "ERROR en la funcion\n");
    fclose(pf);
    graph_free(g);
    return -1;
  }


  fprintf(stdout, "\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");

  fprintf(stdout, "From End to Origin: \n\n");

  if(pathToFrom (stdout, g, ini_id, end_id) == -1){
    fprintf(stderr, "ERROR en la funcion\n");
    fclose(pf);
    graph_free(g);
    return -1;
  }

  graph_free(g);
  fclose(pf);

  return 0;
}
