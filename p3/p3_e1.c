#include <stdio.h>
#include <stdlib.h>
#include "queue_fp.h"
#include "graph.h"
#include "node.h"
#include "types.h"


int main(int argc, char* argv[]){
    Node *n=NULL;
    Graph *g=NULL;
    Queue *q=NULL;
    FILE *pf=NULL;
    int i;
    int flag;
    int nodes;
    long * ids;

    if(argc != 2){
        fprintf(stderr, "ERROR EN EL FORMATO DE EJECUCION");
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

    q=queue_init(node_free, node_copy, node_print);
    if(!q){
        fprintf(stderr, "Error al iniciaizar la cola\n");
        graph_free(g);
        fclose(pf);
        return -1;
    }

    ids=graph_getNodesId(g);
    if(ids==NULL){
      fprintf(stderr, "Error al obtener los ids de los nodos\n");
      graph_free(g);
      return -1;
    }
    for(i=0;i<graph_getNumberOfNodes(g); i++){
        n=graph_getNode(g,ids[i]);
        if(n==NULL){
          fprintf(stderr, "Error al obtener el nodo del grafo\n");
          graph_free(g);
          node_free(n);
          free(ids);
          return -1;
        }
        node_setLabel(n, BLACK);
        graph_setNode(g, n);

        flag=queue_insert(q, (void *)n);
        if(flag==ERROR){
            fclose(pf);
            graph_free(g);
            queue_free(q);
            node_free(n);
            free(ids);
            return -1;
        }
        node_free(n);
    }

    fprintf(stdout, "Nodes in graph: \n");
    flag=graph_print(stdout, g);
    if(flag==-1){
        fprintf(stderr, "Error al imprimir el grafo\n");
        fclose(pf);
        graph_free(g);
        queue_free(q);
        free(ids);
        return -1;
    }
    fprintf(stdout, "\n\n");

    nodes = queue_size(q);
    fprintf(stdout, "Queue size: %d\n", nodes);
    fprintf(stdout, "Nodes in Queue: \n");

    flag=queue_print(stdout, q);
    if(flag==-1){
        fprintf(stderr, "Error al imprimir la cola\n");
        fclose(pf);
        graph_free(g);
        queue_free(q);
        free(ids);
        return -1;
    }
    fprintf(stdout, "\n\n");

    while( queue_isEmpty(q) != TRUE){
        n = queue_extract(q);
        if(n==NULL){
            fclose(pf);
            graph_free(g);
            queue_free(q);
            free(ids);
            return -1;
        }
        fprintf(stdout, "Extract Node : \n");
        flag=node_print(stdout, n);
        if(flag==-1){
            fprintf(stderr, "Error al imprimir la cola\n");
            fclose(pf);
            graph_free(g);
            queue_free(q);
            free(ids);
            return -1;
        }
        fprintf(stdout, "\n\n");

        node_free(n);
    }

    nodes = queue_size(q);
    fprintf(stdout, "Queue size: %d\n", nodes);

    graph_free(g);
    queue_free(q);
    fclose(pf);
    free(ids);

    return 0;
}
