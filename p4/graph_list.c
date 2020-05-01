/**
* @file graph.c
* @author Bernardo zambrano && Alvaro Platon
* @date 4 February 2020
* @version 1.0
* @brief TAD Node
**
@details
**
@see
*/

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph_list.h"
#include "node.h"
#include "list.h"
#define MAX_NODES 1064
#define MAX_LINE 1000
enum {IDS_CONNECTS = 2, NUM_ARGUMENTS};

struct _Graph {
    List *plnode;                            /*!<List with the graph nodes */
    Bool connections[MAX_NODES][MAX_NODES];  /*!<Adjacency matrix */
    int num_nodes;                           /*!<Number of nodes in the graph*/
    int num_edges;                           /*!<Number of connections in the graph */
};

/********************PRIVATE FUNCTIONS************************/
int find_node_index(const Graph * g, long nId1);
long* graph_getConnectionsIndex(const Graph * g, int index);
/*************************************************************/

Graph * graph_init ()
{
    Graph *g=NULL;
    int i, j;

    g=(Graph *)malloc(sizeof(Graph));
    if(!g){
        fprintf(stderr,"Error reserving memory ");
        return NULL;
    }
    g->plnode = list_new(node_free, node_copy, node_print, node_cmp);
    for(i=0;i<MAX_NODES;i++){
        for(j=0;j<MAX_NODES;j++){
            g->connections[i][j]=FALSE;
        }
    }

    g->num_edges=0;
    g->num_nodes=0;

    return g;
}


void graph_free (Graph *g)
{
    if (!g)  return;

    list_free(g->plnode);
    free(g);

    return;
}



Status graph_insertNode (Graph *g, const Node *n)
{
    int index_lista;
		int i;
    Node *tmp;

    if(!g||!n){
        return ERROR;
    }

   index_lista = find_node_index(g, node_getId(n));
   if(index_lista != -1){
		 return ERROR;
	 }

    tmp =(Node *)node_copy(n);
    node_setNConnect(tmp, 0);
    if(list_pushFront(g->plnode, tmp) == ERROR){
      for(i=0;i<g->num_nodes;i++){
				g->connections[i][g->num_nodes]= FALSE;
				g->connections[g->num_nodes][i]= FALSE;
			}
      node_free(tmp);
      return ERROR;
    }
    for(i=0;i<g->num_nodes;i++){
      g->connections[i][g->num_nodes]= FALSE;
      g->connections[g->num_nodes][i]= FALSE;
    }
    g->num_nodes++;
    node_free(tmp);

    return OK;
}


Status graph_insertEdge (Graph *g, const long nId1, const long nId2)
{
    int index_lista1;
    int index_lista2;
    int index_conn1;
    int index_conn2;
    int ncon;

    if (!g || nId1==-1 || nId1==-1) return ERROR;

	index_lista1 = find_node_index(g, nId1);
	index_lista2 = find_node_index(g, nId2);

	if (index_lista1 == -1 || index_lista2 == -1){
		return ERROR;
	}

  index_conn1= g->num_nodes -1 - index_lista1;
  index_conn2= g->num_nodes -1 - index_lista2;
	if (g->connections[index_conn1][index_conn2] == TRUE){
		fprintf(stderr, "Ya conectados.\n");
		return OK;
	}

	(g->num_edges)++;
	g->connections[index_conn1][index_conn2] = TRUE;

	ncon = node_getNConnect(list_getElementInPos(g->plnode, index_lista1));
	if (ncon == -1){
		fprintf(stderr, "Error al obtener el numero de conexiones del nodo\n");
		g->connections[index_conn1][index_conn2] = FALSE;
		(g->num_edges)--;
		return ERROR;
	}
	if(!node_setNConnect(list_getElementInPos(g->plnode, index_lista1), ncon+1)){
		fprintf(stderr, "Error al modificar el numero de conexiones del nodo\n");
		g->connections[index_conn1][index_conn2] = FALSE;
		(g->num_edges)--;
		return ERROR;
    }

	return OK;
}


Node *graph_getNode (const Graph *g, long nId)
{
    int indx=-1;
    Node *n=NULL;

    if(!g||nId<0)
        return NULL;
    indx=find_node_index(g, nId);
    if(indx<0)
        return NULL;
    n=node_copy(list_getElementInPos(g->plnode, indx));

    return n;
}

/**
* Esta implementacion lo que produce es que si hay algun fallo en algun punto el
* nodo original no se restaura
*/
Status graph_setNode (Graph *g, const Node *n)
{
    int indx;
    Node *nlista;

    if (!g||!n)
        return ERROR;

   indx = find_node_index(g, node_getId(n));

	 if(indx == -1){
		 return ERROR;
	 }

	nlista=list_getElementInPos(g->plnode,indx);
  node_setName(nlista, node_getName(n));
  node_setLabel(nlista, node_getLabel(n));
  node_setPredecessorId(nlista, node_getPredecessorId(n));

	return OK;
}


long * graph_getNodesId (const Graph *g)
{
    int i;
    long *ids;

    if(!g)
        return NULL;

    ids=(long *)malloc(sizeof(long)*g->num_nodes);
    if(!ids)
        return NULL;

    for(i=0;i<g->num_nodes ;i++){
        ids[i]=node_getId(list_getElementInPos(g->plnode, i));
    }


    return ids;
}



int graph_getNumberOfNodes (const Graph *g)
{
    if(!g)
        return -1;

    return g->num_nodes;
}



int graph_getNumberOfEdges (const Graph *g)
{
    if(!g)
        return -1;

    return g->num_edges;
}



