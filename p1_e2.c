/**
* @file p1_e1.c
* @author Bernardo Zambrano && Alvaro Platon
* @date 4 Frebuary 2020
* @version 1.0
* @brief Test of TAD Node
**
@details
**
@see
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "node.h"
#include "graph.h"

int main (int argc, char** argv){
    Node * n1;
    Node * n2;
    Graph *g;
    int aux;
    
    fprintf(stdout,"\n");
    
    n1=node_init();
    if(!n1) return -1;
    
    n2=node_init();
    if(!n2) {
        node_free(n1);
        return -1;
    }
    
    if(node_setId(n1,111)==ERROR){
        fprintf(stdout,"ERROR while setting Id1\n");
        node_free(n1);
        node_free(n2);
        return -1;
    }
    
    if(node_setId(n2,222)==ERROR){
        fprintf(stdout,"ERROR while setting Id2\n");
        node_free(n1);
        node_free(n2);
        return -1;
    }
    
    if(node_setName(n1,"first")==ERROR){
        fprintf(stdout,"ERROR while setting name1\n");
        node_free(n1);
        node_free(n2);
        return -1;
    }
    
    if(node_setName(n2,"second")==ERROR){
        fprintf(stdout,"ERROR while setting name2\n");
        node_free(n1);
        node_free(n2);
        return -1;
    }
    
    if(node_setNConnect(n1,0)==ERROR){
        fprintf(stdout,"ERROR while setting connections\n");
        node_free(n1);
        node_free(n2);
        return -1;
    }
    
    if(node_setNConnect(n2,0)==ERROR){
        fprintf(stdout,"ERROR while setting connections\n");
        node_free(n1);
        node_free(n2);
        return -1;
    }

    if(node_setLabel(n1,WHITE)==ERROR){
        fprintf(stdout,"ERROR while setting labels\n");
        node_free(n1);
        node_free(n2);
        return -1;
    }
    
    if(node_setLabel(n2,WHITE)==ERROR){
        fprintf(stdout,"ERROR while setting labels\n");
        node_free(n1);
        node_free(n2);
        return -1;
    }

    g=graph_init();

    aux=graph_insertNode(g, n1);
    fprintf(stdout,"Insertando nodo 1...resultado...: %d\n", aux);
    aux=graph_insertNode(g, n2);
    fprintf(stdout,"Insertando nodo 2...resultado...: %d\n\n\n", aux);

    graph_insertEdge(g, node_getId(n2), node_getId(n1));    
    fprintf(stdout, "Insertando edge: nodo 2  ---> nodo 1\n\n\n");

    fprintf(stdout,"Conectados nodo 1 y nodo 2? ");
    if((graph_areConnected(g,node_getId(n1),node_getId(n2)))==TRUE){
        fprintf(stdout,"Si \n");
    }
    else{
        fprintf(stdout,"No\n");
    }

    fprintf(stdout,"Conectados nodo 2 y nodo 1? ");
    if((graph_areConnected(g,node_getId(n2),node_getId(n1)))==TRUE){
        fprintf(stdout,"Si \n\n\n");
    }
    else{
        fprintf(stdout,"No \n\n\n");
    }

    aux=graph_insertNode(g, n2);
    fprintf(stdout,"Insertando nodo 2...resultado...: %d\n\n\n", aux);

    graph_print(stdout, g);


    node_free(n1);
    node_free(n2);
    graph_free(g);



    return 0;
}