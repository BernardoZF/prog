/**
* @file graph.h
* @author Profesores Prog2
* @date Created on 29 January 2020, 15:03
* @version 1.0
* @brief Library to manage TAD Graph
**
@see
*/

enum {NUM_ARGUMENTS = 3};


#include "graph.h"
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
    int i;

    if(!g||!n){
        return ERROR;
    }

    for(i=0;g->nodes[i]!=NULL;i++){
        if ((node_cmp(g->nodes[i], n))==0){
            return ERROR;
        }
    }

    g->nodes[i]=node_copy(n);
    if(g->nodes[i]==NULL){
        return ERROR;
    }
    g->num_nodes++;

    return OK;
}


Status graph_insertEdge (Graph *g, const long nId1, const long nId2)
{
    int indx1, indx2;

    if (!g || nId1<0 || nId1<0) return ERROR;

	indx1 = find_node_index(g, nId1);
	indx2 = find_node_index(g, nId2);

	if (indx1 == -1 || indx2 == -1){
		fprintf(stderr, "Error al buscar el indice del nodo.\n");
		return ERROR;
	}

	if (g->connections[indx1][indx2] == TRUE){
		fprintf(stderr, "Error: Ya conectados.\n");
		return ERROR;
	}

	(g->num_edges)++;
	g->connections[indx1][indx2] = TRUE;

	indx2 = node_getConnect(g->nodes[indx1]);
	if (indx2 == -1){
		fprintf(stderr, "Error al obtener el numero de conexiones del nodo\n");
		(g->num_edges)--;
		return ERROR;
	}
	if(!node_setNConnect(g->nodes[indx1], indx2+1)){
		fprintf(stderr, "Error al modificar el numero de conexiones del nodo\n");
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
    int i;

    if (!g||!n)
        return ERROR;
    for(i=0;i<MAX_NODES;i++){
        if((node_getId(n))==(node_getId(g->nodes[i]))){
            node_setLabel(g->nodes[i], node_getLabel(n));
            node_setName(g->nodes[i],node_getName((Node *)n));
            node_setNConnect(g->nodes[i],node_getConnect(n));
            return OK;
        }
    }

    return ERROR;
}


long * graph_getNodesId (const Graph *g)
{
    int i;
    long *ids;


    ids=(long *)malloc(sizeof(long)*g->num_nodes);
    if(!ids)
        return NULL;
    if(!g)
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

    if(!g||nId1<0||nId2<0)
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
  int ncon;
  int i;

    if (!g || fromId<0)
      return ERROR;

    for (i=0, ncon=0;i<g->num_nodes;i++){
      if (graph_areConnected(g, fromId, i)==TRUE){
        ncon++;
      }
    }

    return ncon;
}



long* graph_getConnectionsFrom (const Graph *g, const long fromId)
{
    int indx;
    long *ids;

    if(!g || fromId<0)
        return NULL;
    
    indx=find_node_index(g, fromId);
    if (indx<0)
        return NULL;
    ids=graph_getConnectionsIndex(g,indx);

    return ids;
}



int graph_print (FILE *pf, const Graph *g)
{

    int ret = 0;
    int i, j, a, node_id, n_id, n_connected;
    Label n_label;
    char const *n_name = NULL;
    long *conn = NULL;

    if(!pf || !g)
        return -1;

    for(i = 0; i < g->num_nodes; i++){
        n_id = node_getId(g->nodes[i]);
        n_name = node_getName(g->nodes[i]);
        n_label = node_getLabel(g->nodes[i]);
        n_connected = node_getConnect(g->nodes[i]);

        ret += fprintf(pf, "[%d, %s, %d, %d]", n_id, n_name, n_label, n_connected);

        a = find_node_index(g, node_getId(g->nodes[i]));
        conn = graph_getConnectionsIndex(g, a);
        for(j=0;j < node_getConnect(g->nodes[i]) ; j++){
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
    int i, nnodes = 0, id1, id2;
    Label n_label;
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
      printf("i<nnodes\n");
        node_free(n);
        return ERROR;
    }

    while ( fgets(buff, MAX_LINE, fin) ){
      if ( sscanf(buff, "%d %d", &id1,&id2) == NUM_ARGUMENTS )
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
size = node_getConnect (g->nodes[index]);
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