Bool graph_areConnected (const Graph *g, const long nId1, const long nId2)
{
    long index_lista1;
    long index_lista2;
    long index_conn1;
    long index_conn2;

    if(!g||nId1==-1||nId2==-1)
        return FALSE;
    index_lista1= find_node_index(g, nId1);
    if(index_lista1 == -1)
        return FALSE;
    index_lista2= find_node_index(g, nId2);
    if(index_lista2 ==-1)
        return FALSE;

    index_conn1= g->num_nodes - 1 -index_lista1;
    index_conn2= g->num_nodes - 1 -index_lista2;
    return g->connections[index_conn1][index_conn2];
}



int graph_getNumberOfConnectionsFrom (const Graph *g, const long fromId)
{
  int indx;

    if (!g || fromId==-1)
      return -1;

    indx=find_node_index(g, fromId);
    if(indx == -1){
      return -1;
    }

    return node_getNConnect(list_getElementInPos(g->plnode, indx));
}


/** Implementacion nueva por haber entendido mal lo que se pedia */
long* graph_getConnectionsFrom (const Graph *g, const long fromId)
{
  long *array = NULL;
  int i;
  int j=0;
  int tam;
  int index_lista;
  int index_conn;
  if (!g) return NULL;
  if (fromId < 0 ) return NULL;

  tam = graph_getNumberOfConnectionsFrom (g, fromId);
  if(tam == -1) return NULL;

  array = (long *) malloc(sizeof(long) * tam);
  if (!array) {
    fprintf(stderr, "Error en reserva de memoria");
  return NULL;
  }

  index_lista = find_node_index(g, fromId);
  if(index_lista == -1){
    free(array);
    return NULL;
  }

  index_conn= g->num_nodes -1 - index_lista;

  for(i = 0; i< g->num_nodes; i++) {
    if (g->connections[index_conn][i] == TRUE) {
      array[j] = node_getId(list_getElementInPos(g->plnode,i));
      j++;
    }
  }
return array;
}


/**
* cambiar casi por completo
*/
int graph_print (FILE *pf, const Graph *g)
{

    int ret = 0;
    int i, j, index_lista, node_id;
    long *conn = NULL;

    if(!pf || !g)
        return -1;

    for(i = 0; i < g->num_nodes; i++){
        ret += node_print(pf, list_getElementInPos(g->plnode, i));

        index_lista = find_node_index(g, node_getId(list_getElementInPos(g->plnode, i)));
        conn = graph_getConnectionsIndex(g, index_lista);
        for(j=0;j < node_getNConnect(list_getElementInPos(g->plnode, i)) ; j++){
            node_id = node_getId(list_getElementInPos(g->plnode, conn[j]));
            ret += fprintf(pf, " %d", node_id);
        }
        fprintf(pf, "\n");

        free(conn);
    }

    if(ret<1){
        fprintf(stderr, "Error while printing\n");
        return -1;
    }

    return ret;
}



Status graph_readFromFile (FILE *fin, Graph *g)
{
    Node *n;
    char buff[MAX_LINE], name[MAX_LINE];
    int i, nnodes = 0, id1, id2, n_label;
    Status flag = ERROR;

    if ( fgets (buff, MAX_LINE, fin) != NULL)
    if ( sscanf(buff, "%d", &nnodes) != 1) return ERROR;

    n = node_init();
    if (!n) return ERROR;

    for(i=0; i < nnodes; i++) {
        if ( fgets(buff, MAX_LINE, fin) != NULL)
        if (sscanf(buff, "%d %s %d", &id1, name, &n_label) != NUM_ARGUMENTS) break;

        node_setName (n, name);
        node_setId (n, id1);
        if(n_label ==0)
            node_setLabel(n,WHITE);
        else if(n_label == 1)
            node_setLabel(n, BLACK);
        else
            node_setLabel(n, ERROR_NODE);

        if ( graph_insertNode (g, n) == ERROR) break;
    }

    if (i < nnodes) {
        node_free(n);
        return ERROR;
    }

    while ( fgets(buff, MAX_LINE, fin) ){
      if ( sscanf(buff, "%d %d", &id1,&id2) == IDS_CONNECTS )
      if (graph_insertEdge(g, id1,id2) == ERROR) break;
    }

    if (feof(fin)) flag = OK;

    node_free (n);
    return flag;
}


/* It returns the index of the node with id nId1*//*O(n)*/
int find_node_index(const Graph * g, long nId1)
{
Node *tmp;
int index_lista;

if (!g)
    return -1;

  tmp = node_init();
  node_setId(tmp, nId1);

  index_lista= list_getPositionElement(g->plnode, tmp);
  node_free(tmp);

return index_lista;
}

/**It returns an array with the indices of the nodes connected to the node whose index is index
 It also allocates memory for the array.
 */
long* graph_getConnectionsIndex(const Graph * g, int index)
{
long *array = NULL, i, j = 0, size;
int index_conn;
int index_list;

if (!g)
    return NULL;

if (index < 0 || index >g->num_nodes)
    return NULL;

/* get memory for the array*/
size = node_getNConnect (list_getElementInPos(g->plnode, index));
array = (long *) malloc(sizeof (long) * size);

if (!array) {
    /* print error message*/
    fprintf (stderr, "%s\n", strerror(errno));
    return NULL;
}

index_conn = g->num_nodes -1 - index;
/*assign values to the array with the indices of the connected nodes*/
for(i = 0; i< g->num_nodes; i++) {
    if (g->connections[index_conn][i] == TRUE) {
        index_list = g->num_nodes -1 -i;
        array[j++] = index_list;
    }
}

return array;
}
