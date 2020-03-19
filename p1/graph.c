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



#include "graph.h"
#define MAX_NODES 1064
#define MAX_LINE 1000
enum {IDS_CONNECTS = 2, NUM_ARGUMENTS};

struct _Graph {
    Node *nodes[MAX_NODES];                  /*!<Array with the graph nodes*/
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
    for(i=0;i<MAX_NODES;i++){
        g->nodes[i]=NULL;
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
    int i;

    if (!g)
        return ;
    for(i=0;i<MAX_NODES;i++){
        node_free(g->nodes[i]);
    }
    free(g);

    return;
}



Status graph_insertNode (Graph *g, const Node *n)
{
    int indx;
		int i;

    if(!g||!n){
        return ERROR;
    }

   indx= find_node_index(g, node_getId(n));
   if(indx==-1){
		 fprintf(stdout, "Nodo ya en el grafo");
		 return OK;
	 }

    g->nodes[g->num_nodes]=node_copy(n);
    if(g->nodes[g->num_nodes]==NULL){
			for(i=0;i<MAX_NODES;i++){
				g->connections[i][g->num_nodes]= FALSE;
				g->connections[g->num_nodes][i]= FALSE;
			}
        return ERROR;
    }
		node_setNConnect(g->nodes[g->num_nodes], 0);
		for(i=0;i<MAX_NODES;i++){
			g->connections[i][g->num_nodes]= FALSE;
			g->connections[g->num_nodes][i]= FALSE;
		}

    g->num_nodes++;

    return OK;
}


Status graph_insertEdge (Graph *g, const long nId1, const long nId2)
{
    int indx1, indx2, ncon;

    if (!g || nId1==-1 || nId1==-1) return ERROR;

	indx1 = find_node_index(g, nId1);
	indx2 = find_node_index(g, nId2);

	if (indx1 == -1 || indx2 == -1){
		fprintf(stderr, "Error al buscar el indice del nodo.\n");
		return OK;
	}

	if (g->connections[indx1][indx2] == TRUE){
		fprintf(stderr, "Ya conectados.\n");
		return OK;
	}

	(g->num_edges)++;
	g->connections[indx1][indx2] = TRUE;

	ncon = node_getNConnect(g->nodes[indx1]);
	if (ncon == -1){
		fprintf(stderr, "Error al obtener el numero de conexiones del nodo\n");
		g->connections[indx1][indx2] = FALSE;
		(g->num_edges)--;
		return ERROR;
	}
	if(!node_setNConnect(g->nodes[indx1], ncon+1)){
		fprintf(stderr, "Error al modificar el numero de conexiones del nodo\n");
		g->connections[indx1][indx2] = FALSE;
		(g->num_edges)--;
		return ERROR;
    }

	return OK;
}


Node *graph_getNode (const Graph *g, long nId)
{
    int indx;
    Node *n;

    if(!g||nId<0)
        return NULL;
    indx=find_node_index(g, nId);
    if(indx<0)
        return NULL;
    n=node_copy(g->nodes[indx]);

    return n;
}


Status graph_setNode (Graph *g, const Node *n)
{
    int indx;
    if (!g||!n)
        return ERROR;
   indx = find_node_index(g, node_getId(n));
	 if(indx == -1){
		 return ERROR;
	 }
	g->nodes[indx]=node_copy(n);
	if(g->nodes[indx]==NULL)
		return ERROR;

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
        ids[i]=node_getId(g->nodes[i]);
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
    long indx1, indx2;

    if(!g||nId1==-1||nId2==-1)
        return FALSE;
    indx1=find_node_index(g, nId1);
    if(indx1<0)
        return FALSE;
    indx2=find_node_index(g, nId2);
    if(indx2<0)
        return FALSE;

    return g->connections[indx1][indx2];
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

    return node_getNConnect(g->nodes[indx]);
}


/** Implementacion nueva por haber entendido mal lo que se pedia */
long* graph_getConnectionsFrom (const Graph *g, const long fromId)
{
  long *array = NULL;
  int i, j=0, size;
  if (!g) return NULL;
  if (fromId < 0 || fromId >g->num_nodes) return NULL;

  size = node_getNConnect (g->nodes[find_node_index(g,fromId)]);
  array = (long *) malloc(sizeof(long) * size);
  if (!array) {

  fprintf (stderr, "%s\n", strerror(errno));
  return NULL;
  }

  for(i = 0; i< g->num_nodes; i++) {
    if (g->connections[find_node_index(g,fromId)][i] == TRUE) {
      array[j] = node_getId(g->nodes[i]);
      j++;
    }
  }
return array;
}



int graph_print (FILE *pf, const Graph *g)
{

    int ret = 0;
    int i, j, a, node_id;
    long *conn = NULL;

    if(!pf || !g)
        return -1;

    for(i = 0; i < g->num_nodes; i++){
        ret += node_print(stdout, g->nodes[i]);

        a = find_node_index(g, node_getId(g->nodes[i]));
        conn = graph_getConnectionsIndex(g, a);
        for(j=0;j < node_getNConnect(g->nodes[i]) ; j++){
            node_id = node_getId(g->nodes[conn[j]]);
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


/* It returns the index of the node with id nId1*/
int find_node_index(const Graph * g, long nId1)
{
int i;

if (!g)
    return -1;

for(i=0; i < g->num_nodes; i++) {
if (node_getId (g->nodes[i]) == nId1) return i;
}

/* ID not found*/
return -1;
}

/**It returns an array with the indices of the nodes connected to the node whose index is index
 It also allocates memory for the array.
 */
long* graph_getConnectionsIndex(const Graph * g, int index)
{
long *array = NULL, i, j = 0, size;

if (!g)
    return NULL;

if (index < 0 || index >g->num_nodes)
    return NULL;

/* get memory for the array*/
size = node_getNConnect (g->nodes[index]);
array = (long *) malloc(sizeof (long) * size);

if (!array) {
    /* print error message*/
    fprintf (stderr, "%s\n", strerror(errno));
    return NULL;
}

/*assign values to the array with the indices of the connected nodes*/
for(i = 0; i< g->num_nodes; i++) {
    if (g->connections[index][i] == TRUE) {
        array[j++] = i;
    }
}

return array;
}
